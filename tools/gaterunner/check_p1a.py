#!/usr/bin/env python3
"""GATE-P1 P1-A checker and study executor (reference_agreement)."""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
import sys
from collections import defaultdict
from dataclasses import dataclass
from fractions import Fraction
from typing import Any

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO_ROOT, "tools", "gaterunner"))

import gaterunner  # noqa: E402
from ref_parse import (  # noqa: E402
    TOL_S as EXACT_TOL_S,
    TOL_T as EXACT_TOL_T,
    compare_event_deltas,
)

HELDOUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "heldout")
EVENTS_DIR = os.path.join(REPO_ROOT, "tools", "gaterunner", "events")
MANIFESTS_DIR = os.path.join(REPO_ROOT, "tools", "gaterunner", "manifests")
QUASI_WINDOW = 12
EXPLORATORY_END = 25

QUASI_IDS = {
    "HO-poly-quasichaotic-1",
    "HO-poly-quasichaotic-2",
    "HO-poly-quasichaotic-3",
    "HO-poly-quasichaotic-4",
}


@dataclass
class ScenarioResult:
    scenario_id: str
    family: str
    regime: str
    tier: int
    window: int
    ref_count: int
    eng_count: int
    worst_dt: float
    worst_ds: float
    pass_primary: bool
    notes: str = ""


def load_json(path: str) -> Any:
    with open(path, encoding="utf-8") as handle:
        return json.load(handle)


def parse_family_regime(scenario_id: str, fixture: dict[str, Any]) -> tuple[str, str]:
    if "quasichaotic" in scenario_id:
        regime = "quasi-chaotic"
    elif "periodic" in scenario_id:
        regime = "periodic"
    elif "graze" in scenario_id:
        regime = "grazing"
    elif "settle" in scenario_id or "double-root" in scenario_id:
        regime = "settle/transient"
    else:
        regime = "other"
    family = fixture.get("family", "unknown")
    if scenario_id.startswith("HO-flat"):
        curve_family = "flat"
    elif scenario_id.startswith("HO-parabola") or scenario_id.startswith("HO-graze-parabola"):
        curve_family = "parabola"
    elif scenario_id.startswith("HO-poly"):
        curve_family = "deg3-6"
    elif scenario_id.startswith("HO-bezier"):
        curve_family = "bezier"
    else:
        curve_family = family
    return curve_family, regime


def confirmatory_window(scenario_id: str, ref_len: int, eng_len: int) -> int:
    base = min(200, ref_len if ref_len else eng_len, eng_len)
    if scenario_id in QUASI_IDS:
        return min(QUASI_WINDOW, base, ref_len, eng_len)
    return min(200, ref_len if ref_len else eng_len, eng_len)


def parse_event_line(line: str) -> dict[str, Any]:
    return json.loads(line)


def read_engine_events(path: str) -> list[dict[str, Any]]:
    events: list[dict[str, Any]] = []
    with open(path, encoding="utf-8") as handle:
        for lineno, line in enumerate(handle):
            line = line.strip()
            if not line:
                continue
            obj = json.loads(line)
            if lineno == 0 and obj.get("schema") == "bounce-events-v1":
                continue
            events.append(obj)
    return events


def compare_reference_agreement(
    refs: list[dict[str, Any]],
    eng: list[dict[str, Any]],
    window: int | None = None,
) -> tuple[bool, float, float]:
    """Compare reference events to engine events using exact rational tolerances."""
    if len(refs) == 0 and len(eng) == 0:
        return True, 0.0, 0.0

    if window is None:
        window = min(200, len(refs) if refs else len(eng), len(eng))

    worst_dt = Fraction(0)
    worst_ds = Fraction(0)
    ok = True
    if len(refs) < window or len(eng) < window:
        ok = False
    else:
        for i in range(window):
            ref = refs[i]
            ev = eng[i]
            if int(ref["ball_id"]) != int(ev.get("ball_id", -1)):
                ok = False
            if int(ref["seq"]) != int(ev.get("seq", -1)):
                ok = False
            dt, ds = compare_event_deltas(ref, ev)
            worst_dt = max(worst_dt, dt)
            worst_ds = max(worst_ds, ds)
            if dt > EXACT_TOL_T or ds > EXACT_TOL_S:
                ok = False
    return ok, float(worst_dt), float(worst_ds)


def compare_scenario(scenario_id: str) -> tuple[ScenarioResult, dict[str, Any] | None]:
    fixture_path = os.path.join(HELDOUT_DIR, scenario_id + ".json")
    event_path = os.path.join(EVENTS_DIR, "P1-A", scenario_id + ".jsonl")
    fixture = load_json(fixture_path)
    family, regime = parse_family_regime(scenario_id, fixture)
    tier = int(fixture.get("provenance_tier", fixture.get("provenance", {}).get("tier", 0)))
    refs = fixture.get("reference_events", [])
    eng = read_engine_events(event_path) if os.path.isfile(event_path) else []

    if scenario_id == "HO-graze-parabola-1":
        ok = len(refs) == 0 and len(eng) == 0
        return (
            ScenarioResult(
                scenario_id, family, regime, tier, 0, 0, len(eng), 0.0, 0.0, ok,
                "empty-reference grazing fixture",
            ),
            None,
        )

    window = confirmatory_window(scenario_id, len(refs), len(eng))
    ok, worst_dt, worst_ds = compare_reference_agreement(refs, eng, window)

    exploratory = None
    if scenario_id in QUASI_IDS:
        exploratory = {"scenario_id": scenario_id, "rows": []}
        for i in range(QUASI_WINDOW, min(EXPLORATORY_END, len(refs), len(eng))):
            ref = refs[i]
            ev = eng[i]
            dt, ds = compare_event_deltas(ref, ev)
            exploratory["rows"].append(
                {
                    "event": i,
                    "abs_dt": float(dt),
                    "abs_ds": float(ds),
                }
            )

    return (
        ScenarioResult(
            scenario_id, family, regime, tier, window, len(refs), len(eng),
            worst_dt, worst_ds, ok,
        ),
        exploratory,
    )


def execute_study(study_path: str, manifest_out: str) -> int:
    study = load_json(study_path)
    study_id = study["study_id"]
    gate_id = study["gate_id"]
    engine = study.get("engine", "exact")
    engine_params = study.get("engine_params")
    scenario_ids = gaterunner.resolve_scenario_ids(study)
    per_horizon = study.get("per_scenario_max_events", {})
    default_max = gaterunner.horizon_to_max_events(study["horizon"])
    timing_runs = study.get("timing_runs", 1)
    binary = (
        gaterunner.DEFAULT_BASELINE_BINARY
        if engine == "baseline"
        else gaterunner.DEFAULT_BINARY
    )

    gaterunner.validate_split_lock()
    engine_commit, dirty = gaterunner.git_head_info()
    code, tracked_status, _ = gaterunner.run_command(
        ["git", "status", "--porcelain", "--untracked-files=no"]
    )
    tracked_dirty = code == 0 and bool(tracked_status.strip())
    if tracked_dirty:
        print("gaterunner-failed: tracked working tree dirty")
        return 1

    os.makedirs(os.path.join(EVENTS_DIR, study_id), exist_ok=True)
    scenario_records: list[dict[str, Any]] = []
    heldout_ids = gaterunner.list_heldout_scenario_ids()

    for scenario_id in scenario_ids:
        max_events = int(per_horizon.get(scenario_id, default_max))
        scen_path = gaterunner.scenario_path(scenario_id)
        scenario_sha = gaterunner.sha256_file(scen_path)
        out_path = os.path.join(EVENTS_DIR, study_id, scenario_id + ".jsonl")
        wall_times: list[float] = []
        exit_code = 0
        try:
            for _ in range(timing_runs):
                exit_code, elapsed = gaterunner.run_single_scenario(
                    binary=binary,
                    scenario_id=scenario_id,
                    out_path=out_path,
                    max_events=max_events,
                    engine=engine,
                    engine_params=engine_params,
                )
                wall_times.append(elapsed)
        except RuntimeError as exc:
            print(str(exc))
            return 1
        event_sha = gaterunner.sha256_file(out_path)
        scenario_records.append(
            {
                "scenario_id": scenario_id,
                "scenario_sha256": scenario_sha,
                "event_file_sha256": event_sha,
                "event_count": gaterunner.count_events(out_path),
                "exit_code": exit_code,
                "wall_times_seconds": wall_times,
                "wall_time_median_seconds": wall_times[-1],
            }
        )
        if scenario_id in heldout_ids:
            gaterunner.append_access_log(
                scenario_id=scenario_id,
                scenario_sha256=scenario_sha,
                study_id=study_id,
                gate_id=gate_id,
                engine_commit=engine_commit,
            )

    manifest = {
        "engine": engine,
        "engine_binary_sha256": gaterunner.sha256_file(binary),
        "engine_git_commit": engine_commit,
        "engine_git_dirty": tracked_dirty,
        "toolchain": gaterunner.collect_toolchain(),
        "fp_determinism_flags": gaterunner.read_fp_flags(),
        "runner_tool_sha256": gaterunner.sha256_file(gaterunner.RUNNER_VERSION_PATH),
        "study_spec": study,
        "scenarios": scenario_records,
    }
    gaterunner.write_json(manifest_out, manifest)
    print(f"gate-exec-ok study={study_id} manifest={manifest_out}")
    return 0


def family_counts(results: list[ScenarioResult]) -> dict[str, int]:
    counts: dict[str, int] = defaultdict(int)
    for row in results:
        counts[row.family] += 1
    return counts


def largest_family(families: dict[str, int]) -> str:
    return max(families, key=lambda k: families[k])


def print_report(manifest_path: str) -> int:
    manifest = load_json(manifest_path)
    if manifest.get("engine_git_dirty"):
        print("CHECK-FAILED: manifest engine_git_dirty=true")
        return 1

    results: list[ScenarioResult] = []
    exploratory_rows: list[dict[str, Any]] = []
    for entry in manifest["scenarios"]:
        row, exploratory = compare_scenario(entry["scenario_id"])
        results.append(row)
        if exploratory:
            exploratory_rows.append(exploratory)

    print("P1-A per-scenario worst errors (confirmatory window):")
    print(f"{'scenario_id':<28} {'window':>6} {'worst_|dt|':>14} {'worst_|ds|':>14} {'verdict':>8}")
    corpus_pass = True
    for row in sorted(results, key=lambda r: r.scenario_id):
        verdict = "PASS" if row.pass_primary else "FAIL"
        if not row.pass_primary:
            corpus_pass = False
        print(
            f"{row.scenario_id:<28} {row.window:>6} {row.worst_dt:>14.6e} "
            f"{row.worst_ds:>14.6e} {verdict:>8} {row.notes}"
        )

    print("\nPer-family distribution (worst |dt|):")
    by_family: dict[str, list[float]] = defaultdict(list)
    by_regime: dict[str, list[float]] = defaultdict(list)
    for row in results:
        by_family[row.family].append(row.worst_dt)
        by_regime[row.regime].append(row.worst_dt)
    for key in sorted(by_family):
        vals = by_family[key]
        print(f"  {key}: n={len(vals)} max={max(vals):.6e} median={sorted(vals)[len(vals)//2]:.6e}")
    print("\nPer-regime distribution (worst |dt|):")
    for key in sorted(by_regime):
        vals = by_regime[key]
        print(f"  {key}: n={len(vals)} max={max(vals):.6e} median={sorted(vals)[len(vals)//2]:.6e}")

    print("\nQuasi-chaotic exploratory events 13–25 (|dt|, |ds|):")
    for block in exploratory_rows:
        print(f"  {block['scenario_id']}:")
        for item in block["rows"]:
            print(
                f"    event {item['event']:>2}: |dt|={item['abs_dt']:.6e} |ds|={item['abs_ds']:.6e}"
            )

    families = family_counts(results)
    dom = largest_family(families)
    print(f"\nRed team — leave-one-family-out (exclude {dom}):")
    rt_results = [r for r in results if r.family != dom]
    rt_pass = all(r.pass_primary for r in rt_results)
    print(f"  scenarios={len(rt_results)} verdict={'PASS' if rt_pass else 'FAIL'}")

    print("\nRed team — Tier-1 fixtures only:")
    t1_results = [r for r in results if r.tier == 1]
    t1_pass = all(r.pass_primary for r in t1_results)
    print(f"  scenarios={len(t1_results)} verdict={'PASS' if t1_pass else 'FAIL'}")

    worst_dt = max((r.worst_dt for r in results), default=0.0)
    worst_ds = max((r.worst_ds for r in results), default=0.0)
    print(f"\nP1-A CORPUS VERDICT: {'PASS' if corpus_pass else 'FAIL'}")
    print(f"  corpus worst |dt|={worst_dt:.6e}  corpus worst |ds|={worst_ds:.6e}")
    return 0 if corpus_pass else 1


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--execute", action="store_true")
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--study", default=os.path.join(REPO_ROOT, "tools", "gaterunner", "studies", "P1-A.json"))
    parser.add_argument(
        "--manifest",
        default=os.path.join(MANIFESTS_DIR, "P1-A.json"),
    )
    args = parser.parse_args()
    if args.execute:
        return execute_study(args.study, args.manifest)
    if args.check:
        return print_report(args.manifest)
    parser.error("specify --execute and/or --check")
    return 1


if __name__ == "__main__":
    sys.exit(main())

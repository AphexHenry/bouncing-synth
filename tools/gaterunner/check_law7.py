#!/usr/bin/env python3
"""GATE-P1 Law 7 checker (matched-compute comparison)."""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import sys
from fractions import Fraction

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO_ROOT, "tools", "gaterunner"))

from check_p1a import execute_study, parse_family_regime, read_engine_events  # noqa: E402
from check_p1c import interval_vector, period_event_count  # noqa: E402
from ref_parse import compare_event_deltas  # noqa: E402

MANIFESTS_DIR = os.path.join(REPO_ROOT, "tools", "gaterunner", "manifests")
EVENTS_EXACT = os.path.join(REPO_ROOT, "tools", "gaterunner", "events", "LAW7-EXACT")
EVENTS_BASE = os.path.join(REPO_ROOT, "tools", "gaterunner", "events", "LAW7-BASELINE")
EVENTS_P1C = os.path.join(REPO_ROOT, "tools", "gaterunner", "events", "P1-C")
HELDOUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "heldout")
TUNE_PATH = os.path.join(REPO_ROOT, "tools", "gaterunner", "tune", "TUNE-LAW7.json")
MARGIN = 100.0

PERIODIC = [
    "HO-flat-periodic-1",
    "HO-flat-periodic-2",
    "HO-flat-periodic-3",
    "HO-parabola-periodic-1",
    "HO-parabola-periodic-2",
    "HO-poly-periodic-1",
    "HO-poly-periodic-2",
    "HO-bezier-periodic-1",
    "HO-bezier-periodic-2",
]


def load_json(path: str):
    with open(path, encoding="utf-8") as handle:
        return json.load(handle)


def exact_count_from_p1a(scenario_id: str) -> int:
    path = os.path.join(REPO_ROOT, "tools", "gaterunner", "events", "P1-A", scenario_id + ".jsonl")
    return len(read_engine_events(path))


def worst_abs_dt(events: list[dict], refs: list[dict], k: int) -> float:
    n = min(k, len(events), len(refs))
    worst = Fraction(0)
    for i in range(n):
        dt, _ = compare_event_deltas(refs[i], events[i])
        worst = max(worst, dt)
    return float(worst)


def first_drift_period(path: str, period_events: int) -> int:
    times = [float(ev["t"]) for ev in read_engine_events(path)]
    if len(times) < period_events * 2:
        return -1
    period1 = interval_vector(times, period_events, 0)
    periods = len(times) // period_events
    for period in range(1, periods):
        if interval_vector(times, period_events, period) != period1:
            return period
    return -1


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--execute", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    if args.execute:
        for study_name in ("LAW7-EXACT", "LAW7-BASELINE"):
            study = os.path.join(REPO_ROOT, "tools", "gaterunner", "studies", study_name + ".json")
            manifest = os.path.join(MANIFESTS_DIR, study_name + ".json")
            if execute_study(study, manifest) != 0:
                return 1

    manifest_exact = load_json(os.path.join(MANIFESTS_DIR, "LAW7-EXACT.json"))
    manifest_base = load_json(os.path.join(MANIFESTS_DIR, "LAW7-BASELINE.json"))
    if manifest_exact.get("engine_git_dirty") or manifest_base.get("engine_git_dirty"):
        print("CHECK-FAILED: manifest engine_git_dirty=true")
        return 1

    tune = load_json(TUNE_PATH)
    tune_sha = hashlib.sha256(open(TUNE_PATH, "rb").read()).hexdigest()
    print(f"TUNE-LAW7.json sha256={tune_sha}")
    print(
        f"frozen tune dt={tune['chosen']['dt']} segments={tune['chosen']['segments']} "
        f"mean_ratio={tune['chosen']['mean_ratio_vs_exact']}"
    )

    rows = []
    shortfalls = []
    for entry in manifest_exact["scenarios"]:
        sid = entry["scenario_id"]
        fixture = load_json(os.path.join(HELDOUT_DIR, sid + ".json"))
        refs = fixture["reference_events"]
        k = min(200, exact_count_from_p1a(sid))
        exact_events = read_engine_events(os.path.join(EVENTS_EXACT, sid + ".jsonl"))
        base_events = read_engine_events(os.path.join(EVENTS_BASE, sid + ".jsonl"))
        exact_worst = worst_abs_dt(exact_events, refs, k)
        shortfall = len(base_events) < k
        if shortfall:
            base_worst = float("inf")
            shortfalls.append(
                {
                    "scenario_id": sid,
                    "k": k,
                    "baseline_events": len(base_events),
                    "classification": "physics shortfall (baseline < K events)",
                }
            )
        else:
            base_worst = worst_abs_dt(base_events, refs, k)
        family, regime = parse_family_regime(sid, fixture)
        rows.append(
            {
                "scenario_id": sid,
                "family": family,
                "regime": regime,
                "k": k,
                "exact_worst": exact_worst,
                "baseline_worst": base_worst,
                "shortfall": shortfall,
            }
        )

    print("\nLaw 7 per-scenario accuracy (K events):")
    print(f"{'scenario_id':<28} {'K':>4} {'exact_|dt|':>14} {'base_|dt|':>14} {'shortfall':>10}")
    for row in rows:
        base_display = "SHORTFALL" if row["shortfall"] else f"{row['baseline_worst']:.6e}"
        print(
            f"{row['scenario_id']:<28} {row['k']:>4} {row['exact_worst']:>14.6e} "
            f"{base_display:>14} {str(row['shortfall']):>10}"
        )

    if shortfalls:
        print("\nShortfall list:")
        for item in shortfalls:
            print(
                f"  {item['scenario_id']}: K={item['k']} baseline_events={item['baseline_events']} "
                f"class={item['classification']}"
            )

    finite = [r for r in rows if not r["shortfall"] and r["baseline_worst"] > 0]
    ratio_explore = (
        sum(r["exact_worst"] / r["baseline_worst"] for r in finite) / len(finite)
        if finite
        else float("nan")
    )
    print(f"\nExploratory finite-scenarios mean exact/baseline ratio: {ratio_explore:.6f}")

    print("\nPer family × regime (worst exact |dt|):")
    buckets: dict[tuple[str, str], float] = {}
    for row in rows:
        key = (row["family"], row["regime"])
        buckets[key] = max(buckets.get(key, 0.0), row["exact_worst"])
    for key in sorted(buckets):
        print(f"  {key[0]} / {key[1]}: {buckets[key]:.6e}")

    worst_exact = max(r["exact_worst"] for r in rows)
    if shortfalls:
        worst_base = float("inf")
    else:
        worst_base = max(r["baseline_worst"] for r in rows if not r["shortfall"])
    arm1 = worst_exact <= (worst_base / MARGIN)
    print(
        f"\nPrimary arm 1 (100× margin): worst_exact={worst_exact:.6e} "
        f"worst_baseline={worst_base} threshold="
        f"{(worst_base / MARGIN) if worst_base != float('inf') else float('inf'):.6e} "
        f"{'PASS' if arm1 else 'FAIL'}"
    )

    print("\nPeriodic drift table (P1-C method):")
    print(f"{'scenario_id':<28} {'exact_drift':>12} {'baseline_drift':>14}")
    drift_ok = True
    for sid in PERIODIC:
        pe = period_event_count(sid)
        exact_path = os.path.join(EVENTS_P1C, sid + ".jsonl")
        base_path = os.path.join(EVENTS_BASE, sid + ".jsonl")
        exact_div = first_drift_period(exact_path, pe)
        base_div = first_drift_period(base_path, pe)
        exact_drift = 0 if exact_div < 0 else exact_div
        base_drift = 0 if base_div < 0 else base_div
        if base_drift > 0 and exact_drift != 0:
            drift_ok = False
        print(
            f"{sid:<28} {exact_drift:>12} {base_drift:>14} "
            f"{'ok' if not (base_drift > 0 and exact_drift != 0) else 'FAIL':>8}"
        )

    arm2 = drift_ok
    print(f"\nPrimary arm 2 (drift): {'PASS' if arm2 else 'FAIL'}")
    verdict = arm1 and arm2
    print(f"\nLAW 7 VERDICT: {'PASS' if verdict else 'FAIL'}")
    return 0 if verdict else 1


if __name__ == "__main__":
    sys.exit(main())

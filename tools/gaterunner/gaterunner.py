#!/usr/bin/env python3
"""I-004 gate runner — study orchestrator, manifest writer, held-out access discipline."""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import subprocess
import sys
import tempfile
import time
from datetime import datetime, timezone
from statistics import median
from typing import Any

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
SCENARIOS_ROOT = os.path.join(REPO_ROOT, "data", "scenarios")
CALIBRATION_DIR = os.path.join(SCENARIOS_ROOT, "calibration")
HELDOUT_DIR = os.path.join(SCENARIOS_ROOT, "heldout")
SPLIT_LOCK_PATH = os.path.join(SCENARIOS_ROOT, "split-lock.json")
HELDOUT_MANIFEST_PATH = os.path.join(HELDOUT_DIR, "MANIFEST.json")
ACCESS_LOG_PATH = os.path.join(HELDOUT_DIR, "ACCESS_LOG.jsonl")
FP_DETERMINISM_PATH = os.path.join(REPO_ROOT, "config", "fp-determinism.cmake")
DEFAULT_BINARY = os.path.join(REPO_ROOT, "build", "default", "bounce-run-scenario")
DEFAULT_BASELINE_BINARY = os.path.join(REPO_ROOT, "build", "default", "bounce-baseline-run")
K_MAX_SIM_EVENTS = 256
RUNNER_VERSION_PATH = os.path.join(REPO_ROOT, "tools", "gaterunner", "gaterunner.py")


def sha256_file(path: str) -> str:
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for chunk in iter(lambda: handle.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def load_json(path: str) -> Any:
    with open(path, encoding="utf-8") as handle:
        return json.load(handle)


def write_json(path: str, payload: Any) -> None:
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", newline="\n", encoding="utf-8") as handle:
        json.dump(payload, handle, indent=2, sort_keys=True)
        handle.write("\n")


def run_command(cmd: list[str], *, cwd: str | None = None) -> tuple[int, str, str]:
    proc = subprocess.run(
        cmd,
        cwd=cwd or REPO_ROOT,
        capture_output=True,
        text=True,
        check=False,
    )
    return proc.returncode, proc.stdout, proc.stderr


def git_head_info() -> tuple[str, bool]:
    code, out, _ = run_command(["git", "rev-parse", "HEAD"])
    if code != 0:
        raise RuntimeError("failed to read git HEAD")
    commit = out.strip()
    code, status, _ = run_command(["git", "status", "--porcelain"])
    dirty = code == 0 and bool(status.strip())
    return commit, dirty


def read_fp_flags() -> list[str]:
    with open(FP_DETERMINISM_PATH, encoding="utf-8") as handle:
        text = handle.read()
    flags: list[str] = []
    for line in text.splitlines():
        stripped = line.strip()
        if stripped.startswith("-ffp-contract=off"):
            flags.append("-ffp-contract=off")
        if stripped.startswith("-fno-fast-math"):
            flags.append("-fno-fast-math")
    if flags != ["-ffp-contract=off", "-fno-fast-math"]:
        raise ValueError("unexpected fp-determinism.cmake flags")
    return flags


def list_calibration_scenarios() -> list[str]:
    return sorted(
        name[:-5]
        for name in os.listdir(CALIBRATION_DIR)
        if name.endswith(".json")
    )


def list_heldout_scenario_ids() -> set[str]:
    return {
        name[:-5]
        for name in os.listdir(HELDOUT_DIR)
        if name.endswith(".json") and name != "MANIFEST.json"
    }


def validate_split_lock() -> tuple[int, int]:
    if not os.path.isfile(SPLIT_LOCK_PATH):
        raise FileNotFoundError(f"missing split-lock marker: {SPLIT_LOCK_PATH}")
    if not os.path.isfile(HELDOUT_MANIFEST_PATH):
        raise FileNotFoundError(f"missing heldout manifest: {HELDOUT_MANIFEST_PATH}")
    manifest_hash = sha256_file(HELDOUT_MANIFEST_PATH)
    lock = load_json(SPLIT_LOCK_PATH)
    if lock.get("schema_version") != "1":
        raise ValueError("split-lock schema_version must be '1'")
    if lock.get("split_locked") is not True:
        raise ValueError("split_locked must be true")
    if lock.get("heldout_manifest_sha256") != manifest_hash:
        raise ValueError("heldout_manifest_sha256 mismatch")
    calibration_names = list_calibration_scenarios()
    if lock.get("calibration_count") != len(calibration_names):
        raise ValueError("calibration_count mismatch")
    manifest = load_json(HELDOUT_MANIFEST_PATH)
    if manifest.get("locked") is not True:
        raise ValueError("heldout manifest locked must be true")
    scenarios = manifest.get("scenarios")
    if not isinstance(scenarios, list):
        raise ValueError("heldout manifest scenarios must be a list")
    heldout_ids = list_heldout_scenario_ids()
    if lock.get("heldout_count") != len(scenarios):
        raise ValueError("heldout_count mismatch")
    if len(heldout_ids) != len(scenarios):
        raise ValueError("heldout file count mismatch")
    manifest_ids = {entry["scenario_id"] for entry in scenarios}
    if manifest_ids != heldout_ids:
        raise ValueError("manifest scenario ids mismatch heldout files")
    for entry in scenarios:
        sid = entry["scenario_id"]
        path = os.path.join(HELDOUT_DIR, sid + ".json")
        if sha256_file(path) != entry["sha256"]:
            raise ValueError(f"sha256 mismatch for {sid}")
    return len(calibration_names), len(scenarios)


def scenario_path(scenario_id: str) -> str:
    if scenario_id in list_heldout_scenario_ids():
        return os.path.join(HELDOUT_DIR, scenario_id + ".json")
    cal_path = os.path.join(CALIBRATION_DIR, scenario_id + ".json")
    if os.path.isfile(cal_path):
        return cal_path
    raise FileNotFoundError(f"unknown scenario id: {scenario_id}")


def resolve_scenario_ids(study: dict[str, Any]) -> list[str]:
    scenario_set = study["scenario_set"]
    if scenario_set == "calibration":
        return list_calibration_scenarios()
    if isinstance(scenario_set, list):
        if not scenario_set:
            raise ValueError("scenario_set list must not be empty")
        return list(scenario_set)
    raise ValueError("scenario_set must be 'calibration' or a list of ids")


def horizon_to_max_events(horizon: Any) -> int:
    if horizon == "to_settle":
        return K_MAX_SIM_EVENTS
    if isinstance(horizon, int):
        if horizon <= 0:
            raise ValueError("horizon max_events must be positive")
        return horizon
    raise ValueError("horizon must be an integer or 'to_settle'")


def append_access_log(
    *,
    scenario_id: str,
    scenario_sha256: str,
    study_id: str,
    gate_id: str,
    engine_commit: str,
) -> None:
    entry = {
        "scenario_id": scenario_id,
        "sha256": scenario_sha256,
        "study_id": study_id,
        "gate_id": gate_id,
        "engine_commit": engine_commit,
        "timestamp": datetime.now(timezone.utc).isoformat(),
    }
    os.makedirs(HELDOUT_DIR, exist_ok=True)
    with open(ACCESS_LOG_PATH, "a", encoding="utf-8", newline="\n") as handle:
        handle.write(json.dumps(entry, sort_keys=True) + "\n")


def count_events(path: str) -> int:
    count = 0
    with open(path, encoding="utf-8") as handle:
        for line in handle:
            if line.strip():
                count += 1
    return max(0, count - 1)


def run_single_scenario(
    *,
    binary: str,
    scenario_id: str,
    out_path: str,
    max_events: int,
    engine: str,
    engine_params: dict[str, Any] | None,
) -> tuple[int, float]:
    scen_path = scenario_path(scenario_id)
    cmd = [
        binary,
        "--scenario",
        scen_path,
        "--out",
        out_path,
        "--max-events",
        str(max_events),
    ]
    if engine == "baseline":
        if engine_params is None:
            raise RuntimeError("baseline engine requires engine_params")
        cmd.extend(
            [
                "--dt",
                str(engine_params["dt"]),
                "--segments",
                str(engine_params["segments"]),
            ]
        )
    start = time.perf_counter()
    code, _, stderr = run_command(cmd)
    elapsed = time.perf_counter() - start
    if code != 0:
        msg = stderr.strip() or f"engine failed for {scenario_id}"
        raise RuntimeError(msg)
    return code, elapsed


def identity_scenario_record(record: dict[str, Any]) -> dict[str, Any]:
    return {
        "scenario_id": record["scenario_id"],
        "scenario_sha256": record["scenario_sha256"],
        "event_file_sha256": record["event_file_sha256"],
        "event_count": record["event_count"],
        "exit_code": record["exit_code"],
    }


def normalized_study_spec(study: dict[str, Any]) -> dict[str, Any]:
    keys = ("study_id", "gate_id", "horizon", "scenario_set", "timing_runs")
    return {key: study[key] for key in keys if key in study}


def engine_identity(manifest: dict[str, Any]) -> dict[str, Any]:
    study = manifest.get("study_spec", {})
    identity: dict[str, Any] = {
        "engine": study.get("engine", "exact"),
        "engine_binary_sha256": manifest.get("engine_binary_sha256"),
        "engine_params": study.get("engine_params"),
    }
    return identity


def compare_manifests(path_a: str, path_b: str, *, cross_engine: bool = False) -> int:
    manifest_a = load_json(path_a)
    manifest_b = load_json(path_b)
    if normalized_study_spec(manifest_a.get("study_spec", {})) != normalized_study_spec(
        manifest_b.get("study_spec", {})
    ):
        print("compare-failed: study_spec differs")
        return 1
    id_a = engine_identity(manifest_a)
    id_b = engine_identity(manifest_b)
    if id_a != id_b and not cross_engine:
        print("compare-failed: engine identity differs")
        return 1
    scenarios_a = {
        row["scenario_id"]: identity_scenario_record(row)
        for row in manifest_a.get("scenarios", [])
    }
    scenarios_b = {
        row["scenario_id"]: identity_scenario_record(row)
        for row in manifest_b.get("scenarios", [])
    }
    if set(scenarios_a) != set(scenarios_b):
        print("compare-failed: scenario id sets differ")
        return 1
    if cross_engine and id_a != id_b:
        print("cross-engine-summary:")
        for sid in sorted(scenarios_a):
            count_a = scenarios_a[sid]["event_count"]
            count_b = scenarios_b[sid]["event_count"]
            print(f"  {sid}: event_count exact={count_a} baseline={count_b}")
            if scenarios_a[sid]["event_file_sha256"] == scenarios_b[sid]["event_file_sha256"]:
                print(f"  {sid}: first-divergence=none (byte-identical)")
            else:
                print(f"  {sid}: first-divergence=event_file_sha256")
        return 0
    ok = True
    for sid in sorted(scenarios_a):
        if scenarios_a[sid] != scenarios_b[sid]:
            print(f"compare-failed: identity mismatch for {sid}")
            print(f"  A: {scenarios_a[sid]}")
            print(f"  B: {scenarios_b[sid]}")
            ok = False
        elif (
            scenarios_a[sid]["event_file_sha256"]
            != scenarios_b[sid]["event_file_sha256"]
        ):
            print(f"compare-failed: event file sha256 mismatch for {sid}")
            ok = False
        else:
            print(
                f"compare-ok: {sid} event_file_sha256="
                f"{scenarios_a[sid]['event_file_sha256']}"
            )
    if not ok:
        return 1
    print("compare-ok: all calibration scenarios byte-identical across manifests")
    return 0


def collect_toolchain() -> dict[str, str]:
    cmake_code, cmake_out, _ = run_command(["cmake", "--version"])
    if cmake_code != 0:
        raise RuntimeError("cmake --version failed")
    compiler = os.environ.get("CXX", "c++")
    compiler_code, compiler_out, _ = run_command([compiler, "--version"])
    if compiler_code != 0:
        raise RuntimeError(f"{compiler} --version failed")
    python_code, python_out, _ = run_command([sys.executable, "--version"])
    if python_code != 0:
        raise RuntimeError("python --version failed")
    return {
        "cmake": cmake_out.splitlines()[0],
        "compiler": compiler_out.splitlines()[0],
        "python": python_out.strip(),
    }


def run_study(
    study_path: str,
    *,
    manifest_out: str,
    binary: str | None = None,
    baseline_binary: str = DEFAULT_BASELINE_BINARY,
) -> int:
    study = load_json(study_path)
    engine = study.get("engine", "exact")
    if engine not in ("exact", "baseline"):
        print(f"gaterunner-failed: unknown engine {engine!r}")
        return 1
    engine_params = study.get("engine_params")
    if engine == "baseline":
        if not isinstance(engine_params, dict):
            print("gaterunner-failed: baseline engine requires engine_params")
            return 1
        for key in ("dt", "segments"):
            if key not in engine_params:
                print(f"gaterunner-failed: engine_params missing {key}")
                return 1
    chosen_binary = binary or (
        baseline_binary if engine == "baseline" else DEFAULT_BINARY
    )
    if not os.path.isfile(chosen_binary):
        print(f"gaterunner-failed: missing binary {chosen_binary}")
        return 1
    required = ("study_id", "gate_id", "scenario_set", "horizon", "timing_runs")
    missing = [key for key in required if key not in study]
    if missing:
        print(f"gaterunner-failed: study spec missing fields: {missing}")
        return 1
    timing_runs = study.get("timing_runs", 10)
    if not isinstance(timing_runs, int) or timing_runs <= 0:
        print("gaterunner-failed: timing_runs must be a positive integer")
        return 1

    try:
        validate_split_lock()
        scenario_ids = resolve_scenario_ids(study)
        max_events = horizon_to_max_events(study["horizon"])
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"gaterunner-failed: {exc}")
        return 1

    heldout_ids = list_heldout_scenario_ids()
    requested_heldout = [sid for sid in scenario_ids if sid in heldout_ids]
    gate_id = study["gate_id"]
    if requested_heldout and gate_id is None:
        print("heldout-access-denied: gate_id required for held-out scenarios")
        return 1

    engine_commit, dirty = git_head_info()
    fp_flags = read_fp_flags()
    toolchain = collect_toolchain()
    runner_sha256 = sha256_file(RUNNER_VERSION_PATH)
    engine_binary_sha256 = sha256_file(chosen_binary)

    scenario_records: list[dict[str, Any]] = []
    with tempfile.TemporaryDirectory(prefix="gaterunner-") as tmpdir:
        for scenario_id in scenario_ids:
            scen_path = scenario_path(scenario_id)
            scenario_sha = sha256_file(scen_path)
            wall_times: list[float] = []
            last_out = os.path.join(tmpdir, scenario_id + ".jsonl")
            exit_code = 0
            try:
                for _ in range(timing_runs):
                    out_path = os.path.join(tmpdir, f"{scenario_id}.jsonl")
                    exit_code, elapsed = run_single_scenario(
                        binary=chosen_binary,
                        scenario_id=scenario_id,
                        out_path=out_path,
                        max_events=max_events,
                        engine=engine,
                        engine_params=engine_params,
                    )
                    wall_times.append(elapsed)
                    last_out = out_path
            except RuntimeError as exc:
                print(str(exc))
                return 1

            event_sha = sha256_file(last_out)
            scenario_records.append(
                {
                    "scenario_id": scenario_id,
                    "scenario_sha256": scenario_sha,
                    "event_file_sha256": event_sha,
                    "event_count": count_events(last_out),
                    "exit_code": exit_code,
                    "wall_times_seconds": wall_times,
                    "wall_time_median_seconds": median(wall_times),
                }
            )
            if scenario_id in heldout_ids:
                append_access_log(
                    scenario_id=scenario_id,
                    scenario_sha256=scenario_sha,
                    study_id=study["study_id"],
                    gate_id=gate_id,
                    engine_commit=engine_commit,
                )

    manifest = {
        "engine": engine,
        "engine_binary_sha256": engine_binary_sha256,
        "engine_git_commit": engine_commit,
        "engine_git_dirty": dirty,
        "toolchain": toolchain,
        "fp_determinism_flags": fp_flags,
        "runner_tool_sha256": runner_sha256,
        "study_spec": study,
        "scenarios": scenario_records,
    }
    write_json(manifest_out, manifest)
    print(f"gaterunner-ok study={study['study_id']} manifest={manifest_out}")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description="I-004 gate runner")
    parser.add_argument(
        "study",
        nargs="?",
        help="path to study spec JSON",
    )
    parser.add_argument(
        "--out",
        dest="manifest_out",
        help="manifest output path (default: tools/gaterunner/manifests/<study_id>.json)",
    )
    parser.add_argument(
        "--binary",
        default=None,
        help="path to engine binary (default: exact or baseline per study spec)",
    )
    parser.add_argument(
        "--baseline-binary",
        default=DEFAULT_BASELINE_BINARY,
        help="path to bounce-baseline-run binary",
    )
    parser.add_argument(
        "--compare",
        nargs=2,
        metavar=("MANIFEST_A", "MANIFEST_B"),
        help="compare identity-bearing fields across two manifests",
    )
    parser.add_argument(
        "--cross-engine",
        action="store_true",
        help="with --compare, summarize cross-engine differences instead of refusing",
    )
    args = parser.parse_args()

    if args.compare:
        return compare_manifests(
            args.compare[0], args.compare[1], cross_engine=args.cross_engine
        )

    if args.study is None:
        parser.error("study spec path required unless --compare is used")

    study = load_json(args.study)
    manifest_out = args.manifest_out
    if manifest_out is None:
        manifest_out = os.path.join(
            REPO_ROOT,
            "tools",
            "gaterunner",
            "manifests",
            study["study_id"] + ".json",
        )
    return run_study(
        args.study,
        manifest_out=manifest_out,
        binary=args.binary,
        baseline_binary=args.baseline_binary,
    )


if __name__ == "__main__":
    sys.exit(main())

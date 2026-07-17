#!/usr/bin/env python3
"""C-001-T12 Law 7 compute-match tune — calibration only (FL-1, PB-1)."""
from __future__ import annotations

import hashlib
import json
import os
import subprocess
import sys
import tempfile
import time
from datetime import datetime, timezone
from statistics import median

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
CALIBRATION_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "calibration")
EXACT_BINARY = os.path.join(REPO_ROOT, "build", "default", "bounce-run-scenario")
BASELINE_BINARY = os.path.join(REPO_ROOT, "build", "default", "bounce-baseline-run")
TUNE_OUT = os.path.join(os.path.dirname(__file__), "tune", "TUNE-LAW7.json")

DT_GRID = [1e-3, 5e-4, 2e-4, 1e-4, 5e-5, 2e-5, 1e-5]
N_GRID = [64, 128, 256, 512, 1024]
TIMING_RUNS = 10

NATURAL_HORIZON = {
    "FL-1-h5-g10-e1o2": 13,
    "PB-1-h9-g16-c1": 2,
}

TIER1_FIRST_CONTACT = {
    "FL-1-h5-g10-e1o2": 1.0,
    "PB-1-h9-g16-c1": 1.0,
}


def sha256_file(path: str) -> str:
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for chunk in iter(lambda: handle.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


def run_cmd(cmd: list[str]) -> tuple[int, str, str]:
    proc = subprocess.run(cmd, cwd=REPO_ROOT, capture_output=True, text=True, check=False)
    return proc.returncode, proc.stdout, proc.stderr


def git_head() -> tuple[str, bool]:
    code, out, _ = run_cmd(["git", "rev-parse", "HEAD"])
    if code != 0:
        raise RuntimeError("git rev-parse failed")
    code, status, _ = run_cmd(["git", "status", "--porcelain", "--untracked-files=no"])
    dirty = code == 0 and bool(status.strip())
    return out.strip(), dirty


def scenario_path(scenario_id: str) -> str:
    return os.path.join(CALIBRATION_DIR, scenario_id + ".json")


def parse_hex_field(line: str, key: str) -> float:
    needle = f'"{key}":"'
    pos = line.find(needle)
    if pos == -1:
        raise ValueError(f"missing {key}")
    start = pos + len(needle)
    end = line.find('"', start)
    hex_text = line[start:end]
    if not hex_text.startswith("0x"):
        hex_text = "0x" + hex_text.lstrip("+-")
    return float.fromhex(hex_text)


def last_event_time(event_path: str) -> float:
    last_t = 0.0
    with open(event_path, encoding="utf-8") as handle:
        first = True
        for line in handle:
            if first:
                first = False
                continue
            if line.strip():
                last_t = parse_hex_field(line, "t_hex")
    if last_t <= 0.0:
        raise RuntimeError(f"could not determine simulated seconds from {event_path}")
    return last_t


def first_contact_dt(event_path: str, ref_t: float) -> float:
    with open(event_path, encoding="utf-8") as handle:
        first = True
        for line in handle:
            if first:
                first = False
                continue
            if line.strip():
                return abs(parse_hex_field(line, "t_hex") - ref_t)
    raise RuntimeError("no events in file")


def run_engine(
    *,
    engine: str,
    scenario_id: str,
    max_events: int,
    dt: float | None = None,
    segments: int | None = None,
    out_path: str,
) -> tuple[float, int]:
    scen = scenario_path(scenario_id)
    if engine == "exact":
        cmd = [EXACT_BINARY, "--scenario", scen, "--out", out_path, "--max-events", str(max_events)]
    else:
        cmd = [
            BASELINE_BINARY,
            "--scenario",
            scen,
            "--out",
            out_path,
            "--dt",
            repr(dt),
            "--segments",
            str(segments),
            "--max-events",
            str(max_events),
        ]
    start = time.perf_counter()
    code, _, stderr = run_cmd(cmd)
    elapsed = time.perf_counter() - start
    if code != 0:
        raise RuntimeError(stderr.strip() or f"{engine} failed for {scenario_id}")
    with open(out_path, encoding="utf-8") as handle:
        header = handle.readline()
    key = '"engine_events":'
    pos = header.find(key)
    count = int(header[pos + len(key) : header.find("}", pos)])
    return elapsed, count


def median_rate(scenario_id: str, engine: str, max_events: int, dt=None, segments=None) -> dict:
    rates: list[float] = []
    wall_times: list[float] = []
    last_count = 0
    sim_seconds = 0.0
    with tempfile.TemporaryDirectory(prefix="tune-") as tmp:
        for i in range(TIMING_RUNS):
            out = os.path.join(tmp, f"{scenario_id}-{engine}-{i}.jsonl")
            wall, count = run_engine(
                engine=engine,
                scenario_id=scenario_id,
                max_events=max_events,
                dt=dt,
                segments=segments,
                out_path=out,
            )
            sim_seconds = last_event_time(out)
            rates.append(wall / sim_seconds)
            wall_times.append(wall)
            last_count = count
    return {
        "median_wall_seconds": median(wall_times),
        "median_rate_wall_per_sim_second": median(rates),
        "simulated_seconds": sim_seconds,
        "event_count": last_count,
        "wall_times_seconds": wall_times,
    }


def main() -> int:
    commit, dirty = git_head()
    if dirty:
        print("tune-blocked: git tree dirty", file=sys.stderr)
        return 1

    exact_sha = sha256_file(EXACT_BINARY)
    baseline_sha = sha256_file(BASELINE_BINARY)

    exact_timing: dict[str, dict] = {}
    for sid, horizon in NATURAL_HORIZON.items():
        exact_timing[sid] = median_rate(sid, "exact", horizon)

    grid_rows: list[dict] = []
    for dt in DT_GRID:
        for n in N_GRID:
            row: dict = {"dt": dt, "segments": n, "per_scenario": {}, "feasible": True}
            ratio_sum = 0.0
            fl1_dt = None
            try:
                for sid, horizon in NATURAL_HORIZON.items():
                    timing = median_rate(sid, "baseline", horizon, dt=dt, segments=n)
                    ratio = timing["median_rate_wall_per_sim_second"] / exact_timing[sid][
                        "median_rate_wall_per_sim_second"
                    ]
                    timing["ratio_vs_exact"] = ratio
                    row["per_scenario"][sid] = timing
                    ratio_sum += ratio
                    if sid == "FL-1-h5-g10-e1o2":
                        with tempfile.TemporaryDirectory(prefix="fl1-") as tmp:
                            out = os.path.join(tmp, "fl1.jsonl")
                            run_engine(
                                engine="baseline",
                                scenario_id=sid,
                                max_events=horizon,
                                dt=dt,
                                segments=n,
                                out_path=out,
                            )
                            fl1_dt = first_contact_dt(out, TIER1_FIRST_CONTACT[sid])
                row["mean_ratio_vs_exact"] = ratio_sum / len(NATURAL_HORIZON)
                row["fl1_first_contact_abs_dt"] = fl1_dt
            except RuntimeError as exc:
                row["feasible"] = False
                row["error"] = str(exc)
            grid_rows.append(row)

    feasible = [r for r in grid_rows if r.get("feasible")]
    in_window = [r for r in feasible if 1.0 <= r["mean_ratio_vs_exact"] <= 2.0]
    if not in_window:
        print("tune-blocked: no configuration in [1.0, 2.0] window", file=sys.stderr)
        print(json.dumps(grid_rows, indent=2))
        return 1

    chosen = sorted(
        in_window,
        key=lambda r: (r["fl1_first_contact_abs_dt"], -r["segments"]),
    )[0]

    payload = {
        "schema": "tune-law7-v1",
        "date": datetime.now(timezone.utc).strftime("%Y-%m-%d"),
        "git_commit": commit,
        "chosen": {
            "dt": chosen["dt"],
            "segments": chosen["segments"],
            "mean_ratio_vs_exact": chosen["mean_ratio_vs_exact"],
            "fl1_first_contact_abs_dt": chosen["fl1_first_contact_abs_dt"],
        },
        "exact_engine_binary_sha256": exact_sha,
        "baseline_engine_binary_sha256": baseline_sha,
        "timing_runs": TIMING_RUNS,
        "exact_timing": exact_timing,
        "grid": grid_rows,
    }

    os.makedirs(os.path.dirname(TUNE_OUT), exist_ok=True)
    with open(TUNE_OUT, "w", newline="\n", encoding="utf-8") as handle:
        json.dump(payload, handle, indent=2, sort_keys=True)
        handle.write("\n")

    print(json.dumps(payload["chosen"], indent=2))
    print(f"tune-ok: wrote {TUNE_OUT}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

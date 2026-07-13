#!/usr/bin/env python3
"""GATE-P1 P1-C checker (loop_stability)."""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import struct
import sys

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO_ROOT, "tools", "gaterunner"))

from check_p1a import execute_study, read_engine_events  # noqa: E402

MANIFESTS_DIR = os.path.join(REPO_ROOT, "tools", "gaterunner", "manifests")
EVENTS_DIR = os.path.join(REPO_ROOT, "tools", "gaterunner", "events", "P1-C")
HELDOUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "heldout")
PERIODS = 10_000


def load_json(path: str):
    with open(path, encoding="utf-8") as handle:
        return json.load(handle)


def period_event_count(scenario_id: str) -> int:
    fixture = load_json(os.path.join(HELDOUT_DIR, scenario_id + ".json"))
    return len(fixture["reference_events"])


def interval_vector(times: list[float], period_events: int, period_index: int) -> list[float]:
    start = period_index * period_events
    chunk = times[start : start + period_events]
    if len(chunk) < 2:
        return []
    return [chunk[i + 1] - chunk[i] for i in range(len(chunk) - 1)]


def vector_hash(vector: list[float]) -> str:
    payload = b"".join(struct.pack("=d", value) for value in vector)
    return hashlib.sha256(payload).hexdigest()


def check_fixture(scenario_id: str) -> tuple[bool, int | None, str]:
    period_events = period_event_count(scenario_id)
    event_path = os.path.join(EVENTS_DIR, scenario_id + ".jsonl")
    events = read_engine_events(event_path)
    times = [float(ev["t"]) for ev in events]
    needed = period_events * PERIODS
    if len(times) < needed:
        return False, 0, "insufficient-events"

    period1 = interval_vector(times, period_events, 0)
    if not period1:
        return False, 0, "empty-period1"
    h1 = vector_hash(period1)
    for period in range(1, PERIODS):
        vec = interval_vector(times, period_events, period)
        if len(vec) != len(period1):
            return False, period, h1
        for a, b in zip(period1, vec):
            if a != b:
                return False, period, h1
    return True, None, h1


def print_report() -> int:
    manifest = load_json(os.path.join(MANIFESTS_DIR, "P1-C.json"))
    if manifest.get("engine_git_dirty"):
        print("CHECK-FAILED: manifest engine_git_dirty=true")
        return 1

    print(f"{'scenario_id':<28} {'period_ev':>9} {'periods':>8} {'first_div':>10} {'interval_hash':>16} {'verdict':>8}")
    ok = True
    max_div = 0
    for entry in manifest["scenarios"]:
        sid = entry["scenario_id"]
        pe = period_event_count(sid)
        passed, div, ih = check_fixture(sid)
        if not passed:
            ok = False
        div_display = "none" if div is None else str(div)
        if div is not None:
            max_div = max(max_div, div if isinstance(div, int) else 0)
        print(
            f"{sid:<28} {pe:>9} {PERIODS:>8} {div_display:>10} {ih[:16]:>16} "
            f"{'PASS' if passed else 'FAIL':>8}"
        )
    print(f"\nP1-C VERDICT: {'PASS' if ok else 'FAIL'}")
    print(f"  max_first_divergence={'none' if ok else max_div}")
    return 0 if ok else 1


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--execute", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    study = os.path.join(REPO_ROOT, "tools", "gaterunner", "studies", "P1-C.json")
    manifest = os.path.join(MANIFESTS_DIR, "P1-C.json")
    if args.execute:
        if execute_study(study, manifest) != 0:
            return 1
    if args.check or not args.execute:
        return print_report()
    return 0


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
"""Checker shape self-test for GATE-P1-R3 pre-flight D7 (L-17)."""
from __future__ import annotations

import json
import os
import sys
from dataclasses import dataclass
from typing import Any, Callable

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO_ROOT, "tools", "gaterunner"))

from check_p1a import compare_reference_agreement, read_engine_events  # noqa: E402

FIXTURE_ROOT = os.path.join(REPO_ROOT, "tests", "fixtures", "gaterunner-selftest")


@dataclass
class VectorSpec:
    name: str
    expect_pass: bool
    expected_fail: bool = False
    zero_event: bool = False


VECTORS: list[VectorSpec] = [
    VectorSpec("rational_5_2", expect_pass=True),
    VectorSpec("decimal_scientific", expect_pass=True),
    VectorSpec("zero_event", expect_pass=True, zero_event=True),
    VectorSpec("within_tolerance", expect_pass=True),
    VectorSpec("over_tolerance", expect_pass=False, expected_fail=True),
    VectorSpec("rational_hexfloat_mixed", expect_pass=True),
]


def load_vector(name: str) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    vector_dir = os.path.join(FIXTURE_ROOT, name)
    fixture_path = os.path.join(vector_dir, "fixture.json")
    events_path = os.path.join(vector_dir, "events.jsonl")
    with open(fixture_path, encoding="utf-8") as handle:
        fixture = json.load(handle)
    refs = fixture.get("reference_events", [])
    eng = read_engine_events(events_path)
    return refs, eng


def run_vector(spec: VectorSpec) -> tuple[str, str, str]:
    refs, eng = load_vector(spec.name)
    if spec.zero_event:
        passed = len(refs) == 0 and len(eng) == 0
        detail = "count-only empty reference and engine"
    else:
        passed, worst_dt, worst_ds = compare_reference_agreement(refs, eng, window=len(refs) or None)
        detail = f"worst_|dt|={worst_dt:.6e} worst_|ds|={worst_ds:.6e}"

    if spec.expected_fail:
        if not passed:
            status = "expected-fail ok"
        else:
            status = "FAIL"
    elif passed == spec.expect_pass:
        status = "PASS"
    else:
        status = "FAIL"

    return spec.name, status, detail


def main() -> int:
    print(f"{'vector':<28} {'status':>18} detail")
    ok = True
    for spec in VECTORS:
        name, status, detail = run_vector(spec)
        if status == "FAIL":
            ok = False
        print(f"{name:<28} {status:>18} {detail}")

    if not ok:
        print("checker-shape-selftest: FAIL")
        return 1
    print("checker-shape-selftest: PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())

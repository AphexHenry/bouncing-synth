#!/usr/bin/env python3
"""I-003 scenario store validator and split-lock access gate.

Validates calibration scenarios against config/scenario-fixture-schema-v1.json,
checks split-lock marker against heldout/MANIFEST.json, and enforces held-out
access only when BOUNCE_HELDOUT_LOCK=1 (gate runner / gate-time use).
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import sys

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
SCENARIOS_ROOT = os.path.join(REPO_ROOT, "data", "scenarios")
CALIBRATION_DIR = os.path.join(SCENARIOS_ROOT, "calibration")
HELDOUT_DIR = os.path.join(SCENARIOS_ROOT, "heldout")
SPLIT_LOCK_PATH = os.path.join(SCENARIOS_ROOT, "split-lock.json")
HELDOUT_MANIFEST_PATH = os.path.join(HELDOUT_DIR, "MANIFEST.json")
SCHEMA_PATH = os.path.join(REPO_ROOT, "config", "scenario-fixture-schema-v1.json")

HELDOUT_LOCK_ENV = "BOUNCE_HELDOUT_LOCK"

REQUIRED_SCENARIO_KEYS = (
    "schema_version",
    "scenario_id",
    "provenance_tier",
    "family",
    "curve",
    "initial_state",
    "physics",
    "reference_events",
    "verification",
)


def sha256_file(path: str) -> str:
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for chunk in iter(lambda: handle.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


def load_json(path: str) -> object:
    with open(path, encoding="utf-8") as handle:
        return json.load(handle)


def validate_scenario_record(record: dict, path: str) -> None:
    missing = [key for key in REQUIRED_SCENARIO_KEYS if key not in record]
    if missing:
        raise ValueError(f"{path}: missing required keys: {missing}")
    if record["schema_version"] != "1":
        raise ValueError(f"{path}: schema_version must be '1'")
    if record["provenance_tier"] not in (1, 2):
        raise ValueError(f"{path}: invalid provenance_tier")
    curve = record["curve"]
    for key in ("curve_id", "family", "domain"):
        if key not in curve:
            raise ValueError(f"{path}: curve missing {key}")
    if curve["family"] not in ("polynomial", "piecewise-bezier"):
        raise ValueError(f"{path}: curve family must be polynomial or piecewise-bezier")
    if curve["family"] == "polynomial":
        if "coeffs" not in curve:
            raise ValueError(f"{path}: curve missing coeffs")
    else:
        if "segments" not in curve:
            raise ValueError(f"{path}: curve missing segments")
    if not record["initial_state"]:
        raise ValueError(f"{path}: initial_state empty")
    if "gravity" not in record["physics"]:
        raise ValueError(f"{path}: physics missing gravity")
    for event in record["reference_events"]:
        for key in ("seq", "t", "ball_id", "contact", "tier"):
            if key not in event:
                raise ValueError(f"{path}: reference_events missing {key}")
    for key in ("method", "residual_max"):
        if key not in record["verification"]:
            raise ValueError(f"{path}: verification missing {key}")


def list_calibration_scenarios() -> list[str]:
    if not os.path.isdir(CALIBRATION_DIR):
        raise FileNotFoundError(f"missing calibration dir: {CALIBRATION_DIR}")
    return sorted(
        name
        for name in os.listdir(CALIBRATION_DIR)
        if name.endswith(".json")
    )


def list_heldout_scenarios() -> list[str]:
    if not os.path.isdir(HELDOUT_DIR):
        raise FileNotFoundError(f"missing heldout dir: {HELDOUT_DIR}")
    return sorted(
        name
        for name in os.listdir(HELDOUT_DIR)
        if name.endswith(".json") and name != "MANIFEST.json"
    )


def validate_calibration() -> int:
    if not os.path.isfile(SCHEMA_PATH):
        raise FileNotFoundError(f"missing schema: {SCHEMA_PATH}")
    load_json(SCHEMA_PATH)
    names = list_calibration_scenarios()
    if not names:
        raise ValueError("calibration corpus empty")
    for name in names:
        path = os.path.join(CALIBRATION_DIR, name)
        record = load_json(path)
        if not isinstance(record, dict):
            raise ValueError(f"{path}: expected object")
        validate_scenario_record(record, path)
    return len(names)


def validate_split_lock(calibration_count: int) -> int:
    if not os.path.isfile(SPLIT_LOCK_PATH):
        raise FileNotFoundError(f"missing split-lock marker: {SPLIT_LOCK_PATH}")
    if not os.path.isfile(HELDOUT_MANIFEST_PATH):
        raise FileNotFoundError(f"missing heldout manifest: {HELDOUT_MANIFEST_PATH}")
    manifest_hash = sha256_file(HELDOUT_MANIFEST_PATH)
    lock = load_json(SPLIT_LOCK_PATH)
    if not isinstance(lock, dict):
        raise ValueError("split-lock.json must be an object")
    if lock.get("schema_version") != "1":
        raise ValueError("split-lock schema_version must be '1'")
    if lock.get("split_locked") is not True:
        raise ValueError("split_locked must be true")
    if lock.get("heldout_manifest_sha256") != manifest_hash:
        raise ValueError("heldout_manifest_sha256 mismatch")
    if lock.get("calibration_count") != calibration_count:
        raise ValueError("calibration_count mismatch")
    manifest = load_json(HELDOUT_MANIFEST_PATH)
    if manifest.get("locked") is not True:
        raise ValueError("heldout manifest locked must be true")
    scenarios = manifest.get("scenarios")
    if not isinstance(scenarios, list):
        raise ValueError("heldout manifest scenarios must be a list")
    heldout_names = list_heldout_scenarios()
    if lock.get("heldout_count") != len(scenarios):
        raise ValueError("heldout_count mismatch")
    if len(heldout_names) != len(scenarios):
        raise ValueError(
            f"heldout file count {len(heldout_names)} != manifest {len(scenarios)}"
        )
    manifest_ids = {entry["scenario_id"] for entry in scenarios}
    file_ids = {name[:-5] for name in heldout_names}
    if manifest_ids != file_ids:
        raise ValueError("manifest scenario ids mismatch heldout files")
    for entry in scenarios:
        sid = entry["scenario_id"]
        expected = entry["sha256"]
        path = os.path.join(HELDOUT_DIR, sid + ".json")
        actual = sha256_file(path)
        if actual != expected:
            raise ValueError(f"sha256 mismatch for {sid}")
    return len(scenarios)


def check_heldout_access() -> int:
    if os.environ.get(HELDOUT_LOCK_ENV) != "1":
        print("heldout-access-denied: BOUNCE_HELDOUT_LOCK required")
        return 1
    print("heldout-access-ok")
    return 0


def run_validate() -> int:
    calibration_count = validate_calibration()
    heldout_count = validate_split_lock(calibration_count)
    print("validate-store-ok")
    print(f"calibration_scenarios={calibration_count}")
    print(f"heldout_scenarios={heldout_count}")
    print("split_locked=true")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description="I-003 scenario store validator")
    parser.add_argument(
        "--check-heldout-access",
        action="store_true",
        help="exit 0 only when BOUNCE_HELDOUT_LOCK=1",
    )
    args = parser.parse_args()
    try:
        if args.check_heldout_access:
            return check_heldout_access()
        return run_validate()
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"validate-store-failed: {exc}")
        return 1


if __name__ == "__main__":
    sys.exit(main())

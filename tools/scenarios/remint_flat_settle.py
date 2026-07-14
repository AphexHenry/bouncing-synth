#!/usr/bin/env python3
"""I-003-T4: Law-1 re-mint of poisoned HO-flat-settle-{1..4} (refsim/CAS only)."""
from __future__ import annotations

import hashlib
import json
import os
import sys

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
HELDOUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "heldout")
MANIFEST_PATH = os.path.join(HELDOUT_DIR, "MANIFEST.json")
SPLIT_LOCK_PATH = os.path.join(REPO_ROOT, "data", "scenarios", "split-lock.json")

TARGET_IDS = (
    "HO-flat-settle-1",
    "HO-flat-settle-2",
    "HO-flat-settle-3",
    "HO-flat-settle-4",
)

sys.path.insert(0, os.path.dirname(__file__))
import mint_tier1_heldout as m1  # noqa: E402


def sha256_file(path: str) -> str:
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for chunk in iter(lambda: handle.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


def main() -> int:
    v_graze, contact_version, v_graze_hex = m1.read_v_graze()
    print(
        f"v_graze_mpf={m1.mp.nstr(v_graze, 50)} "
        f"v_graze_hex={v_graze_hex} version={contact_version}"
    )
    scenarios, _, _, self_checks = m1.build_all(v_graze, contact_version, v_graze_hex)
    by_id = {record["scenario_id"]: record for record in scenarios}
    missing = [sid for sid in TARGET_IDS if sid not in by_id]
    if missing:
        print(f"remint-flat-settle-FAILED: missing ids {missing}")
        return 1
    with open(MANIFEST_PATH, encoding="utf-8") as handle:
        manifest = json.load(handle)
    for sid in TARGET_IDS:
        record = by_id[sid]
        path = m1.write_scenario(record)
        digest = sha256_file(path)
        print(f"wrote {os.path.relpath(path, REPO_ROOT)} sha256={digest}")
        for entry in manifest["scenarios"]:
            if entry["scenario_id"] == sid:
                entry["sha256"] = digest
                break
        else:
            print(f"remint-flat-settle-FAILED: {sid} not in manifest")
            return 1
    with open(MANIFEST_PATH, "w", newline="\n") as handle:
        json.dump(manifest, handle, indent=2, sort_keys=True)
        handle.write("\n")
    manifest_hash = sha256_file(MANIFEST_PATH)
    with open(SPLIT_LOCK_PATH, encoding="utf-8") as handle:
        lock = json.load(handle)
    lock["heldout_manifest_sha256"] = manifest_hash
    with open(SPLIT_LOCK_PATH, "w", newline="\n") as handle:
        json.dump(lock, handle, indent=2, sort_keys=True)
        handle.write("\n")
    print("dual_precision_self_checks_R4 (re-minted flat-settle):")
    for sid, worst in self_checks:
        if sid in TARGET_IDS:
            print(f"  {sid}: worst_case_agreement_digits={worst}")
    print("remint-flat-settle-ok 4")
    return 0


if __name__ == "__main__":
    sys.exit(main())

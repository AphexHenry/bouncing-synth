#!/usr/bin/env python3
"""GATE-P1 P1-B checker (determinism_repro)."""
from __future__ import annotations

import argparse
import json
import os
import subprocess
import sys

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO_ROOT, "tools", "gaterunner"))

import gaterunner  # noqa: E402

from check_p1a import execute_study  # noqa: E402

HELDOUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "heldout")
MANIFESTS_DIR = os.path.join(REPO_ROOT, "tools", "gaterunner", "manifests")
BINARY = os.path.join(REPO_ROOT, "build", "default", "bounce-run-scenario")


def heldout_ids() -> list[str]:
    return sorted(
        name[:-5]
        for name in os.listdir(HELDOUT_DIR)
        if name.endswith(".json") and name != "MANIFEST.json"
    )


def log_repeat_access(scenario_id: str, study_id: str = "P1-B-REPEAT") -> None:
    scen_path = os.path.join(HELDOUT_DIR, scenario_id + ".json")
    commit, _ = gaterunner.git_head_info()
    gaterunner.append_access_log(
        scenario_id=scenario_id,
        scenario_sha256=gaterunner.sha256_file(scen_path),
        study_id=study_id,
        gate_id="P1-B",
        engine_commit=commit,
    )


def run_repeat_suite(max_events: int = 200, repeat: int = 100) -> int:
    ok = True
    for scenario_id in heldout_ids():
        scen_path = os.path.join(HELDOUT_DIR, scenario_id + ".json")
        out_path = os.path.join(REPO_ROOT, "tools", "gaterunner", "events", "P1-B-repeat", scenario_id + ".jsonl")
        os.makedirs(os.path.dirname(out_path), exist_ok=True)
        proc = subprocess.run(
            [
                BINARY,
                "--scenario",
                scen_path,
                "--out",
                out_path,
                "--max-events",
                str(max_events),
                "--repeat",
                str(repeat),
            ],
            cwd=REPO_ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        log_repeat_access(scenario_id)
        line = proc.stdout.strip().splitlines()[-1] if proc.stdout else ""
        if proc.returncode != 0:
            ok = False
            print(proc.stderr.strip() or f"repeat-failed: {scenario_id}")
        else:
            print(line if line.startswith("repeat-identity") else f"repeat-identity ok N={repeat}")
    return 0 if ok else 1


def compare_manifests(a: str, b: str) -> int:
    return gaterunner.compare_manifests(a, b)


def run_fresh_process_suite() -> int:
    study = os.path.join(REPO_ROOT, "tools", "gaterunner", "studies", "P1-B.json")
    manifests = []
    for label in "ABCDEFGHIJ":
        manifest = os.path.join(MANIFESTS_DIR, f"P1-B-run{label}.json")
        code = execute_study(study, manifest)
        if code != 0:
            return code
        manifests.append(manifest)
    base = manifests[0]
    ok = True
    for other in manifests[1:]:
        print(f"compare {os.path.basename(base)} vs {os.path.basename(other)}:")
        code = compare_manifests(base, other)
        if code != 0:
            ok = False
    return 0 if ok else 1


def clean_rebuild_compare() -> int:
    build_dir = os.path.join(REPO_ROOT, "build", "default")
    study = os.path.join(REPO_ROOT, "tools", "gaterunner", "studies", "P1-B.json")
    base_manifest = os.path.join(MANIFESTS_DIR, "P1-B-runA.json")

    def toolchain_paste(label: str) -> None:
        tc = gaterunner.collect_toolchain()
        print(f"toolchain {label}: cmake={tc['cmake']} compiler={tc['compiler']} python={tc['python']}")

    results = []
    for idx in (1, 2):
        toolchain_paste(f"before-rebuild-{idx}")
        subprocess.run(["rm", "-rf", build_dir], cwd=REPO_ROOT, check=True)
        cfg = subprocess.run(
            ["cmake", "--preset", "default"],
            cwd=REPO_ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        if cfg.returncode != 0:
            print(cfg.stderr)
            return 1
        bld = subprocess.run(
            ["cmake", "--build", "build/default", "-j"],
            cwd=REPO_ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        if bld.returncode != 0:
            print(bld.stderr)
            return 1
        toolchain_paste(f"after-rebuild-{idx}")
        manifest = os.path.join(MANIFESTS_DIR, f"P1-B-rebuild{idx}.json")
        code = execute_study(study, manifest)
        if code != 0:
            return code
        print(f"compare {os.path.basename(base_manifest)} vs {os.path.basename(manifest)}:")
        results.append(compare_manifests(base_manifest, manifest))
    return 0 if all(code == 0 for code in results) else 1


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--repeat-suite", action="store_true")
    parser.add_argument("--fresh-process", action="store_true")
    parser.add_argument("--rebuild-compare", action="store_true")
    parser.add_argument("--all", action="store_true")
    args = parser.parse_args()

    if args.all or args.repeat_suite:
        if run_repeat_suite() != 0:
            return 1
    if args.all or args.fresh_process:
        if run_fresh_process_suite() != 0:
            return 1
    if args.all or args.rebuild_compare:
        if clean_rebuild_compare() != 0:
            return 1
    if not any((args.all, args.repeat_suite, args.fresh_process, args.rebuild_compare)):
        parser.error("no action selected")
    print("P1-B VERDICT: PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())

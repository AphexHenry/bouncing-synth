#!/usr/bin/env python3
"""Emit Tier-1 scenarios into the I-003 store layout (I-002-T4).

Reads closed-form fixtures from tier1_fixtures and writes scenario records to
data/scenarios/calibration/ per config/scenario-fixture-schema-v1.json.
Deterministic: sorted JSON keys, LF endings, exact rational strings preserved.
"""
import json
import os

import tier1_fixtures as t1

SCHEMA_VERSION = "1"
REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
OUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "calibration")


def scenario_from_fl(fl_fixture, times):
    p = fl_fixture["params"]
    return {
        "schema_version": SCHEMA_VERSION,
        "scenario_id": fl_fixture["id"],
        "provenance_tier": 1,
        "family": fl_fixture["family"],
        "curve": {
            "curve_id": fl_fixture["id"] + "-curve",
            "family": "polynomial",
            "coeffs": fl_fixture["curve"]["coeffs"],
            "domain": ["0", "100"],
        },
        "initial_state": [
            {
                "ball_id": 0,
                "pos": {"x": "0", "y": p["h"]},
                "vel": {"vx": p["vx"], "vy": "0"},
                "radius": "0.1",
                "restitution": p["e"],
            }
        ],
        "physics": {"gravity": p["g"]},
        "reference_events": [
            {
                "seq": i,
                "t": ev["t"],
                "ball_id": 0,
                "contact": {"x": ev["x"], "y": "0"},
                "tier": 1,
            }
            for i, ev in enumerate(fl_fixture["events"])
        ],
        "verification": fl_fixture["verification"],
        "claims": fl_fixture["claims"],
    }


def scenario_from_pb(pb_fixture):
    p = pb_fixture["params"]
    ev = pb_fixture["events"][0]
    return {
        "schema_version": SCHEMA_VERSION,
        "scenario_id": pb_fixture["id"],
        "provenance_tier": 1,
        "family": pb_fixture["family"],
        "curve": {
            "curve_id": pb_fixture["id"] + "-curve",
            "family": "polynomial",
            "coeffs": pb_fixture["curve"]["coeffs"],
            "domain": ["0", "100"],
        },
        "initial_state": [
            {
                "ball_id": 0,
                "pos": {"x": "0", "y": p["h"]},
                "vel": {"vx": p["vx"], "vy": "0"},
                "radius": "0.1",
                "restitution": "1/2",
            }
        ],
        "physics": {"gravity": p["g"]},
        "reference_events": [
            {
                "seq": 0,
                "t": ev["t"],
                "ball_id": 0,
                "contact": {"x": ev["contact"][0], "y": ev["contact"][1]},
                "tier": 1,
            }
        ],
        "verification": pb_fixture["verification"],
        "claims": pb_fixture["claims"],
    }


def write_scenario(scenario):
    path = os.path.join(OUT_DIR, scenario["scenario_id"] + ".json")
    with open(path, "w", newline="\n") as f:
        json.dump(scenario, f, indent=2, sort_keys=True)
        f.write("\n")
    return path


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    fl_fixture, fl_times = t1.fl1()
    pb_fixture, pb_t1, pb_contact, pb_res = t1.pb1()
    paths = [
        write_scenario(scenario_from_fl(fl_fixture, fl_times)),
        write_scenario(scenario_from_pb(pb_fixture)),
    ]
    print("schema_version=%s scenarios=%d"
          % (SCHEMA_VERSION, len(paths)))
    for path in sorted(paths):
        print("wrote %s" % os.path.relpath(path, REPO_ROOT))
    print("emit-scenarios-ok")


if __name__ == "__main__":
    main()

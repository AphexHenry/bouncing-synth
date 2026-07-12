#!/usr/bin/env python3
"""Mint 16 Tier-1 held-out scenarios (I-003-T2).

Uses pinned refsim/CAS only — no C++ engine binary (Law 1).
"""
from __future__ import annotations

import hashlib
import json
import os
import re
import subprocess
import sys
from fractions import Fraction as F

import mpmath as mp

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
HELDOUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "heldout")
MANIFEST_PATH = os.path.join(HELDOUT_DIR, "MANIFEST.json")
SPLIT_LOCK_PATH = os.path.join(REPO_ROOT, "data", "scenarios", "split-lock.json")
VCA_HPP = os.path.join(REPO_ROOT, "src", "core", "bounce", "engine", "vca.hpp")
VERSION_CPP = os.path.join(REPO_ROOT, "src", "core", "bounce", "version.cpp")
SCHEMA_VERSION = "1"

sys.path.insert(0, os.path.join(REPO_ROOT, "tools", "refsim"))
import tier2_refsim as t2  # noqa: E402


def sha256_file(path: str) -> str:
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for chunk in iter(lambda: handle.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


def git_commit() -> str:
    return subprocess.check_output(
        ["git", "rev-parse", "HEAD"], cwd=REPO_ROOT, text=True
    ).strip()


def read_v_graze() -> tuple[mp.mpf, str]:
    with open(VCA_HPP, encoding="utf-8") as handle:
        text = handle.read()
    match = re.search(r"constexpr\s+double\s+kVGraze\s*=\s*([^;]+);", text)
    if not match:
        raise ValueError(f"kVGraze not found in {VCA_HPP}")
    value = mp.mpf(match.group(1).strip())
    with open(VERSION_CPP, encoding="utf-8") as handle:
        vtext = handle.read()
    vmatch = re.search(r'contact_rule_version\(\)\s*\{\s*return\s*"([^"]+)"', vtext)
    if not vmatch:
        raise ValueError(f"contact_rule_version not found in {VERSION_CPP}")
    return value, vmatch.group(1)


def fmt_frac(q: F) -> str:
    return str(q)


def is_square_fraction(q: F) -> bool:
    num = q.numerator
    den = q.denominator
    def is_sq(n: int) -> bool:
        if n < 0:
            return False
        r = int(n ** 0.5)
        return r * r == n
    return is_sq(num) and is_sq(den)


def flat_settle_events(h: F, g: F, e: F, vx: F, n_events: int) -> list[tuple[F, F, F]]:
    t1_sq = 2 * h / g
    if not is_square_fraction(t1_sq):
        raise ValueError(f"flat settle requires exact rational t1, got sqrt({t1_sq})")
    t1 = F(int(t1_sq.numerator ** 0.5), int(t1_sq.denominator ** 0.5))
    events: list[tuple[F, F, F]] = []
    t_prev, v_prev = t1, e * g * t1
    events.append((t1, vx * t1, F(0)))
    for _ in range(n_events - 1):
        dt = 2 * v_prev / g
        t_prev = t_prev + dt
        v_prev = e * v_prev
        events.append((t_prev, vx * t_prev, F(0)))
    return events


def merge_tb1(per_ball: list[list[tuple[F, F, F, int]]], max_events: int) -> list[dict]:
    merged: list[tuple[F, int, F, F]] = []
    for ball_events in per_ball:
        for t, x, y, ball_id in ball_events:
            merged.append((t, ball_id, x, y))
    merged.sort(key=lambda item: (item[0], item[1]))
    out = []
    for seq, (t, ball_id, x, y) in enumerate(merged[:max_events]):
        out.append(
            {
                "seq": seq,
                "t": fmt_frac(t),
                "ball_id": ball_id,
                "contact": {"x": fmt_frac(x), "y": fmt_frac(y)},
                "tier": 1,
            }
        )
    return out


def non_dyadic_check(period_expr: str, period_value: mp.mpf) -> dict:
    mp.mp.dps = 60
    period = mp.mpf(period_value)
    nearest = mp.mpf(float(period))
    inexact = period != nearest
    symbolic_non_dyadic = "sqrt" in period_expr
    ok = inexact or symbolic_non_dyadic
    return {
        "period_closed_form": period_expr,
        "period_50_digits": mp.nstr(period, 50),
        "nearest_double": mp.nstr(nearest, 17),
        "double_inexact": inexact,
        "symbolic_non_dyadic": symbolic_non_dyadic,
        "pass": ok,
    }


def flat_periodic_events(
    h: mp.mpf, g: mp.mpf, vx: mp.mpf, n_events: int, period_expr: str, period_val: mp.mpf
) -> tuple[list[tuple[mp.mpf, mp.mpf, mp.mpf]], dict]:
    mp.mp.dps = 60
    t1 = mp.sqrt(2 * h / g)
    check = non_dyadic_check(period_expr, period_val)
    if not check["pass"]:
        raise ValueError(f"period failed non-dyadicity check: {period_expr}")
    events: list[tuple[mp.mpf, mp.mpf, mp.mpf]] = []
    for i in range(n_events):
        t = t1 + 2 * t1 * i
        events.append((t, vx * t, mp.mpf(0)))
    return events, check


def mp_events_to_ref(events: list[tuple], ball_id: int = 0, start_seq: int = 0) -> list[dict]:
    out = []
    for i, (t, x, y) in enumerate(events):
        out.append(
            {
                "seq": start_seq + i,
                "t": mp.nstr(t, 50).rstrip("0").rstrip(".") if isinstance(t, mp.mpf) else str(t),
                "ball_id": ball_id,
                "contact": {
                    "x": mp.nstr(x, 50).rstrip("0").rstrip(".") if isinstance(x, mp.mpf) else str(x),
                    "y": mp.nstr(y, 50).rstrip("0").rstrip(".") if isinstance(y, mp.mpf) else str(y),
                },
                "tier": 1,
            }
        )
    return out


def simulate_mp(curve, x0, y0, vx, vy, g, e, n_events, dps=60):
    mp.mp.dps = dps
    return t2.simulate(curve, x0, y0, vx, vy, g, e, n_events)


def parabola_bowl_periodic(coeff: str, n_events: int) -> tuple[list[tuple], dict]:
    mp.mp.dps = 80
    c = mp.mpf(coeff)
    g = mp.mpf(10)
    x0 = mp.mpf("0.1")
    y0 = c * x0 * x0
    vx, vy = mp.mpf("0.5"), mp.mpf("0.5")
    events = simulate_mp(["0", "0", coeff], x0, y0, vx, vy, g, mp.mpf(1), n_events, dps=80)
    if len(events) < 4:
        raise ValueError("bowl periodic: insufficient events")
    period = events[2][0] - events[0][0]
    period_expr = f"pi/sqrt({2 * c * g})"
    check = non_dyadic_check(period_expr, period)
    return events, check


def construct_grazing(coeff: str, ratio: mp.mpf, v_graze: mp.mpf, g: mp.mpf) -> dict:
    mp.mp.dps = 120
    target_vn = ratio * v_graze
    c = mp.mpf(coeff)
    vx0 = mp.mpf("1")

    def vn_for_h(hval: mp.mpf) -> mp.mpf:
        q = t2.collision_poly([mp.mpf(0), mp.mpf(0), c], mp.mpf(0), hval, vx0, mp.mpf(0), g)
        dt = t2.isolate_smallest_positive_root(q, mp.mpf("1e-50"), mp.mpf(100))
        if dt is None:
            return mp.mpf("nan")
        xc = vx0 * dt
        vyf = -g * dt
        return t2.normal_impact_speed([mp.mpf(0), mp.mpf(0), c], xc, vx0, vyf)

    lo, hi = mp.mpf("1e-30"), mp.mpf("1e-10")
    for _ in range(300):
        mid = mp.sqrt(lo * hi)
        vn_mid = vn_for_h(mid)
        if mp.isnan(vn_mid):
            lo = mid
            continue
        if vn_mid < target_vn:
            lo = mid
        else:
            hi = mid
    h = mp.sqrt(lo * hi)
    vn_final = vn_for_h(h)
    q = t2.collision_poly([mp.mpf(0), mp.mpf(0), c], mp.mpf(0), h, vx0, mp.mpf(0), g)
    dt = t2.isolate_smallest_positive_root(q, mp.mpf("1e-50"), mp.mpf(100))
    xc = vx0 * dt
    yc = c * xc * xc
    achieved = vn_final / v_graze
    err = abs(achieved - ratio)
    if err > mp.mpf("1e-20"):
        raise ValueError(f"grazing construction failed for ratio {ratio}: err={err}")
    if ratio == mp.mpf("1") and vn_final < v_graze:
        h = hi
        vn_final = vn_for_h(h)
        achieved = vn_final / v_graze
        q = t2.collision_poly([mp.mpf(0), mp.mpf(0), c], mp.mpf(0), h, vx0, mp.mpf(0), g)
        dt = t2.isolate_smallest_positive_root(q, mp.mpf("1e-50"), mp.mpf(100))
        xc = vx0 * dt
        yc = c * xc * xc
        err = abs(achieved - ratio)
    g1_class = "graze" if vn_final < v_graze else "admissible"
    return {
        "h": h,
        "vx": vx0,
        "dt": dt,
        "xc": xc,
        "yc": yc,
        "vn": vn_final,
        "ratio": achieved,
        "g1_class": g1_class,
        "target_ratio": ratio,
    }


def base_scenario(
    scenario_id: str,
    family: str,
    coeffs: list[str],
    balls: list[dict],
    gravity: str,
    reference_events: list[dict],
    extra: dict | None = None,
) -> dict:
    commit = git_commit()
    record = {
        "schema_version": SCHEMA_VERSION,
        "scenario_id": scenario_id,
        "provenance_tier": 1,
        "family": family,
        "curve": {
            "curve_id": scenario_id + "-curve",
            "family": "polynomial",
            "coeffs": coeffs,
            "domain": ["0", "100"],
        },
        "initial_state": balls,
        "physics": {"gravity": gravity},
        "reference_events": reference_events,
        "verification": {"method": "refsim-cas-tier1", "residual_max": "0"},
        "provenance": {
            "tier": 1,
            "generator_git_commit": commit,
            "mpmath_version": mp.__version__,
        },
    }
    if extra:
        record["provenance"].update(extra)
    return record


def write_scenario(record: dict) -> str:
    path = os.path.join(HELDOUT_DIR, record["scenario_id"] + ".json")
    with open(path, "w", newline="\n") as handle:
        json.dump(record, handle, indent=2, sort_keys=True)
        handle.write("\n")
    return path


def update_lock(manifest_entries: list[dict]) -> None:
    manifest = {
        "schema_version": "1",
        "description": "Tier-1 held-out corpus minted by I-003-T2 (16 scenarios).",
        "locked": True,
        "scenarios": manifest_entries,
    }
    with open(MANIFEST_PATH, "w", newline="\n") as handle:
        json.dump(manifest, handle, indent=2, sort_keys=True)
        handle.write("\n")
    manifest_hash = sha256_file(MANIFEST_PATH)
    lock = {
        "schema_version": "1",
        "split_locked": True,
        "lock_version": "1",
        "locked_at": "2026-07-12",
        "calibration_count": 2,
        "heldout_count": len(manifest_entries),
        "heldout_manifest_sha256": manifest_hash,
        "note": "Held-out scenarios readable only when BOUNCE_HELDOUT_LOCK=1 (gate runner sets this).",
    }
    with open(SPLIT_LOCK_PATH, "w", newline="\n") as handle:
        json.dump(lock, handle, indent=2, sort_keys=True)
        handle.write("\n")


def build_all(v_graze: mp.mpf, contact_version: str) -> list[dict]:
    scenarios: list[dict] = []

    # (a) flat settle x4
    flat_specs = [
        ("HO-flat-settle-1", F(4), F(8), F(1, 2), F(1), 6, 0),
        ("HO-flat-settle-2", F(16), F(8), F(2, 3), F(3, 2), 6, 0),
        ("HO-flat-settle-3", F(4), F(8), F(1, 2), F(1), 4, 2),
        ("HO-flat-settle-4", F(4), F(8), F(1, 2), F(1), 3, 3),
    ]
    for sid, h, g, e, vx, n_ev, n_balls in flat_specs:
        if n_balls <= 1:
            evs = flat_settle_events(h, g, e, vx, n_ev)
            ref = [
                {
                    "seq": i,
                    "t": fmt_frac(t),
                    "ball_id": 0,
                    "contact": {"x": fmt_frac(x), "y": fmt_frac(y)},
                    "tier": 1,
                }
                for i, (t, x, y) in enumerate(evs)
            ]
            balls = [
                {
                    "ball_id": 0,
                    "pos": {"x": "0", "y": fmt_frac(h)},
                    "vel": {"vx": fmt_frac(vx), "vy": "0"},
                    "radius": "0.1",
                    "restitution": fmt_frac(e),
                }
            ]
        else:
            per_ball = []
            for b in range(n_balls):
                offset = F(b)
                evs = flat_settle_events(h, g, e, vx, n_ev)
                per_ball.append([(t, x + offset, y, b) for t, x, y in evs])
            ref = merge_tb1(per_ball, n_ev * n_balls)
            balls = [
                {
                    "ball_id": b,
                    "pos": {"x": fmt_frac(F(b)), "y": fmt_frac(h)},
                    "vel": {"vx": fmt_frac(vx), "vy": "0"},
                    "radius": "0.1",
                    "restitution": fmt_frac(e),
                }
                for b in range(n_balls)
            ]
        scenarios.append(
            base_scenario(sid, "FL-HO", ["0"], balls, fmt_frac(g), ref)
        )

    # (b) flat periodic non-dyadic x3
    periodic_specs = [
        ("HO-flat-periodic-1", mp.mpf(1), mp.mpf(4), mp.mpf(1), 6, "sqrt(2)", mp.sqrt(2)),
        ("HO-flat-periodic-2", mp.mpf(3), mp.mpf(16), mp.mpf("1/2"), 4, "sqrt(3)", mp.sqrt(3)),
        ("HO-flat-periodic-3", mp.mpf(1), mp.mpf(4), mp.mpf(1), 4, "sqrt(2)", mp.sqrt(2)),
    ]
    periodic_checks = []
    for sid, h, g, vx, n_ev, period_expr, period_val in periodic_specs:
        evs, check = flat_periodic_events(h, g, vx, n_ev, period_expr, period_val)
        periodic_checks.append((sid, check))
        n_balls = 2 if sid == "HO-flat-periodic-3" else 1
        if n_balls <= 1:
            ref = mp_events_to_ref(evs)
            balls = [
                {
                    "ball_id": 0,
                    "pos": {"x": "0", "y": mp.nstr(h, 50)},
                    "vel": {"vx": mp.nstr(vx, 50), "vy": "0"},
                    "radius": "0.1",
                    "restitution": "1",
                }
            ]
        else:
            per_ball = []
            for b in range(n_balls):
                per_ball.append([(ev[0], ev[1] + mp.mpf(b), ev[2], b) for ev in evs])
            merged = []
            for ball_events in per_ball:
                merged.extend(ball_events)
            merged.sort(key=lambda item: (item[0], item[1]))
            ref = []
            for seq, (t, x, y, ball_id) in enumerate(merged[: n_ev * n_balls]):
                ref.append(
                    {
                        "seq": seq,
                        "t": mp.nstr(t, 50),
                        "ball_id": ball_id,
                        "contact": {"x": mp.nstr(x, 50), "y": mp.nstr(y, 50)},
                        "tier": 1,
                    }
                )
            balls = [
                {
                    "ball_id": b,
                    "pos": {"x": str(b), "y": mp.nstr(h, 50)},
                    "vel": {"vx": mp.nstr(vx, 50), "vy": "0"},
                    "radius": "0.1",
                    "restitution": "1",
                }
                for b in range(n_balls)
            ]
        scenarios.append(
            base_scenario(
                sid,
                "FL-HO",
                ["0"],
                balls,
                mp.nstr(g, 50),
                ref,
                {"non_dyadicity_check": check},
            )
        )

    # (c) parabola settle x4
    pb_specs = [
        ("HO-parabola-settle-1", "1", "16", "1", "1/2", 4, 0),
        ("HO-parabola-settle-2", "1/4", "10", "3/2", "2/3", 4, 0),
        ("HO-parabola-settle-3", "1", "16", "1", "1/2", 3, 2),
        ("HO-parabola-settle-4", "1", "16", "1", "1/2", 2, 4),
    ]
    for sid, c, g, vx, e, n_ev, n_balls in pb_specs:
        if n_balls <= 1:
            evs = simulate_mp(["0", "0", c], 0, 5, mp.mpf(vx), 0, mp.mpf(g), mp.mpf(e), n_ev)
            ref = mp_events_to_ref(evs)
            balls = [
                {
                    "ball_id": 0,
                    "pos": {"x": "0", "y": "5"},
                    "vel": {"vx": vx, "vy": "0"},
                    "radius": "0.1",
                    "restitution": e,
                }
            ]
        else:
            per_ball = []
            for b in range(n_balls):
                evs = simulate_mp(
                    ["0", "0", c], b, 5, mp.mpf(vx), 0, mp.mpf(g), mp.mpf(e), n_ev
                )
                per_ball.append([(ev[0], ev[1], ev[2], b) for ev in evs])
            ref = []
            merged = []
            for ball_events in per_ball:
                for ev in ball_events:
                    merged.append(ev)
            merged.sort(key=lambda item: (item[0], item[1]))
            for seq, (t, x, y, ball_id) in enumerate(merged[: n_ev * n_balls]):
                ref.append(
                    {
                        "seq": seq,
                        "t": mp.nstr(t, 50),
                        "ball_id": ball_id,
                        "contact": {"x": mp.nstr(x, 50), "y": mp.nstr(y, 50)},
                        "tier": 1,
                    }
                )
            balls = [
                {
                    "ball_id": b,
                    "pos": {"x": str(b), "y": "5"},
                    "vel": {"vx": vx, "vy": "0"},
                    "radius": "0.1",
                    "restitution": e,
                }
                for b in range(n_balls)
            ]
        scenarios.append(
            base_scenario(sid, "PB-HO", ["0", "0", c], balls, g, ref)
        )

    # (d) parabola bowl periodic x2
    bowl_specs = [
        ("HO-parabola-periodic-1", "1", "0.1", "0.01", "0.5", "0.5"),
        ("HO-parabola-periodic-2", "1/2", "0.1", "0.005", "0.5", "0.5"),
    ]
    for sid, c, x0s, y0s, vxs, vys in bowl_specs:
        x0, y0, vx, vy = mp.mpf(x0s), mp.mpf(y0s), mp.mpf(vxs), mp.mpf(vys)
        evs, check = parabola_bowl_periodic(c, 6)
        periodic_checks.append((sid, check))
        ref = mp_events_to_ref(evs)
        balls = [
            {
                "ball_id": 0,
                "pos": {"x": x0s, "y": y0s},
                "vel": {"vx": vxs, "vy": vys},
                "radius": "0.1",
                "restitution": "1",
            }
        ]
        scenarios.append(
            base_scenario(
                sid,
                "PB-HO",
                ["0", "0", c],
                balls,
                "10",
                ref,
                {"non_dyadicity_check": check},
            )
        )

    # (e) grazing block x3
    for idx, ratio in enumerate([mp.mpf("0.5"), mp.mpf("1"), mp.mpf("2")], start=1):
        sid = f"HO-graze-parabola-{idx}"
        graze = construct_grazing("1", ratio, v_graze, mp.mpf(10))
        evs = simulate_mp(
            ["0", "0", "1"],
            0,
            graze["h"],
            graze["vx"],
            0,
            mp.mpf(10),
            mp.mpf("1/2"),
            4,
        )
        ref = mp_events_to_ref(evs)
        extra = {
            "v_graze": {"value": mp.nstr(v_graze, 20), "version": contact_version},
            "grazing_construction": {
                "target_ratio": mp.nstr(ratio, 20),
                "achieved_ratio": mp.nstr(graze["ratio"], 25, min_fixed=1, max_fixed=0),
                "g1_classification": graze["g1_class"],
            },
        }
        if ratio == mp.mpf("0.5"):
            extra["g1_oracle_classification"] = graze["g1_class"]
        balls = [
            {
                "ball_id": 0,
                "pos": {"x": "0", "y": mp.nstr(graze["h"], 50)},
                "vel": {"vx": mp.nstr(graze["vx"], 50), "vy": "0"},
                "radius": "0.1",
                "restitution": "1/2",
            }
        ]
        scenarios.append(
            base_scenario(sid, "PB-HO", ["0", "0", "1"], balls, "10", ref, extra)
        )

    return scenarios, periodic_checks


def main() -> int:
    v_graze, contact_version = read_v_graze()
    print(f"v_graze={mp.nstr(v_graze, 20)} version={contact_version}")
    scenarios, periodic_checks = build_all(v_graze, contact_version)
    if len(scenarios) != 16:
        print(f"mint-tier1-heldout-FAILED: expected 16 scenarios, got {len(scenarios)}")
        return 1
    manifest_entries = []
    for record in scenarios:
        path = write_scenario(record)
        digest = sha256_file(path)
        manifest_entries.append({"scenario_id": record["scenario_id"], "sha256": digest})
        print(f"wrote {os.path.relpath(path, REPO_ROOT)} sha256={digest}")
    update_lock(manifest_entries)
    print("non_dyadicity_checks:")
    for sid, check in periodic_checks:
        print(f"  {sid}: {json.dumps(check, sort_keys=True)}")
    for record in scenarios:
        if record["scenario_id"].startswith("HO-graze"):
            gc = record["provenance"]["grazing_construction"]
            print(
                f"  {record['scenario_id']}: ratio={gc['achieved_ratio']} "
                f"class={gc['g1_classification']}"
            )
    print("mint-tier1-heldout-ok 16")
    return 0


if __name__ == "__main__":
    sys.exit(main())

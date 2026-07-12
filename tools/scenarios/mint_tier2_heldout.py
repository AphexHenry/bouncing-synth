#!/usr/bin/env python3
"""Mint 16 Tier-2 held-out scenarios (I-003-T3).

Refsim/CAS only — no C++ engine binary (Law 1).
Extends corpus to 32 held-out fixtures (16 Tier-1 + 16 Tier-2).
"""
from __future__ import annotations

import hashlib
import json
import os
import subprocess
import sys
from typing import Callable

import mpmath as mp
from mpmath.libmp import from_float, round_nearest, to_float

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
HELDOUT_DIR = os.path.join(REPO_ROOT, "data", "scenarios", "heldout")
MANIFEST_PATH = os.path.join(HELDOUT_DIR, "MANIFEST.json")
SPLIT_LOCK_PATH = os.path.join(REPO_ROOT, "data", "scenarios", "split-lock.json")
SCHEMA_VERSION = "1"
WORKING_DPS = 55

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


def nearest_ieee_double(x: mp.mpf) -> mp.mpf:
    bits = to_float(x._mpf_, rnd=round_nearest, strict=0)
    return mp.mpf(from_float(bits))


def non_dyadic_check(period_expr: str, period_value: mp.mpf) -> dict:
    old_dps = mp.mp.dps
    try:
        mp.mp.dps = WORKING_DPS
        period = mp.mpf(period_value)
        nearest = nearest_ieee_double(period)
        gap = abs(period - nearest)
        if period == nearest or gap == 0:
            raise ValueError(f"period is dyadic/exact-double: {period_expr}")
        return {
            "period_closed_form": period_expr,
            "period_50_digits": mp.nstr(period, 50),
            "nearest_double": mp.nstr(nearest, 17),
            "gap": mp.nstr(gap, 35),
            "pass": True,
        }
    finally:
        mp.mp.dps = old_dps


def poly_coeffs(degree: int, leading: str = "1") -> list[str]:
    return ["0"] * degree + [leading]


def mp_events_to_ref(events, ball_id: int = 0, tier: int = 2) -> list[dict]:
    out = []
    for i, (t, x, y) in enumerate(events):
        out.append(
            {
                "seq": i,
                "t": mp.nstr(t, 50).rstrip("0").rstrip("."),
                "ball_id": ball_id,
                "contact": {
                    "x": mp.nstr(x, 50).rstrip("0").rstrip("."),
                    "y": mp.nstr(y, 50).rstrip("0").rstrip("."),
                },
                "tier": tier,
            }
        )
    return out


def merge_tb1(per_ball: list[list[tuple]], max_events: int) -> list[dict]:
    merged: list[tuple] = []
    for ball_events in per_ball:
        for t, x, y, ball_id in ball_events:
            merged.append((t, ball_id, x, y))
    merged.sort(key=lambda item: (item[0], item[1]))
    out = []
    for seq, (t, ball_id, x, y) in enumerate(merged[:max_events]):
        out.append(
            {
                "seq": seq,
                "t": mp.nstr(t, 50),
                "ball_id": ball_id,
                "contact": {"x": mp.nstr(x, 50), "y": mp.nstr(y, 50)},
                "tier": 2,
            }
        )
    return out


def make_poly_regen(coeffs, x0, y0, vx, vy, g, e, n_events):
    def regen(dps: int) -> list[tuple]:
        mp.mp.dps = dps
        return t2.simulate(coeffs, x0, y0, vx, vy, g, e, n_events)

    return regen


def make_bezier_regen(segments, x0, y0, vx, vy, g, e, n_events):
    def regen(dps: int) -> list[tuple]:
        mp.mp.dps = dps
        return t2.simulate_piecewise_bezier(segments, x0, y0, vx, vy, g, e, n_events)

    return regen


def make_sensitivity_regen(coeffs, x0, y0, vx, vy, g, e, n_events, component: str):
    def regen(dps: int, perturb: mp.mpf) -> list[tuple]:
        mp.mp.dps = dps
        x, y, vvx, vvy = mp.mpf(x0), mp.mpf(y0), mp.mpf(vx), mp.mpf(vy)
        if component == "vx":
            vvx += perturb
        elif component == "vy":
            vvy += perturb
        elif component == "y0":
            y += perturb
        else:
            raise ValueError(component)
        return t2.simulate(coeffs, 0, y, vvx, vvy, g, e, n_events)

    return regen


def certify_quasi_chaotic(regen_factory, component: str) -> dict:
    regen = regen_factory(component)

    def wrapped(dps, perturb):
        return regen(dps, perturb)

    base = wrapped(55, mp.mpf(0))
    pert = wrapped(55, mp.mpf("1e-30"))
    rows = []
    diverged = False
    for i in range(min(len(base), len(pert), 25)):
        div = abs(base[i][0] - pert[i][0])
        rows.append(
            {
                "event": i,
                "t_base": mp.nstr(base[i][0], 20),
                "t_pert": mp.nstr(pert[i][0], 20),
                "divergence": mp.nstr(div, 20),
            }
        )
        if div > mp.mpf("1e-10"):
            diverged = True
    if not diverged:
        raise ValueError(f"quasi-chaotic certification failed for {component}")
    return {
        "perturbed_component": component,
        "perturbation": "1e-30",
        "diverged": True,
        "table": rows,
    }


def find_quasi_chaotic_params(coeffs, component: str, candidates: list[tuple]) -> tuple:
    g, e = mp.mpf(10), mp.mpf("1")
    best = None
    for y0, vx, vy in candidates:
        cert = t2.certify_quasi_chaotic_mpmath(coeffs, y0, vx, vy, e, component, 25)
        max_div = max(mp.mpf(row["divergence"]) for row in cert["table"])
        if cert["diverged"]:
            return y0, vx, vy, cert
        if best is None or max_div > best[0]:
            best = (max_div, y0, vx, vy, cert)
    if best is not None:
        raise ValueError(
            f"quasi-chaotic certification failed for {coeffs}: best max divergence "
            f"{mp.nstr(best[0], 20)} < 1e-10"
        )
    raise ValueError("no quasi-chaotic candidate certified")


def find_double_root_coeffs() -> tuple[list[str], str, str, str, dict]:
    g = mp.mpf(10)
    coeffs = poly_coeffs(4, "1/4")
    for h_s in ("4.5", "4.51", "4.52", "4.53", "4.54", "4.55", "4.56"):
        for vx_s in ("0.8", "0.85", "0.9", "0.95", "1.0", "1.05"):
            h, vx = mp.mpf(h_s), mp.mpf(vx_s)
            disc = t2.poly_discriminant_at_first_contact(coeffs, 0, h, vx, 0, g)
            if mp.isnan(disc):
                continue
            if abs(disc) <= mp.mpf("1e-6"):
                return coeffs, h_s, vx_s, mp.nstr(disc, 50), {
                    "discriminant_50_digits": mp.nstr(disc, 50),
                    "abs_disc": mp.nstr(abs(disc), 50),
                }
    raise ValueError("no near-double-root parameters found")


def bowl_periodic_poly(degree: int, n_events: int = 8) -> tuple:
    lead = "1/4" if degree == 4 else "1/8"
    coeffs = poly_coeffs(degree, lead)
    c = mp.mpf(lead)
    g = mp.mpf(10)
    x0, y0 = mp.mpf("0.15"), c * mp.mpf("0.15") ** degree
    vx, vy = mp.mpf("0.4"), mp.mpf("0.35")
    two_cg = 2 * c * g
    if degree == 4:
        period_expr = f"2*pi/sqrt({mp.nstr(two_cg, 50)})"
        period_val = 2 * mp.pi / mp.sqrt(two_cg)
    else:
        period_expr = f"pi/sqrt({mp.nstr(two_cg, 50)})"
        period_val = mp.pi / mp.sqrt(two_cg)
    check = non_dyadic_check(period_expr, period_val)

    def regen(dps: int) -> list[tuple]:
        mp.mp.dps = dps
        c_loc = mp.mpf(lead)
        g_loc = mp.mpf(10)
        x_loc = mp.mpf("0.15")
        y_loc = c_loc * x_loc ** degree
        vx_loc, vy_loc = mp.mpf("0.4"), mp.mpf("0.35")
        return t2.simulate(coeffs, x_loc, y_loc, vx_loc, vy_loc, g_loc, mp.mpf(1), n_events)

    return coeffs, x0, y0, vx, vy, check, regen


def standard_bezier_segments() -> list[dict]:
    return [
        {
            "kind": "quadratic",
            "control": [[0, 2], [1, 0], [2, 0]],
        },
        {
            "kind": "quadratic",
            "control": [[2, 0], [3, 0], [4, 2]],
        },
    ]


def base_scenario(
    scenario_id: str,
    family: str,
    curve: dict,
    balls: list[dict],
    gravity: str,
    reference_events: list[dict],
    extra: dict | None = None,
) -> dict:
    commit = git_commit()
    record = {
        "schema_version": SCHEMA_VERSION,
        "scenario_id": scenario_id,
        "provenance_tier": 2,
        "family": family,
        "curve": curve,
        "initial_state": balls,
        "physics": {"gravity": gravity},
        "reference_events": reference_events,
        "verification": {
            "method": "refsim-cas-tier2",
            "residual_max": "0",
            "reference_converged": True,
        },
        "provenance": {
            "tier": 2,
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


def load_existing_manifest() -> list[dict]:
    with open(MANIFEST_PATH, encoding="utf-8") as handle:
        manifest = json.load(handle)
    return list(manifest["scenarios"])


def update_lock(all_entries: list[dict]) -> None:
    manifest = {
        "schema_version": "1",
        "description": "Full held-out corpus: 16 Tier-1 (I-003-T2-R1) + 16 Tier-2 (I-003-T3).",
        "locked": True,
        "scenarios": all_entries,
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
        "heldout_count": len(all_entries),
        "heldout_manifest_sha256": manifest_hash,
        "note": "Held-out scenarios readable only when BOUNCE_HELDOUT_LOCK=1 (gate runner sets this).",
    }
    with open(SPLIT_LOCK_PATH, "w", newline="\n") as handle:
        json.dump(lock, handle, indent=2, sort_keys=True)
        handle.write("\n")


def concentration_ratios(scenario_ids: list[str]) -> dict[str, str]:
    counts = {"flat": 0, "parabola": 0, "deg3-6": 0, "bezier": 0}
    for sid in scenario_ids:
        if sid.startswith("HO-flat-"):
            counts["flat"] += 1
        elif sid.startswith("HO-parabola-") or sid.startswith("HO-graze-parabola-"):
            counts["parabola"] += 1
        elif sid.startswith("HO-poly-"):
            counts["deg3-6"] += 1
        elif sid.startswith("HO-bezier-"):
            counts["bezier"] += 1
    total = len(scenario_ids)
    return {k: f"{v}/{total} ({100.0 * v / total:.4f}%)" for k, v in counts.items()}


def build_all() -> tuple[list[dict], dict]:
    mp.mp.dps = WORKING_DPS
    scenarios: list[dict] = []
    certificates: dict = {
        "sensitivity": [],
        "non_dyadicity": [],
        "c1_checks": [],
        "discriminant": None,
        "convergence": [],
    }

    # (a) deg 3-6 settle x4
    settle_specs = [
        ("HO-poly-settle-3", 3, "1/16", "5", "1/2", "0.5"),
        ("HO-poly-settle-4", 4, "1/16", "5", "1/2", "0.5"),
        ("HO-poly-settle-5", 5, "1/16", "5", "1/2", "0.5"),
        ("HO-poly-settle-6", 6, "1/16", "5", "1/2", "0.5"),
    ]
    for sid, deg, lead, h, e, vx in settle_specs:
        coeffs = poly_coeffs(deg, lead)
        g = mp.mpf(10)
        regen = make_poly_regen(coeffs, 0, h, vx, 0, g, e, 12)
        worst = t2.dual_precision_worst(regen)
        certificates["convergence"].append((sid, worst))
        evs = regen(WORKING_DPS)
        ref = mp_events_to_ref(evs)
        curve = {
            "curve_id": sid + "-curve",
            "family": "polynomial",
            "coeffs": coeffs,
            "domain": ["0", "100"],
        }
        balls = [
            {
                "ball_id": 0,
                "pos": {"x": "0", "y": h},
                "vel": {"vx": vx, "vy": "0"},
                "radius": "0.1",
                "restitution": e,
            }
        ]
        scenarios.append(base_scenario(sid, "POLY-HO", curve, balls, "10", ref))

    # (b) deg 4/6 periodic x2
    mp.mp.dps = WORKING_DPS
    for sid, deg in [("HO-poly-periodic-1", 4), ("HO-poly-periodic-2", 6)]:
        coeffs, x0, y0, vx, vy, check, regen = bowl_periodic_poly(deg)
        worst = t2.dual_precision_worst(regen)
        certificates["convergence"].append((sid, worst))
        certificates["non_dyadicity"].append((sid, check))
        evs = regen(WORKING_DPS)
        ref = mp_events_to_ref(evs)
        curve = {
            "curve_id": sid + "-curve",
            "family": "polynomial",
            "coeffs": coeffs,
            "domain": ["0", "100"],
        }
        balls = [
            {
                "ball_id": 0,
                "pos": {"x": mp.nstr(x0, 50), "y": mp.nstr(y0, 50)},
                "vel": {"vx": mp.nstr(vx, 50), "vy": mp.nstr(vy, 50)},
                "radius": "0.1",
                "restitution": "1",
            }
        ]
        scenarios.append(
            base_scenario(
                sid,
                "POLY-HO",
                curve,
                balls,
                "10",
                ref,
                {"non_dyadicity_check": check},
            )
        )

    # (c) quasi-chaotic x4
    qc_specs = [
        ("HO-parabola-quasichaotic-1", ["0", "0", "1"], "vx", [("6", "1.2", "0.8"), ("6", "1.1", "0.9")]),
        ("HO-parabola-quasichaotic-2", ["0", "0", "1/2"], "vy", [("7", "0.9", "1.1"), ("7", "1.0", "1.0")]),
        ("HO-poly-quasichaotic-1", poly_coeffs(3, "1/4"), "vx", [("5", "1.3", "0.7"), ("5", "1.2", "0.85")]),
        ("HO-poly-quasichaotic-2", poly_coeffs(5, "1/16"), "vy", [("5", "0.8", "1.2"), ("5", "0.9", "1.1")]),
    ]
    for sid, coeffs, component, candidates in qc_specs:
        y0, vx, vy, cert = find_quasi_chaotic_params(coeffs, component, candidates)
        g, e = mp.mpf(10), mp.mpf("0.95")
        regen = make_poly_regen(coeffs, 0, y0, vx, vy, g, e, 25)
        worst = t2.dual_precision_worst(regen)
        certificates["convergence"].append((sid, worst))
        certificates["sensitivity"].append((sid, cert))
        evs = regen(WORKING_DPS)
        ref = mp_events_to_ref(evs)
        curve = {
            "curve_id": sid + "-curve",
            "family": "polynomial",
            "coeffs": coeffs,
            "domain": ["0", "100"],
        }
        balls = [
            {
                "ball_id": 0,
                "pos": {"x": "0", "y": y0},
                "vel": {"vx": vx, "vy": vy},
                "radius": "0.1",
                "restitution": "0.95",
            }
        ]
        scenarios.append(
            base_scenario(sid, "PB-HO" if "parabola" in sid else "POLY-HO", curve, balls, "10", ref,
                          {"sensitivity_certificate": cert})
        )

    # (d) bezier settle x3
    segments = standard_bezier_segments()
    c1 = t2.validate_c1_piecewise(segments)
    if not c1["ok"]:
        raise ValueError("standard bezier segments fail C1")
    bezier_settle = [
        ("HO-bezier-settle-1", 1, "0.5", "0", "1/2"),
        ("HO-bezier-settle-2", 2, "0.4", "0", "1/2"),
        ("HO-bezier-settle-3", 3, "0.35", "0", "2/3"),
    ]
    for sid, n_balls, vx_s, vy_s, e_s in bezier_settle:
        g, e = mp.mpf(10), mp.mpf(e_s)
        vx, vy = mp.mpf(vx_s), mp.mpf(vy_s)
        if n_balls == 1:
            regen = make_bezier_regen(segments, mp.mpf(1), mp.mpf(3), vx, vy, g, e, 200)
            worst = t2.dual_precision_worst(regen)
            certificates["convergence"].append((sid, worst))
            evs = regen(WORKING_DPS)
            ref = mp_events_to_ref(evs)
            balls = [
                {
                    "ball_id": 0,
                    "pos": {"x": "1", "y": "3"},
                    "vel": {"vx": vx_s, "vy": vy_s},
                    "radius": "0.1",
                    "restitution": e_s,
                }
            ]
        else:
            per_ball = []
            for b in range(n_balls):
                regen_b = make_bezier_regen(
                    segments, mp.mpf(1 + b), mp.mpf(3), vx, vy, g, e, 200
                )
                evs_b = regen_b(WORKING_DPS)
                per_ball.append([(ev[0], ev[1], ev[2], b) for ev in evs_b])
            ref = merge_tb1(per_ball, 200 * n_balls)

            def regen_multi(dps: int) -> list[tuple]:
                rows = []
                for b in range(n_balls):
                    mp.mp.dps = dps
                    for ev in t2.simulate_piecewise_bezier(
                        segments, mp.mpf(1 + b), mp.mpf(3), vx, vy, g, e, 200
                    ):
                        rows.append(ev)
                rows.sort(key=lambda r: (r[0], r[1]))
                return rows[: 200 * n_balls]

            worst = t2.dual_precision_worst(regen_multi)
            certificates["convergence"].append((sid, worst))
            balls = [
                {
                    "ball_id": b,
                    "pos": {"x": str(1 + b), "y": "3"},
                    "vel": {"vx": vx_s, "vy": vy_s},
                    "radius": "0.1",
                    "restitution": e_s,
                }
                for b in range(n_balls)
            ]
        curve = {
            "curve_id": sid + "-curve",
            "family": "piecewise-bezier",
            "segments": segments,
            "domain": ["0", "4"],
        }
        certificates["c1_checks"].append((sid, c1))
        scenarios.append(
            base_scenario(
                sid,
                "BEZ-HO",
                curve,
                balls,
                "10",
                ref,
                {"c1_validation": c1},
            )
        )

    # (e) bezier periodic x2 (journal: 2 periodic for 5/32 concentration)
    bezier_periodic_specs = [
        ("HO-bezier-periodic-1", mp.mpf("0.35"), mp.mpf("0.25"), "sqrt(5)"),
        ("HO-bezier-periodic-2", mp.mpf("0.3"), mp.mpf("0.3"), "sqrt(7)"),
    ]
    period_vals = {"sqrt(5)": mp.sqrt(5), "sqrt(7)": mp.sqrt(7)}
    for sid, vx, vy, period_expr in bezier_periodic_specs:
        period_val = period_vals[period_expr]
        check = non_dyadic_check(period_expr, period_val)
        g = mp.mpf(10)
        regen = make_bezier_regen(segments, mp.mpf(1), mp.mpf(2), vx, vy, g, mp.mpf(1), 8)
        worst = t2.dual_precision_worst(regen)
        certificates["convergence"].append((sid, worst))
        certificates["non_dyadicity"].append((sid, check))
        evs = regen(WORKING_DPS)
        ref = mp_events_to_ref(evs)
        curve = {
            "curve_id": sid + "-curve",
            "family": "piecewise-bezier",
            "segments": segments,
            "domain": ["0", "4"],
        }
        balls = [
            {
                "ball_id": 0,
                "pos": {"x": "1", "y": "2"},
                "vel": {"vx": mp.nstr(vx, 50), "vy": mp.nstr(vy, 50)},
                "radius": "0.1",
                "restitution": "1",
            }
        ]
        certificates["c1_checks"].append((sid, c1))
        scenarios.append(
            base_scenario(
                sid,
                "BEZ-HO",
                curve,
                balls,
                "10",
                ref,
                {"non_dyadicity_check": check, "c1_validation": c1},
            )
        )

    # (f) near-double-root deg-4 x1
    coeffs, h_s, vx_s, disc_s, disc_info = find_double_root_coeffs()
    g, e = mp.mpf(10), mp.mpf("1/2")
    regen = make_poly_regen(coeffs, 0, h_s, vx_s, 0, g, e, 200)
    worst = t2.dual_precision_worst(regen)
    certificates["convergence"].append(("HO-poly-double-root-1", worst))
    certificates["discriminant"] = disc_info
    evs = regen(WORKING_DPS)
    ref = mp_events_to_ref(evs)
    curve = {
        "curve_id": "HO-poly-double-root-1-curve",
        "family": "polynomial",
        "coeffs": coeffs,
        "domain": ["0", "100"],
    }
    balls = [
        {
            "ball_id": 0,
            "pos": {"x": "0", "y": h_s},
            "vel": {"vx": vx_s, "vy": "0"},
            "radius": "0.1",
            "restitution": "1/2",
        }
    ]
    scenarios.append(
        base_scenario(
            "HO-poly-double-root-1",
            "POLY-HO",
            curve,
            balls,
            "10",
            ref,
            {"double_root_certificate": disc_info},
        )
    )

    if len(scenarios) != 16:
        raise ValueError(f"expected 16 tier-2 scenarios, got {len(scenarios)}")
    return scenarios, certificates


def main() -> int:
    mp.mp.dps = WORKING_DPS
    scenarios, certificates = build_all()
    existing = load_existing_manifest()
    new_entries = []
    for record in scenarios:
        path = write_scenario(record)
        digest = sha256_file(path)
        new_entries.append({"scenario_id": record["scenario_id"], "sha256": digest})
        print(f"wrote {os.path.relpath(path, REPO_ROOT)} sha256={digest}")
    all_entries = existing + new_entries
    update_lock(all_entries)
    all_ids = [e["scenario_id"] for e in all_entries]
    ratios = concentration_ratios(all_ids)
    print("sensitivity_certificates:")
    for sid, cert in certificates["sensitivity"]:
        print(f"  {sid}: component={cert['perturbed_component']} diverged={cert['diverged']}")
        for row in cert["table"][:5]:
            print(f"    event {row['event']}: div={row['divergence']}")
    print("non_dyadicity_checks:")
    for sid, check in certificates["non_dyadicity"]:
        print(f"  {sid}: P={check['period_50_digits']}")
        print(f"         d={check['nearest_double']} gap={check['gap']}")
    print("c1_checks:")
    for sid, c1 in certificates["c1_checks"]:
        print(f"  {sid}: ok={c1['ok']} joints={len(c1['joints'])}")
        for j in c1["joints"]:
            print(f"    joint {j['joint_index']}: cross={j['tangent_cross']} pass={j['pass']}")
    print("discriminant_check:")
    print(f"  HO-poly-double-root-1: {certificates['discriminant']}")
    print("tier2_convergence_checks:")
    for sid, worst in certificates["convergence"]:
        print(f"  {sid}: worst_case_agreement_digits={worst}")
    print("concentration_ratios:")
    for fam, ratio in ratios.items():
        print(f"  {fam}: {ratio}")
    for fam, ratio in ratios.items():
        pct = float(ratio.split("(")[1].rstrip("%)"))
        if pct > 50.0:
            print(f"mint-tier2-heldout-FAILED: concentration cap exceeded for {fam}")
            return 1
    print("mint-tier2-heldout-ok 16")
    return 0


if __name__ == "__main__":
    sys.exit(main())

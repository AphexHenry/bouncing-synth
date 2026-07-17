#!/usr/bin/env python3
"""Tier-1 closed-form fixture generator (I-002-T2, DELIVERABLE_B section 6 Tier-1).

Fixtures are constructed so gate-bearing quantities (event times, contact points)
are exact rationals -- dyadic where multi-bounce exactness is claimed -- and
verified with exact rational arithmetic (fractions.Fraction). stdlib only; the
high-precision oracle is Tier-2 (T3). Deterministic output: sorted keys, exact
rational strings, LF line endings.
"""
from fractions import Fraction as F
import json
import os

OUT_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fixtures")


def is_dyadic(q):
    d = q.denominator
    while d % 2 == 0:
        d //= 2
    return d == 1


def float_exact(q):
    return F(float(q)) == q


def fmt(q):
    return str(q)  # Fraction str: "5" or "11/4" -- exact by construction


def fl1():
    """FL-1: flat line y=0, drop from (0,h), restitution e, horizontal speed vx.
    Constructed so t1 = sqrt(2h/g) is exactly 1 and all bounce times are dyadic."""
    h, g, e, vx, n_events = F(5), F(10), F(1, 2), F(1), 8
    t1_sq = 2 * h / g
    assert t1_sq == 1, "construction requires t1 == 1 exactly"
    t1 = F(1)
    times = [t1]
    v = g * t1  # impact speed before first bounce
    t = t1
    while len(times) < n_events:
        v = e * v            # post-bounce vertical speed
        t = t + 2 * v / g    # next impact time
        times.append(t)
    # symbolic verification: replay y(t) across arcs; residual must be exactly 0
    residuals = []
    t_prev, v_prev = t1, e * g * t1
    for tk in times[1:]:
        dt = tk - t_prev
        y = v_prev * dt - g * dt * dt / 2
        residuals.append(y)  # must be exactly 0 at impact
        t_prev, v_prev = tk, e * (v_prev)  # speed at impact equals launch speed
    assert all(r == 0 for r in residuals)
    fixture = {
        "family": "FL-1",
        "id": "FL-1-h5-g10-e1o2",
        "curve": {"kind": "polynomial", "coeffs": ["0"]},
        "params": {"h": fmt(h), "g": fmt(g), "e": fmt(e), "vx": fmt(vx)},
        "events": [
            {"t": fmt(tk), "t_float": float(tk).hex(), "x": fmt(vx * tk)}
            for tk in times
        ],
        "claims": {
            "dyadic": all(is_dyadic(tk) for tk in times),
            "float_exact": all(float_exact(tk) for tk in times),
        },
        "verification": {"method": "exact-rational", "residual_max": "0"},
    }
    return fixture, times


def pb1():
    """PB-1: flight parabola onto curve y = c*x^2. Constructed so the first
    contact time and point are exact integers; later events (irrational normal)
    belong to Tier-2."""
    h, g, c, vx = F(9), F(16), F(1), F(1)
    denom = g / 2 + c * vx * vx
    t1_sq = h / denom
    assert t1_sq == 1
    t1 = F(1)
    x1, y1 = vx * t1, h - g * t1 * t1 / 2
    residual = y1 - c * x1 * x1
    assert residual == 0
    fixture = {
        "family": "PB-1",
        "id": "PB-1-h9-g16-c1",
        "curve": {"kind": "polynomial", "coeffs": ["0", "0", "1"]},
        "params": {"h": fmt(h), "g": fmt(g), "c": fmt(c), "vx": fmt(vx)},
        "events": [{"t": fmt(t1), "t_float": float(t1).hex(),
                    "contact": [fmt(x1), fmt(y1)]}],
        "claims": {"dyadic": is_dyadic(t1), "float_exact": float_exact(t1)},
        "verification": {"method": "exact-rational", "residual_max": "0"},
    }
    return fixture, t1, (x1, y1), residual


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    fl_fixture, fl_times = fl1()
    pb_fixture, pb_t1, pb_contact, pb_res = pb1()
    for fx in (fl_fixture, pb_fixture):
        path = os.path.join(OUT_DIR, fx["id"] + ".json")
        with open(path, "w", newline="\n") as f:
            json.dump(fx, f, indent=2, sort_keys=True)
            f.write("\n")
    print("FL-1 t=[%s] dyadic=%s float-exact=%s residual-max=0"
          % (", ".join(fmt(t) for t in fl_times),
             fl_fixture["claims"]["dyadic"], fl_fixture["claims"]["float_exact"]))
    print("PB-1 t1=%s contact=(%s, %s) residual=%s"
          % (fmt(pb_t1), fmt(pb_contact[0]), fmt(pb_contact[1]), fmt(pb_res)))
    print("tier1-fixtures-ok 2")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Tier-2 high-precision reference simulator (I-002-T3b, DELIVERABLE_B section 6 Tier-2).

Algorithm-identity with bounce-core: VCA root isolation + fixed refinement schedule,
G-1/S-1 contact rules, TB-1 version string. Point-contact ball (R1) on polynomial
curves y = p(x); ballistic flight; collision = smallest admissible root of
q(t) = y(t) - p(x(t)); reflection about the curve normal with restitution along
the normal component. All arithmetic mpmath at the requested working precision.
reference_converged: event sequence at dps agrees with 2*dps to agree_digits.
"""
import mpmath as mp

# Pre-registered contact-rule constants (DELIVERABLE_B section 3, order 1e-9 m/s).
V_GRAZE = mp.mpf("1e-9")
V_SETTLE = mp.mpf("1e-9")
TIE_BREAK_VERSION = "TB-1"
CONTACT_RULE_VERSION = "G-1/S-1"

# Fixed refinement schedule (DELIVERABLE_B section 3).
BISECT_BITS = 40
NEWTON_STEPS = 3


def poly_eval(coeffs, x):
    acc = mp.mpf(0)
    for c in reversed(coeffs):
        acc = acc * x + c
    return acc


def poly_deriv(coeffs):
    return [c * k for k, c in enumerate(coeffs)][1:] or [mp.mpf(0)]


def collision_poly(coeffs, x0, y0, vx, vy, g):
    px = [mp.mpf(0)]
    for c in reversed(coeffs):
        new = [mp.mpf(0)] * (len(px) + 1)
        for k, pk in enumerate(px):
            new[k] += pk * x0
            new[k + 1] += pk * vx
        new[0] += c
        px = new
    q = [-c for c in px]
    q[0] += y0
    if len(q) < 2:
        q += [mp.mpf(0)]
    if len(q) < 3:
        q += [mp.mpf(0)]
    q[1] += vy
    q[2] -= g / 2
    while len(q) > 1 and q[-1] == 0:
        q.pop()
    return q


def has_root_in_interval(coeffs, lo, hi):
    pl = poly_eval(coeffs, lo)
    pr = poly_eval(coeffs, hi)
    if pl == 0 or pr == 0:
        return True
    if pl * pr > 0:
        return False
    if hi - lo <= mp.mpf(10) ** (-(mp.mp.dps - 5)):
        return True
    mid = (lo + hi) / 2
    pm = poly_eval(coeffs, mid)
    if pm == 0:
        return True
    return has_root_in_interval(coeffs, lo, mid) or has_root_in_interval(coeffs, mid, hi)


def refine_root(q, lo, hi):
    scale = hi - lo
    target = scale * mp.mpf(2) ** (-BISECT_BITS)
    a, b = lo, hi
    fa = poly_eval(q, a)
    fb = poly_eval(q, b)
    while b - a > target:
        m = (a + b) / 2
        fm = poly_eval(q, m)
        if fm == 0:
            a = b = m
            break
        if fa * fm <= 0:
            b, fb = m, fm
        else:
            a, fa = m, fm
    t = (a + b) / 2
    dq = poly_deriv(q)
    for _ in range(NEWTON_STEPS):
        ft = poly_eval(q, t)
        dft = poly_eval(dq, t)
        if dft == 0:
            break
        t = t - ft / dft
        if t < lo:
            t = lo
        elif t > hi:
            t = hi
    return t


def isolate_smallest_positive_root(q, t_min, t_max):
    deg = len(q) - 1
    if deg < 1:
        return None
    nseg = max(16, deg * 8)
    step = (t_max - t_min) / nseg
    brackets = []
    prev_t = t_min
    prev_v = poly_eval(q, prev_t)
    for i in range(1, nseg + 1):
        t = t_min + step * i
        v = poly_eval(q, t)
        if prev_v == 0:
            brackets.append((prev_t, prev_t))
        elif v == 0:
            brackets.append((t, t))
        elif prev_v * v < 0 and has_root_in_interval(q, prev_t, t):
            brackets.append((prev_t, t))
        prev_t, prev_v = t, v
    if not brackets:
        return None
    lo, hi = brackets[0]
    return refine_root(q, lo, hi)


def curve_normal(coeffs, xc):
    dp = poly_eval(poly_deriv(coeffs), xc)
    nx, ny = -dp, mp.mpf(1)
    nn = mp.sqrt(nx * nx + ny * ny)
    return nx / nn, ny / nn


def normal_impact_speed(coeffs, xc, vx, vy):
    nx, ny = curve_normal(coeffs, xc)
    return abs(vx * nx + vy * ny)


def reflect(coeffs, xc, vx, vy, e):
    nx, ny = curve_normal(coeffs, xc)
    vn = vx * nx + vy * ny
    vx_out = vx - (1 + e) * vn * nx
    vy_out = vy - (1 + e) * vn * ny
    return vx_out, vy_out, abs(vn)


def simulate(curve_coeffs, x0, y0, vx, vy, g, e, n_events):
    coeffs = [mp.mpf(c) for c in curve_coeffs]
    x0, y0, vx, vy, g, e = (mp.mpf(v) for v in (x0, y0, vx, vy, g, e))
    events = []
    t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
    t_max = mp.mpf(1000)
    settled = False
    for _ in range(n_events):
        if settled:
            break
        q = collision_poly(coeffs, x0, y0, vx, vy, g)
        dt = isolate_smallest_positive_root(q, t_min, t_max)
        if dt is None:
            break
        xc = x0 + vx * dt
        yc = poly_eval(coeffs, xc)
        vyf = vy - g * dt
        vn_in = normal_impact_speed(coeffs, xc, vx, vyf)
        if vn_in < V_GRAZE:
            x0, y0 = xc, yc
            vy = vyf
            t_min = dt + mp.mpf(10) ** (-(mp.mp.dps - 10))
            continue
        t_abs = (events[-1][0] + dt) if events else dt
        events.append((t_abs, xc, yc))
        vx, vy, vn_out = reflect(coeffs, xc, vx, vyf, e)
        if vn_out < V_SETTLE:
            settled = True
            break
        x0, y0 = xc, yc
        t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
    return events


def run_case(name, curve, x0, y0, vx, vy, g, e, n_events, dps, agree_digits):
    mp.mp.dps = dps
    ev1 = simulate(curve, x0, y0, vx, vy, g, e, n_events)
    mp.mp.dps = 2 * dps
    ev2 = simulate(curve, x0, y0, vx, vy, g, e, n_events)
    mp.mp.dps = dps
    conv = len(ev1) == len(ev2) and all(
        abs(a[0] - b[0]) < mp.mpf(10) ** (-agree_digits)
        and abs(a[1] - b[1]) < mp.mpf(10) ** (-agree_digits)
        for a, b in zip(ev1, ev2)
    )
    ts = ", ".join(mp.nstr(t, 12) for t, _, _ in ev1)
    print("%s events=%d reference_converged=%s t=[%s]"
          % (name, len(ev1), conv, ts))
    return ev1, conv


def main():
    print("algorithm=%s tie_break=%s contact_rules=%s"
          % ("VCA+fixed-refinement", TIE_BREAK_VERSION, CONTACT_RULE_VERSION))
    dps, agree = 50, 40
    fl_events, fl_conv = run_case(
        "FL-1", ["0"], 0, 5, 1, 0, 10, mp.mpf(1) / 2, 8, dps, agree)
    exact = [mp.mpf(s) for s in
             ("1", "2", "2.5", "2.75", "2.875", "2.9375", "2.96875", "2.984375")]
    fl_err = max(abs(t - x) for (t, _, _), x in zip(fl_events, exact))
    print("FL-1 max|t - tier1_exact| < 1e-45: %s" % (fl_err < mp.mpf(10) ** -45))
    pb_events, pb_conv = run_case(
        "PB-1", ["0", "0", "1"], 0, 9, 1, 0, 16, mp.mpf(1) / 2, 4, dps, agree)
    t1, x1, y1 = pb_events[0]
    pb_err = max(abs(t1 - 1), abs(x1 - 1), abs(y1 - 1))
    print("PB-1 first-contact |err| < 1e-45: %s" % (pb_err < mp.mpf(10) ** -45))
    ok = fl_conv and pb_conv and fl_err < mp.mpf(10) ** -45 and pb_err < mp.mpf(10) ** -45
    print("tier2-refsim-ok" if ok else "tier2-refsim-FAILED")


if __name__ == "__main__":
    main()

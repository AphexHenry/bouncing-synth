#!/usr/bin/env python3
"""Tier-2 high-precision reference simulator (I-002-T3a, DELIVERABLE_B section 6 Tier-2).

Scope T3a: point-contact ball (R1) on a polynomial curve y = p(x); ballistic
flight x(t) = x0 + vx*t, y(t) = y0 + vy*t - g*t^2/2; collision = smallest
admissible root of q(t) = y(t) - p(x(t)); reflection about the curve normal
with restitution e along the normal component. All arithmetic mpmath at the
requested working precision. reference_converged: the event sequence is
computed at dps and at 2*dps and must agree to `agree_digits` digits.

Deferred to T3b (algorithm-identity with bounce-core): VCA root isolation with
the fixed refinement schedule, and the TB-1/G-1/S-1 versioned rules (tie-break,
grazing, settle). T3a fixtures are constructed to avoid those regimes.
"""
import mpmath as mp


def poly_eval(coeffs, x):
    # coeffs ascending: p(x) = c0 + c1*x + c2*x^2 + ...
    acc = mp.mpf(0)
    for c in reversed(coeffs):
        acc = acc * x + c
    return acc


def poly_deriv(coeffs):
    return [c * k for k, c in enumerate(coeffs)][1:] or [mp.mpf(0)]


def collision_poly(coeffs, x0, y0, vx, vy, g):
    """q(t) = y(t) - p(x(t)) as ascending mpf coefficients in t."""
    # x(t) = x0 + vx t  -> build p(x(t)) by Horner on polynomial (a + b t)
    px = [mp.mpf(0)]
    for c in reversed(coeffs):
        # px = px*(x0 + vx t) + c
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


def smallest_positive_root(q, t_min):
    deg = len(q) - 1
    if deg < 1:
        return None
    roots = mp.polyroots(list(reversed(q)), maxsteps=200, extraprec=mp.mp.dps)
    best = None
    tol = mp.mpf(10) ** (-(mp.mp.dps - 10))
    for r in roots:
        if abs(mp.im(r)) < tol:
            t = mp.re(r)
            if t > t_min and (best is None or t < best):
                best = t
    return best


def simulate(curve_coeffs, x0, y0, vx, vy, g, e, n_events):
    coeffs = [mp.mpf(c) for c in curve_coeffs]
    x0, y0, vx, vy, g, e = (mp.mpf(v) for v in (x0, y0, vx, vy, g, e))
    events = []
    t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
    for _ in range(n_events):
        q = collision_poly(coeffs, x0, y0, vx, vy, g)
        dt = smallest_positive_root(q, t_min)
        if dt is None:
            break
        xc = x0 + vx * dt
        yc = y0 + vy * dt - g * dt * dt / 2
        vyf = vy - g * dt
        t_abs = (events[-1][0] + dt) if events else dt
        events.append((t_abs, xc, yc))
        # reflect (vx, vyf) about the normal of F(x,y)=y-p(x): n = (-p'(x), 1)
        dp = poly_eval(poly_deriv(coeffs), xc)
        nx, ny = -dp, mp.mpf(1)
        nn = nx * nx + ny * ny
        vn = (vx * nx + vyf * ny) / nn
        vx = vx - (1 + e) * vn * nx
        vy = vyf - (1 + e) * vn * ny
        x0, y0 = xc, yc
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
    dps, agree = 50, 40
    # FL-1: exact dyadic ground truth from Tier-1
    fl_events, fl_conv = run_case(
        "FL-1", ["0"], 0, 5, 1, 0, 10, mp.mpf(1) / 2, 8, dps, agree)
    exact = [mp.mpf(s) for s in
             ("1", "2", "2.5", "2.75", "2.875", "2.9375", "2.96875", "2.984375")]
    fl_err = max(abs(t - x) for (t, _, _), x in zip(fl_events, exact))
    print("FL-1 max|t - tier1_exact| < 1e-45: %s" % (fl_err < mp.mpf(10) ** -45))
    # PB-1: first contact exact from Tier-1
    pb_events, pb_conv = run_case(
        "PB-1", ["0", "0", "1"], 0, 9, 1, 0, 16, mp.mpf(1) / 2, 4, dps, agree)
    t1, x1, y1 = pb_events[0]
    pb_err = max(abs(t1 - 1), abs(x1 - 1), abs(y1 - 1))
    print("PB-1 first-contact |err| < 1e-45: %s" % (pb_err < mp.mpf(10) ** -45))
    ok = fl_conv and pb_conv and fl_err < mp.mpf(10) ** -45 and pb_err < mp.mpf(10) ** -45
    print("tier2-refsim-ok" if ok else "tier2-refsim-FAILED")


if __name__ == "__main__":
    main()

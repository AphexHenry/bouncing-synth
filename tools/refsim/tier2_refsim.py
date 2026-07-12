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


# --- Piecewise Bézier extension (I-003-T3; mirrors C-002-T2 bezier.hpp semantics) ---

def _pt(x, y):
    return (mp.mpf(x), mp.mpf(y))


def bezier_eval_quad(p0, p1, p2, s):
    u = mp.mpf(1) - s
    w0, w1, w2 = u * u, 2 * u * s, s * s
    return (
        w0 * p0[0] + w1 * p1[0] + w2 * p2[0],
        w0 * p0[1] + w1 * p1[1] + w2 * p2[1],
    )


def bezier_eval_cubic(p0, p1, p2, p3, s):
    u = mp.mpf(1) - s
    w0, w1, w2, w3 = u * u * u, 3 * u * u * s, 3 * u * s * s, s * s * s
    return (
        w0 * p0[0] + w1 * p1[0] + w2 * p2[0] + w3 * p3[0],
        w0 * p0[1] + w1 * p1[1] + w2 * p2[1] + w3 * p3[1],
    )


def bezier_deriv_quad(p0, p1, p2, s):
    u = mp.mpf(1) - s
    return (
        2 * u * (p1[0] - p0[0]) + 2 * s * (p2[0] - p1[0]),
        2 * u * (p1[1] - p0[1]) + 2 * s * (p2[1] - p1[1]),
    )


def bezier_deriv_cubic(p0, p1, p2, p3, s):
    u = mp.mpf(1) - s
    return (
        3 * u * u * (p1[0] - p0[0]) + 6 * u * s * (p2[0] - p1[0]) + 3 * s * s * (p3[0] - p2[0]),
        3 * u * u * (p1[1] - p0[1]) + 6 * u * s * (p2[1] - p1[1]) + 3 * s * s * (p3[1] - p2[1]),
    )


def bezier_eval_segment(seg, s):
    kind = seg["kind"]
    c = [_pt(*p) for p in seg["control"]]
    if kind == "quadratic":
        return bezier_eval_quad(c[0], c[1], c[2], s)
    if kind == "cubic":
        return bezier_eval_cubic(c[0], c[1], c[2], c[3], s)
    raise ValueError(f"unknown bezier kind: {kind}")


def bezier_deriv_segment(seg, s):
    kind = seg["kind"]
    c = [_pt(*p) for p in seg["control"]]
    if kind == "quadratic":
        return bezier_deriv_quad(c[0], c[1], c[2], s)
    if kind == "cubic":
        return bezier_deriv_cubic(c[0], c[1], c[2], c[3], s)
    raise ValueError(f"unknown bezier kind: {kind}")


def validate_c1_piecewise(segments):
    """C1 check at 50 digits: position match + tangent cross product zero at joints."""
    if len(segments) <= 1:
        return {"ok": True, "joints": []}
    joints = []
    for i in range(1, len(segments)):
        left, right = segments[i - 1], segments[i]
        end_pos = bezier_eval_segment(left, mp.mpf(1))
        start_pos = bezier_eval_segment(right, mp.mpf(0))
        pos_delta = (
            abs(end_pos[0] - start_pos[0]),
            abs(end_pos[1] - start_pos[1]),
        )
        end_tan = bezier_deriv_segment(left, mp.mpf(1))
        start_tan = bezier_deriv_segment(right, mp.mpf(0))
        cross = end_tan[0] * start_tan[1] - end_tan[1] * start_tan[0]
        joint = {
            "joint_index": i - 1,
            "pos_delta_x": mp.nstr(pos_delta[0], 50),
            "pos_delta_y": mp.nstr(pos_delta[1], 50),
            "tangent_cross": mp.nstr(cross, 50),
            "pass": pos_delta[0] <= mp.mpf("1e-45")
            and pos_delta[1] <= mp.mpf("1e-45")
            and abs(cross) <= mp.mpf("1e-45"),
        }
        joints.append(joint)
        if not joint["pass"]:
            return {"ok": False, "joints": joints}
    return {"ok": True, "joints": joints}


def invert_x_on_segment(seg, x_target, lo=mp.mpf(0), hi=mp.mpf(1)):
    """Solve x(s)=x_target on a segment with monotonic x in s."""
    x_lo = bezier_eval_segment(seg, lo)[0]
    x_hi = bezier_eval_segment(seg, hi)[0]
    if x_target < min(x_lo, x_hi) or x_target > max(x_lo, x_hi):
        return None
    a, b = lo, hi
    for _ in range(max(200, mp.mp.dps * 2)):
        m = (a + b) / 2
        xm = bezier_eval_segment(seg, m)[0]
        if xm == x_target:
            return m
        if (xm - x_target) * (x_lo - x_target) <= 0:
            b, x_hi = m, xm
        else:
            a, x_lo = m, xm
    return (a + b) / 2


def y_at_x_bezier(segments, x_target):
    for seg in segments:
        x0 = bezier_eval_segment(seg, mp.mpf(0))[0]
        x1 = bezier_eval_segment(seg, mp.mpf(1))[0]
        if x_target < min(x0, x1) - mp.mpf("1e-40") or x_target > max(x0, x1) + mp.mpf("1e-40"):
            continue
        s = invert_x_on_segment(seg, x_target)
        if s is None:
            continue
        return bezier_eval_segment(seg, s)[1]
    return None


def bezier_curve_normal(seg, s):
    d = bezier_deriv_segment(seg, s)
    nx, ny = -d[1], d[0]
    nn = mp.sqrt(nx * nx + ny * ny)
    if nn == 0:
        return mp.mpf(0), mp.mpf(1)
    return nx / nn, ny / nn


def find_s_for_x(segments, x_pos):
    for idx, seg in enumerate(segments):
        s = invert_x_on_segment(seg, x_pos)
        if s is not None:
            return idx, s
    return None, None


def collision_poly_bezier(segments, x0, y0, vx, vy, g):
    """q(t) = y_ball(t) - y_curve(x_ball(t)) sampled as polynomial in t via series."""
    # Build q(t) by composing ballistic x(t) with y(x) on the active segment domain.
    # For segments with monotonic x, use implicit root finding on t directly.
    t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
    t_max = mp.mpf(50)
    nseg = max(64, mp.mp.dps)
    step = (t_max - t_min) / nseg
    brackets = []
    prev_t = t_min
    prev_v = y0 + vy * prev_t - g * prev_t * prev_t / 2 - y_at_x_bezier(
        segments, x0 + vx * prev_t
    )
    for i in range(1, nseg + 1):
        t = t_min + step * i
        xb = x0 + vx * t
        yc = y_at_x_bezier(segments, xb)
        if yc is None:
            prev_t, prev_v = t, mp.mpf(1)
            continue
        v = y0 + vy * t - g * t * t / 2 - yc
        if prev_v == 0:
            brackets.append((prev_t, prev_t))
        elif v == 0:
            brackets.append((t, t))
        elif prev_v * v < 0:
            brackets.append((prev_t, t))
        prev_t, prev_v = t, v
    if not brackets:
        return None, None
    lo, hi = brackets[0]
    for _ in range(max(120, mp.mp.dps * 2)):
        m = (lo + hi) / 2
        xb = x0 + vx * m
        yc = y_at_x_bezier(segments, xb)
        if yc is None:
            break
        fm = y0 + vy * m - g * m * m / 2 - yc
        if fm == 0:
            return m, xb
        flo = y0 + vy * lo - g * lo * lo / 2 - y_at_x_bezier(segments, x0 + vx * lo)
        if flo * fm <= 0:
            hi = m
        else:
            lo = m
    t_hit = (lo + hi) / 2
    return _refine_bezier_collision_time(segments, x0, y0, vx, vy, g, t_hit)


def _bezier_height_at_t(segments, x0, y0, vx, vy, g, t):
    xb = x0 + vx * t
    yc = y_at_x_bezier(segments, xb)
    if yc is None:
        return None
    return y0 + vy * t - g * t * t / 2 - yc


def _refine_bezier_collision_time(segments, x0, y0, vx, vy, g, t0):
    """Newton polish on y_ball(t) - y_curve(x(t)) after bracketing."""
    t = mp.mpf(t0)
    for _ in range(max(12, mp.mp.dps // 4)):
        f = _bezier_height_at_t(segments, x0, y0, vx, vy, g, t)
        if f is None:
            break
        if f == 0:
            break
        dt = mp.mpf("1e-6")
        fp = _bezier_height_at_t(segments, x0, y0, vx, vy, g, t + dt)
        fm = _bezier_height_at_t(segments, x0, y0, vx, vy, g, t - dt)
        if fp is None or fm is None:
            break
        deriv = (fp - fm) / (2 * dt)
        if deriv == 0:
            break
        step = f / deriv
        t_next = t - step
        if t_next <= 0:
            break
        if abs(step) <= mp.mpf(10) ** (-(mp.mp.dps - 5)):
            t = t_next
            break
        t = t_next
    return t, x0 + vx * t


def simulate_piecewise_bezier(segments, x0, y0, vx, vy, g, e, n_events):
    x0, y0, vx, vy, g, e = (mp.mpf(v) for v in (x0, y0, vx, vy, g, e))
    events = []
    t_abs = mp.mpf(0)
    settled = False
    t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
    for _ in range(n_events):
        if settled:
            break
        dt, xc = collision_poly_bezier(segments, x0, y0, vx, vy, g)
        if dt is None or dt <= t_min:
            break
        seg_idx, s_hit = find_s_for_x(segments, xc)
        if seg_idx is None:
            break
        seg = segments[seg_idx]
        yc = bezier_eval_segment(seg, s_hit)[1]
        vyf = vy - g * dt
        nx, ny = bezier_curve_normal(seg, s_hit)
        vn_in = abs(vx * nx + vyf * ny)
        if vn_in < V_GRAZE:
            x0, y0 = xc, yc
            vy = vyf
            t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
            continue
        t_abs = t_abs + dt
        events.append((t_abs, xc, yc))
        vn = vx * nx + vyf * ny
        vx = vx - (1 + e) * vn * nx
        vy = vyf - (1 + e) * vn * ny
        vn_out = abs(vx * nx + vy * ny)
        x0, y0 = xc, yc
        if vn_out < V_SETTLE:
            settled = True
            break
        t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
    return events


def agreement_digits(a, b):
    if a == b:
        return 100.0
    diff = abs(a - b)
    if diff == 0:
        return 100.0
    scale = max(abs(a), abs(b), mp.mpf(1))
    rel = diff / scale
    if rel == 0:
        return 100.0
    return float(-mp.log10(rel))


def dual_precision_worst(regen, dps_lo=50, dps_hi=100):
    ev_lo = regen(dps_lo)
    ev_hi = regen(dps_hi)
    if len(ev_lo) != len(ev_hi):
        raise ValueError(f"event count mismatch: {len(ev_lo)} vs {len(ev_hi)}")
    worst = 100.0
    for row_lo, row_hi in zip(ev_lo, ev_hi):
        for a, b in zip(row_lo, row_hi):
            worst = min(worst, agreement_digits(a, b))
    if worst < 45:
        raise ValueError(f"dual-precision convergence failed: worst={worst}")
    return worst


def sensitivity_certificate(regen, perturb_component, perturbation=mp.mpf("1e-30"), max_events=25):
    """Compare event-time sequences under base vs perturbed IC."""
    base = regen(55, mp.mpf(0))
    pert = regen(55, perturbation)
    rows = []
    diverged = False
    for i in range(min(len(base), len(pert), max_events)):
        div = abs(base[i][0] - pert[i][0])
        rows.append({"event": i, "t_base": mp.nstr(base[i][0], 20), "t_pert": mp.nstr(pert[i][0], 20),
                     "divergence": mp.nstr(div, 20)})
        if div > mp.mpf("1e-10"):
            diverged = True
    return {"perturbed_component": perturb_component, "perturbation": "1e-30",
            "diverged": diverged, "table": rows}


def _f64(x):
    import struct
    return struct.unpack("!d", struct.pack("!d", float(x)))[0]


def simulate_float64_polynomial(coeffs, x0, y0, vx, vy, g, e, n_events):
    """Float64 shadow trajectory for quasi-chaotic sensitivity certification (I-003-T3)."""
    coeffs = [float(c) for c in coeffs]
    x0, y0, vx, vy, g, e = float(x0), float(y0), float(vx), float(vy), float(g), float(e)
    v_graze, v_settle = 1e-9, 1e-9
    events = []
    t_abs = 0.0
    settled = False
    t_min = 1e-12
    for _ in range(n_events):
        if settled:
            break
        # quadratic collision for low-degree polynomial via sampling
        t_max = 50.0
        best_t = None
        prev = y0 - poly_eval(coeffs, x0)
        for i in range(1, 513):
            t = t_min + (t_max - t_min) * i / 512
            xb = x0 + vx * t
            yb = y0 + vy * t - 0.5 * g * t * t
            val = yb - poly_eval(coeffs, xb)
            if prev * val <= 0 and i > 1:
                best_t = t
                break
            prev = val
        if best_t is None:
            break
        dt = best_t
        xc = x0 + vx * dt
        yc = poly_eval(coeffs, xc)
        vyf = vy - g * dt
        dp = poly_eval(poly_deriv(coeffs), xc)
        nn = (dp * dp + 1.0) ** 0.5
        nx, ny = -dp / nn, 1.0 / nn
        vn_in = abs(vx * nx + vyf * ny)
        if vn_in < v_graze:
            x0, y0, vy = xc, yc, vyf
            t_min = 1e-12
            continue
        t_abs += dt
        events.append((t_abs, xc, yc))
        vn = vx * nx + vyf * ny
        vx = vx - (1.0 + e) * vn * nx
        vy = vyf - (1.0 + e) * vn * ny
        vn_out = abs(vx * nx + vy * ny)
        x0, y0 = xc, yc
        if vn_out < v_settle:
            settled = True
            break
        t_min = 1e-12
    return events


def simulate_rounded(coeffs, x0, y0, vx, vy, g, e, n_events, keep_digits=50):
    """Simulate with state rounded to keep_digits after each event (chaotic envelope)."""
    coeffs = [mp.mpf(c) for c in coeffs]
    x0, y0, vx, vy, g, e = (mp.mpf(v) for v in (x0, y0, vx, vy, g, e))

    def round_state(x, y, vx, vy):
        return (
            mp.mpf(mp.nstr(x, keep_digits)),
            mp.mpf(mp.nstr(y, keep_digits)),
            mp.mpf(mp.nstr(vx, keep_digits)),
            mp.mpf(mp.nstr(vy, keep_digits)),
        )

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
            x0, y0, vy = xc, yc, vyf
            x0, y0, vx, vy = round_state(x0, y0, vx, vy)
            t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
            continue
        t_abs = (events[-1][0] + dt) if events else dt
        events.append((t_abs, xc, yc))
        vx, vy, vn_out = reflect(coeffs, xc, vx, vyf, e)
        x0, y0 = xc, yc
        x0, y0, vx, vy = round_state(x0, y0, vx, vy)
        if vn_out < V_SETTLE:
            settled = True
            break
        t_min = mp.mpf(10) ** (-(mp.mp.dps - 10))
    return events


def amplification_at_epsilon(coeffs, y0, vx, vy, e, component, epsilon, n_events=25):
    """Single-ε amplification probe for parameter search (I-003-T3-R1)."""
    eps = mp.mpf(epsilon)

    def run(apply_pert):
        mp.mp.dps = 55
        x, y, vvx, vvy = mp.mpf(0), mp.mpf(y0), mp.mpf(vx), mp.mpf(vy)
        if component == "vx":
            vvx += apply_pert
        elif component == "vy":
            vvy += apply_pert
        else:
            y += apply_pert
        return simulate_rounded(coeffs, x, y, vvx, vvy, 10, e, n_events, keep_digits=50)

    base = run(mp.mpf(0))
    p = run(eps)
    max_div = mp.mpf(0)
    for i in range(min(len(base), len(p), n_events)):
        max_div = max(max_div, abs(base[i][0] - p[i][0]))
    return max_div / eps


def certify_quasi_chaotic_mpmath(coeffs, y0, vx, vy, e, component, n_events=25):
    """Amplification-based sensitivity certificate (I-003-T3-R1 / prereg v1.1 A2)."""
    eps_30 = mp.mpf("1e-30")
    eps_20 = mp.mpf("1e-20")
    min_amplification = mp.mpf("1e6")
    linearity_factor = mp.mpf(10)

    def run(apply_pert):
        mp.mp.dps = 55
        x, y, vvx, vvy = mp.mpf(0), mp.mpf(y0), mp.mpf(vx), mp.mpf(vy)
        if component == "vx":
            vvx += apply_pert
        elif component == "vy":
            vvy += apply_pert
        else:
            y += apply_pert
        return simulate_rounded(coeffs, x, y, vvx, vvy, 10, e, n_events, keep_digits=50)

    def max_divergence(pert):
        base = run(mp.mpf(0))
        p = run(pert)
        max_div = mp.mpf(0)
        rows = []
        for i in range(min(len(base), len(p), n_events)):
            div = abs(base[i][0] - p[i][0])
            max_div = max(max_div, div)
            rows.append(
                {
                    "event": i,
                    "t_base": mp.nstr(base[i][0], 20),
                    "t_pert": mp.nstr(p[i][0], 20),
                    "divergence": mp.nstr(div, 20),
                }
            )
        return max_div, rows

    max_div_30, rows_30 = max_divergence(eps_30)
    max_div_20, rows_20 = max_divergence(eps_20)
    amp_30 = max_div_30 / eps_30
    amp_20 = max_div_20 / eps_20
    ratio = amp_20 / amp_30 if amp_30 != 0 else mp.mpf("inf")
    linearity_ok = (amp_30 >= min_amplification) and (
        ratio <= linearity_factor and ratio >= 1 / linearity_factor
    )
    return {
        "perturbed_component": component,
        "perturbation_primary": "1e-30",
        "perturbation_linearity": "1e-20",
        "method": "rounded-state-envelope",
        "amplification_at_1e-30": mp.nstr(amp_30, 20),
        "amplification_at_1e-20": mp.nstr(amp_20, 20),
        "linearity_ratio": mp.nstr(ratio, 20),
        "linearity_within_10x": bool(linearity_ok),
        "admitted": bool(linearity_ok),
        "table_at_1e-30": rows_30,
        "table_at_1e-20": rows_20,
    }


def poly_discriminant_at_first_contact(coeffs, x0, y0, vx, vy, g):
    coeffs_m = [mp.mpf(c) for c in coeffs]
    x0, y0, vx, vy, g = mp.mpf(x0), mp.mpf(y0), mp.mpf(vx), mp.mpf(vy), mp.mpf(g)
    q = collision_poly(coeffs_m, x0, y0, vx, vy, g)
    while len(q) > 1 and q[-1] == 0:
        q.pop()
    deg = len(q) - 1
    if deg == 2:
        a, b, c = q[2], q[1], q[0]
        return b * b - 4 * a * c
    if deg >= 2:
        old_dps = mp.mp.dps
        try:
            mp.mp.dps = max(old_dps, 80)
            coeffs_high = [q[i] for i in range(deg, -1, -1)]
            roots = mp.polyroots(coeffs_high, maxsteps=200)
            disc = mp.mpf(1)
            for i in range(len(roots)):
                for j in range(i + 1, len(roots)):
                    disc *= (roots[i] - roots[j]) ** 2
            return disc
        finally:
            mp.mp.dps = old_dps
    return mp.mpf("nan")


if __name__ == "__main__":
    main()

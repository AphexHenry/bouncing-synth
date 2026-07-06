# DELIVERABLE (b) — Numerics decision memo

```
doc_id:   C-000-DELIV-B
layer:    track
audience: Director (Phase-0 gate), PM; later cited by C-001/C-002 briefs
status:   DRAFT (pending Phase-0 gate approval)
parent:   C-000-BRIEF / PROJECT §3(b), instantiates the plan PROJECT §7 defers to Phase 0
```

## 1. The central reduction (why exactness is tractable)

Between events a ball is in free flight: x(t) = x₀ + vₓt, y(t) = y₀ + v_y t − ½gt². For vₓ ≠ 0
the flight path in space is a parabola y = P(x) with deg(P) ≤ 2 (vertical line when vₓ = 0).
Therefore every collision query is "parabola ∩ curve":

- Explicit polynomial curve y = f(x), deg n → f(x) − P(x) = 0, a real polynomial of degree
  max(n, 2) in x; collision time recovered exactly as t = (x − x₀)/vₓ.
- Parametric polynomial (Bézier) segment (X(s), Y(s)), deg d → Y(s) − P(X(s)) = 0, a polynomial
  of degree 2d in s on s ∈ [0,1] (deg 6 for cubic Bézier); t recovered from X(s).

Every gate-bearing collision in Phase 1 is thus real-root isolation of a univariate polynomial —
no transcendental functions, no libm in the collision core. This is the load-bearing decision:
it converts "exact real-time physics" from an aspiration into polynomial arithmetic.

## 2. Curve representation (decision)

Phase-1 gate-bearing curve families: **explicit polynomial** (y = f(x), degree ≤ 8) and
**piecewise Bézier** (quadratic and cubic segments, C1 continuity declared per PROJECT §6;
undeclared kinks rejected by the validator; declared vertices carry their own collision rule).
Curve params are stored exactly as IEEE-754 doubles in `CurveSpec`; derived polynomial
coefficients are computed once at curve-compile time in double-double arithmetic and pinned.
`sine` and `catenary` remain in the §6 enum but are **deferred from Phase-1 gates** (scope
ruling R3, §7 below): they reintroduce libm and break the no-transcendentals determinism story;
they re-enter, if ever, as a new component thesis with a correctly-rounded-libm plan.

## 3. Root-solving strategy (decision — this is the fixed solver spec of PROJECT §7)

- **Isolation:** Descartes'-rule-of-signs bisection (VCA) over the valid interval (x beyond the
  current position in flight direction; s ∈ [0,1] per segment), on coefficients held in
  double-double. Output: the isolating interval of the smallest admissible root, or "none".
- **Refinement:** deterministic fixed schedule — bisection to interval width ≤ 2⁻⁴⁰ of the
  interval scale, then exactly 3 Newton steps in double-double, then one rounding to double.
  No adaptive iteration counts, no convergence-dependent branching.
- **Admissibility filter:** a root is a collision only if the ball approaches the curve from the
  non-penetrating side with normal-component speed > 0 at contact (sign test on exact
  double-double evaluations).
- **Degeneracy / grazing (PROJECT §9 named risk):** near-tangency shows up as root clusters.
  Rule G-1: if the isolated crossing has |normal impact speed| < v_graze (pre-registered
  constant, order 1e-9 m/s), the event is a graze — no bounce, flight continues past it.
  Rule S-1 (Zeno guard): with restitution < 1 bounce intervals form a convergent series; when
  post-bounce normal speed < v_settle (pre-registered), the ball is marked SETTLED and emits no
  further events in Phase 1 (rolling/sliding contact is out of Phase-1 scope). Both constants
  and both rules are versioned; changing either is an engine version bump.

## 4. Floating-point determinism plan (decision)

- IEEE-754 binary64 throughout the engine; round-to-nearest-even; FTZ/DAZ off; `-ffast-math`
  and value-changing FP optimizations forbidden; collision core compiled with
  `-ffp-contract=off` (explicit FMA policy: none), so results cannot vary with FMA availability.
- Double-double arithmetic built only from +, −, ×, ÷ error-free transforms (no FMA variant),
  plus IEEE-correctly-rounded sqrt where normals are normalized. No libm calls in the core.
- Single-threaded solver per scenario; no SIMD in the core; parallelism only across scenarios.
- Time bookkeeping: absolute engine time = (int64 sample count, double sub-sample residual in
  [0,1)), normalized deterministically after every event; per-arc durations are computed from
  local event state, so a bit-identical state recurrence yields a bit-identical interval
  sequence — this is what makes zero phase drift structural (`loop_stability` measures interval
  sequences, not absolute times).
- MIDI placement: an event with time t in block [t_b, t_b+1) gets
  sample_offset = floor((t − t_b)·fs + 0.5), computed in double-double; block membership decided
  by exact comparison. (`midi_timing` gate.)
- Platform claim: environment of record is arm64 macOS / Apple clang 17 (JRN-C000-5).
  Cross-platform bit-identity (adding Linux x86-64 in CI) is *expected* under the rules above —
  polynomial-only core, no libm, no FMA — but is gated (`determinism_repro` per platform), never
  assumed; if it fails on a platform, the claim is scoped per PROJECT §9(b) and the discrepancy
  becomes a tracked defect.

## 5. Event ordering & tie-breaking (decision — tie-break version TB-1)

One global event queue; next event = minimum over balls of the next collision. Total order:
(t exact-compare, ball_id, curve segment index, event kind). Bit-identical simultaneous events
are processed in that order, each resolving independently. `CollisionEvent.seq` is assigned in
processing order and is the determinism witness for `determinism_repro`. TB-1 is versioned;
any change bumps the engine version (PROJECT §9(c)).

## 6. Reference & fixtures (feeds I-002; Law 5 / Law 6)

- Tier-1: closed-form fixtures solved symbolically (CAS) — flat line, single parabola-on-parabola
  arcs, low-degree cases with rational parameters; symbolic verification recorded per fixture.
- Tier-2: Python/mpmath reference simulator, ≥ 50 significant digits, same algorithm on exact
  rational/high-precision coefficients; `reference_converged` = event sequence invariant under
  doubling the working precision. Runs offline only; used at gate time and red-team item 8.

## 7. Scope rulings for Director ratification (with the (a)–(d) approval)

- **R1 — Point-contact model (Phase 1).** Physics treats balls as points; `radius` remains in
  `BallState` (validated > 0) but is visual-only in Phase 1. Rationale: disc contact means
  solving against the offset curve, which is not polynomial (normal normalization introduces
  sqrt into the geometry); offset-exact contact is a well-posed future thesis, not a Phase-1
  gamble. Consequence honestly stated: Phase-1 "exact physics" is exact *point* physics.
- **R2 — No ball–ball collisions (Phase 1).** Balls are mutually transparent. Ball–ball events
  are a possible later component (new thesis; re-enters via the register), interacting with R1.
- **R3 — Transcendental curve families deferred** from Phase-1 gates (see §2). The user-facing
  curve vocabulary at Phase 1 is polynomial + piecewise Bézier — which already covers freely
  hand-shaped curves via Bézier fitting in the UI layer (Phase 2 concern).

## 8. What this memo deliberately does not decide

Musical-time sync (host tempo vs wall clock), mapping semantics (C-003), UI curve-editing
ergonomics, and preset format details — Phase-2 questions, owned by their component theses.

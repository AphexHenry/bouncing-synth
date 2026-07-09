# THESIS — C-001 Exact collision engine

```
doc_id:   C-001-THESIS
layer:    track
audience: PM, Director, agents (gate context)
status:   ACTIVE
parent:   PROJECT §2 / DELIVERABLE_D §Phase 1 item 2 / DELIVERABLE_B §3–§5
```

1. CLAIM            — A headless event-driven engine that propagates balls in closed-form ballistic
                      arcs (parabola P(x) per DELIVERABLE_B §1), finds the next collision by VCA
                      polynomial root isolation + fixed refinement schedule (DELIVERABLE_B §3) on
                      C-002 compiled curves, applies TB-1 tie-breaking and G-1/S-1 grazing/settle
                      rules (R1 point-contact, R2 no ball–ball), and emits a monotone
                      CollisionEvent stream with zero heap allocation on the processing path,
                      yields bit-identical event sequences across runs and block sizes
                      (`determinism_repro`), zero phase drift on periodic Tier-1 orbits
                      (`loop_stability`), agreement with Tier-1/Tier-2 references within
                      pre-registered tolerance (`reference_agreement`), and beats the named
                      baseline on accuracy at matched compute (Law 7).
2. NOVELTY CHECK    — Prior art (DELIVERABLE_A): physics sequencers integrate on polyline
                      approximations or fixed timesteps; none gate exact analytic collision times
                      against the true curve equation in real time. Bounce's engine is the
                      execution layer of the central reduction (DELIVERABLE_B §1): every Phase-1
                      collision is real-root isolation of a univariate polynomial. This is not a
                      general rigid-body simulator — it is a specialized event scheduler for
                      parabola∩curve with deterministic numerics.
3. CONFOUND SKETCH  — (a) *adaptive iteration counts breaking determinism* — killed by fixed
                      refinement schedule (bisection to 2⁻⁴⁰ scale + exactly 3 Newton steps,
                      DELIVERABLE_B §3). (b) *libm or FMA variance in the core* — killed by
                      polynomial-only collision arithmetic, `-ffp-contract=off`, double-double
                      built without FMA (DELIVERABLE_B §4). (c) *polyline geometry smuggled in* —
                      killed by the named baseline: **naive fixed-timestep engine with
                      polyline-sampled curve** at matched compute budget (PROJECT §5 Law 7,
                      DELIVERABLE_D); the exact engine must beat it on drift/accuracy at equal or
                      lower cost. (d) *held-out peeking during tuning* — killed by I-003
                      split-lock + gate-runner-only held-out access (Law 1).
4. DATA FEASIBILITY — Tier-1 calibration scenarios in data/scenarios/calibration/ (I-002-T4,
                      schema v1; FL-1, PB-1 seeded). Tier-2 oracle tools/refsim/ (I-002
                      VERIFIED). C-002 curve library supplies compiled geometry (C-002-T1
                      VERIFIED). Held-out corpus empty until I-003 split-lock; gate runs via
                      I-004 when briefed. No external datasets. Reachability: fixtures and refsim
                      on disk; curves in src/core/bounce/curve/.
5. SCALE & COST     — zero spend. Coverage table at prereg: {curve family × dynamical regime ×
                      ball count} per PROJECT §9 L-07; empty cells declared at C-001 prereg time.
                      Grazing cases mandatory (PROJECT §9 domain safeguard).
6. KILL SKETCH      — `determinism_repro` fails on environment of record; `loop_stability` shows
                      drift > bound on periodic Tier-1 fixtures; `reference_agreement` exceeds
                      tolerance on calibration set; or the exact engine matches the naive
                      polyline baseline within tolerance at equal cost without beating it on
                      accuracy — any kills the analytic-collision bet.
SCORE (PM):         — prior: DELIVERABLE_D mandates second / reuse: high (product core) /
                      moat: high (exact real-time polynomial collision) / risk: high (numerics +
                      grazing degeneracy).

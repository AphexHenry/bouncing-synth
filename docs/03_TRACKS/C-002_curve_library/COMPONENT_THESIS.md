# THESIS — C-002 Curve library

```
doc_id:   C-002-THESIS
layer:    track
audience: PM, Director, agents (gate context)
status:   ACTIVE
parent:   PROJECT §2 / DELIVERABLE_D §Phase 1 item 1
```

1. CLAIM            — A compile-once curve library for Phase-1 families (explicit polynomial
                      degree ≤ 8; piecewise quadratic/cubic Bézier with declared C1 per
                      DELIVERABLE_B §2) provides exact IEEE-754 evaluation, derivative, and
                      unit-normal queries at pinned coefficient sets with zero heap allocation
                      after compile, and matches Tier-1 CAS/reference values at gate fixtures
                      (FL-1 flat line, PB-1 parabola-on-parabola) to bitwise or pre-registered
                      tolerance.
2. NOVELTY CHECK    — Prior art (DELIVERABLE_A): physics sequencers approximate geometry as
                      polylines or grids; Bounce's bet is solving on the true curve equation.
                      No FOSS curve layer was found that compiles user shapes to pinned
                      polynomial coefficients for an analytic collision core — this component
                      is the geometry front-end of that bet, not a general CAD kernel.
3. CONFOUND SKETCH  — (a) *compile-time precision loss masked by loose tolerance* — killed by
                      Tier-1 exact-rational fixtures and Tier-2 cross-check on PB-1 normals.
                      (b) *per-query re-derivation hiding compile bugs* — killed by the named
                      baseline: **direct per-query evaluation without compilation** at matched
                      compile+query cost (DELIVERABLE_D); the compiled path must beat it on
                      accuracy at equal or lower cost. (c) *undeclared kinks smuggled in* —
                      killed by validator rejection table in a later task (C-002-T3 sketch).
4. DATA FEASIBILITY — Tier-1 fixtures in data/scenarios/calibration/ (I-002-T4, schema v1);
                      Tier-2 oracle tools/refsim/ (I-002 VERIFIED). CAS check for polynomial
                      cases is exact rational arithmetic in tier1_fixtures.py (Tier 1). No
                      external datasets. Reachability: fixtures on disk at I-002-T4 ACCEPT.
5. SCALE & COST     — zero spend. Coverage table at prereg: {polynomial, piecewise-bezier} ×
                      {degree/regime cells} — empty cells declared at C-002 prereg time.
6. KILL SKETCH      — compiled eval/deriv/normal fails Tier-1 fixtures at any gate point, or
                      matches the per-query baseline within tolerance at equal cost without
                      beating it on accuracy — either kills the compile-once design.
SCORE (PM):         — prior: DELIVERABLE_D mandates first / reuse: high (engine depends on it) /
                      moat: medium (exact polynomial front-end) / risk: medium (Bézier piece in T2+).

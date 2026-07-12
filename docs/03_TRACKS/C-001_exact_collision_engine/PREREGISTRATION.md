# PREREGISTRATION — C-001 Exact collision engine (Phase-1 gate studies)

```
doc_id:   C-001-PREREG
layer:    track
audience: PM, Director, agents (gate context), I-003/I-004 (input contract)
status:   ACTIVE v1.0 — registered 2026-07-12 (PACKET 36); amendments only by new packet with
          CORRECTION entry, never by edit
parent:   C-001-THESIS / PROJECT §3 Phase 1, §4, §5, §8, §9 / P2
```

## 0. Scope and standing

This document pre-registers the confirmatory studies whose passage constitutes the C-001 side
of the Phase-1 gate (PROJECT §3). Registered values in this file are fixed: changing any
tolerance, horizon, nuisance set, margin, or coverage-cell assignment after a held-out run has
occurred requires a Director-approved CORRECTION packet and voids affected results. The
T1–T10 calibration precursors (JRN-C001-43) are development evidence only and carry no weight
here. All studies execute exclusively through the I-004 gate runner against the I-003 locked
held-out corpus; any held-out scenario executed outside I-004 is a Law 1 violation and
poisons that scenario (retired from the corpus, replacement minted).

Environment of record: the Director's machine as pinned by I-001 (`config/fp-determinism.cmake`
flags; toolchain versions recorded per manifest at each gate run). Cross-platform claims are
out of scope for v1.0 (§9 safeguard b: claims scoped to one platform explicitly) and enter
only via a registered addendum once I-007 exists.

## 1. Study P1-A — reference_agreement (Design A)

- Unit of analysis: one held-out scenario (curve + initial state + params) run to horizon
  H = min(200 events, settle per S-1).
- References: Tier-1 (CAS-verified closed form) where available; Tier-2 (mpmath refsim,
  `reference_converged` passed per Law 5) otherwise. Tier fixed at fixture creation.
- PRIMARY CRITERION (the only confirmatory claim of this study): over every event of every
  held-out scenario, max |t_engine − t_ref| ≤ 1e-9 s AND max |s_engine − s_ref| ≤ 1e-9
  (curve-parameter units), with ball_id and seq exactly equal per event. One scenario over
  tolerance fails the study. Threshold basis: fixed refinement (bisection to 2⁻⁴⁰ + 3 DD
  Newton, DELIVERABLE_B §3) bounds per-root error near double-precision scale; 1e-9 grants
  ×1000 headroom for state propagation over ≤200 events while remaining ≥4 orders below any
  fixed-timestep competitor.
- Reporting (L-05 analog): worst case per scenario and per corpus, full error distributions,
  per-family and per-regime breakdown; per-event error-growth curves are exploratory.
- Quasi-chaotic cells: reference agreement evaluated over the first 25 events only (Tier-2
  convergence horizon cap for exponentially diverging orbits); declared in the coverage table.

## 2. Study P1-B — determinism_repro (Design B)

- Unit of analysis: one held-out scenario replayed under a nuisance condition.
- Registered nuisance set (v1.0, environment of record): (i) 100 in-process repetitions;
  (ii) 10 fresh-process invocations; (iii) 2 clean-checkout rebuilds (delete build tree,
  reconfigure, rebuild, rerun). Block-size variance enters when block-based emission exists
  (C-003); platform variance enters with I-007 — both by registered addendum only.
- PRIMARY CRITERION: bit-identical CollisionEvent sequence (0 diff on every field of every
  event) across all runs of the full nuisance set, for every held-out scenario. Exact gate,
  no tolerance (PROJECT §8).
- Scope statement (binding on all downstream claims): v1.0 determinism is claimed for the
  environment of record only. No marketing, docs, or register text may state cross-platform
  determinism before the addendum passes.

## 3. Study P1-C — loop_stability (Design C)

- Unit of analysis: one periodic orbit run for 10^4 periods.
- Held-out orbit families must include at least: one non-dyadic flat-line orbit (bounce
  period not exactly representable in binary), one parabola-bowl orbit, one piecewise-Bézier
  orbit. The dyadic FL-1 family is calibration-only and confirmatory-inadmissible here
  (JRN-C001-43: zero drift by construction).
- PRIMARY CRITERION: the collision-interval sequence of every period is bit-identical to the
  first period's, over 10^4 periods, for every held-out periodic fixture — drift exactly 0
  (PROJECT §4 Design C target). If a family is proven analytically incapable of bit-exact
  period repetition, that proof is itself the deliverable and the family's criterion is
  re-registered by CORRECTION packet before any run counts.
- Reporting: per-period first-divergence index (should be none), interval-sequence hashes.

## 4. Study P1-D — realtime_budget (Design D): DEFERRED

No compute budget is registered in v1.0. A budget with no measured basis is not a threshold,
it is a guess, and both failure modes (sandbagged-easy and theatrically-tight) corrupt the
gate. P1-D is deferred to a registered addendum that requires: I-004 operational, an I-005
profiling harness run on the calibration set producing measured per-event and per-query
costs on the environment of record, and Director approval of the derived budget. Until that
addendum passes, no "real time" claim attaches to C-001 in any register, journal, or
Director-facing summary; the THESIS claim's "in real time" clause is pending, not evidenced.

## 5. Law 7 baseline study — matched-compute comparison

- Contestants: C-001 exact engine vs the named baseline (PROJECT §5 Law 7) — fixed-timestep
  semi-implicit (symplectic) Euler integrator over a polyline-sampled curve, with impulse
  reflection at segment crossings. The baseline is agent-authored from a PM spec (L-14);
  the spec must be good-faith competitive (registered here): polyline vertex count and dt are
  chosen by the compute-matching rule below, not fixed a priori, and the integrator uses the
  same restitution and settle rules.
- Compute matching (registered methodology): budget = exact engine's wall-time per simulated
  scenario-second, measured per scenario by I-004 on the environment of record (median of 10
  timed runs). The baseline's dt (and polyline density, coupled dt↔N by equal per-step cost)
  is tuned — on calibration scenarios only — to the largest accuracy configuration whose
  wall-time per simulated scenario-second is within +10% of the budget (equal-or-more compute
  allowed to the baseline; never less).
- PRIMARY CRITERION: on the held-out corpus, worst-case per-event |Δt| vs reference of the
  exact engine ≤ (baseline's worst-case per-event |Δt|) / 100 at matched-or-lower compute;
  AND on held-out periodic fixtures, exact-engine drift = 0 where the baseline's measured
  drift > 0. Failing either arm kills the analytic-collision bet (THESIS §6).
- Reporting: full accuracy-vs-compute curves for both engines (exploratory), worst-case table
  per family × regime.

## 6. Split, lock, and access (Law 1 / L-04 analog)

- Held-out fraction: ~40% of the scenario corpus, stratified by curve family × dynamical
  regime; remainder is the calibration set (free use).
- Minting: I-003-T2 generates held-out scenarios from the coverage table below — Tier-1 via
  CAS-verified closed forms, Tier-2 via the refsim with `reference_converged` passed — and
  locks them (split-lock marker + manifest) before any C-001 binary executes any of them.
- Access: held-out scenarios run only via the I-004 gate runner, which logs every execution
  to the manifest. Any other execution poisons the scenario (retire + re-mint + journal).
- The seeded calibration fixtures FL-1 and PB-1 are calibration-set members permanently.

## 7. Coverage table (L-07 analog; input contract for I-003-T2)

Cells marked HO receive held-out scenarios; CAL calibration-only; — declared empty with the
reason. Ball counts: every non-empty cell at 1 ball; multi-ball (2–4, TB-1 stress) required
where marked +MB.

| family \ regime | settle/transient | periodic | quasi-chaotic |
|---|---|---|---|
| flat line | CAL (FL-1) + HO +MB | HO non-dyadic (P1-C) +MB | — (flat line: no chaotic single-ball regime, R2) |
| explicit poly deg 2 (parabola) | CAL (PB-1) + HO +MB | HO bowl orbit (P1-C) | HO (25-event cap, §1) |
| explicit poly deg 3–6 | HO | HO | HO (25-event cap) |
| piecewise Bézier C1 | HO +MB | HO (P1-C) | — (Phase-1 Tier-2 reference-horizon cost; declared, revisit Phase 2) |

Declared empty program-wide: transcendental curve families (Director ruling R3); ball–ball
collisions (R2); ball counts 8–16 (enter with P1-D addendum only).

Mandatory grazing block (PROJECT §9 domain safeguard a) — held-out, gate-bearing in P1-A:
at least 3 near-tangency scenarios with normal impact speed |v_n| at 0.5×, 1.0×, and 2.0×
v_graze (spanning the G-1 admissibility boundary from both sides, including the boundary
case whose G-1 classification is itself the oracle value), plus 1 near-double-root geometry
(discriminant within 1e-6 of zero at contact). At least one grazing scenario on a Bézier
segment.

## 8. Multiplicity and red team (L-06, P2 §6)

One primary criterion per study (§1–§3, §5); everything else labeled exploratory. Red-team
items accompanying the Phase-1 gate call: (i) leave-one-curve-family-out — P1-A re-evaluated
excluding the dominant family, result reported; (ii) trusted-tier-only — P1-A re-evaluated on
Tier-1 fixtures alone; (iii) concentration check — no single family may contribute >50% of
held-out scenarios (I-003-T2 mint constraint).

## Changelog
- v1.0 — Initial registration (PACKET 36, JRN-C001-45). P1-A/B/C registered; P1-D deferred;
  Law 7 methodology and margin fixed; coverage table issued as I-003-T2 input contract.

# BRIEF — C-001 Exact collision engine

```
doc_id:   C-001-BRIEF
layer:    track
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   C-001-THESIS
```

## Context for agents
Phase-1 physics core for bounce-core (DELIVERABLE_C §1). The engine owns ballistic propagation,
polynomial collision-time root-solving against C-002 curves, TB-1 event ordering, and G-1/S-1
rules. No JUCE, no heap on the processing path, no libm in the collision core (DELIVERABLE_B
§3–§4). C-002 leads by one packet — engine tasks dispatch only after the curve layer has the
slice the task needs. Failures are reported verbatim (FAILED/BLOCKED), never patched mid-task.

## Files you may read
- `AGENTS.md` · assigned `inbox/PACKET_<n>.md` · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- `docs/00_PROJECT.md` §6–§8 · `docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_B_NUMERICS.md` §1–§5
- `docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md` §1
- This brief · track `JOURNAL.md` · `src/core/bounce/curve/` (C-002)
- `config/fp-determinism.cmake` · `data/scenarios/calibration/` (read-only)

## Files you will write
- Under `src/core/bounce/` (engine, numerics, events) and `tests/` per task
- `docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md` (append)
- `docs/03_TRACKS/C-001_exact_collision_engine/reports/` task reports
- `outbox/OUT_<serial>_C-001-T<n>.md`

## TASK C-001-T1: Double-double arithmetic + ballistic parabola P(x) + unit tests
depends_on: C-002-T2 VERIFIED (JRN-C002-9); I-001 (VERIFIED)
objective: DD add/mul/div without FMA; compile ballistic flight path y=P(x) from BallisticInit
           using DD coefficient arithmetic; doctest on FL-1 ground hit and vx=0 rejection.
VERIFIED (JRN-C001-5; OUT_25; TR_C-001-T1.md).

## TASK C-001-T2: VCA root isolation on explicit-polynomial curve + unit tests
depends_on: C-001-T1 VERIFIED (JRN-C001-5)
objective: Build f(x)−P(x) collision polynomial and isolate the smallest root bracket on
           [x_min, x_max] via VCA bracket scan (DELIVERABLE_B §3 isolation step).
VERIFIED (JRN-C001-9; OUT_26; TR_C-001-T2.md).

## TASK C-001-T3: Fixed refinement + admissibility filter + single-ball event step + unit tests
depends_on: C-001-T2 VERIFIED (JRN-C001-9)
objective: Refine isolated root (bisection 2⁻⁴⁰ + 3 DD Newton), apply G-1 admissibility
           (|normal impact speed| ≥ v_graze), expose step_ball_next_collision for one collision
           query on explicit-polynomial curves; doctest on FL-1 ground hit.
VERIFIED (JRN-C001-13; OUT_27; TR_C-001-T3.md).

## TASK C-001-T4: Elastic reflection + graze continuation + multi-event FL-1 sequence + unit tests
depends_on: C-001-T3 VERIFIED (JRN-C001-13)
objective: reflect_velocity about curve normal with restitution; simulate_ball_collisions loop
           with G-1 graze continuation and S-1 settle; doctest on FL-1 eight tier-1 event times.
VERIFIED (JRN-C001-17; OUT_28; TR_C-001-T4.md).

## TASK C-001-T5: CollisionEvent schema + PB-1 first-contact agreement + unit tests
depends_on: C-001-T4 VERIFIED (JRN-C001-17)
objective: Introduce PROJECT §6 CollisionEvent struct; simulator emits full schema events;
           doctest on PB-1 tier-1 first contact (t=1, s=1 on y=x²).
VERIFIED (JRN-C001-21; OUT_29; TR_C-001-T5.md).

## TASK C-001-T6: TB-1 multi-ball global event queue + unit tests
depends_on: C-001-T5 VERIFIED (JRN-C001-21)
objective: simulate_multi_ball_collisions with TB-1 ordering (min t, then ball_id); doctests
           on simultaneous tie-break, earliest-time selection, monotone seq.
VERIFIED (JRN-C001-25; OUT_30; TR_C-001-T6.md).

## TASK C-001-T7: Calibration scenario JSON runner (FL-1/PB-1 end-to-end) + unit tests
depends_on: C-001-T6 VERIFIED (JRN-C001-25)
objective: load_calibration_scenario + run_calibration_scenario for schema-v1 calibration
           JSON; doctest FL-1 eight tier-1 reference events and PB-1 first contact.
VERIFIED (JRN-C001-29; OUT_31; TR_C-001-T7.md).

## TASK C-001-T8: determinism_repro repeated-run identity on FL-1 + unit tests
depends_on: C-001-T7 VERIFIED (JRN-C001-29)
objective: events_equal helper (exact == on all CollisionEvent fields) + doctest FL-1
           determinism_repro — 100 repeated run_calibration_scenario calls, each bit-identical
           to baseline (PROJECT §8 determinism_repro gate).
VERIFIED (JRN-C001-33; OUT_32; TR_C-001-T8.md).

## TASK C-001-T9: loop_stability zero interval-sequence drift on FL-1 + unit tests
depends_on: C-001-T8 VERIFIED (JRN-C001-33)
objective: extract_collision_intervals + intervals_equal helpers; doctest FL-1 loop_stability —
           11 dyadic-halving intervals bit-exact, 100 repeated full-horizon runs with zero
           interval-sequence drift through settle (PROJECT §8 loop_stability gate).
VERIFIED (JRN-C001-37; OUT_33; TR_C-001-T9.md).

## TASK C-001-T10: reference_agreement tier-1 calibration corpus + unit tests
depends_on: C-001-T9 VERIFIED (JRN-C001-37)
objective: agrees_with_tier1_reference helper (ε=1e-12 on t/s, exact ball_id/seq) + doctest
           tier-1 calibration corpus FL-1 + PB-1 (PROJECT §8 reference_agreement gate).
(Dispatched in PACKET 34.)

## TASK C-001-T11 (sketch): naive polyline baseline engine (Law 7) — at prereg.

# BRIEF — C-002 Curve library

```
doc_id:   C-002-BRIEF
layer:    track
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   C-002-THESIS
```

## Context for agents
Phase-1 geometry for bounce-core. Curves must compile from CurveSpec to pinned coefficients,
then serve exact eval / derivative / unit-normal queries with no heap allocation on the query
path (DELIVERABLE_B §2, DELIVERABLE_D). C-002 leads C-001 by one packet so the engine always
has real curves. Failures are reported verbatim (FAILED/BLOCKED), never patched mid-task.

## Files you may read
- `AGENTS.md` · assigned `inbox/PACKET_<n>.md` · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- `docs/00_PROJECT.md` §6 (CurveSpec) · `docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_B_NUMERICS.md` §2
- This brief · track `JOURNAL.md` · `config/scenario-fixture-schema-v1.json`
- `data/scenarios/calibration/` Tier-1 scenarios (read-only reference)

## Files you will write
- Under `src/core/bounce/curve/` and `tests/` per task
- `docs/03_TRACKS/C-002_curve_library/JOURNAL.md` (append)
- `docs/03_TRACKS/C-002_curve_library/reports/` task reports
- `outbox/OUT_<serial>_C-002-T<n>.md`

## TASK C-002-T1: Polynomial compile + eval/deriv/normal + unit tests
depends_on: I-002-T4 (VERIFIED, JRN-I002-25); I-001 (VERIFIED)
objective: First curve family slice — explicit polynomial through degree 8 — with doctest
           coverage on FL-1 (y=0) and PB-1 (y=x²) Tier-1 points.
VERIFIED (JRN-C002-5; OUT_21; TR_C-002-T1.md).

## TASK C-002-T2: Piecewise Bézier segments + C1 validator + unit tests
depends_on: C-002-T1 VERIFIED (JRN-C002-5); I-003-T1 VERIFIED (JRN-I003-5)
objective: Quadratic/cubic Bézier compile + parametric eval/deriv/normal; piecewise assembly
           with C1 validator rejecting undeclared kinks (DELIVERABLE_B §2).
(Dispatched in PACKET 24.)

## TASK C-002-T3 (sketch): Validator corpus + compile-time allocation gate — at prereg.

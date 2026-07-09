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

## TASK C-001-T1 (sketch): Double-double arithmetic + ballistic parabola P(x) — dispatch after C-002-T2.
## TASK C-001-T2 (sketch): VCA root isolation on explicit-polynomial curve — after T1.
## TASK C-001-T3 (sketch): Fixed refinement + admissibility filter + single-ball event step — at prereg.

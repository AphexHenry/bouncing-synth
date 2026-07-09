# BRIEF — I-003 Scenario store + split-lock

```
doc_id:   I-003-BRIEF
layer:    infra
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   INFRASTRUCTURE_REGISTER I-003 / DELIVERABLE_C §2 / config/scenario-fixture-schema-v1.json
```

## Context for agents
Law-1 enforcement surface: `data/scenarios/calibration/` (development) vs `heldout/` (gate-only).
Schema pinned at I-002-T4. Split-lock machinery prevents held-out peeking during development.
I-003 follows C-002-T1 dispatch (parallel authoring; first I-003 task briefed after C-002-T1
is in flight).

## Files you may read
- `AGENTS.md` · assigned packet · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- `config/scenario-fixture-schema-v1.json` · `data/scenarios/`
- `docs/05_INFRA/I-002_refsim/BRIEF.md` (T4 lineage)

## Files you will write
- `data/scenarios/` store artifacts · `tools/scenarios/` validators per task
- `docs/05_INFRA/I-003_scenario_store/JOURNAL.md` (append)
- `docs/05_INFRA/I-003_scenario_store/reports/` · `outbox/`

## TASK I-003-T1 (sketch): Split-lock marker + store validator + held-out empty manifest
depends_on: I-002-T4 VERIFIED; schema v1 on disk
objective: Formalize calibration vs heldout access rules; validator script exits 0 on the
           seeded calibration corpus and rejects held-out reads without lock.
(Dispatched in a subsequent packet after C-002-T1.)

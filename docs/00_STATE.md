# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_5/RV1 accepted; deliverables (a)–(d) filed; RV2 dispatched (PACKET 6)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 0 — Scoping (PROJECT §3). Module v0.1 ACTIVE (Director-approved 2026-07-06). License: GPLv3
(Director 2026-07-06; PROJECT §11 text amendment batched to module v0.2 at Phase-0 exit).
All four Phase-0 deliverables authored and transcription-verified (RV1, JRN-C000-13):
(a) LANDSCAPE, (b) NUMERICS, (c) ARCHITECTURE, (d) SLATE under
docs/03_TRACKS/C-000_scoping/reports/.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-000 Phase-0 scoping | RUNNING (T1, RV1 accepted) | GATE_REVIEW — Phase-0 exit presentation | RV2 (repo normalization); then Director approval of (a)–(d) incl. rulings R1–R3 |

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | SPECCED | brief | Phase-0 exit |
| I-002 high-precision reference sim | SPECCED | brief | Phase-0 exit (creates venv, installs pinned mpmath) |
| I-003 scenario store + split-lock | SPECCED | brief | Phase-0 exit |
| I-004 gate runner + manifests | SPECCED | brief | Phase-0 exit |
| I-005 event/pattern analysis harness | SPECCED | brief | Phase-0 exit |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Phase-0 exit (Director creates hosting/CI account first, PROJECT §11) |

## Open decisions (Director)
1. Phase-0 exit gate: approve deliverables (a)–(d) including numerics scope rulings R1
   (point-contact), R2 (no ball–ball), R3 (transcendental families deferred). Options:
   approve / amend. PM rec: approve — presented after RV2 confirms a clean repository.

## Recent gate calls
None yet (first gate is the Phase-0 exit, Director-owned).

## Pointers
Repository normalization in progress (RV2, JRN-C000-13): step-1 evidence of OUT_5 showed a
partially tracked tree (protocols/module/AGENTS.md untracked) and unmerged stacked packet
branches with HEAD on packet/4. After RV2: main is the single line of history; every task
branch starts from main; Director merges after each ACCEPT. Environment of record unchanged
(JRN-C000-5). Git history before RV2 is non-linear; content authority for that span is the
RV1 evidence, not branch topology.

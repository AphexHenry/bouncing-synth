# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_48 BLOCKED processed; C-001-T14 dispatched; PACKET 49

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE (blocked on zero-event write). Harness load VERIFIED
(C-001-T13: 32/32). GATE-P1-R1 halted at P1-A scenario 14/32: `finish_event_stream` fails
when `engine_events=0` on HO-graze-parabola-1 (grazing rule requires zero events — correct
simulation, broken write path). C-001-T14 dispatched: shared io fix + zero-event smoke.
GATE-P1-R2 pre-staged as PACKET 50. Partial P1-A (13 scenarios, gate-authorized ACCESS_LOG)
is not Law-1 poisoning. On eventual gate PASS: Phase-1 gate call; Phase 2 opens.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — GATE BLOCKED (zero-event write) | T14 → GATE-P1-R2 | OUT_49 |
| C-002 Curve library | BRIEFED | T3 prereg | Phase-1 gate call |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 | VERIFIED | — | — |
| I-002 | VERIFIED | — | — |
| I-003 | VERIFIED — corpus 32 locked (T4 re-mint complete) | — | — |
| I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | Phase-1 gate call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Known issues
Zero-event `finish_event_stream` write failure (OUT_48). Baseline CLI write failure at N≥512
(outside gate path; OUT_45). Validator calibration_scenarios=3 (OUT_47 forward finding).

## Recent review verdicts
OUT_48/GATE-P1-R1: ACCEPT halt — infrastructure BLOCKED (JRN-C001-71).
OUT_47/I-003-T4+C-001-T13: ACCEPT — T4 + T13 VERIFIED (JRN-C001-67).
OUT_46/GATE-P1: ACCEPT halt — infrastructure BLOCKED (JRN-C001-63).

## Pointers
Branch rule: task/C-001-T14 from task/GATE-P1-R1 tip. GATE-P1-R2: PACKET 50 (pre-staged).
Gate governance: PREREGISTRATION.md v1.3; TUNE-LAW7.json by sha256.

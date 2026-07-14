# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_47 ACCEPT — T13 + I-003-T4 VERIFIED; GATE-P1-R1 dispatched; PACKET 48

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE. Harness unblock VERIFIED (C-001-T13: 32/32 load;
Bézier exact collision; Law-1 re-mint complete for four flat-settle fixtures). GATE-P1-R1
dispatched: first authorized held-out engine contact — P1-A → P1-B → P1-C → Law 7 per
PREREG v1.3, halt-on-failure, dirty=false, access-logged. Construction from OUT_46 at tip
(merge if needed); execution only. Task compliance ≠ gate verdicts: a clean FAIL is the
falsification record. On PASS: Phase-1 gate call to Director; Phase 2 opens.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — GATE-P1-R1 IN FLIGHT | gate verdicts → Phase-1 gate call | OUT_48 |
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
Baseline CLI write failure at N≥512 (outside gate path; OUT_45). Validator reports
calibration_scenarios=3 (OUT_47 forward finding — non-blocking). Merge housekeeping
(PACKET 40) optional.

## Recent review verdicts
OUT_47/I-003-T4+C-001-T13: ACCEPT — T4 VERIFIED (JRN-I003-26); T13 VERIFIED (JRN-C001-67).
OUT_46/GATE-P1: ACCEPT halt — infrastructure BLOCKED (JRN-C001-63).
OUT_45/C-001-T12-R1: ACCEPT — T12 VERIFIED via R1 (JRN-C001-59).

## Pointers
Branch rule: task/GATE-P1-R1 from task/C-001-T13 tip (harness + gate construction).
Gate governance: PREREGISTRATION.md v1.3; TUNE-LAW7.json by sha256; MANIFEST.json current
(I-003-T4 sha256s for HO-flat-settle-{1..4}).

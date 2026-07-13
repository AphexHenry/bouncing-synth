# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_45 ACCEPT — T12 VERIFIED (JRN-C001-59); PREREG v1.3; GATE-P1 dispatched; PACKET 46

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE. All construction complete and VERIFIED: exact
engine (T1–T12), Law 7 baseline at frozen tune (dt=5e-4, N=128, ratio 1.8987 —
over-resourced on FL-1, favorable to contestant), locked 32-scenario corpus, gate runner
with manifests and mechanical held-out discipline. PREREG v1.3: quasi-chaotic P1-A window
12 events by A3 feasibility audit (25 unsatisfiable in binary64 — amended BEFORE any
held-out run). GATE-P1 dispatched: P1-A → P1-B → P1-C → Law 7, halt-on-failure,
dirty=false, every held-out execution gate-authorized and access-logged. Construction
scope in-task: checkers, study specs, --repeat flag only. Task compliance ≠ gate verdicts:
a clean FAIL is a valid outcome and would be the bet's falsification record. On PASS:
Phase-1 gate call to Director; Phase 2 (C-003 mapping, I-006 JUCE shell — the sound) opens.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — GATE RUNS IN FLIGHT | gate verdicts → Phase-1 gate call | OUT_46 |
| C-002 Curve library | BRIEFED | T3 prereg | Phase-1 gate call |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 | VERIFIED | — | — |
| I-002 | VERIFIED | — | — |
| I-003 | VERIFIED — corpus 32 locked; first contact = GATE-P1 | — | — |
| I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | Phase-1 gate call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Known issues
Baseline CLI write failure at N≥512 (outside gate path; OUT_45). Merge housekeeping
instruction (PACKET 40 message) stands, optional — dirty=false is a working-tree property.

## Recent review verdicts
OUT_45/C-001-T12-R1: ACCEPT — T12 VERIFIED via R1 (JRN-C001-59).
OUT_44/C-001-T12: REJECT — inadmissible evidence (JRN-C001-55; L-16).
OUT_43/C-001-T11: ACCEPT — C-001-T11 VERIFIED (JRN-C001-50).
OUT_42/I-004-T2+T3: ACCEPT — I-004 COMPLETE (JRN-I004-8).

## Pointers
Branch rule: task/GATE-P1 branches from task/C-001-T12. Gate governance:
PREREGISTRATION.md v1.3 (windows, tolerances, order, halt, dirty rule, log rule);
TUNE-LAW7.json by sha256 is the contestant configuration of record.

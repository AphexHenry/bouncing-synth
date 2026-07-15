# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_49 ACCEPT (C-001-T14 VERIFIED); GATE-P1-R2 dispatched; PACKET 50

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE (second execution re-dispatch in flight).
Zero-event write path FIXED and smoke-evidenced (C-001-T14 VERIFIED, JRN-C001-75).
Pre-flight now covers both known output-shape classes: held-out load 32/32 (D1) and
zero-event write (D4, durable fix of JRN-C001-71). GATE-P1-R2 (PACKET 50) executes
P1-A → P1-B → P1-C → Law 7 per PREREG v1.3 with halt-on-failure. OUT_50 is the Phase-1
gate call input (PASS → Director gate call, Phase 2 opens) or the falsification record —
both with numbers.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — GATE-P1-R2 IN FLIGHT | gate verdicts → Phase-1 gate call | OUT_50 |
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
Baseline CLI write failure at N≥512 (outside gate path; tune of record N=128; OUT_45).
Validator calibration_scenarios=3 vs historical 2 (OUT_47 forward finding; trace at next
I-003 maintenance). Zero-event write failure (OUT_48): RESOLVED by C-001-T14.

## Recent review verdicts
OUT_49/C-001-T14: ACCEPT — VERIFIED (JRN-C001-75).
OUT_48/GATE-P1-R1: ACCEPT halt — infrastructure BLOCKED (JRN-C001-71).
OUT_47/I-003-T4+C-001-T13: ACCEPT — T4 + T13 VERIFIED (JRN-C001-67).

## Pointers
Branch rule: task/GATE-P1-R2 from task/C-001-T14 tip (stacked, JRN-I002-6); Director merges
to main remain batched non-blocking housekeeping. Gate governance: PREREGISTRATION.md v1.3;
TUNE-LAW7.json by sha256. Prior ACCESS_LOG baseline: 24 lines (gate-authorized, JRN-C001-71).

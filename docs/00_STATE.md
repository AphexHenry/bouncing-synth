# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_51 AMEND+RETURN (criterion 7, PM-owned; repair rides R3 step 4); GATE-P1-R3 dispatched; PACKET 52

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE (third execution re-dispatch in flight). Checker
reference parsing FIXED and self-tested (C-001-T15: exact Fraction comparison path, 6-vector
shape self-test incl. fail-loudness proof; VERIFIED attaches at R3 step-4 repair,
JRN-C001-83). Pre-flight now covers every failure mode to date: held-out load 32/32 (D1,
full-table remediation), zero-event write (D4), repeat-identity (D3), and the judge itself
(D7 self-test, L-17). GATE-P1-R3 (PACKET 52) executes P1-A → P1-B → P1-C → Law 7 per PREREG
v1.3 with halt-on-failure. OUT_52 is the Phase-1 gate call input (PASS → Director gate call,
Phase 2 opens) or the falsification record — both with numbers.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — GATE-P1-R3 IN FLIGHT | gate verdicts → Phase-1 gate call | OUT_52 |
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
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   pre-flight shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2)
   — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Known issues
Baseline CLI write failure at N≥512 (outside gate path; tune of record N=128; OUT_45).
Validator calibration_scenarios=3 vs historical 2 (OUT_47 forward finding; trace at next
I-003 maintenance). Checker rational-parse defect (OUT_50): RESOLVED (C-001-T15).
Zero-event write (OUT_48): RESOLVED (C-001-T14).

## Recent review verdicts
OUT_51/C-001-T15: AMEND + RETURN scoped to criterion 7 (PM-owned defective criterion;
L-13 v2; repair = R3 step 4); capability evidence complete (JRN-C001-83).
OUT_50/GATE-P1-R2: ACCEPT halt — infrastructure BLOCKED at checker (JRN-C001-79).
OUT_49/C-001-T14: ACCEPT — VERIFIED (JRN-C001-75).

## Pointers
Branch rule: task/GATE-P1-R3 from task/C-001-T15 tip (stacked, JRN-I002-6); Director merges
to main remain batched non-blocking housekeeping. Gate governance: PREREGISTRATION.md v1.3;
TUNE-LAW7.json by sha256. ACCESS_LOG baseline: 56 (24 R1 + 32 R2, all gate-authorized). R2
gate outputs (events + P1-A manifest) removed at R3 step 4; gate_r2_evidence/ committed as
R2 evidence of record at R3 step 4 (OUT_51 criterion-7 repair). Workspace-state criteria:
L-13 v2 delta-scoped text of record (JRN-C001-83).

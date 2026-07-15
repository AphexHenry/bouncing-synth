# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_50 BLOCKED processed (ACCEPT halt); C-001-T15 dispatched; PACKET 51

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE (third infrastructure halt, checker-side).
GATE-P1-R2 halted at P1-A --check: `check_p1a.py` cannot parse exact rational reference
fields (`"t": "5/2"`, Tier-1 by design) — execute itself completed 32/32 gate-authorized,
engine_git_dirty=false, no verdict produced. Ruling: locked corpus stays exact; the judge
is extended (C-001-T15: shared exact reference parser + checker shape self-test, L-17).
GATE-P1-R3 pre-staged as PACKET 52 with new pre-flight D7 (checker self-test) and the D1
full-survey remediation (L-15 v2, JRN-C001-79). On eventual gate PASS: Phase-1 gate call;
Phase 2 opens. On FAIL: falsification record.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — GATE BLOCKED (checker reference parse) | T15 → GATE-P1-R3 | OUT_51 |
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
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; NEW: P6 §4
   judge-side pre-flight shape coverage, per L-17/JRN-C001-79) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Known issues
Checker rational-reference parse defect (OUT_50) — fix in flight (C-001-T15). Baseline CLI
write failure at N≥512 (outside gate path; tune of record N=128; OUT_45). Validator
calibration_scenarios=3 vs historical 2 (OUT_47 forward finding; trace at next I-003
maintenance). Zero-event write (OUT_48): RESOLVED (C-001-T14).

## Recent review verdicts
OUT_50/GATE-P1-R2: ACCEPT halt — infrastructure BLOCKED at checker (JRN-C001-79); criterion
3 to L-15 v2 remediation (full D1 survey re-derived in R3).
OUT_49/C-001-T14: ACCEPT — VERIFIED (JRN-C001-75).
OUT_48/GATE-P1-R1: ACCEPT halt — infrastructure BLOCKED (JRN-C001-71).

## Pointers
Branch rule: task/C-001-T15 from task/GATE-P1-R2 tip (stacked, JRN-I002-6); Director merges
to main remain batched non-blocking housekeeping. Gate governance: PREREGISTRATION.md v1.3;
TUNE-LAW7.json by sha256. ACCESS_LOG baseline: 56 lines (24 R1 + 32 R2, all gate-authorized).
R2 P1-A artifacts (32 event files + manifest) are valid but verdict-free; R3 re-executes
fresh at its own tip. GATE-P1-R3: PACKET 52 (pre-staged: D7 checker self-test pre-flight;
D1 full-table paste, elision forbidden; D6 baseline 56).

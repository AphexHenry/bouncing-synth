# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_46 BLOCKED processed; Law-1 re-mint + C-001-T13 dispatched; PACKET 47

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE (blocked on harness). Construction VERIFIED through
C-001-T12; GATE-P1 construction (checkers, studies, --repeat) committed on task/GATE-P1 but
halted at P1-A: loader cannot parse 28/32 held-out fixtures; exact engine lacks parametric
Bézier collision path. PREREG v1.3 unchanged. Law-1: four flat-settle fixtures poisoned by
ungated OUT_46 survey — I-003-T4 re-mint dispatched. C-001-T13 dispatched: loader (decimal,
empty ref, schema-v1 curves) + Bézier exact collision per DELIVERABLE_B. GATE-P1
re-dispatch pre-staged as PACKET 48 contingent on OUT_47 ACCEPT. On eventual gate PASS:
Phase-1 gate call to Director; Phase 2 opens.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — GATE BLOCKED (harness) | T13 → GATE-P1 re-run | OUT_47 |
| C-002 Curve library | BRIEFED | T3 prereg | Phase-1 gate call |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 | VERIFIED | — | — |
| I-002 | VERIFIED | — | — |
| I-003 | VERIFIED — corpus 32 locked; 4 fixtures poisoned → T4 re-mint | T4 re-mint | OUT_47 |
| I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | Phase-1 gate call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Known issues
Baseline CLI write failure at N≥512 (outside gate path; OUT_45). GATE-P1 loader/harness gap
(OUT_46). HO-flat-settle-{1..4} Law-1 poisoning (OUT_46 survey). Merge housekeeping
instruction (PACKET 40) optional.

## Recent review verdicts
OUT_46/GATE-P1: ACCEPT halt — infrastructure BLOCKED, properly documented (JRN-C001-63).
OUT_45/C-001-T12-R1: ACCEPT — T12 VERIFIED via R1 (JRN-C001-59).
OUT_44/C-001-T12: REJECT — inadmissible evidence (JRN-C001-55; L-16).
OUT_43/C-001-T11: ACCEPT — C-001-T11 VERIFIED (JRN-C001-50).

## Pointers
Branch rule: task/C-001-T13 branches from task/GATE-P1 (preserves gate construction).
GATE-P1 re-dispatch: PACKET 48 (pre-staged). Gate governance: PREREGISTRATION.md v1.3;
TUNE-LAW7.json by sha256 is the contestant configuration of record.

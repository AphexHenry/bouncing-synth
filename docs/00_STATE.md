# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_41 ACCEPT — I-003-T3 VERIFIED, corpus complete (JRN-I003-22); L-15 v2; I-004-T2+T3 dispatched; PACKET 42

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. MILESTONE: held-out corpus COMPLETE — 32 scenarios locked
covering every non-empty C-001-PREREG v1.1 cell (four measured-chaotic geometries, grazing
triplet, near-double-root, non-dyadic orbits, five Bézier fixtures); §8.iii cap satisfied
(max family 34.4%); I-003 VERIFIED and closed. L-15 v2 issued (machine-attested aggregates
with recoverable per-item artifacts → remediation; ratified by PACKET 42 dispatch).
I-004-T2+T3 dispatched batched: orchestrator + manifest of record + mechanical split-lock
discipline; calibration-only execution — the corpus's first engine contact is reserved for
a real gate run. Remaining Phase-1 critical path: OUT_42 → C-001-T11 baseline spec
(agent-authored, L-14) → gate runs (P1-A/B/C + Law 7).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.1) | T11 spec dispatch | OUT_42 |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern (available) |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED | — | — |
| I-003 scenario store + split-lock | VERIFIED — corpus complete (32 locked) | — | — |
| I-004 gate runner + manifests | BRIEFED (T1 VERIFIED; T2+T3 in flight) | T2+T3 review | OUT_42 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004; feeds P1-D addendum |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Merge housekeeping
Corrected instruction (PACKET 40 message) stands, non-blocking: main ← chain tip (--no-ff),
archive task/I-003-T1. Paste outputs with any OUT when run.

## Recent review verdicts
OUT_41/I-003-T3-R1: ACCEPT — I-003-T3 VERIFIED; corpus complete (JRN-I003-22; L-15 v2
remediation at PACKET 42 step 0).
OUT_40/I-003-T3: BLOCKED — properly executed (JRN-I003-17); resolved via prereg v1.1.
OUT_39/I-003-T2-R1: ACCEPT — I-003-T2 VERIFIED (JRN-I003-13).
OUT_38/I-003-T2: REJECT (JRN-I003-9).

## Pointers
Branch rule: task/I-004-T23 branches from task/I-003-T3; successors extend it. C-001
confirmatory work governed by PREREGISTRATION.md v1.1. Held-out access: I-004 runner only,
gate-authorized, logged.

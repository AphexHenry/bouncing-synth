# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_40 BLOCKED processed; PREREG v1.1; I-003-T3-R1 dispatched; PACKET 41

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001 PREREGISTERED — v1.1 (PACKET 41, Director-approved by
dispatch): parabola×quasi-chaotic declared empty by measurement (integrable parabolic
billiard; A≈2e1 vs deg-6 A≈1.7e11), quasi-chaotic admission amplification-based (A ≥ 1e6
at ε=1e-30 within ≤25 events), Bézier×periodic ×2, feasibility-derivation authoring rule.
Two PM authoring defects owned (JRN-I003-18). OUT_40 was a model BLOCK; L-15 remediation
CLOSED (T2-R1 digest ledger complete). I-003-T3-R1 dispatched on the same branch. After
OUT_41: I-004-T2+T3 batched (PACKET 42), C-001-T11 baseline spec, gate runs schedulable.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.1) | T11 spec dispatch | I-004-T2/T3 (PACKET 42) |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern (available) |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1, T2 VERIFIED; T3-R1 in flight) | T3-R1 review | OUT_41 |
| I-004 gate runner + manifests | BRIEFED (T1 VERIFIED) | T2+T3 batched dispatch | PACKET 42 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004; feeds P1-D addendum |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Merge housekeeping
Corrected instruction (PACKET 40 message) stands: main ← chain tip (--no-ff), archive
task/I-003-T1. If already run, paste outputs with any OUT; otherwise run at convenience —
non-blocking.

## Recent review verdicts
OUT_40/I-003-T3: BLOCKED — properly executed (JRN-I003-17); resolved via prereg v1.1 +
T3-R1.
OUT_39/I-003-T2-R1: ACCEPT — I-003-T2 VERIFIED (JRN-I003-13); L-15 remediation CLOSED at
OUT_40 step 0.
OUT_38/I-003-T2: REJECT (JRN-I003-9).
OUT_37/I-004-T1: ACCEPT — I-004-T1 VERIFIED (JRN-I004-4).

## Pointers
Branch rule: T3-R1 extends task/I-003-T3 in place (WIP tooling present). C-001 confirmatory
work governed by PREREGISTRATION.md v1.1. Full held-out corpus after T3-R1: 32 scenarios,
locked, I-004-access-only.

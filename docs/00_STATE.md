# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_39 ACCEPT — I-003-T2 VERIFIED via R1 (JRN-I003-13); L-15; I-003-T3 dispatched; PACKET 40

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001 PREREGISTERED (v1.0 binding). I-004-T1 VERIFIED.
I-003-T2 VERIFIED via R1: 16 Tier-1 held-out fixtures at full precision discipline
(exact-zero grazing ratios, true 50-digit periods, 49.6-digit convergence floor). L-15
issued (review proportionality for evidence defects); OUT_39 digest remediation rides as
step 0 of PACKET 40. I-003-T3 dispatched full-width (step-size ruling): 16 Tier-2 fixtures
closing the C-001-PREREG §7 coverage table; corpus → 32; §8.iii concentration cap closes.
Corrected merge DIRECTOR ACTION issued (chain-tip merge + archival of off-chain
task/I-003-T1). Next: I-004-T2+T3 batched (PACKET 41), C-001-T11 baseline spec, then gate
runs become schedulable.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED | T11 spec dispatch | I-004-T2/T3 (PACKET 41) |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern (available) |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1, T2 VERIFIED) | T3 review | OUT_40 |
| I-004 gate runner + manifests | BRIEFED (T1 VERIFIED) | T2+T3 batched dispatch | PACKET 41 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004; feeds P1-D addendum |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Merge housekeeping — corrected instruction issued with PACKET 40
main ← task/I-003-T2 (--no-ff; serials 13–39), then archive off-chain task/I-003-T1
(content subsumed via the OUT_38 import commit; evidence OUT_23). Outputs pasted with
OUT_40.

## Recent review verdicts
OUT_39/I-003-T2-R1: ACCEPT — I-003-T2 VERIFIED (JRN-I003-13; L-15 remediation in
PACKET 40 step 0).
OUT_38/I-003-T2: REJECT (JRN-I003-9).
OUT_37/I-004-T1: ACCEPT — I-004-T1 VERIFIED (JRN-I004-4).
OUT_36/apply-only: ACCEPT — C-001 PREREGISTERED (JRN-C001-46).

## Pointers
Branch rule: task/I-003-T3 branches from task/I-003-T2; successors extend it. C-001
confirmatory work governed by PREREGISTRATION.md v1.0. Full held-out corpus after T3: 32
scenarios, locked, I-004-access-only.

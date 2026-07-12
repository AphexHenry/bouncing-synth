# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_38 REJECT (JRN-I003-9); I-003-T2-R1 dispatched; merge ON HOLD; PACKET 39

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001 PREREGISTERED (v1.0 binding). I-004-T1 VERIFIED. I-003-T2
REJECTED (JRN-I003-9): float64 contamination of the mint pipeline (grazing ratios 17 digits
vs registered 20; "50-digit" periods were double expansions) + non-verbatim evidence paste;
16 fixtures quarantined non-gate-bearing, no Law-1 poisoning. R1 re-mint dispatched
(PACKET 39) with precision-discipline spec (two permitted float64 touchpoints, strict
non-dyadicity, 1e-30 ratio bound, 45-digit dual-precision self-check). First substantive
model-B REJECT — review independence functioning. Director step-size ruling 2026-07-12:
larger batched tasks at unchanged rigor from PACKET 40.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED | T11 spec dispatch | I-004-T2/T3; I-003-T2-R1/T3 |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern (available) |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1 VERIFIED; T2 REJECTED) | T2-R1 review | OUT_39 |
| I-004 gate runner + manifests | BRIEFED (T1 VERIFIED) | T2+T3 batched brief | PACKET 40/41 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004; feeds P1-D addendum |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking;
   approval requested.
3. GPLv3 -only vs -or-later — Phase 3.

## Merge housekeeping — ON HOLD
The PACKET 38 merge DIRECTOR ACTION is superseded: the branch chain is NOT linear
(task/I-003-T1 off-chain per OUT_38 DEVIATIONS). Do not run it if not yet run; if already
run, paste outputs — task/I-003-T1 remaining unmerged is expected, harmless. Corrected
two-branch instruction ships after I-003-T2-R1.

## Recent review verdicts
OUT_38/I-003-T2: REJECT (JRN-I003-9) — R1 dispatched.
OUT_37/I-004-T1: ACCEPT — I-004-T1 VERIFIED (JRN-I004-4).
OUT_36/apply-only: ACCEPT — C-001 PREREGISTERED (JRN-C001-46).
OUT_35/apply-only: ACCEPT — PACKET 35 APPLIED (JRN-C001-44).

## Pointers
Branch rule: I-003-T2-R1 extends task/I-003-T2 (in-place supersession of the quarantined
mint). Main merges remain batched Director housekeeping. C-001 confirmatory work governed by
PREREGISTRATION.md v1.0.

# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_28 ACCEPT — C-001-T4 VERIFIED (JRN-C001-17); C-001-T5 (PACKET 29)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001-T1/T2/T3/T4 VERIFIED. C-001-T5 in PACKET 29 (CollisionEvent
schema + PB-1 first contact). C-002-T1/T2 VERIFIED. I-003-T1 VERIFIED.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | BRIEFED | T5 dispatch | PACKET 29 apply |
| C-002 Curve library | BRIEFED | T3 prereg | — |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED | T1 complete | — |
| I-004 gate runner + manifests | SPECCED | brief | PM packet |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 (recommended; non-blocking).
2. P6 §4.6 amendment (L-11, L-13) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Recent review verdicts
OUT_28/C-001-T4: ACCEPT — C-001-T4 VERIFIED (JRN-C001-17).
OUT_27/C-001-T3: ACCEPT — C-001-T3 VERIFIED (JRN-C001-13).
OUT_26/C-001-T2: ACCEPT — C-001-T2 VERIFIED (JRN-C001-9).
OUT_25/C-001-T1: ACCEPT — C-001-T1 VERIFIED (JRN-C001-5).

## Pointers
Component branch rule: C-001-T5 branches from task/C-001-T4. Infra I-00x stacked from task/I-002-T4.

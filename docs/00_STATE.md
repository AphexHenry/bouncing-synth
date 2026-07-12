# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_33 ACCEPT — C-001-T9 VERIFIED (JRN-C001-37); C-001-T10 (PACKET 34)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001-T1/T2/T3/T4/T5/T6/T7/T8/T9 VERIFIED. C-001-T10 in PACKET 34
(reference_agreement corpus). C-002-T1/T2 VERIFIED. I-003-T1 VERIFIED.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | BRIEFED | T10 dispatch | PACKET 34 apply |
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
OUT_33/C-001-T9: ACCEPT — C-001-T9 VERIFIED (JRN-C001-37).
OUT_32/C-001-T8: ACCEPT — C-001-T8 VERIFIED (JRN-C001-33).
OUT_31/C-001-T7: ACCEPT — C-001-T7 VERIFIED (JRN-C001-29).
OUT_30/C-001-T6: ACCEPT — C-001-T6 VERIFIED (JRN-C001-25).

## Pointers
Component branch rule: C-001-T10 branches from task/C-001-T9. Infra I-00x stacked from task/I-002-T4.

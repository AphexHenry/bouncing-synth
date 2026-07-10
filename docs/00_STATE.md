# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_23 ACCEPT — I-003-T1 VERIFIED (JRN-I003-5); C-002-T2 (PACKET 24)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. I-003-T1 VERIFIED (split-lock + validator). C-002-T2 in PACKET 24
(piecewise Bézier + C1). C-001 at THESIS.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-002 Curve library | BRIEFED | T2 review | OUT_24 |
| C-001 Exact collision engine | THESIS | T1 brief | C-002-T2 ACCEPT |

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
OUT_23/I-003-T1: ACCEPT — I-003-T1 VERIFIED (JRN-I003-5).
OUT_22: APPLIED — C-002-T1 VERIFIED (JRN-C002-5); C-001 thesis.

## Pointers
Component branch rule: C-00x tasks branch from task/C-002-T1 (C-002-T2 from same tip).
Infra I-00x stacked from task/I-002-T4.

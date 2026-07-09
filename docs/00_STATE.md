# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_21 ACCEPT — C-002-T1 VERIFIED (JRN-C002-5); C-001 thesis (PACKET 22)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-002-T1 VERIFIED (polynomial slice). C-001 at THESIS. I-003-T1 in
PACKET 23 (split-lock + store validator).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-002 Curve library | BRIEFED | T2 brief | PACKET 24 (after I-003-T1) |
| C-001 Exact collision engine | THESIS | BRIEFED / T1 sketch | C-002-T2 |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED | T1 dispatch | PACKET 23 |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 (recommended; non-blocking).
2. P6 §4.6 amendment (L-11, L-13) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Recent review verdicts
OUT_21/C-002-T1: ACCEPT — C-002-T1 VERIFIED (JRN-C002-5).
OUT_19/I-002-T4: ACCEPT — I-002 VERIFIED (JRN-I002-25).

## Pointers
Component branch rule: C-00x tasks branch from the current Phase-1 component tip (task/C-002-T1
until merged to main). Infra I-00x tasks use stacked-branch rule from task/I-002-T4.

# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_19 ACCEPT — I-002 VERIFIED (JRN-I002-25); C-002 thesis + I-003 brief (PACKET 20)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. I-002 refsim workstream VERIFIED. C-002 at THESIS; C-002-T1 in
PACKET 21. I-003 brief authored; T1 follows C-002-T1 dispatch.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-002 Curve library | THESIS | BRIEFED / T1 | PACKET 21 (C-002-T1) |
| C-001 Exact collision engine | IDEA | THESIS | after C-002-T1 brief stabilizes |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED | T1 dispatch | PM packet after C-002-T1 |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 (recommended; non-blocking).
2. P6 §4.6 amendment (L-11, L-13) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Recent review verdicts
OUT_19/I-002-T4: ACCEPT — I-002 VERIFIED (JRN-I002-25).
OUT_18/I-002-T3b-R1: ACCEPT — I-002-T3b VERIFIED.

## Pointers
Component branch rule: C-00x tasks branch from the current Phase-1 infra tip (task/I-002-T4
until merged to main). Stacked-branch rule remains for I-00x infra tasks.

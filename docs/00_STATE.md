# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_37 ACCEPT — I-004-T1 VERIFIED (JRN-I004-4); I-003-T2 dispatched; PACKET 38

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001 PREREGISTERED (PREREGISTRATION.md v1.0 binding). I-004-T1
VERIFIED (JRN-I004-4): bounce-run-scenario CLI + canonical lossless serialization —
byte-identity = bit-identity; first fully model-B deliverable. I-003-T2 dispatched
(PACKET 38): 16 Tier-1 held-out scenarios, refsim/CAS-only mint, lock-on-mint. Merge
housekeeping DIRECTOR ACTION issued (main → task/I-004-T1 tip; 19 branches, linear chain).
Authorship model B (L-14) and packet-as-file delivery in force. C-002-T1/T2 VERIFIED.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED | T11 spec dispatch | I-004-T2; I-003-T2/T3 |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern (available) |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1 VERIFIED) | T2 review | OUT_38 |
| I-004 gate runner + manifests | BRIEFED (T1 VERIFIED, JRN-I004-4) | T2 brief — orchestrator + manifest writer | PACKET 39 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004-T2; feeds P1-D addendum |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED: P1-B beyond a single machine and any
   cross-platform determinism claim are blocked on it.
2. Protocol amendment bundle: P6 §4.6 (L-11, L-13, L-14); P6 §7.4 clarification
   (pre-verification = oracle derivation from specs, never running the codebase); P6 §7.5
   packet-as-file delivery rule; P5 §2 amendment — APPLIED.log is the sole apply ledger,
   inbox/ packets are uncommitted Director courier surface (ratifying practice, per L-13) —
   non-blocking; approval requested.
3. GPLv3 -only vs -or-later — Phase 3.

## Outstanding Director evidence
PACKET 38 DIRECTOR ACTION (merge): paste outputs of the --no-ff merge and
`git branch --no-merged main` with the next OUT.

## Recent review verdicts
OUT_37/I-004-T1: ACCEPT — I-004-T1 VERIFIED (JRN-I004-4).
OUT_36/apply-only: ACCEPT — PACKET 36 APPLIED; C-001 PREREGISTERED (JRN-C001-46).
OUT_35/apply-only: ACCEPT — PACKET 35 APPLIED (JRN-C001-44).
OUT_34/C-001-T10: ACCEPT — C-001-T10 VERIFIED (JRN-C001-41).

## Pointers
Branch rule: task/I-003-T2 branches from task/I-004-T1; successors extend it. Main merges
remain batched Director housekeeping (JRN-I002-6). C-001 confirmatory work is governed by
PREREGISTRATION.md v1.0.

# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_36 ACCEPT (JRN-C001-46); I-004 BRIEFED + T1 dispatched; PACKET 37

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001 PREREGISTERED (PREREGISTRATION.md v1.0 binding,
JRN-C001-45); T1–T10 VERIFIED (T8–T10 calibration-mode precursors — JRN-C001-43). I-004
BRIEFED, T1 dispatched (PACKET 37): scenario-runner CLI with canonical lossless event
serialization — byte-identity = bit-identity for P1-B/P1-C. Authorship model B in force
(L-14); packet-as-file delivery rule in force. C-002-T1/T2 VERIFIED. I-003-T1 VERIFIED.
Merge-sizing git evidence gathered as read-only diagnostics in OUT_37 (P6 §7.1(b) reroute);
merge instruction in PACKET 38 with the I-003-T2 mint.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED | T11 spec dispatch | I-004-T1/T2 |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern (available) |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1 VERIFIED, JRN-I003-5) | T2 brief — held-out mint per C-001-PREREG §7 | PACKET 38 |
| I-004 gate runner + manifests | BRIEFED (JRN-I004-1) | T1 review | OUT_37 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004; feeds P1-D addendum |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED: P1-B beyond a single machine (platform
   variance) and any cross-platform determinism claim are blocked on it.
2. P6 amendment bundle: §4.6 (L-11, L-13, L-14); §7.4 clarification (pre-verification =
   oracle derivation from specs, never running the codebase); §7.5 packet-as-file delivery
   rule — non-blocking; approval requested.
3. GPLv3 -only vs -or-later — Phase 3.

## Recent review verdicts
OUT_36/apply-only: ACCEPT — PACKET 36 APPLIED; C-001 PREREGISTERED (JRN-C001-46).
OUT_35/apply-only: ACCEPT — PACKET 35 APPLIED (JRN-C001-44).
OUT_34/C-001-T10: ACCEPT — C-001-T10 VERIFIED (JRN-C001-41).
OUT_33/C-001-T9: ACCEPT — C-001-T9 VERIFIED (JRN-C001-37).

## Pointers
Branch rule: task/I-004-T1 branches from packet/36; successors extend task/I-004-T1 until
the PACKET 38 merge instruction lands. C-001 confirmatory work is governed by
PREREGISTRATION.md v1.0 — registered values change only by Director-approved CORRECTION
packet.

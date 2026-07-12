# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_34 ACCEPT — C-001-T10 VERIFIED (JRN-C001-41); authorship model B ruling (JRN-C001-42, L-14); PACKET 35

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001-T1…T10 VERIFIED. Authorship model B in force (Director ruling
2026-07-12; JRN-C001-42, L-14): implementation is agent-authored from PM specs; the PM does not
build or execute the repo. T8–T10 scoped as calibration-mode gate precursors, not §8 gate runs
(JRN-C001-43). Packet delivery rule in force (Director-ordered, 2026-07-12): every packet is
emitted to the Director as a standalone PACKET_<serial>.md file, never as inline chat text.
C-002-T1/T2 VERIFIED. I-003-T1 VERIFIED. Next: C-001 preregistration (PACKET 36), I-004 brief
(PACKET 37), Tier-2 hard-cell fixture mint (PACKET 38), then C-001-T11 (agent-authored
baseline).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | BRIEFED | PREREGISTRATION.md | PACKET 36 |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1 VERIFIED, JRN-I003-5) | T2 brief — held-out corpus mint | C-001 prereg coverage table |
| I-004 gate runner + manifests | SPECCED | brief | PACKET 37 (critical path) |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED: Design-B determinism evidence beyond a single
   machine (cross-process, cross-platform, block-size variance) is blocked on it; requested
   this phase.
2. P6 amendment bundle: §4.6 covering L-11, L-13, L-14; §7.4 clarification (pre-verification =
   oracle derivation from specs, never running the codebase); §7.5 packet-as-file delivery
   rule (every packet a standalone PACKET_<serial>.md file, ratifying the 2026-07-12
   Director order) — non-blocking; approval requested.
3. GPLv3 -only vs -or-later — Phase 3.

## Recent review verdicts
OUT_34/C-001-T10: ACCEPT — C-001-T10 VERIFIED (JRN-C001-41).
OUT_33/C-001-T9: ACCEPT — C-001-T9 VERIFIED (JRN-C001-37).
OUT_32/C-001-T8: ACCEPT — C-001-T8 VERIFIED (JRN-C001-33).
OUT_31/C-001-T7: ACCEPT — C-001-T7 VERIFIED (JRN-C001-29).

## Pointers
Branch rule: packet/35 branches from task/C-001-T10; successors extend packet/35. Housekeeping
merge of the stacked chains requested (DIRECTOR ACTION with PACKET 35); merge instruction lands
in PACKET 36 sized to the pasted evidence.

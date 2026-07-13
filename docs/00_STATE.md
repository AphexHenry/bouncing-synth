# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_42 ACCEPT — I-004 COMPLETE (JRN-I004-8); C-001-T11 dispatched; PACKET 43

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. INFRASTRUCTURE COMPLETE: exact engine (T1–T10), locked 32-
scenario held-out corpus, gate runner with manifests of record, byte-identity comparison,
mechanically enforced held-out access (refusal tested; access log provably untouched).
C-001-T11 dispatched — the Law 7 baseline, agent-authored per L-14: capacity lift (64→256;
prereg-horizon blocker found via OUT_42 observation), semi-implicit-Euler polyline engine
with shared canonical serialization, runner engine selection. Standing gate-call rules:
manifests require engine_git_dirty=false; held-out first contact reserved for gate runs.
PACKET 44 = compute-match tune (calibration only, prereg §5) + P1-A/P1-B/P1-C + Law 7.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.1) | T11 review → gate scheduling | OUT_43 |
| C-002 Curve library | BRIEFED | T3 prereg | after Phase-1 gate runs |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 | VERIFIED | — | — |
| I-002 | VERIFIED | — | — |
| I-003 | VERIFIED — corpus complete | — | — |
| I-004 | VERIFIED — Phase-1 complete | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Merge housekeeping
Instruction (PACKET 40 message) stands, non-blocking: main ← chain tip (--no-ff), archive
task/I-003-T1. Paste outputs with any OUT when run.

## Recent review verdicts
OUT_42/I-004-T2+T3: ACCEPT — I-004 COMPLETE (JRN-I004-8).
OUT_41/I-003-T3-R1: ACCEPT — corpus complete (JRN-I003-22).
OUT_40/I-003-T3: BLOCKED — properly executed; resolved via prereg v1.1.
OUT_39/I-003-T2-R1: ACCEPT — I-003-T2 VERIFIED.

## Pointers
Branch rule: task/C-001-T11 branches from task/I-004-T23; successors extend it. Gate runs
governed by PREREGISTRATION.md v1.1; gate manifests require dirty=false; held-out access
via I-004 only, gate-authorized, logged.

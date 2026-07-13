# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_43 ACCEPT (JRN-C001-50); Director rulings D-1/D-2/D-3 → PREREG v1.2; C-001-T12 dispatched; PACKET 44

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001-T11 VERIFIED: Law 7 baseline built agent-authored (L-14),
capacity 64→256, runner engine selection. Director rulings 2026-07-13 registered as PREREG
v1.2: fixed-horizon Law 7 comparison (K = min(200, exact count); no baseline settle
semantics), compute window [1.0×, 2.0×] equal-or-more, gate order P1-A → P1-B → P1-C →
Law 7 with halt-on-failure. Product note on record: no imposed damping; default e=1;
ball–ball excluded per R2 (nothing implemented). Pre-gate blocker found (Director's
long-horizon question): P1-C's ~2–3e4 events exceed the 256 buffer — streaming emission in
C-001-T12, dispatched with F3 diagnostic, F2 .gitignore, and the frozen compute-match tune.
PACKET 45 = pure measurement: the four gate runs, first held-out contact, gate-authorized,
dirty=false.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.2) | gate runs (PACKET 45) | OUT_44 |
| C-002 Curve library | BRIEFED | T3 prereg | after Phase-1 gate runs |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 | VERIFIED | — | — |
| I-002 | VERIFIED | — | — |
| I-003 | VERIFIED — corpus complete (32 locked, untouched) | — | — |
| I-004 | VERIFIED — Phase-1 complete | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.

## Merge housekeeping
Instruction (PACKET 40 message) stands, non-blocking. Gate runs require a committed tree
(dirty=false), so the merge — or at minimum a committed chain tip — must precede PACKET 45
execution; the T12 tune already runs from a committed tree by spec.

## Recent review verdicts
OUT_43/C-001-T11: ACCEPT — C-001-T11 VERIFIED (JRN-C001-50).
OUT_42/I-004-T2+T3: ACCEPT — I-004 COMPLETE (JRN-I004-8).
OUT_41/I-003-T3-R1: ACCEPT — corpus complete (JRN-I003-22).
OUT_40/I-003-T3: BLOCKED — properly executed; resolved via prereg v1.1.

## Pointers
Branch rule: task/C-001-T12 branches from task/C-001-T11; successors extend it. Gate runs
governed by PREREGISTRATION.md v1.2; manifests require dirty=false; held-out access via
I-004 only, gate-authorized, logged; TUNE-LAW7.json is the frozen Law 7 contestant
configuration.

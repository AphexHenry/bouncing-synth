# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_44 REJECT — inadmissible evidence (JRN-C001-55); L-16; C-001-T12-R1 dispatched; PACKET 45

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. OUT_44 REJECTED: the OUT delegated evidence to a repo pointer —
inadmissible under model-B review (PM reads OUTs only); L-16 issued (OUT is the review
surface; full digests; OUT-REQUIREMENTS restated per packet — PM contributing factor
owned). T12 implementation commits stand; C-001-T12-R1 dispatched as EVIDENCE-ONLY rework
with immutability proof (zero src/tools/data changes) and a discrepancy tripwire (any
regenerated value differing from OUT_44's summaries → BLOCK). Summarized T12 outcomes
pending evidence: streaming at 20k events; F3 = physics (domain exit); tune frozen at
dt=5e-4, N=128, ratio 1.899. Gates slip one cycle: PACKET 46 = P1-A → P1-B → P1-C → Law 7
(v1.2 B3) on OUT_45 ACCEPT — committed tree, dirty=false, first held-out contact.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.2) | T12-R1 review → gate runs | OUT_45 |
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
Instruction (PACKET 40 message) stands. Gate runs (PACKET 46) require a committed tree —
merge or committed chain tip before execution.

## Recent review verdicts
OUT_44/C-001-T12: REJECT — inadmissible evidence (JRN-C001-55; L-16).
OUT_43/C-001-T11: ACCEPT — C-001-T11 VERIFIED (JRN-C001-50).
OUT_42/I-004-T2+T3: ACCEPT — I-004 COMPLETE (JRN-I004-8).
OUT_41/I-003-T3-R1: ACCEPT — corpus complete (JRN-I003-22).

## Pointers
Branch rule: T12-R1 extends task/C-001-T12 in place. Gate runs governed by
PREREGISTRATION.md v1.2; TUNE-LAW7.json is the frozen Law 7 configuration pending OUT_45
evidence.

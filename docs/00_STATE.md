# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_52 task ACCEPT; P1-A verdict SUB JUDICE (harness deviation from registered windows); C-001-T16 forensic diagnostic dispatched; PACKET 53

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core, AT THE GATE — P1-A verdict SUB JUDICE. GATE-P1-R3 executed
cleanly (all pre-flights green; 32/32 gate-authorized; halt per G2) and its checker printed
"P1-A CORPUS VERDICT: FAIL" (16/32 over tolerance; corpus worst |Δt|=2.09, |Δs|=3.18) — but
the check's own report shows it compared 0–9 events per scenario against registered windows
of 12 (quasi-chaotic, v1.3 C1) and min(200, settle) (§1), with the mandatory 13–25
exploratory tables empty. The executed procedure ≠ the registered procedure, so the ENTIRE
check is void SYMMETRICALLY — its 16 FAILs and its 16 PASSes (incl. window-0 vacuous
passes) alike (JRN-C001-87). The registered rule v1.2 B2 governs: "a harness defect is
fixed before gates, a physics shortfall stands." C-001-T16 (in flight) is the read-only
forensic diagnostic — count table, checker code audit, bounded event excerpts — with the
harness-vs-physics decision rules PRE-REGISTERED in PACKET 53 (R-a..R-e). THE PHYSICS
QUESTION IS OPEN: if engine streams are genuinely short or genuinely divergent, the
shortfall stands and the falsification record proceeds; a harness fix would only make that
FAIL admissible.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED (v1.3) — P1-A SUB JUDICE; T16 forensics IN FLIGHT | classification → T17 fix + GATE-P1-R4, or falsification record | OUT_53 |
| C-002 Curve library | BRIEFED | T3 prereg | Phase-1 gate call |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 | VERIFIED | — | — |
| I-002 | VERIFIED | — | — |
| I-003 | VERIFIED — corpus 32 locked | possible escalation if T16 fires R-b (short references) | OUT_53 |
| I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | Phase-1 gate call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   pre-flight shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2)
   — non-blocking. L-17 v2 (judge-side window/count/pairing SEMANTICS in self-test) to be
   minted with the fix packet after T16.
3. GPLv3 -only vs -or-later — Phase 3.

## Known issues
P1-A check harness deviation (OUT_52): executed windows 0–9 vs registered 12/min(200,
settle); empty mandatory exploratory tables; suspected silent min-length truncation and
possible s-parameter endpoint-wrap comparison defect — under T16 forensics; verdict SUB
JUDICE. Baseline CLI write failure at N≥512 (outside gate path; tune N=128; OUT_45).
Validator calibration_scenarios=3 (OUT_47 forward finding). Resolved: zero-event write
(T14); checker rational parse (T15).

## Recent review verdicts
OUT_52/GATE-P1-R3: task ACCEPT; P1-A verdict INADMISSIBLE AS REGISTERED — SUB JUDICE
(JRN-C001-87); C-001-T15 VERIFIED via step-4 repair.
OUT_51/C-001-T15: AMEND + RETURN scoped to criterion 7 — repair discharged at R3 step 4.
OUT_50/GATE-P1-R2: ACCEPT halt — infrastructure BLOCKED at checker (JRN-C001-79).

## Pointers
Branch rule: task/C-001-T16 from task/GATE-P1-R3 tip (stacked, JRN-I002-6). Gate
governance: PREREGISTRATION.md v1.3; classification rule of record v1.2 B2; T16 decision
rules R-a..R-e pre-registered in PACKET 53. ACCESS_LOG: 88 (all gate-authorized); T16 must
leave it at 88. R3 gate artifacts committed at b426bbd (custody-verified in T16 step 3).
GATE_SUMMARY.md stands as R3's record; the sub-judice ruling lives in JRN-C001-87 + this
STATE.

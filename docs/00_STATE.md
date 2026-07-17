# STATE — Bounce
last_updated_by: pm-cursor-grok-4.5 | trigger: OUT_71 ACCEPT — I-008-T7 VERIFIED;
S15 live; awaiting Director look-and-listen (F7 closure + F8 verdict) then decision 4

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — harness assessment loop, presentation-quality leg COMPLETE on the agent
side. I-008-T7 VERIFIED (OUT_71, 9/9): S15 assessment-grade camera and overlays
(uniform aspect-preserving scale — curve may zoom, never distort; quantized hysteretic
zoom with printed levels; 1-2-5 labeled grid/axes + scale bar; min ball draw ≥3 px with
marker ring; camera lock; pause + step-to-next-event; HUD; bounded probes) and S14.1
stamp dirty-scope (post-commit stamp clean of courier residue). S14 build stamp and S13
Load remain from T6.

CRITICAL PATH IS NOW DIRECTOR-ONLY: (1) merge `task/I-008-T7` tip and REBUILD; (2)
look-and-listen on the four assessment scenes — one line closes F7 if no detachment
(H1 confirmed); F8 closes only if physics is assessable (stable scale, no curve
distortion, visible balls, usable axes); (3) OPEN DECISION 4 (corpus-A reuse vs fresh
corpus-B — PM recommendation: B), the sole gate to D-4 step 3 (resumption bundle →
P1-A rerun, P1-B, P1-C). Falsification record JRN-C001-91 stands for the pre-T17 build.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 + T18(+R1–R3) VERIFIED; E1/E2/E4a/E4b closed | gate-resumption bundle (decisions 4+5) | Director decision 4 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness | T1–T7 VERIFIED; F8 OPEN; F7 = H1 pending | Director look-and-listen → decision 4 | Director |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (L-18; L-19; L-20; L-22) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption — GATES D-4 STEP 3. (i) reuse corpus-A; (ii)
   fresh corpus-B — PM RECOMMENDATION; (iii) hybrid.
5. Gate-resumption registration bundle: simultaneous-contact ordering; periodic reference
   horizons; S-1 semantics + reference_termination + per-class tier; checker fix + L-17
   v2; P1-B coverage of fallback/directional/time-scan paths + per-path counts; held-out
   re-test of all E-classes; energy-bound re-derivation (excursion-aware); E4a/E4b window
   asymmetry; benign cross-build numerics shifts documented.
6. Rolling/sliding contact — Phase-2 slate; urgency low under D-5.

## Known issues
Harness: F8 OPEN (S15 implemented; closes on Director look-and-listen); F7 = H1 pending
Director rebuilt re-test (one clean line). Engine: none open; monitored items per
JRN-C001-110. COURIER: inbox tracked-deletion disposition pending (Director). Baseline
CLI N≥512 (OUT_45). Validator calibration_scenarios=3 (OUT_47). PROCESS: L-21 in force;
S14.1 stamp scope live; bounded probes (S15).

## Recent review verdicts
OUT_71/I-008-T7: ACCEPT — 9/9; T7 VERIFIED; S15 live; F8 pending Director
(JRN-I008-38).
OUT_70/I-008-T6-R1: ACCEPT — 8/8; T6 VERIFIED; F7 → H1 pending; F8 registered
(JRN-I008-35).
OUT_69/I-008-T6: FAILED accepted as valid ending — harmless halt; whitelist corrected
(JRN-I008-32).

## Pointers
Branch rule: merge task/I-008-T7 tip (stacked from T6-R1). Director REBUILD before live
assessment. Standing forms: L-20 committed-tree OUTs; L-21 hygiene; L-22 machine-checked
numbers; L-18/L-19; c7-v2 isolation with base proof; harness whitelists include src/
read-only; bounded probes (S15); S14.1 dirty scope. ACCESS_LOG: 88. Directions: D-4
(gated on decision 4), D-5, D-6. Findings F1–F8 (F7 pending closure line; F8 open
pending Director). Gate-resumption bundle: decisions 4 + 5.

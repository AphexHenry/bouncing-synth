# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_67 ACCEPT — E4 campaign CLOSED, C-001-T18
(+R1–R3) VERIFIED; I-008-T5-R2 dispatched (scenes v3 + F6); decision 4 gates D-4 step 3

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — E4 CAMPAIGN CLOSED (OUT_67, 12/12): the engine sustains 2000-event confined
lossless streams on both problem families (W-well quartic, bezier valley); energy
conserved at the held 1e-9 bound (9.32e-10); E4b reference window at 1.54e-13; event
storage vector-backed with round-trip proof; capacity scan flight-time-derived (suite
78/78 in 0.6 s); departure-root deflation now covers x- and s-domains with every root
path ending in the registered refinement schedule. C-001-T18+R1–R3 VERIFIED. Monitored
for resumption: E4a-vs-E4b window asymmetry (5.9e-10 vs 1.5e-13); scaling excursion at
event 1678; per-path count drift across builds (P1-B coverage item).

NOW IN FLIGHT: I-008-T5-R2 (PACKET 68) — the harness backlog on the capable engine: F6
display fix (bezier replay world-mapping; paste-provable contact-frame check), scene
library v3 (genuine W-well and bezier-valley scenes, cap-reached 2000, identity +
distinctness criteria per L-19), frames, camera re-verification, determinism, 78/78
regression. Then: DIRECTOR RE-ASSESSMENT (look-and-listen on the real scenes) and
DECISION 4 — still the sole gate to D-4 step 3 (resumption bundle → P1-B/P1-C).
Falsification record JRN-C001-91 stands for the pre-T17 build.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 + T18(+R1–R3) VERIFIED; defect classes E1/E2/E4a/E4b closed with standing coverage; E3 inferentially fixed | gate-resumption bundle (decisions 4+5) → P1-A rerun, P1-B, P1-C | Director decision 4 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness | T1–T4 VERIFIED; T5-R2 IN FLIGHT (scenes v3 + F6 + frames + re-assessment runway) | OUT_68 → Director re-assessment | OUT_68 |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (L-18 derivation; L-19 clause-to-criterion; L-20
   committed-tree emission) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption — GATES D-4 STEP 3. (i) reuse corpus-A; (ii)
   fresh corpus-B — PM RECOMMENDATION (strengthened: E4 pattern-overlap with 13 R-a rows;
   corpus-B would also carry E4-class long-chain scenarios + the reference_termination
   schema); (iii) hybrid.
5. Gate-resumption registration bundle: simultaneous-contact ordering; periodic reference
   horizons; S-1 semantics + reference_termination + per-class tier; checker fix + L-17
   v2; P1-B coverage of T17 fallback/directional + T18 time-scan paths + per-path event
   counts; held-out re-test of all E-classes incl. both original E3 scenarios;
   energy-bound re-derivation modeling excursions (event-1678 datum); E4a/E4b window
   asymmetry characterization; gate-runner storage exposure check (resolved in core;
   confirm runner).
6. Rolling/sliding contact — Phase-2 slate; urgency low under D-5.

## Known issues
Engine: none open — E1/E2/E4a/E4b closed with standing coverage; E3 held-out re-test at
resumption; monitored items per JRN-C001-110 (window asymmetry; scaling excursion;
path-mix drift). Harness: F6 display divergence UNDER FIX (T5-R2); scene library v3 in
flight. COURIER: inbox tracked-deletion disposition pending (Director). Baseline CLI
N≥512 (OUT_45). Validator calibration_scenarios=3 (OUT_47). PROCESS: L-21 in force;
first artifact clean. Resolved this campaign: E4a/E4b; 256-array storage UB; capacity
hang; CLI overrun; circular reference; energy-drift precision regression.

## Recent review verdicts
OUT_67/C-001-T18-R3: ACCEPT — 12/12; E4 closed; C-001-T18+R1–R3 VERIFIED (JRN-C001-110).
OUT_66/C-001-T18-R2: RETURN_FOR_REPAIR — inadmissible emission; repaired in R3; L-20 +
L-21 issued (JRN-C001-107).
OUT_65/C-001-T18-R1: RETURN_FOR_REPAIR — API audit ordered (JRN-C001-104).

## Pointers
Branch rule: task/I-008-T5-R2 from task/C-001-T18 tip (stacked — the scenes need the
fixed engine). Merge to main: batched at Director's convenience (chain now long; verify
final OUT commit as tip per L-12). Standing forms: L-20 committed-tree OUTs, all evidence
inline; L-21 hygiene artifact; isolation from CLAIM-stated base with git proof; L-18
derivations; L-19 clause-to-criterion; confinement = cap-reached. ACCESS_LOG: 88.
Directions: D-4 (step 3 gated on decision 4), D-5, D-6. Held bound: e=1 energy drift
≤ 1e-9 / 2000 events. Findings F1–F6 (F6 under fix). Gate-resumption bundle: decisions
4 + 5.

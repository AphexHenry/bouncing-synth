# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_60 ACCEPT; Director asked for curved surfaces
— already supported; I-008-T4 dispatched (S11 assessment scene library); decision 4 still
gates D-4 step 3

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — D-4 steps 1–2 COMPLETE; harness in assessment-feedback loop. C-001-T17 VERIFIED.
I-008 T1–T3 VERIFIED (feature-complete core); T4 IN FLIGHT (PACKET 61): the S11 assessment
scene library — four curved scenes (parabola bowl, two-well deg-4 poly, bezier landscape,
three-ball polyphony) designed for sustained default-lossless playback (≥60 s sim time
within ≤2000 events each), stored under tools/bounce-view/scenarios/ as presentation
assets; data/ remains fully frozen. Curved-surface rendering itself already existed — the
Director had only seen the FL-1 flat-line example.

CRITICAL PATH THROUGH THE DIRECTOR, unchanged: (1) live re-assessment (now best done on
the T4 scenes once landed); (2) inbox courier disposition (uncommitted tracked deletions,
JRN-I008-14); (3) OPEN DECISION 4 (corpus-A reuse vs fresh corpus-B mint) — the single
gate to D-4 step 3: resumption bundle → P1-B/P1-C. Falsification record JRN-C001-91
stands for the pre-T17 build; registered P1-A verdict deferred to gate resumption.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 VERIFIED | gate-resumption bundle (decisions 4+5) → P1-B/P1-C | Director decision 4 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | T1–T3 VERIFIED; T4 IN FLIGHT (S11 scenes) | OUT_61 review → Director plays the scenes | OUT_61 |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (incl. P6 §4 numeric-criterion derivation rule per L-18) —
   non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption — GATES D-4 STEP 3. (i) reuse corpus-A
   (development-exposed at defect-class level); (ii) fresh corpus-B, corpus-A becomes
   exploratory regression set — PM RECOMMENDATION; (iii) hybrid (not recommended). Also
   sets where the reference_termination schema fix lands.
5. Gate-resumption registration bundle (all PRE-registered before any future gate
   execution): simultaneous-contact ordering rule (R-e); periodic reference horizons; S-1
   post-settle semantics — reference-termination schema gap sighted three times on
   calibration; schema gains reference_termination + explicit per-class tier as mint
   requirements; checker fix + L-17 v2; P1-B coverage of the T17 time-domain-fallback and
   directional-search branches; held-out re-test of E-classes incl. the two original E3
   scenarios (fixed inferentially only).
6. Rolling/sliding contact — Phase-2 slate question; urgency low under D-5. PM
   recommendation: defer to Phase-2 planning.

## Known issues
Engine: E1/E2 fixed (T17 VERIFIED); E3 green on the fresh fixture — the two original
held-out E3 scenarios remain untested until gate resumption. T17's time-domain fallback +
directional search: P1-B coverage item (decision 5). Checker harness (T16 D2/D3) —
deferred to gate resumption. Fixture schema: no reference_termination field; per-class
tier wording — routed to the resumption bundle. COURIER: uncommitted deletions of tracked
inbox/PACKET_1–11.md — Director disposition pending (JRN-I008-14). Baseline CLI write
failure at N≥512 (OUT_45). Validator calibration_scenarios=3 (OUT_47). Resolved:
zero-event write (T14); checker rational parse (T15); contact-loop E1/E2 (T17);
__pycache__ residue (OUT_56); harness F1/F2/F3 (T2/T3, Director taste verdict pending).

## Recent review verdicts
OUT_60/apply-only: ACCEPT (JRN-I008-15).
OUT_59/I-008-T3: ACCEPT — 12/12; I-008-T3 VERIFIED (JRN-I008-14).
OUT_58/I-008-T2: ACCEPT — c7-v2; L-18 violation owned by PM; VERIFIED (JRN-I008-11).

## Pointers
Branch rule: task/I-008-T4 from packet/60 tip (stacked). Merge instruction: merge the
latest task tip into main when convenient (batched); verify final OUT commit as tip
(L-12). Standing criterion form: isolation from the CLAIM-stated base (c7-v2). ACCESS_LOG:
88 — must remain 88 until gate resumption. Directions of record: D-4 (step 3 gated on
decision 4), D-5 (default lossless — implemented). Falsification record: JRN-C001-91
(pre-T17 build). Invariant set of record: nine TEST_CASEs. Numeric-criterion rule: L-18.
Gate-resumption bundle: decisions 4 + 5. Phase-2 slate: decision 6.

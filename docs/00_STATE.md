# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_58 ACCEPT (c7 amended, L-18 violation owned);
D-5 recorded (default lossless playback); I-008-T3 dispatched (PACKET 59); decision 4
still gates D-4 step 3

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — D-4 steps 1 and 2 COMPLETE; assessment-feedback loop running. C-001-T17
VERIFIED. I-008-T1 and T2 VERIFIED: bounce-view now has the optimized render path (GREEN
p95 16.381 ms @120 Hz under the registered bound), settled-ball persistence, and the AV-2
voice. OUT_58 ACCEPTED with criterion 7 amended (c7-v2 — isolation ranges from the
CLAIM-stated base; the main-anchored original asserted Director courier state: an L-18
violation by the PM, owned in JRN-I008-11). Measurand finding: OUT_58's RED perf numbers
are not interval-comparable to GREEN; S8 v2 pins the measurand and T3 re-pastes perf.

DIRECTOR PRODUCT DIRECTION D-5 (recorded): the tool aims at infinite bounces — default
lossless (e=1, confirming v1.2 B4); damping strictly opt-in. TASK I-008-T3 IN FLIGHT
(PACKET 59): S10 restitution override (interactive default e=1; evidence modes
scenario-faithful), S8 v2 perf re-paste, S9 language rule.

The falsification record JRN-C001-91 describes the pre-T17 build; the registered P1-A
verdict on the fixed build stays deferred to gate resumption. D-4 STEP 3 REMAINS GATED ON
DECISION 4 (corpus-A reuse vs fresh corpus-B mint — PM recommendation: B).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 VERIFIED; falsification record stands for the pre-T17 build | gate-resumption bundle (open decisions 4+5) → P1-B/P1-C | Director decision 4 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | T1+T2 VERIFIED; T3 IN FLIGHT (PACKET 59) — D-5 default-lossless playback | OUT_59 review → Director re-assessment | OUT_59 |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2; P6 §4
   numeric-criterion derivation rule per L-18 — urgency raised by the OUT_58 c7 violation,
   JRN-I008-11) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption: corpus-A DEVELOPMENT-EXPOSED at defect-class
   level; confirmatory reuse vs fresh corpus-B mint. GATES D-4 STEP 3 — PM recommendation
   on record: fresh corpus-B; corpus-A becomes exploratory regression set.
5. Gate-resumption registration bundle (all PRE-registered before any future gate
   execution): simultaneous-contact ordering rule (R-e); periodic reference horizons;
   S-1 post-settle semantics — reference-termination schema gap now sighted three times on
   calibration (CF-E2b 26/12, CF-E2a 28/4); schema gains reference_termination + explicit
   per-class tier as mint requirements; checker fix + L-17 v2; P1-B coverage of the T17
   time-domain-fallback and directional-search branches; held-out re-test of E-classes
   incl. the two original E3 scenarios (fixed inferentially only).
6. Rolling/sliding contact (from finding F2): charter a rolling-contact component thesis
   for the Phase-2 slate? Options: (i) no — settled-at-rest is the behavior (D-5 default
   e=1 never settles); (ii) yes — new component thesis (deterministic fixed-order
   quadrature design, own gates); (iii) defer to Phase-2 planning with the slate. PM
   recommendation: (iii). D-5 lowers this decision's urgency further: in the default
   product regime, settling never occurs.

## Known issues
Engine: E1/E2 fixed (T17 VERIFIED); E3 green on the fresh fixture — the two original
held-out E3 scenarios remain untested until gate resumption. T17's time-domain fallback +
directional search: P1-B coverage item (decision 5). Checker harness (T16 D2/D3) —
deferred to gate resumption. Fixture schema: no reference_termination field; per-class
tier wording — routed to the resumption bundle. Harness: F1 fixed under the registered
GREEN bound but RED not interval-comparable (measurand shift; S8 v2 pins it — re-paste in
T3); F2 settled-ball persistence DONE; F3 AV-2 DONE — Director re-assessment pending after
T3. Baseline CLI write failure at N≥512 (OUT_45). Validator calibration_scenarios=3
(OUT_47). Resolved: zero-event write (T14); checker rational parse (T15); contact-loop
E1/E2 (T17); __pycache__ residue (OUT_56).

## Recent review verdicts
OUT_58/I-008-T2: ACCEPT — c7 amended to c7-v2, satisfied on file; L-18 violation owned by
PM; I-008-T2 VERIFIED (JRN-I008-11).
OUT_57/apply-only: ACCEPT (JRN-I008-8).
OUT_56/I-008-T1-R1: ACCEPT — I-008-T1 VERIFIED (JRN-I008-7).

## Pointers
Branch rule: task/I-008-T3 from task/I-008-T2 tip (stacked; carries packet/57). Director
merge instruction: merge the task/I-008-T2 chain (or later the T3 tip) into main —
batched, non-blocking; verify final OUT commit as tip per L-12. Standing criterion form:
isolation ranges from the CLAIM-stated base (c7-v2). ACCESS_LOG: 88 — must remain 88 until
gate resumption. Directions of record: D-4 (step 3 gated on decision 4), D-5 (default
lossless; damping opt-in). Falsification record: JRN-C001-91 (pre-T17 build). Invariant
set of record: nine TEST_CASEs. Numeric-criterion rule: L-18. Assessment findings F1–F3:
JRN-I008-8/11. Gate-resumption bundle: decisions 4 + 5. Phase-2 slate: decision 6.

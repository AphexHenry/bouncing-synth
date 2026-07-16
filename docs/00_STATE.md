# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_59 ACCEPT — I-008-T3 VERIFIED; harness
feature-complete for assessment; critical path now runs through Director inputs
(re-assessment + decision 4)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — D-4 steps 1–2 COMPLETE; assessment-feedback loop delivered in full. C-001-T17
VERIFIED. I-008 T1–T3 VERIFIED: bounce-view is feature-complete for its purpose — D-5
default-lossless interactive playback (e=1 override; damping strictly opt-in via
--restitution / --scenario-restitution; effective restitution always printed), AV-2 voice,
settled-ball persistence, optimized render path measured under the S8 v2 measurand (p95
9.314 ms @120 Hz), deterministic selftest, Law-1 guard. The e=1 override selftest reached
its 500-event cap cleanly (500/500 blip-per-collision).

THE CRITICAL PATH NOW RUNS THROUGH THE DIRECTOR: (1) live re-assessment of the harness
(fluidity, AV-2 voice, infinite default) — RUN section in OUT_59; (2) inbox courier
disposition (uncommitted deletions of tracked inbox/PACKET_1–11.md — restore or commit;
JRN-I008-14); (3) OPEN DECISION 4 (corpus-A reuse vs fresh corpus-B mint) — the single
gate to D-4 step 3: the gate-resumption registration bundle, then P1-B/P1-C.

The falsification record JRN-C001-91 describes the pre-T17 build; the registered P1-A
verdict on the fixed build stays deferred to gate resumption.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 VERIFIED; falsification record stands for the pre-T17 build | gate-resumption bundle (decisions 4+5) → P1-B/P1-C | Director decision 4 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | T1–T3 VERIFIED — FEATURE-COMPLETE for D-4 assessment | Director re-assessment | Director |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2; P6 §4
   numeric-criterion derivation rule per L-18) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption — GATES D-4 STEP 3. Options: (i) reuse corpus-A
   (development-exposed at defect-class level); (ii) mint fresh corpus-B, corpus-A becomes
   exploratory regression set — PM RECOMMENDATION; (iii) hybrid (two campaigns; not
   recommended). The answer also sets where the reference_termination schema fix lands.
5. Gate-resumption registration bundle (all PRE-registered before any future gate
   execution): simultaneous-contact ordering rule (R-e); periodic reference horizons;
   S-1 post-settle semantics — reference-termination schema gap sighted three times on
   calibration (CF-E2b 26/12, CF-E2a 28/4); schema gains reference_termination + explicit
   per-class tier as mint requirements; checker fix + L-17 v2; P1-B coverage of the T17
   time-domain-fallback and directional-search branches; held-out re-test of E-classes
   incl. the two original E3 scenarios (fixed inferentially only).
6. Rolling/sliding contact — Phase-2 slate question; urgency low under D-5 (default e=1
   never settles). PM recommendation: defer to Phase-2 planning.

## Known issues
Engine: E1/E2 fixed (T17 VERIFIED); E3 green on the fresh fixture — the two original
held-out E3 scenarios remain untested until gate resumption. T17's time-domain fallback +
directional search: P1-B coverage item (decision 5). Checker harness (T16 D2/D3) —
deferred to gate resumption. Fixture schema: no reference_termination field; per-class
tier wording — routed to the resumption bundle. COURIER: uncommitted deletions of tracked
inbox/PACKET_1–11.md in the working tree — Director disposition pending (restore or commit
cleanup; JRN-I008-14); risk: a future `git add -A` commits them silently. Baseline CLI
write failure at N≥512 (OUT_45). Validator calibration_scenarios=3 (OUT_47). Resolved:
zero-event write (T14); checker rational parse (T15); contact-loop E1/E2 (T17);
__pycache__ residue (OUT_56); harness findings F1/F2/F3 (T2/T3, pending Director taste
verdict).

## Recent review verdicts
OUT_59/I-008-T3: ACCEPT — 12/12 COMPLIANT; I-008-T3 VERIFIED (JRN-I008-14).
OUT_58/I-008-T2: ACCEPT — c7 amended to c7-v2; L-18 violation owned by PM; VERIFIED
(JRN-I008-11).
OUT_57/apply-only: ACCEPT (JRN-I008-8).

## Pointers
Merge instruction of record: merge the task/I-008-T3 tip into main (carries the stacked
chain through serial 59); verify final OUT commit as tip (L-12). Standing criterion form:
isolation ranges from the CLAIM-stated base (c7-v2). ACCESS_LOG: 88 — must remain 88 until
gate resumption. Directions of record: D-4 (step 3 gated on decision 4), D-5 (default
lossless; damping opt-in — implemented, OUT_59). Falsification record: JRN-C001-91
(pre-T17 build). Invariant set of record: nine TEST_CASEs. Numeric-criterion rule: L-18.
Gate-resumption bundle: decisions 4 + 5. Phase-2 slate: decision 6.

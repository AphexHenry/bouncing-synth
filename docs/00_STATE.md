# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_57 ACCEPT; merges done; Director AV assessment
recorded (F1–F3) — D-4 step 2 COMPLETE; I-008-T2 dispatched (PACKET 58); open decision 6
added (rolling contact); decision 4 still gates D-4 step 3

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — D-4 steps 1 and 2 COMPLETE. C-001-T17 VERIFIED (contact loop fixed; nine
invariant TEST_CASEs of record; 63/63 suite). I-008-T1 VERIFIED; stacked chain merged to
main through serial 57. The Director's live AV assessment is on record (JRN-I008-8):
F1 frame rate not fluid (~10 fps felt) — harness defect, T2 fixes repro-first with
measured evidence; F2 settled ball disappears — registered S-1/R1 semantics made visible:
harness gains settled-ball persistence (T2), true rolling contact escalated as open
decision 6 (Phase-2 component thesis question; the e=1 product default never settles);
F3 sound too "beep" — AV-1 superseded by the AV-2 voice spec (BRIEF S3 v2). TASK I-008-T2
IN FLIGHT (PACKET 58).

The falsification record JRN-C001-91 describes the pre-T17 build; the registered P1-A
verdict on the fixed build stays deferred to gate resumption. D-4 STEP 3 REMAINS GATED ON
DECISION 4 (corpus-A confirmatory reuse vs fresh corpus-B mint — PM recommendation: B).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 VERIFIED; merged to main; falsification record stands for the pre-T17 build | gate-resumption bundle (open decisions 4+5) → P1-B/P1-C | Director decision 4 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | VERIFIED; assessment delivered (F1–F3); T2 IN FLIGHT (PACKET 58) | OUT_58 review → Director re-assessment | OUT_58 |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2; P6 §4
   numeric-criterion derivation rule per L-18) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption: corpus-A is DEVELOPMENT-EXPOSED at defect-class
   level (T16 D4); confirmatory reuse vs fresh corpus-B mint (I-003 scope). GATES D-4 STEP
   3 — PM recommendation on record: fresh corpus-B for confirmatory gates, corpus-A
   retained as exploratory regression set.
5. Gate-resumption registration bundle (all to be PRE-registered before any future gate
   execution): simultaneous-contact ordering rule (R-e / HO-flat-periodic-3); periodic
   reference horizons (refs 1–8 events vs §1's H=200 for non-settling orbits); S-1
   post-settle semantics — CF-E2b 26-vs-12 open as a schema gap; schema gains
   reference_termination (settle | horizon <N> | cap) + explicit per-class tier as mint
   requirements (JRN-I008-7, JRN-C001-97); checker fix + L-17 v2; P1-B coverage of the T17
   time-domain-fallback and directional-search branches (JRN-C001-95); held-out re-test of
   E-classes incl. the two original E3 scenarios (fixed inferentially only).
6. NEW — Rolling/sliding contact (from AV assessment finding F2): a SETTLED ball currently
   ends its Phase-1 story at rest (S-1; rolling explicitly out of scope, DELIVERABLE_B §3
   / R1). Question: charter a rolling-contact component thesis for the Phase-2 slate?
   Options: (i) no — settled-at-rest is the product behavior (default e=1 never settles);
   (ii) yes — new component thesis (constrained motion along the curve with a departure
   condition; no closed-form time-parametrization in general → a deterministic fixed-order
   quadrature design, its own gates, NOT an engine patch); (iii) defer to Phase-2 planning
   with the slate. PM recommendation: (iii) — decide with the full Phase-2 slate in view;
   nothing in Phase 1 depends on it.

## Known issues
Engine: E1/E2 fixed (T17 VERIFIED); E3 green on the fresh fixture — the two original
held-out E3 scenarios remain untested until gate resumption. T17's time-domain fallback +
directional search: P1-B coverage item (decision 5). Checker harness (T16 D2/D3): window
shrinkage; silent zip-truncation; positional pairing; no simultaneity/wrap handling —
deferred to gate resumption. Fixture schema: no reference_termination field; per-class
tier wording in briefs — routed to the resumption bundle. Harness (Director assessment):
F1 frame rate, F2 settled-ball visibility, F3 voice quality — UNDER FIX (T2). Baseline CLI
write failure at N≥512 (outside current path; OUT_45). Validator calibration_scenarios=3
(OUT_47). Resolved: zero-event write (T14); checker rational parse (T15); contact-loop
E1/E2 (T17); __pycache__ residue (OUT_56).

## Recent review verdicts
OUT_57/apply-only: ACCEPT (JRN-I008-8).
OUT_56/I-008-T1-R1: ACCEPT — 7/7 COMPLIANT; I-008-T1 VERIFIED (JRN-I008-7).
OUT_55/I-008-T1: BLOCKED → AMEND + RETURN scoped (JRN-I008-4); C-001-T17 VERIFIED
(JRN-C001-96); L-18 issued.

## Pointers
Branch rule: task/I-008-T2 from main (chain merged through serial 57; packet/57 merged or
mergeable — Director verifies tip per L-12). ACCESS_LOG: 88 — must remain 88 until gate
resumption. Contamination rule of record: fresh fixtures never replicate held-out
parameter tuples. Falsification record: JRN-C001-91 (pre-T17 build). Direction of record:
D-4 (steps 1–2 complete; step 3 gated on decision 4). Invariant set of record: nine
TEST_CASEs (JRN-C001-96). Numeric-criterion rule: L-18. Assessment findings of record:
F1–F3 (JRN-I008-8). Gate-resumption bundle: open decisions 4 + 5. Phase-2 slate question:
open decision 6.

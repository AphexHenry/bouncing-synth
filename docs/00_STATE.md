# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_56 ACCEPT — I-008-T1 VERIFIED; batched merge
released; awaiting Director AV assessment (D-4 step 2) and decision 4 to open the
gate-resumption bundle

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — D-4 steps 1 and 2 (build side) COMPLETE. C-001-T17 VERIFIED (JRN-C001-96):
contact-loop defect classes E1/E2/E3 fixed; nine invariant TEST_CASEs of record; 63/63
suite; ACCESS_LOG 88 throughout. I-008-T1 VERIFIED (JRN-I008-7): bounce-view operational —
deterministic headless selftest, Law-1 path guard proven, frames committed, RUN section on
file (OUT_55). The falsification record JRN-C001-91 describes the pre-T17 build; the
registered P1-A verdict on the fixed build stays deferred to gate resumption.

PENDING ON THE DIRECTOR: (1) batched merge of the stacked chain task/C-001-T17 →
task/I-008-T1 → task/I-008-T1-R1 into main (merge the R1 tip; verify the final OUT commit
as tip per L-12); (2) the live AV assessment (D-4 step 2 payoff; RUN commands in OUT_55);
(3) decision 4 — corpus-A confirmatory reuse vs fresh corpus-B mint — which opens the PM's
drafting of the gate-resumption registration bundle (D-4 step 3).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 VERIFIED; contact loop fixed, invariants of record; falsification record stands for the pre-T17 build | gate-resumption bundle (open decisions 4+5) → P1-B/P1-C | Director decision 4 + AV assessment |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | VERIFIED (T1+R1, OUT_55/56) | Director live assessment → D-4 step 3 | Director |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2; P6 §4
   numeric-criterion derivation rule per L-18) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption: corpus-A is DEVELOPMENT-EXPOSED at defect-class
   level (T16 D4); confirmatory reuse vs fresh corpus-B mint (I-003 scope). THIS DECISION
   OPENS D-4 STEP 3 — PM recommendation delivered with PACKET 57.
5. Gate-resumption registration bundle (all to be PRE-registered before any future gate
   execution): simultaneous-contact ordering rule (R-e / HO-flat-periodic-3); periodic
   reference horizons (refs 1–8 events vs §1's H=200 for non-settling orbits); S-1
   post-settle semantics — CF-E2b 26-vs-12 remains OPEN as a schema gap (no
   reference_termination field, OUT_56); schema gains reference_termination
   (settle | horizon <N> | cap) + explicit per-class tier as mint requirements
   (JRN-I008-7, JRN-C001-97); checker fix + L-17 v2; P1-B coverage of the T17
   time-domain-fallback and directional-search branches (JRN-C001-95); held-out re-test of
   E-classes incl. the two original E3 scenarios (fixed inferentially only).

## Known issues
Engine: E1/E2 fixed with nine invariant TEST_CASEs of record (T17 VERIFIED); E3 green on
the fresh fixture (5.6e-16) — the two original held-out E3 scenarios remain untested until
gate resumption. T17's time-domain fallback + directional search: P1-B coverage item (open
decision 5). Checker harness (T16 D2/D3): window shrinkage; silent zip-truncation;
positional pairing; no simultaneity/wrap handling — deferred to gate resumption. Fixture
schema: no reference_termination field; per-class tier wording in briefs (JRN-C001-97) —
both routed to the resumption bundle. Baseline CLI write failure at N≥512 (outside current
path; OUT_45). Validator calibration_scenarios=3 (OUT_47). Resolved: zero-event write
(T14); checker rational parse (T15); contact-loop E1/E2 (T17); __pycache__ residue
(R1 gitignore, OUT_56).

## Recent review verdicts
OUT_56/I-008-T1-R1: ACCEPT — 7/7 COMPLIANT; I-008-T1 VERIFIED (JRN-I008-7).
OUT_55/I-008-T1: BLOCKED → AMEND + RETURN scoped to criteria 3 and 6 (JRN-I008-4); repairs
adjudicated; C-001-T17 VERIFIED (JRN-C001-96); L-18 issued.
OUT_54/C-001-T17: AMEND + RETURN scoped to criteria 3 and 6 (JRN-C001-95); repairs landed.

## Pointers
Merge instruction of record: merge task/I-008-T1-R1 tip into main (carries the stacked
chain); verify final OUT commit as tip (L-12). ACCESS_LOG: 88 — must remain 88 until gate
resumption. Contamination rule of record: fresh fixtures never replicate held-out
parameter tuples (JRN-C001-91/92). Falsification record: JRN-C001-91 (pre-T17 build).
Direction of record: D-4 (steps 1–2 build side complete; Director assessment + decision 4
open step 3). Invariant set of record: nine TEST_CASEs (JRN-C001-96). Numeric-criterion
rule: L-18. Gate-resumption bundle: open decisions 4 + 5.

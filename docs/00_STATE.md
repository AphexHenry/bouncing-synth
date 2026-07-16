# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_55 disposition — C-001-T17 VERIFIED; OUT_55
AMEND + RETURN scoped (c3 adjudicated, c6 PM defect → L-18); I-008-T1-R1 dispatched
(PACKET 56); Director AV assessment runnable

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — D-4 step 1 COMPLETE: C-001-T17 VERIFIED (JRN-C001-96). Contact-loop defect
classes E1/E2/E3 fixed with evidence of record: 4/4 CF fixtures GREEN (worst |Δt| 1.2e-13,
CF-E3 at 5.6e-16), nine permanent invariant TEST_CASEs (per-fixture monotone-t and
no-duplicate, plus 1e-9 reference agreement), 63/63 doctest, FL-1/PB-1 exact,
repeat-identity N=3, ACCESS_LOG 88 throughout. The falsification record JRN-C001-91
describes the pre-T17 build; the registered P1-A verdict on the fixed build stays deferred
to gate resumption.

D-4 step 2 SUBSTANTIALLY DELIVERED: bounce-view harness operational on branch task/I-008-T1
— SDL2 2.32.8 target built, deterministic headless selftest (FL-1 A/B diff = 0), Law-1
path guard proven (exact refusal, exit=2, guard precedes existence check), 2 PPM frames
committed, RUN section on file (OUT_55). OUT_55 ended BLOCKED on two criteria; both
adjudicated: (i) repair-B byte-match — OUT_54's TR listed compressed notation as literal
test names; the nine true TEST_CASEs are now of record and repair-B's purpose is fulfilled;
(ii) step-9 tripwire — PM authoring defect (reference-window count 12 bound to an S5
settle run that correctly emits 26); second occurrence of the empirical-value class →
L-18 issued + P6 §4 amendment proposal on the open-decision-2 bundle. I-008-T1-R1
dispatched (PACKET 56): suite-run tripwire, CF-E2b metadata disambiguation, pycache
gitignore. The DIRECTOR AV ASSESSMENT (D-4 step 2 payoff) is runnable now from OUT_55's
RUN section and proceeds in parallel with R1.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 VERIFIED (JRN-C001-96); contact loop fixed, invariants of record; falsification record stands for the pre-T17 build | gate-resumption bundle (open decisions 4+5) | D-4 steps 2–3 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | T1 delivered (OUT_55, AMEND + RETURN scoped); R1 IN FLIGHT (PACKET 56); harness runnable for Director assessment | I-008-T1 VERIFIED at OUT_56 → register update + batched merges | OUT_56 · Director AV assessment |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2; NEW — P6 §4
   numeric-criterion derivation rule per L-18) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption: corpus-A is DEVELOPMENT-EXPOSED at defect-class
   level (T16 D4); confirmatory reuse vs fresh corpus-B mint (I-003 scope).
5. Gate-resumption registration bundle (all to be PRE-registered before any future gate
   execution): simultaneous-contact ordering rule (R-e / HO-flat-periodic-3); periodic
   reference horizons (refs 1–8 events vs §1's H=200 for non-settling orbits); S-1
   post-settle semantics — now with a live calibration instance: CF-E2b settle run 26
   events vs 12-event reference (generator-horizon vs settle-limited disambiguation pends
   R1 step 5 metadata); checker fix + L-17 v2; P1-B coverage of the T17
   time-domain-fallback and directional-search branches (JRN-C001-95); held-out re-test of
   E-classes incl. the two original E3 scenarios (fixed inferentially only).

## Known issues
Engine: E1/E2 fixed with nine invariant TEST_CASEs of record (T17 VERIFIED); E3 green on
the fresh fixture (5.6e-16) — the two original held-out E3 scenarios remain untested until
gate resumption. T17's time-domain fallback + directional search: P1-B coverage item (open
decision 5). Checker harness (T16 D2/D3): window shrinkage; silent zip-truncation;
positional pairing; no simultaneity/wrap handling — deferred to gate resumption. Baseline
CLI write failure at N≥512 (outside current path; OUT_45). Validator
calibration_scenarios=3 (OUT_47). Workspace: tools/refsim/__pycache__/ and
tools/scenarios/__pycache__/ untracked residue — gitignore disposition in R1 (L-13 v2).
Resolved: zero-event write (T14); checker rational parse (T15); contact-loop E1/E2 (T17).

## Recent review verdicts
OUT_55/I-008-T1: BLOCKED → AMEND + RETURN scoped to criteria 3 and 6 (JRN-I008-4); 9/11
COMPLIANT; harness evidence stands; C-001-T17 VERIFIED on landed repairs (JRN-C001-96);
L-18 issued.
OUT_54/C-001-T17: AMEND + RETURN scoped to criteria 3 and 6 (JRN-C001-95); repairs rode
PACKET 55 and landed.
OUT_53/C-001-T16: ACCEPT — classification ratified; falsification record (JRN-C001-91).

## Pointers
Branch rule: task/I-008-T1-R1 from task/I-008-T1 tip (stacked, JRN-I002-6). Main merges of
task/C-001-T17, task/I-008-T1, and task/I-008-T1-R1 are held until OUT_56 review, then
batched. ACCESS_LOG: 88 — must remain 88 (no held-out execution until gate resumption;
bounce-view carries the S6 Law-1 guard, proven OUT_55). Contamination rule of record:
fresh fixtures never replicate held-out parameter tuples (JRN-C001-91/92). Falsification
record: JRN-C001-91 (pre-T17 build). Direction of record: D-4 (step 1 complete; step 2
assessment runnable; step 3 next). Invariant set of record: nine TEST_CASEs (JRN-C001-96).
Numeric-criterion rule: L-18. Gate-resumption bundle: open decisions 4 + 5.

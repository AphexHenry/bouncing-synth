# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_63 ACCEPT — diagnostic fired BRANCH B; defect
class E4 registered (premature stream termination, confined e=1 W-well dead at 25
events); C-001-T18 dispatched (PACKET 64); I-008-T5-R2 deferred behind T18

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — ENGINE TRACK REOPENED. The I-008 diagnostic (OUT_63, designed BLOCKED) proved
by energy conservation that a confined lossless run dies early: genuine W-well quartic,
E0/m = 5.78 against rim potential 9,900 (g·y_wall = 108,900), stream ends at 25/2000
events with the ball mid-well at |v_n| ≈ 4.08, settled=false. DEFECT CLASS E4: silent
premature stream termination (E1/E2-family cousin; deg-4 a2<0 and long lossless chains
were never probed by any prior fixture). Attribution held at pipeline level: the engine
is the strong suspect but D1 ran through the harness; C-001-T18 (PACKET 64) isolates with
an engine-only repro FIRST, then fixes repro-first per the T17 pattern, adds a standing
e=1 energy-drift invariant and long-chain probes to the test diet, and validates a
50-event Tier-2 window. Bezier early-end (~38 events) rides as E4b candidate. Banked from
OUT_63 regardless: T5 evidence anchored in commits; bezier helper dispositioned
display-only (S1 clean); D1 scene + method committed.

SEQUENCE: OUT_64 (T18) → I-008-T5-R2 (scene library v3 + Director re-assessment) → gate
resumption (decisions 4+5). P1-C RELEVANCE, stated plainly: long-horizon confined runs
ARE P1-C's substance — E4's fix is now on the critical path to the loop-stability gate.
Falsification record JRN-C001-91 stands for the pre-T17 build; registered P1-A verdict
deferred to gate resumption.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | T17 VERIFIED; E4 REGISTERED (JRN-C001-98) — T18 IN FLIGHT: isolate engine-vs-harness, root-cause, fix | OUT_64 → gate-resumption bundle (decisions 4+5) | OUT_64 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness | T1–T4 VERIFIED; T5-R1 CLOSED-BLOCKED (successful diagnostic, JRN-I008-24); T5-R2 (scene library v3) DEFERRED behind C-001-T18 | after OUT_64 | C-001-T18 |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (incl. P6 §4 derivation rule per L-18; P6 §4
   clause-to-criterion mapping per L-19) — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption — GATES D-4 STEP 3. (i) reuse corpus-A; (ii)
   fresh corpus-B — PM RECOMMENDATION; (iii) hybrid (not recommended).
5. Gate-resumption registration bundle: simultaneous-contact ordering; periodic reference
   horizons; S-1 semantics + reference_termination schema field + per-class tier; checker
   fix + L-17 v2; P1-B coverage of T17 fallback/directional branches; held-out re-test of
   E-classes incl. both original E3 scenarios; NEW — E4: held-out cross-check from the
   COMMITTED T16 classification tables (analysis-only, zero held-out execution) + E4
   coverage in any corpus-B mint (long-chain confined lossless family).
6. Rolling/sliding contact — Phase-2 slate; urgency low under D-5.

## Known issues
Engine: E4 UNDER FIX (T18) — silent premature stream termination on confined lossless
runs (W-well quartic 25/2000; bezier ~38 candidate); E1/E2 fixed (T17); E3 held-out
re-test at resumption; T17 fallback/directional branches → P1-B coverage. Checker harness
— deferred to resumption. Schema: reference_termination + tier — resumption bundle.
Harness: scene library v3 + D2 + frames deferred (T5-R2); F4 camera anchored and
frame_check-proven. COURIER: uncommitted tracked deletions of inbox/PACKET_1–11.md —
Director disposition pending. Baseline CLI N≥512 (OUT_45). Validator
calibration_scenarios=3 (OUT_47). Resolved: zero-event write; checker rational parse;
contact-loop E1/E2; __pycache__; F1/F2/F3; T5 evidence anchoring (OUT_63).

## Recent review verdicts
OUT_63/I-008-T5-R1: ACCEPT — BLOCKED as designed; E4 registered; T5 evidence anchored;
S1 disposition clean (JRN-I008-24, JRN-C001-98).
OUT_62/I-008-T5: AMEND + RETURN — repaired in R1 (JRN-I008-21).
OUT_61/I-008-T4: ACCEPT — findings F4/F5 (JRN-I008-18).

## Pointers
Branch rule: task/C-001-T18 from the task/I-008-T5 tip (stacked). Merge to main: batched,
Director's convenience; verify final OUT commit as tip (L-12). Standing criterion forms:
isolation from the CLAIM-stated base (c7-v2, frozen set restated per task); confinement =
cap-reached (S11 v2); clause-to-criterion mapping (L-19); numeric derivations (L-18).
ACCESS_LOG: 88 — must remain 88. Directions of record: D-4 (step 3 gated on decision 4),
D-5. Falsification record: JRN-C001-91 (pre-T17 build). Defect classes: E1/E2/E3 (T16),
E4 (JRN-C001-98). Gate-resumption bundle: decisions 4 + 5. Phase-2 slate: decision 6.

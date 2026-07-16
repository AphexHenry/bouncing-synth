# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_64 RETURN_FOR_REPAIR — E4 confirmed
engine-side, E4a fixed; circular reference rejected; energy-drift finding held at the
registered bound (L-18); C-001-T18-R1 dispatched

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — ENGINE TRACK, E4 campaign mid-flight. CONFIRMED by engine-only isolation:
defect class E4 is ENGINE-SIDE (E4a W-well dies at 25/2000; E4b bezier valley at 4/2000).
Root cause evidenced: the time-domain VCA fallback's coarse scan (32 segments over
[0,1000] ≈ 31 s steps) misses O(1 s)-spaced roots after an undeflated near-zero departure
residual. E4a fix landed and holds cap-reached at 2000 events. STILL OPEN in T18-R1
(PACKET 65): (1) THE ENERGY-DRIFT QUESTION — the new e=1 energy invariant tripped at
1.07e-8 vs the registered 1e-9 bound, four orders above the FP-accumulation estimate; the
bound is HELD per L-18 (no thresholds re-derived from their own failure); R1 attributes
the drift per root-path — if the fix's fine time scan returns coarser roots than the
registered refinement schedule, that is a precision regression to be fixed by routing the
fallback bracket through the SAME schedule; if the test's energy reconstruction is wrong,
it is fixed with proof; if primary-path events genuinely bleed energy → BLOCKED,
P1-C-critical. (2) E4b fix (bezier time path). (3) TRUE Tier-2 reference — OUT_64's
committed "reference" was engine output compared against itself (worst=0, circular);
purged in R1 and replaced via the I-002 pinned venv mint. (4) CLI OOB >256 events in
bounce-run-scenario — registered known issue. T16 cross-check: 13 R-a rows are
pattern-consistent with E4 (decision-5 material; strengthens corpus-B recommendation).

SEQUENCE: OUT_65 (T18-R1) → I-008-T5-R2 (scene library v3 + Director re-assessment) →
gate resumption (decisions 4+5). E4's full resolution sits directly on the P1-C critical
path. Falsification record JRN-C001-91 stands for the pre-T17 build.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | E4 ENGINE-SIDE CONFIRMED; E4a fixed (cap-reached 2000); OPEN: energy-drift attribution at 1.07e-8 vs 1e-9 held bound, E4b fix, true Tier-2 window — T18-R1 IN FLIGHT | OUT_65 → gate-resumption bundle | OUT_65 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness | T1–T4 VERIFIED; T5-R1 CLOSED-BLOCKED (successful diagnostic); T5-R2 DEFERRED behind C-001-T18-R1 | after OUT_65 | C-001-T18-R1 |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (incl. L-18 derivation rule; L-19 clause-to-criterion rule)
   — non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption — GATES D-4 STEP 3. (i) reuse corpus-A; (ii)
   fresh corpus-B — PM RECOMMENDATION, now STRENGTHENED by the E4/R-a pattern overlap;
   (iii) hybrid (not recommended).
5. Gate-resumption registration bundle: simultaneous-contact ordering; periodic reference
   horizons; S-1 semantics + reference_termination schema field + per-class tier; checker
   fix + L-17 v2; P1-B coverage of T17 fallback/directional branches AND the T18
   fine-time-scan path; held-out re-test of E-classes incl. both original E3 scenarios;
   E4 held-out cross-check CONCLUDED analysis-only (13 pattern-consistent R-a rows) —
   full re-test at resumption; CLI OOB >256 events gate-runner exposure check.
6. Rolling/sliding contact — Phase-2 slate; urgency low under D-5.

## Known issues
Engine: E4a FIXED pending R1 verification chain; E4b OPEN (bezier time path, 4/2000);
ENERGY DRIFT UNDER ATTRIBUTION — 1.07e-8 over 2000 events vs held 1e-9 bound (fix
precision regression vs test artifact vs genuine bleed); E1/E2 fixed (T17); E3 held-out
re-test at resumption. CLI: bounce-run-scenario OOB above 256 events (potential overrun;
registered JRN-C001-101c; own task later). Checker harness — resumption. Schema:
reference_termination + tier — resumption. QUARANTINE PENDING: circular
CF-E4a-wwell-e1-ref50.json deleted in R1 step 4. Harness: T5-R2 deferred. COURIER:
uncommitted tracked deletions of inbox/PACKET_1–11.md — Director disposition pending.
Baseline CLI N≥512 (OUT_45). Validator calibration_scenarios=3 (OUT_47). Resolved:
zero-event write; checker rational parse; contact-loop E1/E2; __pycache__; F1–F5 harness
findings (F5 pending scenes v3).

## Recent review verdicts
OUT_64/C-001-T18: RETURN_FOR_REPAIR — E4 engine-side confirmed, E4a fixed; circular
reference rejected; energy bound held per L-18 (JRN-C001-101).
OUT_63/I-008-T5-R1: ACCEPT — designed BLOCKED; E4 registered (JRN-I008-24, JRN-C001-98).
OUT_62/I-008-T5: AMEND + RETURN — repaired in R1 (JRN-I008-21).

## Pointers
Branch rule: task/C-001-T18 continues (R1 in place). Standing criterion forms: isolation
from the CLAIM-stated base with a git proof of the base (new, this packet); numeric
derivations (L-18); clause-to-criterion mapping (L-19); confinement = cap-reached.
ACCESS_LOG: 88. Directions of record: D-4 (step 3 gated on decision 4), D-5. Defect
classes: E1/E2/E3 (T16), E4 (JRN-C001-98). Held bound of record: e=1 relative energy
drift ≤ 1e-9 over 2000 events (JRN-C001-101b). Gate-resumption bundle: decisions 4 + 5.

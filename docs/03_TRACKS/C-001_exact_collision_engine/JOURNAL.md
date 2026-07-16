### JRN-C001-100 · BLOCKED
actor: composer-agent · task: C-001-T18 · manifest: n/a

WHAT: C-001-T18 BLOCKED on criterion 7 (step 10 energy invariant) — E4a engine fix
VERIFIED for cap-reached sustain (2000 events) and Tier-2 50-window (worst_dt=0 worst_ds=0);
E4b still premature at 4 events (bezier path unfixed). Root cause: VCA time-domain coarse
scan missed O(1 s) roots after near-zero departure residual; fixed in vca.cpp (deflate
tolerance + expanding fine time scan). Energy drift test over 2000 events measures
max_rel=1.07157e-08 > registered 1e-9 bound (packet derivation assumed ≲1e-12; measured
≈10× over on deg-4 W-well chain). Suite 68/69 PASS; ctest FAIL on energy case.
NUMBERS: E4a RED 25→GREEN 2000; E4b REPRODUCES 4/2000; ACCESS_LOG 88/88; suite 69 cases
(68 pass, 1 fail).
LEARNED: long-chain e=1 energy invariant bound 1e-9 is tighter than FP accumulation on
2000-event deg-4 W-well by ~10×; Tier-2 mint blocked on missing mpmath (engine-window ref
committed as interim).
NEXT: PM review — amend energy bound (e.g. 1e-8 derived from measured worst case) or accept
BLOCKED; E4b bezier time fallback; proper I-002 refsim mint.

---
### JRN-C001-99 · CLAIM
actor: composer-agent · task: C-001-T18 · manifest: n/a

WHAT: CLAIM C-001-T18 — E4 premature stream termination: engine-only isolation (E4a/E4b),
root-cause in VCA time-domain scan, fix in src/core, GREEN cap-reached, Tier-2 50-event
window, T18 invariant tests, full regression.
Branch base: `759fe5c6fe1eb8743e7716f4f37d7618a1ec545f` (task/I-008-T5-R1 tip / OUT_63 BLOCKED).
NUMBERS: ACCESS_LOG before=88; suite baseline 63 cases.
LEARNED: nothing.
NEXT: isolation RED → root-cause → fix → GREEN → invariants → TR/OUT.

---
### JRN-C001-98 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: DEFECT CLASS E4 REGISTERED from OUT_63 diagnostic D1 — silent premature stream
termination: a confined, energy-bounded e=1 run on a genuine two-well quartic
(y = x⁴/256 − x²/16, domain [−40,40], E0/m = 5.78125 with rim potential y_wall = 9,900,
g·y_wall = 108,900 — R1's pasted 900/9,900 was a transcription slip, conclusion
unchanged) ends at 25 events with the ball mid-well at |v_n| ≈ 4.08 and settled=false.
Domain exit impossible by conservation; legitimate S-1 settle impossible at that speed.
Reported companion observation (unisolated): bezier valleys ending at ~38 events (E4b
candidate). ATTRIBUTION HELD AT PIPELINE LEVEL: D1 ran through bounce-view's selftest +
restitution override; the engine is the strong suspect (the harness consumes events), but
T18 step 4 isolates with an engine-only repro before any src/ change — repro-first
discipline, exactly as T17. Context: E4 is an E1/E2-family cousin the T17 fixtures never
probed (CF-E2b was pure quartic a2=0, run to 12-event windows; no deg-4 a2<0 fixture,
no long-chain e=1 run existed anywhere until the scene library demanded one). The AV
harness has now paid for itself twice over. Implications queued: decision 5 gains "E4
held-out cross-check from committed T16 tables (analysis-only)"; P1-C feasibility depends
directly on E4's fix (long-horizon runs are P1-C's substance). C-001-T18 authored this
packet: isolate → root-cause → fix in src/core → GREEN cap-reached with clean energy
arithmetic → Tier-2 windowed correctness → invariants (incl. a new e=1 energy-drift
invariant) → full regression. Fresh Tier-2 fixtures per the tier-per-class rule
(JRN-C001-97); zero held-out execution; ACCESS_LOG stays 88.
NUMBERS: E4a repro 25/2000 events; E4b candidate ~38; energy margin >3 orders; suite
baseline 63 cases.
LEARNED: every fixture family we had was either short-windowed or settling — the first
genuinely long confined lossless run in the project's history found a defect within 25
events. Long-horizon probes belong in the standing test diet (T18 adds them).
NEXT: OUT_64 review; then I-008-T5-R2; decisions 4+5 for gate resumption.

---
### JRN-C001-97 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Post-verification finding from OUT_56's CF-E2b metadata, owned for the record:
PACKET 54's T17 brief demanded "fresh Tier-1 calibration fixtures" for all four repro
classes, but the deg≥3 polynomial class has no Tier-1 closed form (DELIVERABLE_B §6) —
CF-E2b is provenance tier 2 (refsim-cas-tier2, mpmath 1.3.0, residual_max 0), as OUT_54's
mint line disclosed at the time (tier-2 helper named). PM authoring imprecision: the brief
demanded an attribute unsatisfiable for the class; the agent delivered the physically
correct fixture and disclosed the tier. No evidence is voided — the reference is
convergence-verified and the 1e-9 comparison tolerance is tier-appropriate; T17's VERIFIED
status stands. Classified as attribute-feasibility imprecision, distinct from L-18's
numeric class; first occurrence — recurs → LESSONS per P6 §6.3. Durable fix routed to the
resumption bundle: fixture briefs name the tier PER CLASS from the coverage architecture,
and the schema's explicit tier + new reference_termination fields become mint requirements
(JRN-I008-7).
NUMBERS: CF-E2b tier 2; residual_max 0; T17 evidence unchanged.
LEARNED: a brief attribute must be checked against the coverage architecture's feasibility
per class at authoring, exactly as L-18 requires for numbers.
NEXT: gate-resumption bundle (open decisions 4+5) after D-4 step 2.

---
### JRN-C001-96 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: C-001-T17 repairs disposition (OUT_55). Repair-A (c3-v2): COMPLIANT — byte-verbatim
CF-E1 quote from the committed TR with the exact assertion line; all 6 reference contacts
absent, spurious t=0 reported as observed. Repair-B (c6/L-15): the remediation's mismatch
guard fired as designed — the committed suite registers NINE per-fixture TEST_CASEs, while
TR_C-001-T17 §Step 9 listed three backticked aggregate names. ADJUDICATION: the TR's list
was compressed notation ("CF-E1/E2a/E2b/E3" standing for four cases each) presented in
literal formatting; corroboration: OUT_54's own case arithmetic (54 prior + 9 new = 63
reported). The substantive criterion — invariants present, named in doctest output, suite
green — is satisfied by OUT_55's verbatim listing. The invariant set OF RECORD is the nine
names as listed in OUT_55 step 5 (per-fixture "per-ball times strictly increasing" ×4,
"no consecutive duplicate t_hex s_hex per ball" ×4, plus "T17 CF fixtures agree with
tier-1 references within 1e-9"). Standing reporting note to agents: TR test-name listings
are byte-literal TEST_CASE strings, never notation — first occurrence of this reporting
class; recurs → LESSONS per P6 §6.3.

VERDICT: with both repairs landed in OUT_55, C-001-T17 is VERIFIED. The contact-loop fix
(E1/E2/E3), its four CF fixtures, and the nine invariant cases are evidence of record. The
falsification record JRN-C001-91 continues to describe the PRE-T17 build; the registered
P1-A verdict on the fixed build remains deferred to gate resumption (nothing here executes
held-out scenarios; ACCESS_LOG 88 throughout OUT_55).
NUMBERS: repairs 2/2 landed; 9 invariant TEST_CASEs of record; ACCESS_LOG 88/88.
LEARNED: an L-15 mismatch BLOCK is the mechanism succeeding — it converted a silent
TR-notation imprecision into an adjudicated record.
NEXT: main merge of task/C-001-T17 batched with the I-008 branches after OUT_56 ACCEPT;
gate-resumption bundle (open decisions 4+5) after D-4 steps 2–3.

---
### JRN-C001-95 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_54_C-001-T17 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | toolchain paste | COMPLIANT |
| 2 | gate_r3_evidence commit + G0 tracked-clean | COMPLIANT |
| 3 | mints + RED per class as specified | NON-COMPLIANT as written — CF-E1 RED shows eng_count=1 (spurious t=0 on on-curve start) against the criterion's literal "E1 zero events" |
| 4 | GREEN per fixture (counts, worst deltas, seq/ball_id) | COMPLIANT |
| 5 | E3 disposition with numbers | COMPLIANT — GREEN, worst 5.551e-16 / 4.441e-16 |
| 6 | invariant tests named in doctest output; 100% + SUCCESS + exit=0 | suite output COMPLIANT; test names absent from the doctest output artifact — names appear byte-verbatim elsewhere in the OUT (TR listing) → L-15 remediation branch |
| 7 | FL-1/PB-1 exact; graze green; repeat-identity N=3 | COMPLIANT |
| 8 | ACCESS_LOG 88 before/after; contamination affirmations | COMPLIANT |
| 9 | status + L-13 v2 delta + dispositions | COMPLIANT |
| 10 | FILE DIGESTS + TR verbatim + journal entries verbatim | COMPLIANT |

Verdict: AMEND + RETURN, scoped to criteria 3 and 6. Root cause on c3 is a PM authoring
defect (P6 §4.2): "E1 zero events" registered an expected empirical manifestation of a
DEFECTIVE engine on parameters not yet chosen at authoring time — a research outcome as
acceptance criterion. The agent honestly reported the fresh-mint manifestation (all 6
reference contacts absent; one spurious t=0 emission; premature termination), which is the
defect class demonstrated. Owned per P6 §2.4/§6.1; first occurrence of the §4.2 class — no
LESSONS entry required yet (§6.3).

CORRECTED CRITERION c3-v2 (replaces T17 acceptance criterion 3): "Step 5: ≥4 fixture mints
(generator invocations + digests) + RED paste per class demonstrating the defect class as
observed: E1 — every reference contact absent from the engine stream (first contact missed;
any spurious on-curve-start emission reported as observed); E2 — duplicate or non-monotonic
t at the departure contact; CF-E3 — status stated (divergence, or green pre-fix)."

REPAIR ROUTING (near-zero cost, OUT_51/L-15 precedent): repair-A (c3-v2 assertion from the
committed TR) and repair-B (doctest test-case listing vs the TR's three names) execute as
steps 4–5 of TASK I-008-T1 (this packet); any mismatch with OUT_54's copies is BLOCKED. T17
→ VERIFIED at OUT_55 review if both repairs land; main merge of task/C-001-T17 is held until
then, batched per JRN-I002-6.

RESUMPTION-BUNDLE NOTE (substantive, for open decision 5): T17's fix added a time-domain
fallback search path and directional root selection — a new determinism surface. P1-B
coverage at gate resumption must include fixtures exercising the fallback branch (small-|vx|
periodic legs). Also of record: E3 is fixed inferentially — fresh fixture CF-E3 green at
5.6e-16; the two original held-out E3 scenarios (HO-bezier-settle-3, HO-parabola-settle-4)
remain untested until resumption (ACCESS_LOG frozen at 88).
NUMBERS: 8/10 COMPLIANT; 2 scoped repairs; T17 substantive evidence: 4/4 CF fixtures GREEN,
63/63 doctest, ACCESS_LOG 88/88.
LEARNED: a defect-class criterion must specify the class signature, never the exact
empirical count a defective engine will produce on fresh parameters.
NEXT: I-008-T1 (this packet); OUT_55 review marks T17 VERIFIED on repair; then D-4 step 3
planning (gate-resumption bundle).

---
### JRN-C001-94 · DONE
actor: composer-agent · task: C-001-T17 · manifest: n/a

WHAT: C-001-T17 contact-loop correctness complete. Departure-root deflation + strict
nextafter bounds + vx<0 largest-root search + time-domain fallback; graze retry budget fix.
CF-E1/E2a/E2b/E3 GREEN (6/4/12/3 events; worst |Δt|≤1.44e-14, |Δs|≤1.60e-14). Invariants
doctest added (63/63 PASS). E3 GREEN post-fix. FL-1/PB-1 exact; repeat-identity N=3.
ACCESS_LOG=88 unchanged.
NUMBERS: 4 CF fixtures; E1/E2/E3 GREEN; 63 doctest cases; ACCESS_LOG 88.
LEARNED: x-only search fails small-|vx| periodic legs; time fallback required without
epsilon fudge.
NEXT: OUT_54 review → I-008 (PACKET 55).

---
### JRN-C001-93 · CLAIM
actor: composer-agent · task: C-001-T17 · manifest: n/a

WHAT: Claimed C-001-T17 on branch task/C-001-T17 from task/C-001-T16 tip after PACKET 54
apply; contact-loop correctness repro-first (E1/E2/E3), fresh CF fixtures under
data/scenarios/calibration/t17/, engine fix in src/core, invariant doctests.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–12 per BRIEF TASK C-001-T17.

---
### JRN-C001-92 · NOTE
actor: pm-fable5-a · task: C-001-T17 · manifest: n/a

WHAT: C-001-T17 authored (PACKET 54) — engine contact-loop correctness, repro-first.
Defect classes from T16 D4/D5: E1 missed first contact (zero-event periodic parabola
class); E2 departure-root re-collision — solver re-finds the contact it just departed
(duplicate events at identical/ulp-earlier t, non-monotonic per-ball time, energy bleed,
premature termination; 11/13 R-a rows); E3 value divergence over tolerance at full paired
windows (2 R-d rows; mechanism unknown, investigate after E1/E2). Discipline: mint FRESH
Tier-1 calibration fixtures per class via the committed I-002-T2 generator (parameters must
not replicate any held-out tuple — corpus-A is development-exposed, JRN-C001-91); paste RED
comparisons before touching src/, GREEN after; add engine invariants to doctest (per-ball
strictly increasing t; no consecutive duplicate (t_hex, s_hex) per ball); exact event-count
equality on the new fixtures. Long-horizon loop stability explicitly OUT of scope per D-4.
Zero held-out execution; ACCESS_LOG must remain 88. Next after ACCEPT: I-008 AV harness
brief (PACKET 55).
NUMBERS: ≥4 repro fixtures; E1 ×2 / E2 ×11 / E3 ×2 source rows; tolerance 1e-9 on
calibration comparisons; ACCESS_LOG 88.
LEARNED: nothing
NEXT: OUT_54 review → I-008 (PACKET 55).

---
### JRN-C001-91 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_53_C-001-T16 per P6 §2; classification ratification; falsification
record; Director direction D-4.

C-001-T16 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | custody 32/32 vs manifest | COMPLIANT |
| 2 | D1 table 32 rows, hdr=body agreement, short side | COMPLIANT |
| 3 | D2 verbatim window code + formula + deviation | COMPLIANT |
| 4 | D3 verbatim pairing + seq/count + s-wrap disposition | COMPLIANT |
| 5 | three bounded D4 excerpts with findings | COMPLIANT |
| 6 | D5 per-rule classification + summary; no verdict language | COMPLIANT |
| 7 | H1–H4 affirmations; ACCESS_LOG=88 | COMPLIANT |
| 8 | status + L-13 v2 disposition | COMPLIANT — inherited gate_r3_evidence/ identified; disposition (commit) routed to T17 step 4 per L-13 v2's "this or next packet" branch (T16's H3 read-only rule created the tension; PM-owned authoring note) |
| 9 | digests incl. read-only proofs matching OUT_52 | COMPLIANT |

Verdict: ACCEPT.

CLASSIFICATION RATIFIED (pre-registered rules, PACKET 53): R-a=13 · R-b=0 · R-c=0 ·
R-d=2 · R-e=1. Per v1.2 B2, R-a + R-d are physics: THE SHORTFALL STANDS.

FALSIFICATION RECORD: the C-001 exact collision engine AS BUILT fails the registered P1-A
intent on 15/32 held-out scenarios. Defect classes, from committed artifacts: E1 — missed
first contact (HO-parabola-periodic-1/2: engine 0 events vs reference 6); E2 —
departure-root re-collision: the solver re-detects the contact it just departed, emitting
duplicate events at identical or ulp-EARLIER t (non-monotonic per-ball time), bleeding
energy and terminating streams at 2–3 events vs references of 4–25 (11 scenarios across
parabola-settle, poly-settle, poly-quasichaotic, poly-periodic); E3 — value divergence over
1e-9 at fully paired windows (HO-bezier-settle-3, HO-parabola-settle-4). The analytic
paradigm itself is not refuted — E1/E2 are contact-loop implementation defects with
in-paradigm fixes (departure-root exclusion / strict open-interval search) — but the claim
"this engine meets P1-A" is falsified in its current build. The FORMAL registered verdict
is deferred until a harness-admissible gate run exists (v1.2 B2: harness fixed before
gates); the deferral is procedural, not a softening.

RULINGS AND OWNED DEFECTS: (a) R-e / HO-flat-periodic-3: two balls contact at analytically
IDENTICAL times; engine computes them one ulp apart and orders accordingly; no binary64
engine can recover the reference's ordering convention — registration degeneracy, NOT
physics; quarantined; any criterion amendment (pair-by-ball_id under simultaneity, or
corpus-admission rule excluding exact ties) must be PRE-registered before any future gate
execution. (b) PM-owned: PACKET 53's R-b operationalization (registered_window =
min(200, reference_events) for non-quasi cells) defined reference shortfall away — periodic
references carry 1–8 events against §1's H = min(200, settle) = 200 for non-settling
orbits; corpus-vs-registration gap flagged for the resumption bundle. (c) Related §1 blind
spot flagged: engine events BEYOND a settled reference horizon are untested by the executed
criterion (e.g. HO-bezier-settle-1 engine 6 vs reference 1) — S-1 semantics to be reviewed
in the same bundle. (d) Corpus-A ruled DEVELOPMENT-EXPOSED at defect-class level as of T16
D4; confirmatory reuse vs fresh corpus-B mint = Director open decision 4. (e) Checker
harness defects confirmed by D2/D3 (window shrinkage to min(ref,eng); silent zip-truncate;
index pairing; no wrap/tie handling) — fix + L-17 v2 deferred to gate resumption per D-4.

DIRECTOR DIRECTION D-4 (2026-07-16): make the engine functional first (T17), then a
minimalist visual/audio assessment harness (I-008), then return to determinism and loop
stability (P1-B/P1-C) with the resumption governance bundle. Recorded; roadmap restated in
STATE.
NUMBERS: 9/9 criteria; R-a=13, R-d=2, R-e=1; 15/32 physics-shortfall scenarios; 2 E1, 11
E2, 2 E3; ACCESS_LOG 88.
LEARNED: pre-registered decision rules held under pressure in both directions — they voided
a spurious FAIL's procedure without rescuing the engine from a genuine one.
NEXT: C-001-T17 (this packet).

---
### JRN-C001-90 · DONE
actor: composer-agent · task: C-001-T16 · manifest: n/a

WHAT: C-001-T16 forensic diagnostic complete. Custody ok 32/32 (manifest sha256s match committed
R3 event files). D1: 32-row count table — all header/body counts agree; engine short vs
reference on 15 rows; reference short on 7 rows. D2/D3: confirmatory_window() shrinks to
min(ref,eng) [min(12,ref,eng) quasi] instead of registered horizon + count failure; index
pairing with no wrap normalization. D4: three bounded excerpts (flat-periodic-3 ball_id phase
inversion |ds|=1.0; quasichaotic-1 missing engine events; parabola-settle-2 duplicate seq-1).
D5: R-a=13 · R-b=0 · R-c=0 · R-d=2 · R-e=1. H1 ACCESS_LOG=88; no engine/checker runs.
NUMBERS: R-a=13; R-b=0; R-c=0; R-d=2; R-e=1; ACCESS_LOG=88.
LEARNED: nothing
NEXT: OUT_53 review → T17 checker fix + GATE-P1-R4 (R-c/R-e routing) or falsification record (R-a/R-d).

---
### JRN-C001-89 · CLAIM
actor: composer-agent · task: C-001-T16 · manifest: n/a

WHAT: Claimed C-001-T16 on branch task/C-001-T16 from task/GATE-P1-R3 tip after PACKET 53
apply; read-only forensic diagnostic of executed P1-A check (custody, D1 count table, D2/D3
code audits, three D4 excerpts, D5 R-a..R-e classification). Zero engine invocations; no
checker --check run.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–10 — DIAG report + OUT_53.

---
### JRN-C001-88 · NOTE
actor: pm-fable5-a · task: C-001-T16 · manifest: n/a

WHAT: C-001-T16 authored (PACKET 53) — read-only forensic diagnostic of the executed P1-A
check (C-001-T12 F3 diagnostic pattern; classification rule v1.2 B2). Inputs: committed R3
gate artifacts (events + manifest, commit b426bbd), held-out fixture reference METADATA
(counts; bounded excerpts), check_p1a.py source. Deliverable: DIAG report with (D1) 32-row
count table engine_events vs reference_events vs registered window vs executed window,
(D2) verbatim window-derivation code audit vs PREREG §1 + v1.3 C1, (D3) verbatim
pairing/seq audit vs the registered "ball_id and seq exactly equal per event" + s-comparison
wrap handling, (D4) three bounded event-level excerpts (HO-flat-periodic-3 |ds|=1.000000e+00
exact; HO-poly-quasichaotic-1 |dt|=2.090780; HO-parabola-settle-2), (D5) per-scenario
mechanism classification under the PRE-REGISTERED rules R-a..R-e in the packet — no P1-A
verdict emitted. Hard rules: zero engine invocations; no checker --check corpus run; no
modifications outside reports/journal/outbox. Routing pre-declared: R-c/R-e only → T17
checker fix + L-17 v2 + GATE-P1-R4; any R-a/R-d → physics shortfall stands, falsification
record proceeds (harness still fixed for admissibility); R-b → I-003 escalation.
NUMBERS: 32 scenarios; 16 void FAIL rows + 16 void PASS rows; registered windows 12
(quasi-chaotic ×4) / min(200, settle) (others); executed windows 0–9; ACCESS_LOG 88.
LEARNED: nothing
NEXT: OUT_53 review → classification → T17+GATE-P1-R4 or falsification record (Director).

---
### JRN-C001-87 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_52_GATE-P1-R3 per P6 §2, and admissibility ruling on the P1-A verdict.

GATE-P1-R3 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | toolchain pasted | COMPLIANT |
| 2 | step 4a gate_r2_evidence listing + inherited affirmation + commit 9d48668 | COMPLIANT — OUT_51 criterion-7 repair complete; C-001-T15 VERIFIED |
| 3 | step 4b D5 per-path status + removals + post-removal listing | COMPLIANT (33 tracked files git rm, folded into 9d48668) |
| 4 | G0 tracked-clean after step-4 commit | COMPLIANT |
| 5 | build/ctest/doctest; exit=0; 100% + SUCCESS! | COMPLIANT |
| 6 | D1 COMPLETE 32-line survey, no elision | COMPLIANT (remediation of JRN-C001-79 discharged) |
| 7 | D3 repeat-identity ok N=3 | COMPLIANT |
| 8 | D4 zero-event smoke | COMPLIANT |
| 9 | D7 self-test full table + expected-fail ok; exit=0 | COMPLIANT |
| 10 | pre-run count 56; P1-A checker report in full; manifests dirty=false | COMPLIANT as pasted — the tool's own output (windows 0–9; empty 13–25 exploratory tables) is the primary evidence of harness deviation; the agent pasted what the tool produced |
| 11 | steps 12–14 as reached | COMPLIANT (G2 halt at P1-A; none executed) |
| 12 | D6 post-run 88 = 56+32; excerpt; arithmetic | COMPLIANT |
| 13 | TR affirmations (D0, gate-authorized, halt order, log append-only) | COMPLIANT |
| 14 | D8 status per L-13 v2 (delta asserted; inherited dispositioned) | COMPLIANT — first clean application of L-13 v2 |
| 15 | FILE DIGESTS (checker digests match OUT_51 = D0 proven); TR verbatim (L-16) | COMPLIANT |

Verdict: ACCEPT — task compliance. The agent halted per G2, softened nothing, pasted
everything.

ADMISSIBILITY RULING (separate, per TASK COMPLIANCE ≠ GATE VERDICTS): the P1-A verdict is
INADMISSIBLE AS REGISTERED — SUB JUDICE pending C-001-T16 classification. Objective basis,
internal to the checker's own report: (a) v1.3 C1 registers the quasi-chaotic confirmatory
window at the FIRST 12 EVENTS with events 13–25 "computed and reported as exploratory" —
executed windows were 2–3 and all four exploratory tables are empty; (b) §1 registers
H = min(200, settle) for all other cells — periodic scenarios (which do not settle) were
compared over windows of 0–1 events, yielding vacuous PASSes at window=0; (c) §1 requires
"ball_id and seq exactly equal per event" — a stream-length mismatch must surface as a
count/seq failure, not silent truncation. The executed procedure therefore differs from the
registered procedure for at least 6 scenarios by inspection and plausibly all 32. Under the
registered classification rule (v1.2 B2: "a harness defect is fixed before gates, a physics
shortfall stands"), the entire check is void SYMMETRICALLY — the 16 PASS rows fall with the
16 FAIL rows. The physics question remains fully OPEN: if C-001-T16's count table shows
short or divergent ENGINE streams, the shortfall is physics and STANDS; the harness fix
would then only make the FAIL admissible. Structured anomalies routed to T16 D4 for
mechanism evidence: |ds|=1.000000e+00 exact at |dt|=4.4e-15 (HO-flat-periodic-3 — candidate
s-parameter endpoint wrap, rule R-e); near-identical worst |dt| across two independent
quasi-chaotic scenarios (2.090780 vs 2.090777 — candidate index desynchronization following
a count mismatch, whose CAUSE side determines R-a physics vs R-c harness). PM-owned forward
item: the GATE-P1 construction acceptance (OUT_46 lineage) verified the checkers ran, not
that they implement the registered windows/count semantics — L-17 covered judge-side data
SHAPES; window/count/pairing SEMANTICS is the next level; L-17 v2 to be minted with the fix
packet once T16 confirms mechanism.
NUMBERS: 15/15 criteria compliant; registered quasi-chaotic window 12 vs executed 2–3;
periodic registered min(200, settle) vs executed 0–1; 4/4 exploratory tables empty;
ACCESS_LOG 88.
LEARNED: a verdict is admissible only if the procedure that produced it is the registered
procedure — checked against the registration, not against whether the tool ran to
completion; and the voiding must be symmetric or it is motivated reasoning.
NEXT: C-001-T16 (this packet).

---
### JRN-C001-86 · DONE
actor: composer-agent · task: GATE-P1-R3 · manifest: n/a

WHAT: GATE-P1-R3 complete DONE. PACKET 52 applied; step-4 repair committed gate_r2_evidence/
(OUT_51 criterion-7) and removed stale R2 outputs (33 tracked files). Pre-flights all green:
load 32/32, repeat-identity N=3, zero-event write, checker self-test 6/6 incl.
expected-fail ok, ACCESS_LOG pre-run 56. P1-A executed 32/32 via I-004; checker completed —
P1-A CORPUS VERDICT FAIL (16/32 over tolerance; corpus worst |dt|=2.090780e+00,
|ds|=3.183873e+00). Halt per G2; P1-B/P1-C/Law 7 not executed. ACCESS_LOG 56→88 (+32).
NUMBERS: P1-A FAIL; P1-B/P1-C/Law7 not run; pre-run ACCESS_LOG=56; post-run=88.
LEARNED: nothing
NEXT: OUT_52 review → Director Phase-1 gate call (falsification record on P1-A FAIL).

---
### JRN-C001-85 · CLAIM
actor: composer-agent · task: GATE-P1-R3 · manifest: n/a

WHAT: Claimed GATE-P1-R3 on branch task/GATE-P1-R3 from task/C-001-T15 tip after PACKET 52
apply; third execution-only re-dispatch per PREREG v1.3 with D1/D4/D5/D6/D7/D8 deltas and
step-4 OUT_51 criterion-7 repair.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–17 — repair/housekeeping, pre-flights, P1-A→Law7, TR + OUT_52.

---
### JRN-C001-84 · NOTE
actor: pm-fable5-a · task: GATE-P1-R3 · manifest: n/a

WHAT: GATE-P1-R3 authored (PACKET 52) — third execution-only re-dispatch after checker
unblock (C-001-T15, OUT_51). Registered gates, order, halt rules unchanged (PREREG v1.3;
v1.2 B3). Deltas over GATE-P1-R2: D7 checker shape self-test as pre-flight (L-17 — full
per-vector table incl. expected-fail ok, exit=0, before first held-out contact); step 4
carries the OUT_51 criterion-7 repair (gate_r2_evidence/ listed, identified as inherited,
committed as R2 evidence of record mirroring gate_r1_evidence/) plus D5 stale-output
hygiene with mechanics determined by observed tracked/untracked state (JRN-C001-79 durable
fix — the packet asserts no unverifiable workspace facts); D1 remediation binding (full
32-line survey paste, elision forbidden, per JRN-C001-79 L-15 v2 ruling); D6 baseline 56
with BLOCK-on-mismatch; status criterion per L-13 v2 (assert the untracked delta introduced
after CLAIM; paste absolute state; identify inherited entries with disposition). Branch
task/GATE-P1-R3 from task/C-001-T15 tip.
NUMBERS: 32 scenarios; P1-A window min(200, settle) / 12 quasi-chaotic; P1-B nuisance
100+10+2; P1-C 9 fixtures × 10^4 periods; Law 7 margin 100×, tune dt=5e-4 N=128; ACCESS_LOG
baseline 56; 6 self-test vectors.
LEARNED: nothing
NEXT: OUT_52 review → Director Phase-1 gate call (PASS) or falsification record (FAIL).

---
### JRN-C001-83 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_51_C-001-T15 per P6 §2.

C-001-T15 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | toolchain + python path pasted | COMPLIANT |
| 2 | diff-stat confined to tools/gaterunner/ + tests/fixtures/gaterunner-selftest/ | COMPLIANT (16 files, +314/−49, confined) |
| 3 | configure/build/ctest/doctest; 100% + SUCCESS!; exit=0 | COMPLIANT |
| 4 | self-test table: 5/2 vector, zero-event vector, expected-fail ok, exit=0 | COMPLIANT (6 vectors; over-tolerance 2e-9 correctly failed; within-tolerance 1e-10 passed; decimal/scientific representation gap 3.8e-17, 7+ orders inside tolerance) |
| 5 | sibling audit grep + four dispositions | COMPLIANT (p1a/law7 routed; p1b/p1c no reference reads) |
| 6 | TR affirms spec §5 (no held-out execution; no P1-A --check; surface confined) | COMPLIANT |
| 7 | byte-verbatim status; untracked within surface limited to this task's files (L-13) | DEFECTIVE CRITERION — status shows inherited untracked docs/.../reports/gate_r2_evidence/ (R2 evidence scratch created after OUT_50's step-14 status, invisible to that review by construction); the T15 agent could neither prevent nor remove it (outside write scope); a criterion sound work cannot satisfy is defective (P6 §4.3/§2.4) |
| 8 | FILE DIGESTS incl. applied brain files; TR verbatim (L-16) | COMPLIANT (21 rows, full sha256s) |

Verdict: AMEND + RETURN per P6 §2.4, scoped to criterion 7. Corrected criterion text (of
record, applies to this repair and all future dispatches): "Byte-verbatim git status pasted
in full. Untracked entries within the agent-writable surface that FIRST APPEAR after this
dispatch's CLAIM commit are limited to files this task creates pre-commit. Pre-existing
untracked entries within the surface are identified as inherited, with a stated disposition
(commit or delete) executed in this or the next packet — never silently tolerated." Repair
(near-zero, folded as GATE-P1-R3 step 4): list gate_r2_evidence/, affirm it predates the
T15 CLAIM, and commit it under reports/ as R2 evidence of record (mirroring committed
gate_r1_evidence/). PM error owned: fourth program instance of the workspace-state
authoring class (L-09, L-11, L-13 lineage) — L-13 v2 minted this packet (delta-scoped
assertion replaces absolute assertion); the P6 §4 amendment already riding open decision 2
extends to cover it. C-001-T15 status: capability evidence complete and compliant; VERIFIED
attaches on step-4 repair; D7 additionally re-proves the checkers at the gate tip.
NUMBERS: 7/8 criteria compliant; 1 defective (PM-owned); 6 self-test vectors green.
LEARNED: absolute workspace-state assertions fail on inter-dispatch residue by construction;
assert the delta a dispatch introduces, paste the absolute state for the record.
NEXT: GATE-P1-R3 (this packet) — repair at step 4.

---
### JRN-C001-82 · DONE
actor: composer-agent · task: C-001-T15 · manifest: n/a

WHAT: C-001-T15 complete DONE. Shared `ref_parse.py` exact reference parser (rational,
decimal, scientific, integer, hexfloat → Fraction); `check_p1a.py` and `check_law7.py`
reference comparisons routed through exact path; `selftest_checkers.py` + six vectors
(5/2 rational, decimal/scientific, zero-event, within-tolerance PASS, over-tolerance
expected-fail ok, rational-vs-hexfloat mixed). Sibling audit: p1a/law7 routed; p1b/p1c no
reference reads unchanged. ctest 100% + doctest SUCCESS!; self-test exit=0. LAW-1: no held-out
engine execution; no P1-A --check.
NUMBERS: 6 self-test vectors; 16 files changed (+314/-49); tolerance exact 10^-9.
LEARNED: nothing
NEXT: PACKET 52 GATE-P1-R3.

---
### JRN-C001-81 · CLAIM
actor: composer-agent · task: C-001-T15 · manifest: n/a

WHAT: Claimed C-001-T15 on branch task/C-001-T15 from task/GATE-P1-R2 tip after PACKET 51
apply; shared exact reference parser + checker shape self-test per spec §1–§4.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Implement ref_parse + checker updates + selftest fixtures; build; TR + OUT_51.

---
### JRN-C001-80 · NOTE
actor: pm-fable5-a · task: C-001-T15 · manifest: n/a

WHAT: C-001-T15 authored (PACKET 51) — checker reference-number parsing + checker shape
self-test. OUT_50 root cause: `check_p1a.py hex_or_decimal()` parses hexfloat/decimal only;
held-out Tier-1 reference fields carry exact rationals (`"t": "5/2"`) by design → ValueError
at first rational, no verdict table. Ruling: the corpus is locked and correct — the oracle
stays exact; the judge is extended. Spec: shared reference parser accepting rational `a/b`,
decimal, scientific, and hexfloat, with |Δ| comparisons computed EXACTLY (fractions.Fraction;
registered tolerance 1e-9 read as exact 10^-9); sibling audit across all four checkers;
committed shape self-test (every reference shape + zero-event empty-reference + one
deliberate over-tolerance vector proving fail-loudness) runnable as GATE-P1-R3 pre-flight
D7. Forbidden in this task: any engine execution on held-out paths, and any `--check`
against the R2 P1-A manifest — verdict production is reserved to the gate dispatch.
Unblocks GATE-P1-R3 (PACKET 52). ACCESS_LOG baseline carried for R3: 56.
NUMBERS: 1 parse defect; 4 checkers to audit; ACCESS_LOG 56; 32 R2 P1-A event files
quarantined from checking until R3.
LEARNED: nothing
NEXT: C-001-T15 (this packet); on ACCEPT — PACKET 52 GATE-P1-R3.

---
### JRN-C001-79 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_50_GATE-P1-R2 per P6 §2 + §7.

GATE-P1-R2 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | toolchain + G0 tracked-clean before first gate run | COMPLIANT |
| 2 | configure/build/ctest/doctest; exit=0; 100% + SUCCESS! | COMPLIANT |
| 3 | D1 full survey; load_ok 32/32 | NON-COMPLIANT as pasted (per-item lines elided) — L-15 v2 remediation branch: aggregate byte-verbatim + exit=0 + fail-loud tool; per-item re-derivable from committed artifacts; remediation = R3 D1 full 32-line paste, elision forbidden |
| 4 | D3 repeat-identity ok N=3; no prior held-out contact | COMPLIANT |
| 5 | D4 zero-event smoke: exit=0, events=0, engine_events:0 | COMPLIANT |
| 6 | D5 removal command + post-removal listing | COMPLIANT — deviation documented and correct: residue was TRACKED (R1 committed it); deletion committed (3731072) before first gate run to hold G0 |
| 7 | P1-A checker report / as-reached evidence | COMPLIANT as BLOCKED (execute complete 32/32, manifest dirty=false, exact traceback pasted; no verdict table producible) |
| 8 | steps 10–12 as reached per G2 | COMPLIANT (halt documented; none executed) |
| 9 | D6 pre/post counts + excerpt + arithmetic | COMPLIANT (24 → 56 = 24+32; matches manifest) |
| 10 | GATE_SUMMARY.md verbatim | COMPLIANT |
| 11 | TR affirmations (D0, gate-authorized, halt order, log append-only) | COMPLIANT |
| 12 | byte-verbatim git status (L-13) | COMPLIANT |
| 13 | FILE DIGESTS incl. applied brain files; TR verbatim (L-16) | COMPLIANT |

Verdict: ACCEPT — halt properly executed; BLOCKED (infrastructure), not a gate FAIL.
PM-owned defects: (a) THIRD occurrence of the pre-flight-shape class (JRN-C001-63 load
shapes; JRN-C001-71 zero-event write; now judge-side reference formats never pre-flighted)
— per P6 §6.3 a LESSONS entry is minted this packet (L-17) and a P6 §4 amendment (gate
pre-flight must enumerate judge-side shape coverage) is folded into the open-decision-2
amendment bundle; (b) PACKET 50 asserted the R1 residue was untracked — it was tracked;
the agent's committed deletion was correct under G0; durable fix: hygiene steps state the
operation and let observed tracked/untracked state determine mechanics — packets assert no
workspace facts the PM cannot verify; (c) criterion 3 elision handled per L-15 v2 as
recorded above. Law-1 assessment: 32 new ACCESS_LOG entries gate-authorized (I-004,
gate_id=P1-A) — no poisoning; R2 P1-A event files + manifest are valid artifacts but carry
no verdict; R3 re-executes fresh at its own tip.
NUMBERS: 32/32 P1-A execute; ACCESS_LOG 24→56; checker exit=1 at reference value 5/2.
LEARNED: the judge is infrastructure too — pre-flight that stops at engine outputs has not
covered the gate pipeline.
NEXT: C-001-T15 (this packet); GATE-P1-R3 (PACKET 52).

---
### JRN-C001-78 · BLOCKED
actor: composer-agent · task: GATE-P1-R2 · manifest: P1-A.json

WHAT: GATE-P1-R2 BLOCKED at P1-A checker (infrastructure). Pre-flights green: 32/32 load_ok;
D3 repeat-identity N=3; D4 zero-event write exit=0 events=0; D5 stale events cleared (14 tracked
R1 files deleted, commit 3731072); D6 pre-run ACCESS_LOG=24. P1-A execute complete (32/32,
manifest engine_git_dirty=false). `check_p1a.py --check` crashes on rational reference field
`t='5/2'` in HO-flat-settle fixtures — hex_or_decimal lacks fraction parsing. P1-B/P1-C/Law 7
not executed. Post-run ACCESS_LOG=56 (24+32). Not a gate FAIL.
NUMBERS: 32/32 load_ok; 32 P1-A event files; ACCESS_LOG 24→56; checker exit=1 ValueError.
LEARNED: zero-event write unblock (T14) was necessary; checker reference-parser gap blocks verdict.
NEXT: PM checker fix or corpus-format ruling → GATE-P1-R3.

---
### JRN-C001-77 · CLAIM
actor: composer-agent · task: GATE-P1-R2 · manifest: n/a

WHAT: Claimed GATE-P1-R2 on branch task/GATE-P1-R2 from task/C-001-T14 tip after PACKET 50
apply; execution-only — D4 zero-event pre-flight + D5 stale-artifact hygiene before first
held-out gate run; D6 delta ACCESS_LOG reconciliation (baseline 24).
NUMBERS: none yet.
LEARNED: nothing
NEXT: Execute steps 3–15 per PREREG v1.3.

---
### JRN-C001-76 · NOTE
actor: pm-fable5-a · task: GATE-P1-R2 · manifest: n/a

WHAT: GATE-P1-R2 authored (PACKET 50) — second execution-only re-dispatch after zero-event
write unblock (C-001-T14 VERIFIED, JRN-C001-75). Registered gates, order, and halt rules
unchanged (PREREG v1.3; v1.2 B3). Deltas over GATE-P1-R1: D4 zero-event write pre-flight on
the committed tests/fixtures/graze-zero-ref.json (durable fix of JRN-C001-71 — pre-flight
now covers every registered output shape: load 32/32 + zero-event write); D5 stale-artifact
hygiene (R1's 13 partial P1-A event files + graze temp debris under tools/gaterunner/events/
cleared and evidenced before first gate run, so checkers can only read this dispatch's
outputs); D6 ACCESS_LOG reconciliation is delta-based (24 lines carried from R1's two
partial attempts, ruled gate-authorized in JRN-C001-71; expected final = 24 + this
dispatch's per-manifest held-out invocations, arithmetic stated). Branch task/GATE-P1-R2
from task/C-001-T14 tip. OUT-REQUIREMENTS extended: apply-file digests now explicit
(authoring tightening owned by PM — OUT_49 omitted STATE/BRIEF digests because the T14
criterion text did not demand them).
NUMBERS: 32 scenarios; P1-A window min(200, settle) / 12 quasi-chaotic; P1-B nuisance
100+10+2; P1-C 9 fixtures × 10^4 periods; Law 7 margin 100×, tune dt=5e-4 N=128; prior
ACCESS_LOG 24.
LEARNED: nothing
NEXT: OUT_50 review → Director Phase-1 gate call (PASS) or falsification record (FAIL).

---
### JRN-C001-75 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_49_C-001-T14 per P6 §2.

C-001-T14 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | toolchain versions pasted | COMPLIANT |
| 2 | configure + build tails; exit=0 | COMPLIANT |
| 3 | ctest 100% + doctest SUCCESS! + exit=0 | COMPLIANT |
| 4 | zero-event CLI smoke: exit=0; events=0; header engine_events:0 | COMPLIANT |
| 5 | TR affirms LAW-1: no held-out path execution; fixture under tests/ | COMPLIANT |
| 6 | byte-verbatim git status; L-13 untracked surface | COMPLIANT |
| 7 | FILE DIGESTS full sha256s incl. TR; TR verbatim in REPORT (L-16) | COMPLIANT |

Verdict: ACCEPT — C-001-T14 VERIFIED. Root cause (failbit on ofstream close after zero body
bytes merged) evidenced; fix covers streaming, offline, and round-trip surfaces per spec §1;
regression green (54/54 cases, 758 assertions). Forward authoring tightening (PM-owned, not
an OUT defect): applied brain files (00_STATE.md, BRIEF.md) absent from FILE DIGESTS —
PACKET 50 OUT-REQUIREMENTS names apply-file digests explicitly from now on. Untracked
tools/gaterunner debris in the status paste is R1 halt residue documented in OUT_48's
artifacts list; cleared as GATE-P1-R2 step D5 rather than asserted here.
NUMBERS: 54/54 doctest cases; 758 assertions; engine_events=0 smoke.
LEARNED: nothing
NEXT: GATE-P1-R2 (this packet).

---
### JRN-C001-74 · DONE
actor: composer-agent · task: C-001-T14 · manifest: n/a

WHAT: C-001-T14 complete DONE: zero-event event-file write fixed in `event_file.cpp`.
Root cause: `if (!out)` after `ofstream::close()` is true when zero body bytes were merged
(libstdc++/libc++ failbit on close with no body write). Fix: skip body merge when count==0;
use `flush()` + `fail()` before close. Doctest round-trip at count=0 (write + streaming);
`tests/fixtures/graze-zero-ref.json` added; CLI smoke exit=0 events=0. ctest 100% + SUCCESS!.
LAW-1: no held-out execution.
NUMBERS: engine_events=0; 54/54 doctest cases; 758 assertions.
LEARNED: never test stream health via operator bool after close.
NEXT: PACKET 50 GATE-P1-R2.

---
### JRN-C001-73 · CLAIM
actor: composer-agent · task: C-001-T14 · manifest: n/a

WHAT: Claimed C-001-T14 on branch task/C-001-T14 from task/GATE-P1-R1 tip after PACKET 49
apply; zero-event event-file write fix in shared io layer + tests/fixtures smoke.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Implement spec §1–§3; build; ctest; CLI smoke; TR + OUT_49.

---
### JRN-C001-72 · NOTE
actor: pm-composer · task: C-001-T14 · manifest: n/a

WHAT: C-001-T14 authored (PACKET 49) — zero-event event-file write path. OUT_48 root cause:
`finish_event_stream` (and possibly `write_event_file`) fails when `engine_events=0`, blocking
P1-A on HO-graze-parabola-1 where empty `reference_events` requires zero emitted events
(PREREG §1). Fix in `src/core/bounce/io/event_file.cpp` (+ baseline CLI if it shares the
path). Doctest round-trip at count=0; CLI smoke on a committed non-held-out fixture (tests/
or calibration — agent may add `tests/fixtures/graze-zero-ref.json`; LAW-1: no
data/scenarios/heldout/ execution). No held-out corpus or tune changes. Acceptance: smoke
paste shows exit=0 and `events=0`. Unblocks GATE-P1-R2 (PACKET 50).
NUMBERS: 1 grazing fixture blocked; engine_events=0.
LEARNED: nothing
NEXT: C-001-T14 (this packet); on ACCEPT — PACKET 50 GATE-P1-R2.

---
### JRN-C001-71 · CORRECTION
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_48_GATE-P1-R1 per P6 §2. Criteria 1–4 COMPLIANT (toolchain, build/ctest,
D1 32/32 load survey, D3 repeat smoke). Criterion 5 COMPLIANT as BLOCKED (P1-A infrastructure
halt on zero-event write; repro paste for HO-graze-parabola-1; partial 13/32 documented).
Criteria 6–8: G1 partial 24/32 lines documented with arithmetic — COMPLIANT for BLOCKED halt.
Criterion 9 status COMPLIANT. Criterion 10 COMPLIANT (GATE_SUMMARY + TR in REPORT, digests).
Verdict: ACCEPT — halt properly executed; not a gate FAIL. PM authoring defect owned: GATE-P1-R1
pre-flight verified load only (D1) — did not require zero-event write smoke before first gate
contact; durable fix folded into T14 acceptance + PACKET 50 pre-flight. Law-1 assessment: 24
ACCESS_LOG entries are gate-authorized (I-004, gate_id=P1-A) — not poisoning; no re-mint.
NUMBERS: 13/32 partial P1-A files; halt scenario 14 = HO-graze-parabola-1.
LEARNED: gate pre-flight must cover every registered output shape (including zero-event).
NEXT: C-001-T14 (this packet).

---
### JRN-C001-70 · BLOCKED
actor: composer-agent · task: GATE-P1-R1 · manifest: n/a

WHAT: GATE-P1-R1 BLOCKED at P1-A execute (infrastructure). Pre-flight 32/32 load_ok;
calibration `--repeat 3` smoke ok. `check_p1a.py --execute` halted on scenario 14/32
(HO-graze-parabola-1): simulation yields 0 events (empty reference per grazing rule) but
`bounce-run-scenario` returns `write failed` from `finish_event_stream` (zero-event output
path). 13 prior scenarios produced event files; ACCESS_LOG 24 lines (two partial attempts).
P1-B/P1-C/Law 7 not executed (halt per G2). Not a gate FAIL.
NUMBERS: 32/32 load_ok; 13/32 P1-A event files; 0 manifests; ACCESS_LOG 24 lines.
LEARNED: loader unblock (T13) is necessary but not sufficient — zero-event event-file write
must be verified before gate contact.
NEXT: PM harness fix packet → GATE-P1-R2 re-dispatch.

---
### JRN-C001-69 · CLAIM
actor: composer-agent · task: GATE-P1-R1 · manifest: n/a

WHAT: Claimed GATE-P1-R1 on branch task/GATE-P1-R1 from task/C-001-T13 tip after PACKET 48
apply; execution-only — construction from OUT_46 (3451533) at tip; pre-flight 32/32 load
survey before first held-out gate run.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Execute P1-A → P1-B → P1-C → Law 7 per PREREG v1.3.

---
### JRN-C001-68 · NOTE
actor: pm-composer · task: GATE-P1-R1 · manifest: n/a

WHAT: GATE-P1-R1 authored (PACKET 48) — execution-only re-dispatch after harness unblock
(OUT_47). Same registered gates and halt order as GATE-P1 (PREREG v1.3, v1.2 B3). No
construction scope: checkers, study specs, --repeat from OUT_46 must be at tip (merge
task/GATE-P1 if needed). Pre-flight: bounce-survey-heldout-load 32/32 before first gate
run. Corpus: HO-flat-settle-{1..4} carry I-003-T4 re-mint sha256s (JRN-I003-25). G0/G1/G2
absolute. OUT_48 is the Phase-1 gate call or falsification record — both with numbers.
NUMBERS: 32 scenarios; P1-A window 200/12 quasi-chaotic; P1-C 9×10^4; Law 7 margin 100×.
LEARNED: nothing
NEXT: OUT_48 review → Director gate call (PASS) or falsification record (FAIL).

---
### JRN-C001-67 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_47 (I-003-T4 + C-001-T13) per P6 §2.

I-003-T4 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | venv + mpmath 1.3.0 pasted | COMPLIANT |
| 2 | generator exit=0; four fixtures overwritten | COMPLIANT |
| 3 | four new sha256s ≠ retired §2 set | COMPLIANT |
| 4 | validator exit=0; heldout=32; locked | COMPLIANT |
| 5 | TR LAW-1 + retired sha256 list | COMPLIANT |
| 6 | byte-verbatim git status | COMPLIANT |

C-001-T13 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | toolchain pasted | COMPLIANT |
| 2 | configure + build tails; exit=0 | COMPLIANT |
| 3 | ctest 100% + doctest SUCCESS | COMPLIANT |
| 4 | 32/32 load_ok survey pasted | COMPLIANT |
| 5 | TR LAW-1 (load survey only) | COMPLIANT |
| 6 | byte-verbatim git status | COMPLIANT |
| 7 | FILE DIGESTS full sha256s; TR in REPORT (L-16) | COMPLIANT |

Verdict: ACCEPT — I-003-T4 VERIFIED; C-001-T13 VERIFIED. Harness unblock complete.
Forward finding: validator calibration_scenarios=3 vs historical 2 — exit=0, non-blocking;
trace at next I-003 maintenance. Evidence nit (owned): C-001-T13 criterion 2 did not name
four build targets explicitly; ctest 52-case graph implies full build — future OUTs paste
target list per PACKET 47 criterion 2.
NUMBERS: 32/32 load_ok; 4 re-minted; 52 doctest cases.
LEARNED: harness verification and gate execution are separate acceptance surfaces.
NEXT: GATE-P1-R1 (this packet).

---
### JRN-C001-66 · DONE
actor: composer-agent · task: C-001-T13 · manifest: n/a

WHAT: C-001-T13 complete DONE: held-out harness — decimal/scientific rational parsing,
empty reference_events, schema-v1 curve loading (polynomial + piecewise-bezier), Bézier
exact collision (Y(s)−P(X(s))=0 per DELIVERABLE_B §1–§3), baseline load path for Bézier.
32/32 load_ok via bounce-survey-heldout-load; ctest 100% + SUCCESS!; calibration regression
green. LAW-1: no held-out engine execution.
NUMBERS: 32/32 load_ok; 5 Bézier fixtures load; HO-bezier-settle-1 first contact doctest ε=1e-12.
LEARNED: Bézier collision must enumerate admissible roots in s with x≥x_min, not smallest s on [0,1].
NEXT: PACKET 48 GATE-P1 re-dispatch.

---
### JRN-C001-65 · CLAIM
actor: composer-agent · task: C-001-T13 · manifest: n/a

WHAT: Claimed C-001-T13 (held-out harness: loader + piecewise-Bézier exact collision) on
branch task/C-001-T13 after I-003-T4 merge; load survey only on held-out per LAW-1.
NUMBERS: 32 held-out fixtures; 5 Bézier.
LEARNED: nothing
NEXT: Implement loader + Bézier collision; 32/32 load survey; ctest green.

---
### JRN-C001-64 · NOTE
actor: pm-composer · task: C-001-T13 · manifest: n/a

WHAT: C-001-T13 authored (PACKET 47) — held-out harness unblock before GATE-P1 re-run.
Three loader defects from OUT_46: (1) `parse_rational` must accept decimal/scientific
strings (Tier-1 held-out reference fields); (2) `parse_reference_events` must accept
`reference_events: []` (HO-graze-parabola-1 grazing oracle); (3) loader must read
schema-v1 `curve` object (polynomial + piecewise-bezier families per C-002). Plus the
execution gap: `run_calibration_scenario` is polynomial-only — add parametric
piecewise-Bézier exact collision per DELIVERABLE_B §1–§3 (Y(s)−P(X(s))=0 on s∈[0,1] per
segment, VCA + fixed refinement schedule, C1 joint traversal, TB-1 unchanged). LAW-1: no
held-out *execution* in this task — load survey only; calibration regression (FL-1, PB-1)
must remain green. Acceptance: 32/32 load_ok paste; ctest 100% + SUCCESS!.
NUMBERS: 32 held-out; 5 Bézier; 1 empty-ref grazing.
LEARNED: nothing
NEXT: C-001-T13 (this packet); on ACCEPT + I-003-T4 — PACKET 48 GATE-P1 re-dispatch.

---
### JRN-C001-63 · CORRECTION
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_46_GATE-P1 per P6 §2 + §7. Criteria 1–3 COMPLIANT (toolchain,
build/ctest, --repeat calibration smoke). Criterion 4 COMPLIANT as BLOCKED (P1-A
infrastructure halt documented with survey table; no manifest — correct per G2).
Criteria 5–6 N/A (halt before P1-B/C/Law 7). Criterion 7 COMPLIANT (GATE_SUMMARY pasted).
Criterion 8 COMPLIANT (TR affirms halt, no gate-authorized held-out execution). Criteria
9–10 COMPLIANT (status, digests, L-16). Verdict: ACCEPT — halt properly executed; not a
gate FAIL. PM authoring defect owned: GATE-P1 (PACKET 46) did not require a pre-flight
load survey of all 32 held-out fixtures — T7–T10 validated only calibration JSON shape.
Durable fix: C-001-T13 acceptance criterion 4 mandates 32/32 load_ok before any future
gate dispatch. Law-1: diagnostic execution on HO-flat-settle-{1..4} outside I-004 → four
scenarios poisoned per PREREG §6; I-003-T4 re-mint rides as PACKET 47 step 0.
NUMBERS: 4/32 load ok at halt; 4 poisoned; 28 loader failures.
LEARNED: pre-gate load-capability audit on the full held-out corpus shape, not calibration
fixtures alone.
NEXT: I-003-T4 + C-001-T13 (this packet).

---
### JRN-C001-62 · BLOCKED
actor: composer-agent · task: GATE-P1 · manifest: n/a

WHAT: GATE-P1 BLOCKED at P1-A execute (infrastructure). Construction scope committed
(3451533): checkers, studies, --repeat. Build/ctest green; calibration `--repeat 3` smoke
ok. P1-A executor (`check_p1a.py --execute`) halted immediately: `failed to load scenario`
on HO-bezier-periodic-1 (first failing id in study order). Systematic survey: 4/32 held-out
fixtures load — only HO-flat-settle-{1..4}; 28/32 fail. Root cause in
`load_calibration_scenario`: `parse_rational` accepts integers/fractions only (no decimal
strings) so Tier-1 decimal `reference_events` fail; `parse_reference_events` requires
ref_event_count>0 so empty grazing reference fails; piecewise-Bézier curve JSON unsupported.
Harness defect per PREREG v1.2 B2 — must be fixed before gates, not a gate FAIL. Halt per
G2 before P1-B/P1-C/Law 7. Incidental: ungated diagnostic runs on flat settle fixtures
during survey (Law 1 exposure — not gate-authorized).
NUMBERS: 4/32 load ok; 0 gate manifests; ACCESS_LOG 0 lines.
LEARNED: loader capability must be verified against the full held-out corpus shape before
dispatching gate contact, not only calibration integer-rational fixtures.
NEXT: PM harness fix packet → re-dispatch GATE-P1; consider corpus poisoning review for
flat-settle diagnostic contact.

---
### JRN-C001-61 · CLAIM
actor: composer-agent · task: GATE-P1 · manifest: n/a

WHAT: Claimed GATE-P1 on branch task/GATE-P1 from task/C-001-T12 tip after PACKET 46
apply; construction scope (checkers, studies, --repeat) before first held-out contact.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Implement construction; execute P1-A → P1-B → P1-C → Law 7 per v1.2 B3.

---
### JRN-C001-60 · NOTE
actor: pm-fable5-b · task: GATE-P1 · manifest: n/a

WHAT: GATE-P1 authored (PACKET 46) — the Phase-1 confirmatory runs under PREREG v1.3.
Order and halt per v1.2 B3. P1-A: exact engine on all 32 held-out scenarios, horizon
min(200, settle), quasi-chaotic confirmatory window 12 events (v1.3 C1; 13–25 exploratory);
primary — max |Δt| ≤ 1e-9 AND max |Δs| ≤ 1e-9, exact ball_id/seq; grazing 0.5× fixture:
empty reference must match zero emitted events; red team — leave-one-family-out and
Tier-1-only re-evaluations. P1-B: per scenario — 100 in-process repetitions (new --repeat
flag), 10 fresh-process study runs pairwise byte-identical, 2 clean-checkout rebuilds
byte-identical. P1-C: 9 periodic fixtures × 10^4 periods; per-period interval vectors
(binary64 deltas of hexfloat-parsed times) bit-identical to period 1. Law 7: baseline at
frozen tune on all 32; K = min(200, exact count) per v1.2 B2; shortfalls score maximally
(classified physics per OUT_45 F3 where applicable); primary — corpus worst exact |Δt| ≤
corpus worst baseline |Δt| / 100 AND exact drift = 0 where baseline drift > 0 on periodic
fixtures; finite-scenarios-only ratio reported exploratory. Construction scope: checkers,
study specs, --repeat flag only (model B — judges' code is agent-authored). Task DONE =
gates executed per rules; gate verdicts PASS/FAIL are results, not compliance.
NUMBERS: 32 scenarios; windows 200/12; P1-B set 100+10+2; P1-C 9×10^4; Law 7 margin 100×.
LEARNED: nothing
NEXT: OUT_46 review → Phase-1 gate call to Director (PASS) or falsification record (FAIL).

---
### JRN-C001-59 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_45_C-001-T12-R1 per P6 §2. Criteria 1–9 COMPLIANT: immutability diff
confined to docs/ + ledger; builds/tests green; streaming 20k ×2 identical full sha256s
(exact) + parity (baseline, 513@20000); F3 classified (a) physics — post-contact inward
reflection, domain exit t≈1.059 — PB-1 shortfall stands per v1.2 B2; venvs ignored; full
tune grid + complete TUNE-LAW7.json with selection rule correctly applied (min FL-1 |Δt|
in [1,2] window, tie → larger N ⇒ dt=5e-4, N=128, mean ratio 1.8987); byte-verbatim
status; digests complete incl. TR; TR verbatim in REPORT. Verdict: ACCEPT — C-001-T12
VERIFIED via R1. Findings: (i) baseline N≥512 "write failed" — latent defect outside gate
path, known-issue logged, no pre-gate fix; (ii) compute-match mean-vs-per-scenario
interpretation recorded (FL-1 2.25× — contestant over-resourced; direction favorable to
baseline, consistent with Director D-2 "dials up"); (iii) nit — ctest exit code not
echoed; pass/fail fact verbatim. Pre-gate feasibility audit per v1.2 A3 caught a PM
registration defect: P1-A's 25-event quasi-chaotic window is unsatisfiable in binary64
(λ^25 amplification ≈ 2e-5 ≫ 1e-9) — amended to 12 events in v1.3 BEFORE any held-out run.
NUMBERS: tune (5e-4, 128, 1.8987); λ ∈ [2.56, 2.92]; 12-event bound 3.9e-11.
LEARNED: run the A3 feasibility audit against EVERY registered tolerance before its gate
is scheduled, not only the ones that already failed once.
NEXT: GATE-P1 (this packet).

---
### JRN-C001-58 · DONE
actor: composer-agent · task: C-001-T12-R1 · manifest: n/a

WHAT: C-001-T12-R1 evidence-only DONE. Immutability proven: `git diff --name-status
ab39836..HEAD` shows only docs/ and inbox/APPLIED.log — zero src/tools/data/config/tests
changes. All T12 evidence regenerated read-only; values match OUT_44 summaries (exact sha256
6c84d5df2a1cc83c158503a492ecaae18577d50d336f7335be8aadfa585e675b ×2; baseline sha256
6145ff9f1d0b8f492166185cbf29e8a4901a7c24921d1a30f2275239f66e653e ×2 at 513 events;
ratio 1.8986844600152826 dt=5e-4 N=128; F3 classification (a) physics). TR completed with
full evidence + TUNE-LAW7.json; OUT_45 written per L-16.
NUMBERS: stream 20000 exact; baseline 513 at horizon 20000; tune ratio 1.899; FL-1 |Δt|=2.5e-4.
LEARNED: nothing
NEXT: OUT_45 review; on ACCEPT — PACKET 46 gate runs.

---
### JRN-C001-57 · CLAIM
actor: composer-agent · task: C-001-T12-R1 · manifest: n/a

WHAT: Claimed C-001-T12-R1 (evidence-only OUT rework per L-16) on branch task/C-001-T12
after PACKET 45 apply; OUT_44 tip ab39836 immutable.
NUMBERS: none new — regenerate existing T12 evidence only.
LEARNED: nothing
NEXT: Immutability proof; regenerate all §3 evidence; complete TR; write OUT_45.

---
### JRN-C001-56 · NOTE
actor: pm-fable5-b · task: C-001-T12-R1 · manifest: n/a

WHAT: C-001-T12-R1 authored (PACKET 45) — evidence-only rework. The T12 implementation
commits stand untouched; R1 emits a compliant OUT: every T12 acceptance criterion's
artifact pasted byte-verbatim (toolchain, configure/build, ctest + doctest summary, 20k
streaming evidence with FULL sha256s ×2 exact + ×2 baseline parity, F3 dump excerpt +
classification reasoning, gitignore status excerpt, FULL tune grid timing table +
TUNE-LAW7.json content, byte-verbatim git status), full TR pasted in REPORT and listed in
FILE DIGESTS, and an immutability proof: `git diff --name-status <OUT_44 tip>..HEAD`
showing changes confined to docs/, outbox/, and inbox/APPLIED.log — zero diffs under src/,
tools/, data/. L-16 in force; OUT-REQUIREMENTS restated in full below and in all future
packets.
NUMBERS: none new — R1 may not produce new numbers, only evidence existing ones.
LEARNED: nothing (pending R1).
NEXT: OUT_45 review; on ACCEPT — PACKET 46 gate runs (P1-A → P1-B → P1-C → Law 7 per v1.2
B3; committed tree, dirty=false; first held-out contact, gate-authorized, logged).

---
### JRN-C001-55 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_44_C-001-T12 per P6 §2. Criteria 1–8: evidence ABSENT from the OUT —
no toolchain/build/ctest pastes; streaming sha256s truncated to ellipses; no F3 dump
excerpt; no gitignore status excerpt; no tune grid table; no git status; REPORT section is
a repo pointer ("See TR_C-001-T12.md"); criterion 9 NON-COMPLIANT — TR absent from FILE
DIGESTS. Verdict: REJECT — inadmissible evidence class. Rationale of record: model-B
review reads OUT files only (P6 §2.2); accepting repo-pointer evidence one packet before
gate runs would reinstate trust-me review exactly where evidence discipline matters most.
Distinct from OUT_38 (substantive miss → REJECT) and OUT_39/41 (partial, aggregate
verbatim → ACCEPT+remediation, L-15/v2): OUT_44 is wholesale absence → REJECT (ladder
codified in L-16). PM contributing factor owned: OUT-REQUIREMENTS issued by reference
("as PACKET 38") since PACKET 39 — decays across fresh agent instances; L-16 binds the PM
to full restatement per packet. The summarized work product (ratio 1.899, dt=5e-4 N=128,
F3=physics/domain-exit, 20k streaming) is plausibly sound and is NOT re-executed — R1 is
evidence-only with an immutability proof.
NUMBERS: 8 of 9 criteria without in-OUT artifacts.
LEARNED: L-16 (docs/02_PROGRAM/LESSONS.md).
NEXT: C-001-T12-R1 (this packet).

---
### JRN-C001-54 · DONE
actor: composer-agent · task: C-001-T12 · manifest: n/a

WHAT: C-001-T12 complete DONE: EventEmitSink + EventStreamWriter — offline CLIs stream events
to disk via body temp file, --max-events up to 1e6; kMaxSimEvents=256 array retained for
in-process/tests. CAL-E1-FLAT-STREAM (e=1, vx=1/1e6) streaming evidence: 20000 events,
monotone seq, sha256 6c84d5df…e675b byte-identical ×2, wall ~0.12s; baseline parity
sha256 6145ff9f…e653e ×2 at same horizon (513 events, capacity-limited by baseline settle).
F3 PB-1 diagnostic (dt=1e-4, N=64): first contact t≈0.967; domain exit t≈1.059 x<0 after
backward reflection — CLASSIFICATION (a) physics (domain exit under polyline dynamics), not
harness defect. F2: tools/**/.venv/ gitignored. Law 7 tune: dt=5e-4, N=128,
mean_ratio=1.899 ∈ [1.0,2.0], FL-1 |Δt|=2.5e-4; TUNE-LAW7.json frozen at commit 901534c.
49/49 doctest SUCCESS (733 assertions); no golden expectations changed; no held-out contact.
NUMBERS: stream 20000 exact; tune ratio 1.899; chosen dt=5e-4 N=128.
LEARNED: e=1 flat streaming evidence needs near-vertical orbit (tiny vx) to reach 20k events
before fp settle; PB-1 baseline misses second exact contact via domain exit, not CLI bug.
NEXT: PACKET 45 gate runs (P1-A → P1-B → P1-C → Law 7).

---
### JRN-C001-53 · CLAIM
actor: composer-agent · task: C-001-T12 · manifest: n/a

WHAT: Claimed C-001-T12 (streaming emission + F3 diagnostic + F2 fix + Law 7
compute-match tune) on branch task/C-001-T12 after PACKET 44 apply; branched from
task/C-001-T11.
NUMBERS: streaming horizon up to 1e6; tune window [1.0×, 2.0×].
LEARNED: nothing
NEXT: Implement streaming CLIs, F3 dump, .gitignore, TUNE-LAW7.json; run steps 3–11; write TR
and OUT.

---
### JRN-C001-52 · NOTE
actor: pm-fable5-b · task: C-001-T12 · manifest: n/a

WHAT: C-001-T12 authored (PACKET 44) — final pre-gate task, four parts: (1) streaming event
emission in both offline CLIs (bounce-run-scenario, bounce-baseline-run): events written to
the output file as produced through a fixed small buffer; --max-events honored up to 10^6;
the 256-event in-memory capacity ceases to bound offline horizons; the real-time processing
path is untouched (constraint applies to the future plugin path, not offline tools);
evidence — a ~20,000-event e=1 calibration-config run, monotone seq, byte-identical across
two runs. (2) F3 diagnostic: PB-1 baseline trajectory tail dump; classify the missing
second event as physics (tunneling/missed contact/domain exit) or harness defect;
report-only unless harness defect (then fix within task, per prereg v1.2 B2). (3) F2 fix:
.gitignore for local venvs (tools/**/.venv/); status clean thereafter. (4) Compute-match
tune per v1.2 B1: (dt, N) grid on calibration via I-004 timing; frozen tune artifact
tools/gaterunner/tune/TUNE-LAW7.json with the full timing table; chosen ratio in [1.0, 2.0].
NUMBERS: streaming horizon ≤ 1e6; tune window [1.0×, 2.0×]; evidence run ~2e4 events.
LEARNED: nothing
NEXT: C-001-T12 (this packet); PACKET 45 = P1-A → P1-B → P1-C → Law 7 (v1.2 B3), first
held-out contact, gate-authorized, dirty=false.

---
### JRN-C001-51 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Director rulings 2026-07-13, registered as PREREG v1.2 (approval = PACKET 44
dispatch). D-1: no baseline settle criterion — fixed-horizon Law 7 comparison, K = min(200,
exact event count) per scenario; baseline shortfall scores against it after F3
classification (v1.2 B2). Director product statement recorded: no imposed damping — balls
keep energy intact by default (e=1); restitution stays a parameter; e<1 fixtures remain
valid engine coverage (v1.2 B4). D-2: compute window [1.0×, 2.0×], baseline equal-or-more
("dials up", v1.2 B1). D-3: gate order P1-A → P1-B → P1-C → Law 7, halt on exact-gate
failure (v1.2 B3). Ball–ball collisions: confirmed out of scope per R2 — nothing
implemented, optional future feature; multi-ball remains independent balls under TB-1.
Pre-gate blocker credited to the Director's long-horizon question: P1-C (10^4 periods,
~2–3e4 events) exceeds the 256-event buffer — the exact engine could not execute its own
registered gate; streaming emission dispatched in T12.
NUMBERS: P1-C demand ~2–3e4 events vs buffer 256.
LEARNED: registered gates must be checked for *executability* against implementation
constants at registration time, not discovered at scheduling time.
NEXT: T12, then gates (PACKET 45).

---
### JRN-C001-50 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_43 C-001-T11 per P6 §2. Criteria 0-8 all COMPLIANT: capacity 64→256
with 100-event monotone evidence; baseline byte-identical across runs, FL-1 first contact
|Δt|=5.0001e-05 ≤ 2·dt vs tier-1 t=1.0; runner engine selection with binary sha256,
cross-engine compare refusal, cross-engine summary; calibration-only, shared io untouched.
Verdict: ACCEPT — C-001-T11 VERIFIED. Forward findings: (F1) baseline does not settle —
FL-1 capacity-capped at 256 vs exact settle at 13; to_settle undefined for Euler chatter;
resolved by Director D-1 fixed-horizon rule (v1.2 B2). (F2) tools/gaterunner/.venv/
untracked inside L-13 agent surface; .gitignore fix in T12. (F3) PB-1 baseline=1 vs exact=2
events — classify missed-contact vs domain-exit before Law 7 so the baseline loses honestly
or not at all (T12 diagnostic). (F4) gate manifests require engine_git_dirty=false
(standing rule).
NUMBERS: FL-1 exact=13 baseline=256(cap); PB-1 exact=2 baseline=1; |Δt|=5.0001e-05.
LEARNED: a fixed-timestep contestant needs its own termination semantics — the exact
engine's settle concept does not transfer.
NEXT: PACKET 44 (this packet) — rulings + T12; PACKET 45 — gate runs.

---
### JRN-C001-49 · DONE
actor: composer-agent · task: C-001-T11 · manifest: n/a

WHAT: C-001-T11 complete DONE: kMaxSimEvents lifted 64→256 (only collision_sim.hpp change in
src/core/bounce/); bounce-baseline-run semi-implicit-Euler polyline engine in src/baseline/
with shared io serialization; gaterunner engine selection (exact|baseline), manifest engine
identity fields, --compare refusal and --cross-engine summary; 49/49 doctest SUCCESS (733
assertions); FL-1 baseline first-contact |Δt|=5e-05 ≤ 2·dt; capacity test 100 events with
monotone seq; no held-out execution.
NUMBERS: kMaxSimEvents=256; baseline dt=1e-4 segments=64 on FL-1; cross-engine FL-1
exact=13 baseline=256 events.
LEARNED: polyline baseline hits capacity before settle on FL-1 at default horizon.
NEXT: PM review OUT_43.

---
### JRN-C001-48 · CLAIM
actor: composer-agent · task: C-001-T11 · manifest: n/a

WHAT: Claimed C-001-T11 (Law 7 baseline engine + capacity lift + runner engine selection)
on branch task/C-001-T11 after PACKET 43 apply; branched from task/I-004-T23.
NUMBERS: capacity lift 64→256; baseline dt/segments free parameters.
LEARNED: nothing
NEXT: Implement capacity lift, baseline engine, gaterunner selection; run steps 3–10; write TR and OUT.

---
### JRN-C001-47 · NOTE
actor: pm-fable5-b · task: C-001-T11 · manifest: n/a

WHAT: C-001-T11 authored (PACKET 43) — the Law 7 named baseline, agent-authored per L-14;
first contestant-class deliverable under model B, which exists precisely so the PM does not
control both sides of the falsifiable bet (JRN-C001-42). Scope, three coherent parts:
(1) engine event-capacity lift — kMaxSimEvents 64 → 256, runtime --max-events honored up to
capacity, zero heap on the processing path preserved (only src/core/bounce/ change; tested);
(2) baseline engine per C-001-PREREG §5: fixed-timestep semi-implicit Euler over an
N-segment polyline sampling of the curve, impulse reflection at segment crossings with
linear-interpolated crossing times, same restitution/G-1/S-1 constants from the same source
of record, --dt and --segments free parameters, canonical event serialization via the
shared io layer (bounce-baseline-run CLI); (3) gaterunner "engine" study-spec field
(exact|baseline) with binary sha256 recorded in the manifest. dt/N compute-matching is NOT
in this task — it runs on calibration only, via I-004 timing, in the gate packet per
C-001-PREREG §5. Standing gate-call rule recorded: gate manifests require
engine_git_dirty=false.
NUMBERS: capacity 256; baseline parameters dt, N free; prereg margin at stake 100×.
LEARNED: nothing
NEXT: C-001-T11 (this packet); PACKET 44 = compute-match tune + P1-A/P1-B/P1-C + Law 7 gate
runs — first held-out engine contact, gate-authorized and logged.

---
### JRN-C001-46 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_36 (apply only) per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | APPLY CONFIRMATION with serial-36 ledger line + four-file list, PREREG flagged created | COMPLIANT |
| 2 | All applied blocks copied verbatim | COMPLIANT |
| 3 | FILE DIGESTS: byte count + sha256 for all four files | COMPLIANT |
| 4 | Step-3 git status: no modified tracked entries; untracked confined to Director courier surface (L-13) | COMPLIANT |
| 5 | BRANCH/COMMITS ends with L-12 terminator | COMPLIANT |
Verdict: ACCEPT — PACKET 36 APPLIED; C-001 PREREGISTERED (PREREGISTRATION.md v1.0 binding).
PM authoring note: the PACKET 35 DIRECTOR ACTION (merge-sizing git outputs) went unanswered
across two cycles — misrouting owned by the PM: read-only repo evidence is agent-gatherable
per P6 §7.1(b) and never belonged on the Director. Rerouted as diagnostic steps inside
PACKET 37's TASK; the merge instruction is sized from OUT_37 in PACKET 38.
NUMBERS: none
LEARNED: read-only repo evidence routes to a diagnostic packet step, never to a Director
action; Director actions are reserved for acts only the Director can perform.
NEXT: I-004-T1 (PACKET 37); merge instruction + I-003-T2 mint (PACKET 38).

---
### JRN-C001-45 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: C-001 PREREGISTRATION.md authored (PACKET 36); C-001 BRIEFED → PREREGISTERED.
Registered: P1-A (Design A) primary — max per-event |Δt| ≤ 1e-9 s and |Δs| ≤ 1e-9 over the
full held-out corpus, exact ball_id/seq, worst-case + distributions reported (L-05 analog);
P1-B (Design B) primary — bit-identical CollisionEvent sequences across 100 in-process runs,
10 fresh-process runs, 2 clean-checkout rebuilds, scoped to the environment of record until
I-007 (PROJECT §9 safeguard b); P1-C (Design C) primary — bit-exact interval-sequence
repetition over 10^4 periods on held-out periodic fixtures including non-dyadic orbits;
P1-D (Design D) DEFERRED — budget registration requires a measured basis via I-004/I-005
profiling; no realtime claim before its addendum. Law 7: compute matched by wall-time per
simulated scenario-second (±10%) on the environment of record via I-004; margin — exact
engine worst-case held-out event-time error ≤ baseline/100 at matched-or-lower compute, and
zero drift on periodic fixtures where the baseline drifts; baseline agent-authored (L-14).
Coverage table fixed over {flat line, explicit polynomial deg 2–6, piecewise Bézier C1} ×
{settle, periodic, quasi-chaotic} × {1, 2–4 balls}; declared empty: transcendental families
(R3), ball–ball (R2), Bézier×quasi-chaotic (Phase-1 reference-horizon cost), 8–16 balls
(P1-D scope); grazing mandatory — ≥3 near-tangency scenarios at |v_n| ∈ {0.5, 1.0, 2.0} ×
v_graze plus one near-double-root geometry. Held-out: ~40%, stratified by family × regime,
minted by I-003-T2 from Tier-1 CAS + Tier-2 refsim, locked before any engine run, access via
I-004 only (Law 1).
NUMBERS: tolerances 1e-9/1e-9; nuisance set 100+10+2; horizon 10^4 periods; margin 100×;
compute match ±10%; held-out ~40%; grazing ≥3+1.
LEARNED: nothing
NEXT: I-004 gate-runner brief + merge instruction (PACKET 37); Tier-2 hard-cell fixture mint
(PACKET 38); C-001-T11 spec (agent-authored baseline) after I-004 is briefed.

---
### JRN-C001-44 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_35 (apply only) per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | APPLY CONFIRMATION with serial-35 ledger line + five-file list with directions | COMPLIANT |
| 2 | All applied blocks copied verbatim | COMPLIANT |
| 3 | FILE DIGESTS: byte count + sha256 for all five files | COMPLIANT |
| 4 | Step-3 git status: no modified tracked entries; untracked confined to Director courier surface (L-13) | COMPLIANT |
| 5 | BRANCH/COMMITS ends with L-12 terminator | COMPLIANT |
Verdict: ACCEPT — PACKET 35 APPLIED. Model B (L-14), gate scoping (JRN-C001-43), and the
packet-as-file delivery rule are on the record. PACKET 35 DIRECTOR ACTION outputs (tip of
task/C-001-T10; branches unmerged to main) still outstanding — non-blocking; merge
instruction deferred to PACKET 37 and sized to that evidence when pasted.
NUMBERS: none
LEARNED: nothing
NEXT: PACKET 36 (this packet — prereg).
---
### JRN-C001-43 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Gate-language scoping. The T8/T9/T10 doctests exercise the *shapes* of the §8
determinism_repro, loop_stability, and reference_agreement gates on the calibration set; they
are not gate executions. A §8 gate claim requires: C-001 PREREGISTRATION.md (design A/B/C,
coverage table, tolerances), the I-003 held-out corpus locked and populated, execution via the
I-004 gate runner, and grazing cases per PROJECT §9. Known power limits recorded for the
precursors: T8 repeats runs in-process only (no block-size, process, or platform variance —
Design B nuisance conditions untouched); T9's fixture FL-1 has exactly dyadic bounce times, so
zero drift is guaranteed by construction and the test has near-zero power against non-dyadic
periodic orbits; T10's corpus is two easiest-cell fixtures with no Tier-2 members, and its
per-scenario comparisons aggregate into boolean assertions (4 assertions total), hiding which
event/field diverged on failure. No VERIFIED status is suspended — the tests are sound as
calibration coverage — but no journal or register entry may cite them as gates passed.
NUMBERS: precursor power limits — T8: 1 process, 1 machine; T9: 1 dyadic orbit; T10: 2
fixtures, 0 Tier-2, 4 assertions.
LEARNED: naming a development test after a gate invites the record to claim the gate later;
scope the name at authoring time.
NEXT: C-001 PREREGISTRATION.md (PACKET 36); I-004 brief (PACKET 37); Tier-2 fixture mint
targeting grazing / near-double roots / non-dyadic orbit / Bézier segments (PACKET 38).

---
### JRN-C001-42 · CORRECTION
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: PM deviation owned per P6 §6.1. Deviation: C-001-T1 through T10 implementation and test
translation units were PM-authored and carried in packet FILES sections (digests pre-registered,
outputs pre-built), with agents reduced to transcription plus build/test on the environment of
record. This contradicts the standing role boundary (Director correction at I-002: agents write
all product code from C-001 onward) and voids the premise of P6 §2.2 / L-10 that the PM has no
repo access — review became the PM checking its own pre-verified output. Root cause: P6 §7.4
"pre-verifying acceptance outputs" read expansively as license to compose and execute the
codebase. Durable fix: Director ruling 2026-07-12, Option B — packets carry specs, interface
declarations, fixtures, oracle values, and acceptance-test files only; implementation under
src/ is agent-authored; the PM does not build or execute the repository, and §7.4
pre-verification means derivation of expected oracle values from specifications. Codified as
L-14; second occurrence of the PM-authoring class after I-002, so a P6 §4.6 amendment is
proposed to the Director per P6 §6.3 (folded into STATE open decision 2). Status of T1–T10:
VERIFIED statuses stand — their acceptance evidence is agreement with Tier-1 closed-form and
Tier-2 mpmath oracle values, which are independent of implementation authorship — but no §8
gate claim attaches to them (JRN-C001-43), and C-001-T11 (Law 7 baseline) is mandatorily
agent-authored: the PM authoring both the exact engine and its named baseline would control
both sides of the falsifiable bet.
NUMBERS: scope of deviation — 10 tasks (T1–T10), packets 25–34.
LEARNED: L-14 (docs/02_PROGRAM/LESSONS.md).
NEXT: L-14 in force from PACKET 35; P6 §4.6 amendment awaits Director approval (open decision 2).

---
### JRN-C001-41 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_34_C-001-T10 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 39/39 cases, 503/503 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-34 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-37/-38/-39/-40 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T10 VERIFIED. No further C-001 task dispatches until C-001
PREREGISTRATION.md lands (PACKET 36) — T11 is agent-authored per L-14 and gated on the prereg's
matched-compute definition.
NUMBERS: 1 reference_agreement corpus test case (T10).
LEARNED: nothing
NEXT: PACKET 36 (prereg + merge housekeeping).
---
### JRN-C001-40 · DONE
actor: composer-agent · task: C-001-T10 · manifest: n/a

WHAT: C-001-T10 complete DONE: agrees_with_tier1_reference (kTier1ReferenceEpsilon=1e-12 on t/s;
exact ball_id/seq) + doctest tier-1 calibration corpus (FL-1 + PB-1); ctest 100% tests passed with
39 test cases / 503 assertions / SUCCESS; workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 1 new reference_agreement corpus test case.
LEARNED: nothing
NEXT: PM review OUT_34; on ACCEPT, C-001-T11 brief proceeds.

---
### JRN-C001-39 · CLAIM
actor: composer-agent · task: C-001-T10 · manifest: n/a

WHAT: Claimed C-001-T10 (reference_agreement tier-1 calibration corpus + unit tests)
on branch task/C-001-T10 after PACKET 34 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 34; write TR and OUT.

---
### JRN-C001-38 · NOTE
actor: pm-composer · task: C-001-T10 · manifest: n/a

WHAT: C-001-T10 authored (PACKET 34): agrees_with_tier1_reference (kTier1ReferenceEpsilon=1e-12
on t and s; exact ball_id/seq) + doctest tier-1 calibration corpus (FL-1 + PB-1 from
data/scenarios/calibration/). PM pre-verification (P6 §7.4): ctest 100% tests passed; doctest 39
test cases / 503 assertions / SUCCESS. Digests pre-registered.
NUMBERS: 1 new reference_agreement corpus test case.
LEARNED: nothing
NEXT: C-001-T10 (this packet); on ACCEPT, C-001-T11 brief proceeds.

---
### JRN-C001-37 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_33_C-001-T9 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 38/38 cases, 499/499 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-33 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-33/-34/-35/-36 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T9 VERIFIED. C-001-T10 dispatched (PACKET 34).
NUMBERS: 1 loop_stability test case (T9).
LEARNED: nothing
NEXT: C-001-T10 (PACKET 34).

---
### JRN-C001-36 · DONE
actor: composer-agent · task: C-001-T9 · manifest: n/a

WHAT: C-001-T9 complete DONE: extract_collision_intervals + intervals_equal (exact ==) +
doctest FL-1 loop_stability (11 dyadic-halving intervals bit-exact, 100 repeated full-horizon
runs with zero interval-sequence drift); ctest 100% tests passed with 38 test cases / 499
assertions / SUCCESS; workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 1 new loop_stability test case.
LEARNED: nothing
NEXT: PM review OUT_33; on ACCEPT, C-001-T10 brief proceeds.

---
### JRN-C001-35 · CLAIM
actor: composer-agent · task: C-001-T9 · manifest: n/a

WHAT: Claimed C-001-T9 (loop_stability zero interval-sequence drift on FL-1 + unit tests)
on branch task/C-001-T9 after PACKET 33 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 33; write TR and OUT.

---
### JRN-C001-34 · NOTE
actor: pm-composer · task: C-001-T9 · manifest: n/a

WHAT: C-001-T9 authored (PACKET 33): extract_collision_intervals + intervals_equal (exact ==) +
doctest FL-1 loop_stability — 11 dyadic-halving intervals verified bit-exact, then 100 repeated
full-horizon runs with zero interval-sequence drift (12 intervals through settle). PM
pre-verification (P6 §7.4): ctest 100% tests passed; doctest 38 test cases / 499 assertions /
SUCCESS. Digests pre-registered.
NUMBERS: 1 new loop_stability test case.
LEARNED: nothing
NEXT: C-001-T9 (this packet); on ACCEPT, C-001-T10 brief proceeds.

---
### JRN-C001-33 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_32_C-001-T8 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 37/37 cases, 286/286 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-32 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-29/-30/-31/-32 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T8 VERIFIED. C-001-T9 dispatched (PACKET 33).
NUMBERS: 1 determinism_repro test case (T8).
LEARNED: nothing
NEXT: C-001-T9 (PACKET 33).

---
### JRN-C001-32 · DONE
actor: composer-agent · task: C-001-T8 · manifest: n/a

WHAT: C-001-T8 complete DONE: events_equal (exact == on all CollisionEvent fields) +
doctest FL-1 determinism_repro (100 repeated run_calibration_scenario calls, bit-identical
to baseline); ctest 100% tests passed with 37 test cases / 286 assertions / SUCCESS;
workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 1 new determinism_repro test case.
LEARNED: nothing
NEXT: PM review OUT_32; on ACCEPT, C-001-T9 brief proceeds.

---
### JRN-C001-31 · CLAIM
actor: composer-agent · task: C-001-T8 · manifest: n/a

WHAT: Claimed C-001-T8 (determinism_repro repeated-run identity on FL-1 + unit tests)
on branch task/C-001-T8 after PACKET 32 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 32; write TR and OUT.

---
### JRN-C001-29 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_31_C-001-T7 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 36/36 cases, 185/185 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-31 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-25/-26/-27/-28 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T7 VERIFIED. C-001-T8 dispatched (PACKET 32).
NUMBERS: 4 calibration-scenario test cases (T7).
LEARNED: nothing
NEXT: C-001-T8 (PACKET 32).

---
### JRN-C001-30 · NOTE
actor: pm-composer · task: C-001-T8 · manifest: n/a

WHAT: C-001-T8 authored (PACKET 32): events_equal (all CollisionEvent fields, exact ==) +
doctest FL-1 determinism_repro — 100 repeated run_calibration_scenario calls, each bit-identical
to baseline. PM pre-verification (P6 §7.4): ctest 100% tests passed; doctest 37 test cases /
286 assertions / SUCCESS. Digests pre-registered.
NUMBERS: 1 new determinism_repro test case.
LEARNED: nothing
NEXT: C-001-T8 (this packet); on ACCEPT, C-001-T9 brief proceeds.
---
### JRN-C001-28 · DONE
actor: composer-agent · task: C-001-T7 · manifest: n/a

WHAT: C-001-T7 complete DONE: parse_rational + load_calibration_scenario (schema-v1 subset,
stdlib-only JSON scan) + run_calibration_scenario; doctests load/run FL-1 eight tier-1 reference
events and PB-1 first contact from data/scenarios/calibration/; ctest 100% tests passed with 36
test cases / 185 assertions / SUCCESS; workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 4 new calibration-scenario test cases.
LEARNED: nothing
NEXT: PM review OUT_31; on ACCEPT, C-001-T8 brief proceeds.

---
### JRN-C001-27 · CLAIM
actor: composer-agent · task: C-001-T7 · manifest: n/a

WHAT: Claimed C-001-T7 (calibration scenario JSON runner + unit tests)
on branch task/C-001-T7 after PACKET 31 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 31; write TR and OUT.

---
### JRN-C001-26 · NOTE
actor: pm-composer · task: C-001-T7 · manifest: n/a

WHAT: C-001-T7 authored (PACKET 31): parse_rational + load_calibration_scenario (schema-v1
subset, stdlib-only JSON scan) + run_calibration_scenario; doctests load/run FL-1 eight tier-1
reference events and PB-1 first contact from data/scenarios/calibration/. PM pre-verification
(P6 §7.4): ctest 100% tests passed; doctest 36 test cases / 185 assertions / SUCCESS. Digests
pre-registered.
NUMBERS: 4 new calibration-scenario test cases.
LEARNED: nothing
NEXT: C-001-T7 (this packet); on ACCEPT, C-001-T8 brief proceeds.

---
### JRN-C001-25 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_30_C-001-T6 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 32/32 cases, 130/130 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-30 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-21/-22/-23/-24 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T6 VERIFIED. C-001-T7 dispatched (PACKET 31).
NUMBERS: 3 collision-sim test cases (T6).
LEARNED: nothing
NEXT: C-001-T7 (PACKET 31).

---
### JRN-C001-24 · DONE
actor: composer-agent · task: C-001-T6 · manifest: n/a

WHAT: C-001-T6 complete DONE: simulate_multi_ball_collisions with TB-1 ordering (min global t,
then ball_id), fixed-stack ActiveBall state for kMaxBalls=4, global seq assignment; doctests on
simultaneous tie-break, earliest-time pick, monotone seq; ctest 100% tests passed with 32 test
cases / 130 assertions / SUCCESS; workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 3 new collision-sim test cases.
LEARNED: nothing
NEXT: PM review OUT_30; on ACCEPT, C-001-T7 brief proceeds.

---
### JRN-C001-23 · CLAIM
actor: composer-agent · task: C-001-T6 · manifest: n/a

WHAT: Claimed C-001-T6 (TB-1 multi-ball global event queue + unit tests)
on branch task/C-001-T6 after PACKET 30 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 30; write TR and OUT.

---
### JRN-C001-22 · NOTE
actor: pm-composer · task: C-001-T6 · manifest: n/a

WHAT: C-001-T6 authored (PACKET 30): simulate_multi_ball_collisions with TB-1 ordering
(min global t, then ball_id), fixed-stack ActiveBall state for kMaxBalls=4, global seq
assignment; doctests on simultaneous tie-break, earliest-time pick, monotone seq. PM
pre-verification (P6 §7.4): ctest 100% tests passed; doctest 32 test cases / 130 assertions /
SUCCESS. Digests pre-registered.
NUMBERS: 3 new collision-sim test cases.
LEARNED: nothing
NEXT: C-001-T6 (this packet); on ACCEPT, C-001-T7 brief proceeds.

---
### JRN-C001-21 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_29_C-001-T5 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 29/29 cases, 108/108 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-29 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-17/-18/-19/-20 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T5 VERIFIED. C-001-T6 dispatched (PACKET 30).
NUMBERS: 2 collision-sim test cases (T5).
LEARNED: nothing
NEXT: C-001-T6 (PACKET 30).

---
### JRN-C001-20 · DONE
actor: composer-agent · task: C-001-T5 · manifest: n/a

WHAT: C-001-T5 complete DONE: events::CollisionEvent schema (PROJECT §6 fields), simulator
emits full schema events with seq assignment; doctest on PB-1 tier-1 first contact (t=1, s=1 on
y=x²) and unit-normal check; ctest 100% tests passed with 29 test cases / 108 assertions /
SUCCESS; workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 2 new collision-sim test cases.
LEARNED: nothing
NEXT: PM review OUT_29; on ACCEPT, C-001-T6 brief proceeds.

---
### JRN-C001-19 · CLAIM
actor: composer-agent · task: C-001-T5 · manifest: n/a

WHAT: Claimed C-001-T5 (CollisionEvent schema + PB-1 first-contact agreement + unit tests)
on branch task/C-001-T5 after PACKET 29 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 29; write TR and OUT.

---
### JRN-C001-18 · NOTE
actor: pm-composer · task: C-001-T5 · manifest: n/a

WHAT: C-001-T5 authored (PACKET 29): events::CollisionEvent (PROJECT §6 fields), simulator
emits full schema events with seq assignment, PB-1 first-contact tier-1 agreement doctest
(t=1, s=1, ball_id=0, unit normal at x=1 on y=x²). PM pre-verification (P6 §7.4): ctest 100%
tests passed; doctest 29 test cases / 108 assertions / SUCCESS. Digests pre-registered.
NUMBERS: 2 new collision-sim test cases.
LEARNED: nothing
NEXT: C-001-T5 (this packet); on ACCEPT, C-001-T6 brief proceeds.

---
### JRN-C001-17 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_28_C-001-T4 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 27/27 cases, 90/90 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-28 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-14/-15/-16 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T4 VERIFIED. C-001-T5 dispatched (PACKET 29).
NUMBERS: 4 collision-sim test cases (T4).
LEARNED: nothing
NEXT: C-001-T5 (PACKET 29).

---
### JRN-C001-16 · DONE
actor: composer-agent · task: C-001-T4 · manifest: n/a

WHAT: C-001-T4 complete DONE: reflect_velocity + simulate_ball_collisions (G-1 graze
continuation, S-1 settle, fixed-stack event buffer) in src/core/bounce/engine/; doctest on FL-1
eight tier-1 event times, max_events cap, S-1 settle; ctest 100% tests passed with 27 test
cases / 90 assertions / SUCCESS; workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 4 new collision-sim test cases.
LEARNED: nothing
NEXT: PM review OUT_28; on ACCEPT, C-001-T5 brief proceeds.

---
### JRN-C001-15 · CLAIM
actor: composer-agent · task: C-001-T4 · manifest: n/a

WHAT: Claimed C-001-T4 (elastic reflection + graze continuation + multi-event FL-1 sequence +
unit tests) on branch task/C-001-T4 after PACKET 28 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 28; write TR and OUT.

---
### JRN-C001-14 · NOTE
actor: pm-composer · task: C-001-T4 · manifest: n/a

WHAT: C-001-T4 authored (PACKET 28): reflect_velocity (algorithm-identity with tier2_refsim
reflect), simulate_ball_collisions loop (G-1 graze continuation, S-1 settle, fixed-stack event
buffer), FL-1 eight-event tier-1 time sequence doctest. PM pre-verification (P6 §7.4): ctest 100%
tests passed; doctest 27 test cases / 90 assertions / SUCCESS. Digests pre-registered.
NUMBERS: 4 new collision-sim test cases.
LEARNED: nothing
NEXT: C-001-T4 (this packet); on ACCEPT, C-001-T5 brief proceeds.

---
### JRN-C001-13 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_27_C-001-T3 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 23/23 cases, 56/56 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-27 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-10/-11/-12 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T3 VERIFIED. C-001-T4 dispatched (PACKET 28).
NUMBERS: 4 new VCA test cases (T3).
LEARNED: nothing
NEXT: C-001-T4 (PACKET 28).

---
### JRN-C001-12 · DONE
actor: composer-agent · task: C-001-T3 · manifest: n/a

WHAT: C-001-T3 complete DONE: vca_refine_root_x (bisection 2⁻⁴⁰ + 3 DD Newton) +
normal_impact_speed + kVGraze admissibility + step_ball_next_collision in
src/core/bounce/engine/; doctest on FL-1 refinement, impact speed, accepted ground hit, no-hit
case; ctest 100% tests passed with 23 test cases / 56 assertions / SUCCESS; workspace clean per
L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 4 new VCA test cases.
LEARNED: nothing
NEXT: PM review OUT_27; on ACCEPT, C-001-T4 brief proceeds.

---
### JRN-C001-11 · CLAIM
actor: composer-agent · task: C-001-T3 · manifest: n/a

WHAT: Claimed C-001-T3 (fixed refinement + admissibility filter + single-ball event step +
unit tests) on branch task/C-001-T3 after PACKET 27 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 27; write TR and OUT.

---
### JRN-C001-9 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_26_C-001-T2 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 19/19 cases, 44/44 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-26 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-6/-7/-8 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T2 VERIFIED. C-001-T3 dispatched (PACKET 27).
NUMBERS: 3 VCA test cases (T2).
LEARNED: nothing
NEXT: C-001-T3 (PACKET 27).

---
### JRN-C001-10 · NOTE
actor: pm-composer · task: C-001-T3 · manifest: n/a

WHAT: C-001-T3 authored (PACKET 27): vca_refine_root_x (bisection to 2⁻⁴⁰ interval scale +
3 Newton steps in double-double, DELIVERABLE_B §3), normal_impact_speed + kVGraze admissibility
filter, step_ball_next_collision single-ball pipeline (isolate → refine → admissibility). PM
pre-verification (P6 §7.4): ctest 100% tests passed; doctest 23 test cases / 56 assertions /
SUCCESS. Digests pre-registered.
NUMBERS: 4 new VCA test cases.
LEARNED: nothing
NEXT: C-001-T3 (this packet); on ACCEPT, C-001-T4 brief proceeds.

---
### JRN-C001-5 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_25_C-001-T1 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 16/16 cases, 39/39 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-25 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-2/-3/-4 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T1 VERIFIED. C-001-T2 dispatched (PACKET 26).
NUMBERS: 5 engine test cases (T1).
LEARNED: nothing
NEXT: C-001-T2 (PACKET 26).

---
### JRN-C001-8 · DONE
actor: composer-agent · task: C-001-T2 · manifest: n/a

WHAT: C-001-T2 complete DONE: collision_difference_x (curve y − ballistic P(x)) +
vca_isolate_smallest_root bracket scan in src/core/bounce/engine/; doctest on FL-1 ground
crossing bracket, no-root case; ctest 100% tests passed with 19 test cases / 44 assertions /
SUCCESS; workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 3 new VCA test cases.
LEARNED: nothing
NEXT: PM review OUT_26; on ACCEPT, C-001-T3 brief proceeds.

---
### JRN-C001-7 · CLAIM
actor: composer-agent · task: C-001-T2 · manifest: n/a

WHAT: Claimed C-001-T2 (VCA root isolation on explicit-polynomial curve + unit tests)
on branch task/C-001-T2 after PACKET 26 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 26; write TR and OUT.

---
### JRN-C001-6 · NOTE
actor: pm-composer · task: C-001-T2 · manifest: n/a

WHAT: C-001-T2 authored (PACKET 26): collision_difference_x (curve y − ballistic P(x)) +
vca_isolate_smallest_root bracket scan with recursive root-in-interval check (algorithm-identity
with tier2_refsim isolate_smallest_positive_root, x-domain). PM pre-verification (P6 §7.4):
ctest 100% tests passed; doctest 19 test cases / 44 assertions / SUCCESS. Digests pre-registered.
NUMBERS: 3 new VCA test cases.
LEARNED: nothing
NEXT: C-001-T2 (this packet); on ACCEPT, C-001-T3 brief proceeds.

---
### JRN-C001-4 · DONE
actor: composer-agent · task: C-001-T1 · manifest: n/a

WHAT: C-001-T1 complete DONE: double-double add/mul/div + ballistic parabola P(x) in
src/core/bounce/numerics/ and src/core/bounce/engine/; doctest on DD ops, FL-1 ground hit,
vx=0 rejection; ctest 100% tests passed with 16 test cases / 39 assertions / SUCCESS; workspace
clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 5 new engine test cases (3 DD + 2 ballistic).
LEARNED: nothing
NEXT: PM review OUT_25; on ACCEPT, C-001-T2 brief proceeds.

---
### JRN-C001-3 · CLAIM
actor: composer-agent · task: C-001-T1 · manifest: n/a

WHAT: Claimed C-001-T1 (double-double arithmetic + ballistic parabola P(x) + unit tests)
on branch task/C-001-T1 after PACKET 25 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 25; write TR and OUT.

---
### JRN-C001-2 · NOTE
actor: pm-composer · task: C-001-T1 · manifest: n/a

WHAT: C-001-T1 authored (PACKET 25): double-double add/mul/div (no FMA, DELIVERABLE_B §4);
ballistic parabola P(x) coefficient compile via DD + position_at_time; FL-1 ground-hit doctest.
PM pre-verification (P6 §7.4): ctest 100% tests passed; doctest 16 test cases / 39 assertions /
SUCCESS. Digests pre-registered.
NUMBERS: 5 new engine test cases (3 DD + 2 ballistic).
LEARNED: nothing
NEXT: C-001-T1 (this packet); on ACCEPT, C-001-T2 brief proceeds.

---
### JRN-C001-1 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: C-001 thesis and brief applied (PACKET 22). Register → THESIS. First engine task
sketched (double-double + ballistic P(x)); dispatch after C-002-T2 so curve families cover
Bézier before engine integration tests.
NUMBERS: none
LEARNED: nothing
NEXT: I-003-T1 (PACKET 23); C-002-T2 briefed in PACKET 24.

# JOURNAL — I-008 AV assessment harness (bounce-view)

---
### JRN-I008-14 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_59_I-008-T3 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | environment + ACCESS_LOG 88 (before) + branch base in CLAIM | COMPLIANT — f9bf7bf6fe1eb8743e7716f4f37d7618a1ec545f |
| 2 | 5(a) faithful-default paste | COMPLIANT — events=28, t_last consistent with T2 |
| 3 | 5(b) override blip count = events=N | COMPLIANT — 500 = 500; e=1 run reached the cap (no early-end FINDING) |
| 4 | 5(c) flag exclusivity | COMPLIANT — error + exit=1 |
| 5 | paired default proof (interactive override=1; evidence faithful) | COMPLIANT — via --print-config |
| 6 | S8 v2 perf p95 ≤ 2×(1000/refresh_Hz) + frames×mean vs duration statement | COMPLIANT — 9.313905 ≤ 16.667 @120 Hz; 9626 ms vs 10016 ms honestly explained |
| 7 | determinism diff 0 on override run | COMPLIANT |
| 8 | suite 63 (by derivation) SUCCESS exit=0 ctest 100% + c7-v2 isolation 0 | COMPLIANT |
| 9 | ACCESS_LOG 88 (after) | COMPLIANT |
| 10 | TR verbatim, RUN section, both affirmation lines (S7+S9) | COMPLIANT |
| 11 | status + L-13 v2 delta + inherited dispositions | COMPLIANT — courier deletions identified, not asserted (see flag) |
| 12 | FILE DIGESTS complete | COMPLIANT |

Verdict: ACCEPT. I-008-T3 is VERIFIED. With T1–T3 verified, I-008 is FEATURE-COMPLETE for
its D-4 purpose: default infinite-bounce playback (D-5), opt-in damping, AV-2 voice,
settled-ball persistence, S8 v2 perf instrument, selftest determinism, Law-1 guard.
Substantive notes: (a) the e=1 override run reached its 500-event cap with internally
consistent voice parameters — no graze/settle surprise surfaced; (b) perf under the
defined measurand reads p95 9.314 ms, comfortably inside one-and-a-bit refresh intervals
at 120 Hz — the felt-fluidity verdict now belongs to the Director's re-assessment.

COURIER FLAG (Director disposition per L-13 v2 — the PM records, never asserts): the
status paste shows uncommitted deletions of TRACKED inbox/PACKET_1.md–PACKET_11.md and
untracked serials 51–59 only (13–50 removed from disk). Consequence if ignored: a future
`git add -A` commits the deletions silently. Disposition options (Director's): restore
(`git checkout -- inbox/`) or commit the cleanup deliberately as housekeeping
(`git add -u inbox/ && git commit`). Recorded; not a task defect — the agent pasted and
identified without asserting, exactly per L-13 v2.
NUMBERS: 12/12 COMPLIANT; p95 9.313905 ms @120 Hz; override run 500/500; ACCESS_LOG 88/88.
LEARNED: nothing new — three consecutive OUTs with the L-18 discipline applied produced
zero criterion disputes on numeric grounds.
NEXT: Director — live re-assessment (RUN section, OUT_59) + inbox disposition + decision 4
(corpus A vs B), which opens D-4 step 3 (resumption bundle → P1-B/P1-C).

---
### JRN-I008-13 · DONE
actor: composer-agent · task: I-008-T3 · manifest: n/a

WHAT: I-008-T3 complete on branch task/I-008-T3. S10 restitution override: interactive
default e=1 with rolling event extension; evidence modes scenario-faithful; flag exclusivity;
--print-config paired proof; --max-events for selftest. S8 v2 perf measurand (present
interval, first frame excluded): FL-1 p95=9.314 ms ≤ 16.667 ms @120 Hz. CF-E2a override
selftest events=500 blip count match; determinism diff 0. Suite 63/63 ctest 100%.
Isolation 0 vs f9bf7bf base. ACCESS_LOG 88.
NUMBERS: p95=9.313905 ms; frames=1145 mean=8.407328 ms duration=10.016 s; events=500;
diff=0; isolation=0.
LEARNED: evidence and interactive paths need separate default proof artifacts when
--perf-seconds is classified as evidence mode.
NEXT: OUT_59 review → Director re-assessment.

---
### JRN-I008-12 · CLAIM
actor: composer-agent · task: I-008-T3 · manifest: n/a

WHAT: Claimed I-008-T3 on branch task/I-008-T3 from task/I-008-T2 tip f9bf7bf6fe1eb8743e7716f4f37d7618a1ec545f
(chain through serial 59 apply; main merge deferred to Director). Scope: PACKET 59 — S10
restitution override (interactive default e=1; evidence modes scenario-faithful), S8 v2 perf
measurand (present-interval), S9 language rule; zero changes under src/ tests/ config/ data/.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–13 per PACKET 59 TASK I-008-T3.

---
### JRN-I008-11 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_58_I-008-T2 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | environment + ACCESS_LOG 88 (before) | COMPLIANT |
| 2 | instrumentation-only commit line | COMPLIANT — 080167c |
| 3 | RED perf paste + dominant-subsystem paragraph from pasted numbers | COMPLIANT as written — but see MEASURAND FINDING below |
| 4 | GREEN p95 ≤ 2×(1000/refresh_Hz), both values in paste | COMPLIANT — 16.381 ≤ 16.667 @120 Hz |
| 5 | frames + t_frame > t_last from same run | COMPLIANT — 3.5 > 3.0701041642833404 |
| 6 | CF-E2a v2 log + diff 0; FL-1 diff 0 | COMPLIANT |
| 7 | suite 63/63 + zero-count diff main..HEAD on frozen paths | NON-COMPLIANT as written (count 100) — criterion DEFECTIVE; amended c7-v2 below; satisfied on the OUT's packet/57..HEAD = 0 paste |
| 8 | ACCESS_LOG 88 (after) | COMPLIANT |
| 9 | TR verbatim, RUN section, S7 line | COMPLIANT |
| 10 | status + L-13 v2 | COMPLIANT — branch base disclosed in CLAIM |
| 11 | FILE DIGESTS complete | COMPLIANT |

Verdict: ACCEPT. I-008-T2 is VERIFIED (OUT_58 under c7-v2).

C7 ROOT CAUSE — PM authoring defect, owned per P6 §2.4/§6.1: the zero-count was bound to
the range main..HEAD, deriving 0 from an ASSUMED Director merge state (the PACKET 58
precondition), i.e. from courier state that L-13 v2 says is pasted, never asserted — and
with no derivation from the run's own semantics. This violates standing rule L-18, the
first violation since its issuance (third defect of the authoring-precision family in four
packets: JRN-C001-95, JRN-C001-97, here). The agent disclosed its branch base
(packet/57 tip) at CLAIM and supplied the correct isolation proof unprompted.
CORRECTED CRITERION c7-v2 (standing form for all future isolation criteria): "task
isolation is proven by `git diff --name-only <base>..HEAD -- <frozen paths> | wc -l` = 0,
where <base> is the branch-point commit stated in the task's CLAIM entry; ranges anchored
on main or any Director-courier ref are inadmissible as assertions." Satisfied on OUT_58's
existing paste; no return needed (L-15 economics). The pending P6 §4 derivation-rule
amendment (open decision 2) gains urgency from this recurrence.

MEASURAND FINDING (S8): RED reports mean=1.2735 ms over 552 frames in 10 s — a real
frame interval of ~18.1 ms — while GREEN's mean=9.1653 ms matches 10000/1092 exactly. The
pre-fix instrument measured per-frame work; the post-fix instrument measures frame
interval. Consequence, stated plainly: the RED paste does not quantify the Director's felt
~10 fps, and RED→GREEN is not a like-for-like delta; F1's fix is validated by the GREEN
bound plus the Director's live re-assessment only. S8 v2 (BRIEF amendment this packet)
pins the measurand: frame_ms = interval between successive returns from present, monotonic
clock, first frame excluded, identical definition in every mode. T3 re-pastes perf under
S8 v2. Classified with the attribute-precision family; recurrence tracking continues.

D-5 DIRECTOR PRODUCT DIRECTION (recorded verbatim in substance): the tool aims at INFINITE
bounces; damping logic stays but is strictly opt-in; default is none. This confirms the
registered physics default (v1.2 B4: e=1, no imposed damping) and now governs harness
presentation (S10) and, later, product-layer defaults (C-003+). Also noted for open
decision 5: CF-E2a settle run = 28 events vs its 4-event reference window — third
calibration-side sighting of the reference-termination schema gap.
NUMBERS: 10/11 COMPLIANT; c7-v2 satisfied on file; GREEN p95 16.381 ms @120 Hz; RED
interval ≈18.1 ms vs reported 1.27 ms (measurand shift); CF-E2a 28 vs 4.
LEARNED: an isolation criterion anchored on main asserts the Director's housekeeping;
anchor on the CLAIM-stated base, always.
NEXT: T3 (this packet) → Director live re-assessment (fluidity + AV-2 + infinite default);
decision 4 still gates D-4 step 3.

---
### JRN-I008-8 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: OUT_57 apply-only ACCEPTED (confirmation + verbatim copies + digests + L-12
terminator; nothing further to table). Director merged the stacked chain to main and
delivered the live AV assessment — D-4 step 2 COMPLETE. Findings of record:
F1 PERFORMANCE — interactive rendering perceived at ~10 fps, not fluid. Disposition:
harness defect (the engine is event-driven; between-event position queries are closed-form
and cheap — a correct render loop has no reason to miss display refresh). T2 fixes this
repro-first: measurement instrumentation lands first (`--perf-seconds`), RED stats +
per-subsystem timing pasted BEFORE optimization, GREEN after against an L-18-derived
criterion (p95 frame time ≤ 2× the display refresh interval reported by the same run;
derivation: VSYNC pacing makes the refresh interval the run's own expected frame period,
and a 2× bound admits at most isolated missed deadlines, never sustained halving).
F2 SETTLED BALL DISAPPEARS — after an e<1 Zeno cascade the ball vanishes. Disposition,
two parts: (a) the physics is REGISTERED behavior, not a defect — rule S-1
(DELIVERABLE_B §3) marks the ball SETTLED below v_settle and emits no further events;
rolling/sliding contact is explicitly out of Phase-1 scope (R1 companion ruling). The
product-default regime (e=1, v1.2 B4) never settles — the finding manifests only on e<1
fixtures. (b) The HARNESS presentation of that semantics is defective: a SETTLED ball must
remain visible, resting at its settle position on the curve, until restart — fixed in T2
(S2.1). True rolling contact is a genuinely new dynamical regime (constrained motion with
a departure condition; time-parametrization has no closed form in general — a deterministic
fixed-order quadrature thesis, not an engine patch) and is escalated as OPEN DECISION 6,
never smuggled into an assessment-harness task.
F3 SOUND QUALITY — the AV-1 blip is a bare sine by spec (deliberately minimal).
Superseded by AV-2 (BRIEF S3 v2): exponentially decaying three-partial voice, impact speed
driving amplitude, decay time, and brightness; pitch mapping unchanged; still
assessment-only, C-003 inherits nothing.
NUMBERS: 3 findings; F1/F3 harness-scoped (T2); F2 split harness (T2) / component
(decision 6).
LEARNED: the AV harness is doing its job — it converted a Phase-0 scope ruling (S-1, R1)
from registered text into a felt product decision within one session of use.
NEXT: OUT_58 review; decision 4 answer opens the resumption bundle (D-4 step 3);
decision 6 shapes the Phase-2 slate.

---
### JRN-I008-10 · DONE
actor: composer-agent · task: I-008-T2 · manifest: n/a

WHAT: I-008-T2 complete on branch task/I-008-T2. S8 --perf-seconds landed (instrumentation
commit before optimization). RED FL-1: present subsystem dominant (0.313 ms/frame). GREEN:
p95=16.381 ms ≤ 2×(1000/120)=16.667 ms with VSYNC + curve cache + incremental playback.
S2.1 settled-ball persistence: CF-E2a frames at t=2.5 (mid-cascade) and t=3.5 (post-settle,
t_frame > t_last). AV-2 voice + S5.1 v2 log format; CF-E2a and FL-1 A/B diff count 0. Suite
63/63 SUCCESS ctest 100%. Zero diff on frozen paths vs packet/57 tip. ACCESS_LOG 88.
NUMBERS: RED frames=552 p95=0.632 ms; GREEN frames=1092 p95=16.381 ms; events CF-E2a=28
t_last=3.070104; t_frame=3.5; diff counts 0/0.
LEARNED: VSYNC makes present the GREEN bottleneck by design; unoptimized RED cost was
curve_draw + SDL_Delay pacing, not engine query.
NEXT: OUT_58 review → Director re-assessment.

---
### JRN-I008-9 · CLAIM
actor: composer-agent · task: I-008-T2 · manifest: n/a

WHAT: Claimed I-008-T2 on branch task/I-008-T2 from packet/57 tip (chain through serial 57;
main merge deferred to Director). Scope: PACKET 58 assessment-feedback improvements —
S8 perf instrumentation (repro-first RED/GREEN), S2.1 settled-ball persistence, S3 v2 AV-2
voice + S5.1 selftest format; zero changes under src/ tests/ config/ data/.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–14 per PACKET 58 TASK I-008-T2.

---
### JRN-I008-7 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_56_I-008-T1-R1 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | environment paste + ACCESS_LOG 88 (before) | COMPLIANT |
| 2 | suite pastes: 63 cases (derivation: suite unchanged since OUT_54), all passed, SUCCESS!, exit=0; ctest 100% | COMPLIANT |
| 3 | CF-E2b metadata paste per field rule + basis statement | COMPLIANT — schema silent on termination basis; 12 tier-2 reference events |
| 4 | .gitignore diff + status, no __pycache__/ untracked; delta limited to task files | COMPLIANT |
| 5 | ACCESS_LOG 88 (after) | COMPLIANT |
| 6 | TR pasted verbatim (L-16) | COMPLIANT |
| 7 | FILE DIGESTS complete, full sha256s | COMPLIANT |

Verdict: ACCEPT. I-008-T1 is VERIFIED on the union of OUT_55 (harness: build, deterministic
selftest, Law-1 guard proven, frames, RUN section) and OUT_56 (suite tripwire under c6-v2,
metadata, housekeeping). Register updated to VERIFIED this packet. Main merge of the
stacked chain task/C-001-T17 → task/I-008-T1 → task/I-008-T1-R1 released to the Director
(merging the R1 tip carries all three; Director verifies the final OUT commit as tip per
L-12).

SUBSTANTIVE FINDING (open decision 5 material): the fixture schema is SILENT on the
reference's termination basis — the 26-vs-12 question (CF-E2b engine settle run vs
12-event reference) therefore remains OPEN as a schema gap, not resolvable from committed
artifacts. Routed to the gate-resumption bundle: the scenario schema gains a
reference_termination field (settle | horizon <N> | cap) as an I-002/I-003 requirement,
applied at corpus-B mint or corpus-A annotation per the Director's decision 4.
NUMBERS: 7/7 COMPLIANT; 63/63 suite; ACCESS_LOG 88/88; 12 reference events in CF-E2b.
LEARNED: nothing beyond the routed schema gap.
NEXT: Director — batched merge + live AV assessment (D-4 step 2); PM — resumption-bundle
drafting opens on the Director's decision-4 answer (corpus-A reuse vs corpus-B mint).

---
### JRN-I008-6 · DONE
actor: composer-agent · task: I-008-T1-R1 · manifest: n/a

WHAT: I-008-T1-R1 complete. Regression tripwire: 63/63 doctest SUCCESS! exit=0; ctest 100%
exit=0. CF-E2b metadata pasted; schema silent on reference termination basis (horizon vs
settle). __pycache__/ appended to .gitignore; pycache entries no longer untracked.
ACCESS_LOG 88 before and after.
NUMBERS: 63 test cases; ACCESS_LOG 88/88; reference_events count in fixture=12.
LEARNED: none new.
NEXT: OUT_56 review → I-008-T1 VERIFIED.

---
### JRN-I008-5 · CLAIM
actor: composer-agent · task: I-008-T1-R1 · manifest: n/a

WHAT: CLAIM I-008-T1-R1 per PACKET 56. Branch task/I-008-T1-R1 from task/I-008-T1 tip.
Scope: regression tripwire (c6-v2 b), CF-E2b metadata paste, __pycache__/ gitignore
housekeeping. Writable surface: .gitignore, docs/05_INFRA/I-008_av_harness/reports/,
outbox/, journal. PROHIBITED: src/, tests/, tools/, config/, data/ changes; held-out
execution.
NUMBERS: ACCESS_LOG must remain 88.
NEXT: steps 3–9 per PACKET 56 TASK.

---
### JRN-I008-4 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_55_I-008-T1 (BLOCKED) per P6 §2/§7. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | environment paste incl. SDL2 | COMPLIANT — SDL2 2.32.8 |
| 2 | repair-A quote + assertion | COMPLIANT |
| 3 | repair-B listing, three names byte-for-byte | NON-COMPLIANT as written — listing pasted; nine true names ≠ three TR names; adjudicated in JRN-C001-96 (criterion unsatisfiable against repo truth; purpose fulfilled by the verbatim listing) |
| 4 | build tail + zero-diff src/core,config | COMPLIANT — 0, exit=0 |
| 5 | FL-1 selftest run A + A/B diff 0 | COMPLIANT — 34 events, deterministic |
| 6 | CF-E2b 12 blips + events=12 | NON-COMPLIANT as written — events=26 under S5 settle semantics; PM authoring defect (see below) |
| 7 | guard message + exit=2 + ACCESS_LOG 88/88 | COMPLIANT |
| 8 | frames ls + sha256s, committed | COMPLIANT |
| 9 | TR verbatim, RUN section, S7 line | COMPLIANT |
| 10 | status + L-13 v2 delta + dispositions | COMPLIANT — pycache residue identified as inherited; disposition routed to R1 per L-13 v2's "this or next packet" branch |
| 11 | FILE DIGESTS complete, full sha256s | COMPLIANT |

Verdict: AMEND + RETURN, scoped to criteria 3 and 6.

CRITERION 6 ROOT CAUSE — PM authoring defect, owned per P6 §2.4/§6.1: the expected value 12
was OUT_54's REFERENCE-STREAM count for CF-E2b, imported into a criterion governing an S5
run (settle or 200-event cap). The two runs have different semantics; the engine emitting
26 events before S-1 settle is not adjudicable as regression or non-regression by that
number. The agent's diagnosis (cross-check: --max-events 12 reproduces the T17 window) is
accepted. SECOND occurrence of the empirical-value authoring class (first: PACKET 54 c3,
JRN-C001-95) → per P6 §6.3: LESSONS L-18 issued this packet + P6 §4 amendment proposal
(numeric criteria carry their derivation) added to the open-decision-2 bundle.

CORRECTED CRITERION c6-v2 (replaces PACKET 55 criterion 6): "(a) the CF-E2b selftest's blip
line count equals its own `selftest ok events=N` summary (internal 1:1 blip-per-collision)
— SATISFIED on OUT_55's existing paste (26 lines, events=26); (b) the regression tripwire
is the committed test suite: full ctest+doctest run pasted, all cases pass, SUCCESS!,
exit=0, case count 63 — derivation: the suite is unchanged since OUT_54 (tests/ read-only
in T1 and R1), so 63 is a consequence of the run's own semantics; any other count is
BLOCKED (unexpected suite change), per L-18."

SUBSTANTIVE OBSERVATION for open decision 5: CF-E2b engine settle run = 26 events vs a
12-event Tier-1 reference — live calibration-side instance of the reference-horizon /
S-1-semantics gap flagged in JRN-C001-91 (c). Whether the reference is generator-horizon-
limited or settle-limited is disambiguated by R1 step 5 (fixture metadata paste), not by
PM guess.

R1 SCOPE: suite tripwire paste (c6-v2 b), CF-E2b metadata paste, `__pycache__/` gitignore
housekeeping (L-13 v2 disposition), OUT. Harness evidence otherwise stands; I-008-T1 →
VERIFIED at OUT_56 review if R1 lands. The Director's interactive AV assessment (D-4 step
2 payoff) is runnable now from OUT_55's RUN section and proceeds in parallel.
NUMBERS: 9/11 COMPLIANT; 2 scoped amendments; harness: SDL2 2.32.8, FL-1 34 events
deterministic, guard exit=2, frames 2×1440015 bytes, ACCESS_LOG 88/88.
LEARNED: recorded as L-18.
NEXT: OUT_56 review → I-008-T1 VERIFIED + register update + batched merges; Director AV
assessment → D-4 step 3 planning.

---
### JRN-I008-3 · BLOCKED
actor: composer-agent · task: I-008-T1 · manifest: n/a

WHAT: bounce-view v1 implemented per BRIEF S1–S7 (SDL2 target, Law-1 guard, selftest,
interactive RUN, frames). REPAIR-A (c3-v2) satisfied from committed TR. BLOCKED: REPAIR-B —
doctest --list-test-cases emits nine per-fixture T17 names; TR expects three aggregate names
(tests/ read-only). BLOCKED: step 9 CF-E2b selftest events=26 under S5 settle/200 cap;
criterion expects events=12 (T17 paired-window count; engine gives 12 only with max-events=12).
Steps 3/7/8/10/11 evidence on file in TR.
NUMBERS: SDL2 2.32.8; ACCESS_LOG 88/88; FL-1 selftest events=34; CF-E2b events=26; frames 2.
LEARNED: TR-documented doctest names may differ from registered TEST_CASE strings; S5 settle
semantics extend beyond T17 reference windows on settling fixtures.
NEXT: PM disposition on REPAIR-B naming + step 9 event-count criterion vs S5.

---
### JRN-I008-2 · CLAIM
actor: composer-agent · task: I-008-T1 · manifest: n/a

WHAT: Claimed I-008-T1 on branch task/I-008-T1 from task/C-001-T17 tip after PACKET 55
apply; bounce-view harness per BRIEF S1–S7 plus OUT_54 repairs A (c3-v2) and B (L-15).
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–14 per PACKET 55 TASK I-008-T1.

---
### JRN-I008-1 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: I-008 registered and briefed per Director direction D-4 step 2 (JRN-C001-91). Scope:
assessment instrument only — SDL2 app linked against bounce_core; display-only curve
sampling (physics untouched, S2); assessment audio mapping AV-1 (S3; C-003 inherits
nothing); Law-1 path guard built into the binary (S6); no real-time claims (S7, P1-D
pending). Not gate-bearing; no register capability beyond "Director can see and hear the
engine". T1 dispatched by PACKET 55, carrying the two OUT_54 evidentiary repairs (c3-v2,
c6/L-15) as steps 4–5.
NUMBERS: none.
LEARNED: nothing
NEXT: OUT_55 review → T17 VERIFIED on repair → D-4 step 3 (gate-resumption bundle
planning).

---

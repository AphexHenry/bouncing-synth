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

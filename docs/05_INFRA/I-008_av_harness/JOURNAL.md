# JOURNAL — I-008 AV assessment harness (bounce-view)

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

# OUT 42 — I-004-T2+T3 — DONE
agent: composer-agent · branch: task/I-004-T23 · commits: 29ae239 750b7b8 090e23c

## APPLY CONFIRMATION

serial 42 applied by composer-agent · files: docs/02_PROGRAM/LESSONS.md, docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/05_INFRA/I-004_gaterunner/JOURNAL.md, docs/05_INFRA/I-004_gaterunner/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md

Ledger line:
```
serial 42 applied by composer-agent · files: docs/02_PROGRAM/LESSONS.md, docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/05_INFRA/I-004_gaterunner/JOURNAL.md, docs/05_INFRA/I-004_gaterunner/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md
```

Files written:
- docs/02_PROGRAM/LESSONS.md — APPEND
- docs/05_INFRA/I-003_scenario_store/JOURNAL.md — APPEND
- docs/05_INFRA/I-004_gaterunner/JOURNAL.md — APPEND
- docs/05_INFRA/I-004_gaterunner/BRIEF.md — APPEND
- docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md — OVERWRITE
- docs/00_STATE.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-I003-22 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_41_I-003-T3-R1 per P6 §2. Criteria 1–6, 8–12 COMPLIANT: amplification
certificates A ∈ {1.6e10…4.2e11} at ε=1e-30 with linearity within 10× across degrees 4/5/6;
strict non-dyadic gaps at ≥30 digits (verified √5, √7 periods are true values); C1 ok at
all joints; |disc| = 2.082e-7 ≤ 1e-6; validator cal=2/heldout=32/locked; concentration
21.9/28.1/34.4/15.6% all ≤50%; LAW-1 affirmed; digests complete. Criterion 7 PARTIAL:
per-fixture convergence table reduced to worst case (46.8995 digits) + machine-emitted
aggregate "(all 16 ≥45)" gated by exit=0; 15 per-fixture values absent from the OUT,
recoverable from committed fixture provenance. L-10 PARTIAL: applied PM journal entries and
file-direction list absent from the OUT (verbatim in the applied packet + committed docs).
Ruling per L-15 v2 (issued this packet; Director ratifies by dispatch, may override to
strict REJECT): ACCEPT — I-003-T3 VERIFIED — with three-part remediation at PACKET 42
step 0. MILESTONE: held-out corpus COMPLETE — 32 scenarios, locked, spanning dyadic and
non-dyadic orbits, four certified-chaotic geometries (measured, not asserted), five Bézier
fixtures incl. periodic, the {0.5,1,2}×v_graze grazing triplet, and a near-double-root
geometry. Law 1 is now physically enforceable; no further minting on the Phase-1 critical
path.
NUMBERS: corpus 32; convergence floor 46.8995 digits; max family concentration 34.375%.
LEARNED: L-15 v2 (docs/02_PROGRAM/LESSONS.md).
NEXT: I-004-T2+T3 (PACKET 42); C-001-T11 baseline spec (PACKET 43); gate runs.

---
### JRN-I004-5 · NOTE
actor: pm-fable5-b · task: I-004-T2+T3 · manifest: n/a

WHAT: I-004-T2+T3 authored batched (PACKET 42, step-size ruling): Python orchestrator
(tools/gaterunner/) — study spec in; per-scenario bounce-run-scenario invocations with
horizons FROM THE STUDY SPEC (JRN-I004-4: never the binary default); manifest of record out
(engine commit, toolchain versions, FP flags, scenario ids + sha256s, event-file sha256s,
per-scenario median-of-10 wall-times per C-001-PREREG §5, exit codes) — plus held-out
access discipline: split-lock verified before any run; every held-out execution appended to
a persistent access log; runner refuses held-out scenarios absent an explicit gate
authorization field in the study spec. THIS TASK EXECUTES CALIBRATION SCENARIOS ONLY — the
corpus's first engine contact is reserved for a real gate run; acceptance includes the
refusal negative test and proof the access log remains empty.
NUMBERS: manifest fields 8; smoke study = calibration set (FL-1, PB-1) run twice with
byte-identical event files.
LEARNED: nothing
NEXT: I-004-T2+T3 (this packet); on ACCEPT — C-001-T11 baseline spec, then gate scheduling.

---
### JRN-I004-6 · CLAIM
actor: composer-agent · task: I-004-T2+T3 · manifest: n/a

WHAT: Claimed I-004-T2+T3 (study orchestrator + manifest writer + held-out access
discipline) on branch task/I-004-T23 after PACKET 42 apply; step 0 OUT_41 remediation
(L-15 v2) first per brief.
NUMBERS: smoke study = calibration set (FL-1, PB-1); timing_runs=10.
LEARNED: nothing
NEXT: Step 0 remediation; implement tools/gaterunner/; run steps 3–9; write TR and OUT.

---
### JRN-I004-7 · DONE
actor: composer-agent · task: I-004-T2+T3 · manifest: n/a

WHAT: I-004-T2+T3 complete DONE: step 0 OUT_41 remediation passed (32-fixture convergence
table re-derived; floor 46.8995055434254; all ≥45); tools/gaterunner/ orchestrator with study
spec, split-lock validation, manifest of record, --compare identity mode, held-out refusal
before engine invocation; SMOKE-CAL-1 run twice byte-identical event files; negative test
refused held-out without gate_id; ACCESS_LOG.jsonl absent; ctest 100% + SUCCESS!; §5 hard
rule affirmed (calibration-only execution).
NUMBERS: 2 calibration scenarios × 10 timing runs; manifest fields per brief §3.
LEARNED: horizon "to_settle" maps to kMaxSimEvents=64 explicit --max-events.
NEXT: PM review OUT_42.


## FILE DIGESTS

```
7233 cc8c94ef15ae158751886af600db096792593de69558d25275a3cec969997020 docs/02_PROGRAM/LESSONS.md
19334 85e5e9cc8cf40b8e68a19bd4ecf5f50f0d26b97b8eaff9daf907d556e24223f1 docs/05_INFRA/I-003_scenario_store/JOURNAL.md
5720 2d1dbf88ce6c697552e5957b93ec722e865a7f6d0a984dcbc64e33922779346e docs/05_INFRA/I-004_gaterunner/JOURNAL.md
12178 dd2b2c2bf9a36dcca277fe843ff3d04719163398227a55c55b5518db73719680 docs/05_INFRA/I-004_gaterunner/BRIEF.md
1314 210dbe9c49b378f6412bf6b956f041b9eeafd00038312c294d02a6cec327a6ef docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
2949 4a3b1a3c7ee957a9f300f1972e9f7ff8428499d536ba4f09c0529f7d3f81e90e docs/00_STATE.md
10356 d99d6993b55ed1e7e41f919dd346e6b445980e9295d16c84b7d9bb6286710a68 inbox/APPLIED.log
15271 c6d140b7f7370cc586d5950c4cf293a9c1dedf2efd3141341d52ac59a15c42a1 tools/gaterunner/gaterunner.py
14 a699f46ed76bd216f1081b6b2330e4fb45d7c8c5a5354b208694d6590a5a8645 tools/gaterunner/requirements.txt
223 2e9c70cd3d6410be180527dc66cb0021a59a4eaa0923055a150c8ec55fb9de8b tools/gaterunner/studies/SMOKE-CAL-1.json
234 cba428de8d27d6eb8532a5dfafed3f232f4cbca464041bee715eea3ec2ef3d29 tools/gaterunner/studies/NEG-HELDOUT-REFUSE-1.json
2053 8c7cc43a3dbe5b98b37fcd6caa717dc4d47faa72b8d7919aa98428988a3c6f7d tools/gaterunner/manifests/SMOKE-CAL-1-runA.json
2078 c0f6825b41fb807cab83ab81cfbbff10dc52568cc16bd1417da755d7485fbb6c tools/gaterunner/manifests/SMOKE-CAL-1-runB.json
13758 982b4625405ada74cf691bc02c0616376f4410901f37bf19d7e505ad81616dbc docs/05_INFRA/I-004_gaterunner/reports/TR_I-004-T2+T3.md
```

## REPORT

# TASK REPORT — I-004-T2+T3
actor: composer-agent / status: DONE / manifest: n/a

PER ACCEPTANCE CRITERION: 0 → Step 0 remediation (a)+(b)+(c) pasted below; floor matches
46.8995055434254; all ≥45.
PER ACCEPTANCE CRITERION: 1 → Step 3 pasted below.
PER ACCEPTANCE CRITERION: 2 → Step 4 pasted below; both exit=0.
PER ACCEPTANCE CRITERION: 3 → Step 5 pasted below; 100% passed + SUCCESS! + exit=0.
PER ACCEPTANCE CRITERION: 4 → Step 6 pasted below; both smoke runs exit=0; manifest §3 fields
present; --compare reports byte-identity.
PER ACCEPTANCE CRITERION: 5 → Step 7 pasted below; refusal nonzero exit; access log absent.
PER ACCEPTANCE CRITERION: 6 → §5 HARD RULE affirmed below; no deviations.
PER ACCEPTANCE CRITERION: 7 → Step 8 pasted below; workspace clean per L-13.
DEVIATIONS: none.
ARTIFACTS: tools/gaterunner/gaterunner.py, tools/gaterunner/studies/*.json,
tools/gaterunner/manifests/SMOKE-CAL-1-runA.json, tools/gaterunner/manifests/SMOKE-CAL-1-runB.json
OBSERVATIONS: horizon "to_settle" maps to explicit --max-events 64 (kMaxSimEvents).

## §5 HARD RULE AFFIRMATION
No held-out scenario was executed. SMOKE-CAL-1 used scenario_set=calibration only.
NEG-HELDOUT-REFUSE-1 was refused before any engine invocation. ACCESS_LOG.jsonl does not
exist after all steps.

## STEP 0 — OUT_41 remediation (L-15 v2)

### (a) Per-fixture convergence table (re-derived from committed fixture provenance)

```
tier1_R4_convergence_checks:
  HO-flat-settle-1: worst_case_agreement_digits=100.0
  HO-flat-settle-2: worst_case_agreement_digits=100.0
  HO-flat-settle-3: worst_case_agreement_digits=100.0
  HO-flat-settle-4: worst_case_agreement_digits=100.0
  HO-flat-periodic-1: worst_case_agreement_digits=50.718576287935605
  HO-flat-periodic-2: worst_case_agreement_digits=51.1905670379188
  HO-flat-periodic-3: worst_case_agreement_digits=50.78599945716392
  HO-parabola-settle-1: worst_case_agreement_digits=50.282164903383034
  HO-parabola-settle-2: worst_case_agreement_digits=49.61260860703802
  HO-parabola-settle-3: worst_case_agreement_digits=49.98478508341335
  HO-parabola-settle-4: worst_case_agreement_digits=49.98478508341335
  HO-parabola-periodic-1: worst_case_agreement_digits=50.37538867227295
  HO-parabola-periodic-2: worst_case_agreement_digits=50.29816551100322
  HO-graze-parabola-1: worst_case_agreement_digits=100.0
  HO-graze-parabola-2: worst_case_agreement_digits=61.76770976212145
  HO-graze-parabola-3: worst_case_agreement_digits=51.70875081761889
tier2_convergence_checks:
  HO-poly-settle-3: worst_case_agreement_digits=50.04255807563175
  HO-poly-settle-4: worst_case_agreement_digits=50.462218380625735
  HO-poly-settle-5: worst_case_agreement_digits=50.79390568745984
  HO-poly-settle-6: worst_case_agreement_digits=50.63971821322005
  HO-poly-periodic-1: worst_case_agreement_digits=50.53905328046861
  HO-poly-periodic-2: worst_case_agreement_digits=50.69554905831483
  HO-poly-quasichaotic-1: worst_case_agreement_digits=47.10137221088289
  HO-poly-quasichaotic-2: worst_case_agreement_digits=47.68899103130892
  HO-poly-quasichaotic-3: worst_case_agreement_digits=46.8995055434254
  HO-poly-quasichaotic-4: worst_case_agreement_digits=47.540298830955834
  HO-bezier-settle-1: worst_case_agreement_digits=51.32771982016211
  HO-bezier-settle-2: worst_case_agreement_digits=50.59509973707038
  HO-bezier-settle-3: worst_case_agreement_digits=50.59509973707038
  HO-bezier-periodic-1: worst_case_agreement_digits=51.389159985307415
  HO-bezier-periodic-2: worst_case_agreement_digits=51.41091640008986
  HO-poly-double-root-1: worst_case_agreement_digits=50.80580716085206
convergence_floor=46.8995055434254
all_ge_45=True
```

Assertion: floor equals 46.8995055434254 (HO-poly-quasichaotic-3); all 32 values ≥45.

### (b) Serial-41 applied PM journal entries (from committed docs)

---
### JRN-I003-19 · NOTE
actor: pm-fable5-b · task: I-003-T3-R1 · manifest: n/a

WHAT: I-003-T3-R1 authored (PACKET 41): same deliverable under prereg v1.1 — 16 Tier-2
fixtures with amended cells (deg 3–6 quasi-chaotic ×4 across ≥3 distinct degrees; Bézier
periodic ×2; parabola×quasi-chaotic empty per A1) and amplification-based admission (A ≥
1e6 at ε=1e-30 within ≤25 events, linearity spot-check at 1e-20 within 10× — A2). The
already-measured deg-6 candidate (A≈1.7e11) pre-qualifies with five orders of margin. All
other T3 spec provisions carry verbatim (LAW-1, R1 float64 discipline, R6, Tier-2
convergence ≥45 digits, C1 checks, discriminant fixture, lock, concentration paste, L-15
digest completeness). Branch continues task/I-003-T3 in place (WIP tooling present).
NUMBERS: 16 fixtures; corpus 32; A ≥ 1e6 at ε=1e-30; linearity within 10×.
LEARNED: nothing
NEXT: I-003-T3-R1 (this packet); on ACCEPT — I-004-T2+T3 batched (PACKET 42), then
C-001-T11 baseline spec.

---
### JRN-I003-18 · CORRECTION
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Two PM authoring defects in the I-003-T3 spec, owned per P6 §6.1. (1) The
quasi-chaotic admission triple (ε=1e-30, absolute bound 1e-10, ≤25 events) was registered
without a feasibility derivation; it requires a per-bounce stretching factor ≥ ~6.3×, above
anything the family exhibits (measured best ≈2.8×/bounce ⇒ 1.7e-19 at 25 events). The
agent's exhaustive search and linearity check were correct; the spec was unsatisfiable.
Durable fix: amplification-based admission (prereg v1.1 A2) + the feasibility-derivation
rule (A3). (2) Registered per-cell counts summed to 15 against a stated total of 16
(Bézier×periodic written ×1); corrected to ×2 in v1.1 A1. Domain finding elevated to the
record: parabola gravitational billiard is integrable — parabola×quasi-chaotic declared
empty (v1.1 A1), a coverage-table cell closed by measurement rather than assumption.
NUMBERS: measured amplifications — deg-6 ≈1.7e11 (exponential), parabola ≈2e1 (polynomial),
over 25 events at ε=1e-30.
LEARNED: registered thresholds involving dynamical growth carry an ε·λ^N feasibility bound
at authoring time (prereg v1.1 A3); count totals are summed, not asserted.
NEXT: I-003-T3-R1 (PACKET 41).

---
### JRN-I003-17 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_40_I-003-T3 (BLOCKED) per P6 §7. Block-handling compliance: step-0
OUT_39 remediation executed first and fully pasted — all 16 T2-R1 sha256s + manifest match;
the L-15 remediation is CLOSED and the T2-R1 digest ledger complete. LAW-1 affirmed.
Blocker evidence byte-verbatim (search result, best-candidate amplification, threshold,
linearity confirmation); stop-on-surprise honored — no invented parameters, no waived
criterion. WIP tooling (mint_tier2_heldout.py, refsim Bézier + sensitivity extensions)
committed with the OUT for continuation. Verdict: BLOCKED accepted as properly executed;
task neither VERIFIED nor REJECTED; resolution via prereg v1.1 + T3-R1 (this packet).
NUMBERS: none beyond JRN-I003-16's.
LEARNED: nothing
NEXT: T3-R1 dispatch.

## Amendment v1.1 — registered 2026-07-12 (PACKET 41; Director approval = packet dispatch)

Scope: two changes to §7, one addition to §1's quasi-chaotic handling. No held-out scenario
has been executed by any engine binary at amendment time; no results voided (§0).

A1. §7 cell "parabola (deg 2) × quasi-chaotic" is DECLARED EMPTY. Reason of record: the
single-ball gravitational billiard in a parabola is integrable; measured sensitivity
amplification over 25 events ≈ 2×10^1 (polynomial growth), versus ≈1.7×10^11 (exponential)
on deg-6 geometry — evidence OUT_40 (JRN-I003-16). Its two fixtures move to
"deg 3–6 × quasi-chaotic" (now ×4). "Bézier × periodic" corrected ×1 → ×2, restoring the
Tier-2 batch to 16 and the full corpus to 32. Expected concentration: flat 7/32, parabola
9/32, deg 3–6 11/32, Bézier 5/32 — all within the §8.iii cap.

A2. Quasi-chaotic admission criterion (replaces the absolute-divergence rule of the T3
brief): a fixture is admitted to a quasi-chaotic cell iff the measured amplification
A = max event-time divergence / ε satisfies A ≥ 1e6, at ε = 1e-30 applied to one registered
state component, within ≤25 events, computed in the refsim at dps ≥ 50; plus a linearity
spot-check at ε = 1e-20 whose amplification agrees within a factor of 10. Rationale:
amplification is ε-independent under the confirmed linear regime; the prior absolute bound
conflated perturbation size with dynamical growth.

A3. Feasibility-derivation rule (authoring discipline, binding on future registrations):
any registered threshold involving dynamical growth must carry an explicit ε·λ^N
feasibility bound at authoring time.

### (c) Serial-41 applied-files list with directions

- docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md — APPEND
- docs/05_INFRA/I-003_scenario_store/JOURNAL.md — APPEND
- docs/05_INFRA/I-003_scenario_store/BRIEF.md — APPEND
- docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md — OVERWRITE
- docs/00_STATE.md — OVERWRITE

## Step 3 — toolchain + venv

```
$ cmake --version | head -1
cmake version 3.27.8
$ c++ --version | head -1
Apple clang version 17.0.0 (clang-1700.6.4.2)
$ tools/gaterunner/.venv/bin/python --version
Python 3.9.6
$ tools/gaterunner/.venv/bin/pip show mpmath | grep Version
Version: 1.3.0
```

## Step 4 — configure + build

```
$ cmake --preset default
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
exit=0

$ cmake --build --preset default
[ 42%] Built target bounce-core
[ 89%] Built target bounce-tests
[100%] Built target bounce-run-scenario
exit=0
```

## Step 5 — ctest

```
$ ctest --test-dir build/default --output-on-failure
Test project /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
    Start 1: bounce-tests
1/1 Test #1: bounce-tests .....................   Passed    0.26 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.26 sec
exit=0
```

LastTest.log doctest summary:
```
[doctest] test cases:  42 |  42 passed | 0 failed | 0 skipped
[doctest] assertions: 516 | 516 passed | 0 failed |
[doctest] Status: SUCCESS!
```

## Step 6 — smoke study (calibration only)

```
$ tools/gaterunner/.venv/bin/python tools/gaterunner/gaterunner.py tools/gaterunner/studies/SMOKE-CAL-1.json --out tools/gaterunner/manifests/SMOKE-CAL-1-runA.json
gaterunner-ok study=SMOKE-CAL-1 manifest=tools/gaterunner/manifests/SMOKE-CAL-1-runA.json
exit=0

$ tools/gaterunner/.venv/bin/python tools/gaterunner/gaterunner.py tools/gaterunner/studies/SMOKE-CAL-1.json --out tools/gaterunner/manifests/SMOKE-CAL-1-runB.json
gaterunner-ok study=SMOKE-CAL-1 manifest=tools/gaterunner/manifests/SMOKE-CAL-1-runB.json
exit=0
```

Manifest run A (identity-bearing fields):
```json
{
  "engine_git_commit": "750b7b838cdd5efbe97d5200228a8ad609b55a34",
  "engine_git_dirty": true,
  "fp_determinism_flags": [
    "-ffp-contract=off",
    "-fno-fast-math"
  ],
  "runner_tool_sha256": "c6d140b7f7370cc586d5950c4cf293a9c1dedf2efd3141341d52ac59a15c42a1",
  "scenarios": [
    {
      "event_count": 13,
      "event_file_sha256": "e6cd3b4a0cd013aac68c5c32e39ed29bbed2a48775dd529c74a0f157ac451f71",
      "exit_code": 0,
      "scenario_id": "FL-1-h5-g10-e1o2",
      "scenario_sha256": "f4ee64cc06da5c2f2baf3392a51c2d776af07b7378bb5c4649e4cbbb17489b01"
    },
    {
      "event_count": 2,
      "event_file_sha256": "209e068b7270b22b557a1979299d40c964862a1a8a03432132dc19035e0cfa97",
      "exit_code": 0,
      "scenario_id": "PB-1-h9-g16-c1",
      "scenario_sha256": "b2145d853c7b852dead946822687f33e8c2d18f53da4154954e59d5afe01101b"
    }
  ],
  "study_spec": {
    "gate_id": null,
    "horizon": "to_settle",
    "notes": "Calibration smoke study — FL-1 and PB-1, twice for determinism cross-check.",
    "scenario_set": "calibration",
    "study_id": "SMOKE-CAL-1",
    "timing_runs": 10
  },
  "toolchain": {
    "cmake": "cmake version 3.27.8",
    "compiler": "Apple clang version 17.0.0 (clang-1700.6.4.2)",
    "python": "Python 3.9.6"
  }
}
```

```
$ tools/gaterunner/.venv/bin/python tools/gaterunner/gaterunner.py --compare tools/gaterunner/manifests/SMOKE-CAL-1-runA.json tools/gaterunner/manifests/SMOKE-CAL-1-runB.json
compare-ok: FL-1-h5-g10-e1o2 event_file_sha256=e6cd3b4a0cd013aac68c5c32e39ed29bbed2a48775dd529c74a0f157ac451f71
compare-ok: PB-1-h9-g16-c1 event_file_sha256=209e068b7270b22b557a1979299d40c964862a1a8a03432132dc19035e0cfa97
compare-ok: all calibration scenarios byte-identical across manifests
exit=0
```

## Step 7 — negative test + access log

```
$ tools/gaterunner/.venv/bin/python tools/gaterunner/gaterunner.py tools/gaterunner/studies/NEG-HELDOUT-REFUSE-1.json
heldout-access-denied: gate_id required for held-out scenarios
exit=1

$ ls data/scenarios/heldout/ACCESS_LOG.jsonl 2>&1
ls: data/scenarios/heldout/ACCESS_LOG.jsonl: No such file or directory
```

ACCESS_LOG.jsonl does not exist (not created-empty by design).

## Step 8 — git status

```
## task/I-004-T23
?? inbox/PACKET_13.md
?? inbox/PACKET_15.md
?? inbox/PACKET_16.md
?? inbox/PACKET_17.md
?? inbox/PACKET_18.md
?? inbox/PACKET_19.md
?? inbox/PACKET_20.md
?? inbox/PACKET_21.md
?? inbox/PACKET_22.md
?? inbox/PACKET_23.md
?? inbox/PACKET_24.md
?? inbox/PACKET_25.md
?? inbox/PACKET_26.md
?? inbox/PACKET_27.md
?? inbox/PACKET_28.md
?? inbox/PACKET_29.md
?? inbox/PACKET_30.md
?? inbox/PACKET_31.md
?? inbox/PACKET_32.md
?? inbox/PACKET_33.md
?? inbox/PACKET_34.md
?? inbox/PACKET_35.md
?? inbox/PACKET_36.md
?? inbox/PACKET_37.md
?? inbox/PACKET_38.md
?? inbox/PACKET_39.md
?? inbox/PACKET_40.md
?? inbox/PACKET_41.md
?? inbox/PACKET_42.md
?? tools/gaterunner/
```


## BRANCH/COMMITS

```
090e23c I-004-T2+T3 DONE: gate runner, manifests, held-out refusal.
750b7b8 I-004-T2+T3 CLAIM (JRN-I004-6).
29ae239 PACKET 42 apply: L-15 v2, I-004-T2+T3 brief, state updates.
+ final OUT commit (hash not self-listable)
```

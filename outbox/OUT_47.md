# OUT 47 — I-003-T4 + C-001-T13 — DONE
agent: composer-agent · branches: task/I-003-T4, task/C-001-T13 · commits: 071bf6c 14ba395 7d5e05b

## APPLY CONFIRMATION

serial 47 applied by composer-agent · files:
- FILE APPEND: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md (JRN-C001-63, JRN-C001-64)
- FILE APPEND: docs/05_INFRA/I-003_scenario_store/JOURNAL.md (JRN-I003-23)
- FILE APPEND: docs/05_INFRA/I-003_scenario_store/BRIEF.md (TASK I-003-T4)
- FILE APPEND: docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md (TASK C-001-T13)
- FILE OVERWRITE: docs/00_STATE.md
- FILE APPEND: inbox/APPLIED.log (serial 47 line)

## JOURNAL ENTRIES

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
### JRN-I003-25 · DONE
actor: composer-agent · task: I-003-T4 · manifest: n/a

WHAT: I-003-T4 complete DONE: re-minted HO-flat-settle-{1..4} via remint_flat_settle.py
(refsim/CAS; Law-1). Four new sha256s ≠ retired poisoned set; manifest + split-lock updated;
validator exit=0 (heldout=32, split_locked=true).
NUMBERS: 4 fixtures re-minted; corpus 32 unchanged.
LEARNED: nothing
NEXT: C-001-T13 held-out harness (PACKET 47 step 1).

---
### JRN-I003-24 · CLAIM
actor: composer-agent · task: I-003-T4 · manifest: n/a

WHAT: Claimed I-003-T4 (Law-1 re-mint HO-flat-settle-{1..4}) on branch task/I-003-T4 after
PACKET 47 apply; refsim/CAS only — no engine binary.
NUMBERS: 4 poisoned fixtures to retire.
LEARNED: nothing
NEXT: Run remint_flat_settle.py; validate store; TR.

---
### JRN-I003-23 · NOTE
actor: pm-composer · task: I-003-T4 · manifest: n/a

WHAT: I-003-T4 authored (PACKET 47 step 0) — Law-1 re-mint of HO-flat-settle-{1..4}.
OUT_46 failure survey invoked `bounce-run-scenario` on these four held-out fixtures without
I-004 gate authorization (JRN-C001-62). PREREG §6: any non-gate execution poisons the
scenario (retire + re-mint). Re-mint via refsim/CAS at Tier-1 standard with the same
registered per-cell parameters (flat line × settle, counts 4); same scenario_ids; new
fixture bytes and manifest sha256s. LAW-1 HARD RULE: no C++ engine binary built/linked/
invoked. Retired fixture sha256s journaled in the TR for audit.
NUMBERS: 4 scenarios re-minted; corpus remains 32.
LEARNED: gate-BLOCKED debugging must not invoke engine binaries on held-out paths — load-only
surveys suffice.
NEXT: I-003-T4 step 0 of PACKET 47; then C-001-T13.

## FILE DIGESTS

51905 6f14d85cd9881f4cb02a7418ef4b734faf620319354b69cecfbea98d25d3b74a docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md
21010 065e4a5c72d1a4ad145f7e5f007380f3f9fde32b1f79168dacf5d39f8d1c0bad docs/05_INFRA/I-003_scenario_store/JOURNAL.md
22105 2a71d9ef78db31ec41b07c0ab86fb76b5a1d70b9883dc34eac5c0b433db25679 docs/05_INFRA/I-003_scenario_store/BRIEF.md
31365 e1c6c83a40397e175fefab4a81134e3980af1c5acc981f2061917f6f89afbc53 docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md
2757 ceb6282df2c42a6eeab7caea0c634703cfee810e4948e7d2170c358568aece57 docs/00_STATE.md
11556 bb7c1cd5a88e3926c3d5a55d140b29dc7c3234118942b3f110b4cc207a250210 inbox/APPLIED.log
2791 3e42e05f08432c3629ac3d57ca219d95559482c9776fe99e179306cc801bbfb1 tools/scenarios/remint_flat_settle.py
1682 684809757ce90e326e416dd6ae801cc8bd4d47bfbe75c130a1cfe54a9daf2c2c data/scenarios/heldout/HO-flat-settle-1.json
1702 520105ead89a2a3f7f82953f3ad11dbb302aaf2a309e609fef5171800ddb53b9 data/scenarios/heldout/HO-flat-settle-2.json
2169 832f8bf04f41c5bd11f603ff57730e877432f0641c9eab2307fce5fc1b8d2803 data/scenarios/heldout/HO-flat-settle-3.json
2508 82f788302e4e38df9a1d8f1ce0cd7036d502030f90dee3762192579b2500b95a data/scenarios/heldout/HO-flat-settle-4.json
4634 cf6084dd21cd01f8977ca39b03077be1a8e37539de55790ef2e61f1345747598 data/scenarios/heldout/MANIFEST.json
348 197ef14641d8649f52c93b79ec83fbb6db8db9841ea683fd971c60f547b626f0 data/scenarios/split-lock.json
1580 bb056a0b3751e49a11fffa61d47e5d12a6f556b57a2af694bf127b7df33fc1f3 docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T4.md
1918 23a2d1cb8aa242c3b4cd96a6ef4acefdf40a12253e349f661a49ea824cdfbeb7 docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_C-001-T13.md
3111 b2b56e8534ff85107b5e11388c50d741fe391caa45aa318fafc4988d508e4569 CMakeLists.txt
2073 7cff2dd5488926f957899226c2dae25f2888f9f93e26b44be2fdff12f6fd17dd src/core/bounce/scenario/rational.cpp
2157 4788426948b39ee7907b3993d83c86b09d86334d109b114a0bd19c85dca8782e src/core/bounce/scenario/calibration_loader.hpp
18311 3829e7cb5b4d873139140a7fc1b339652abd6f699e223b3e66502b60b58336fd src/core/bounce/scenario/calibration_loader.cpp
1647 c5bb1dc949d5c42bf5f742ae4bc45666df82435d6b8d04511bb55594cc163e97 src/core/bounce/engine/vca.hpp
14067 60ecb7332b31be988b41f05ffc16dbd21043ddda4fd112ae6e88ebb1a2ea84c0 src/core/bounce/engine/vca.cpp
2186 353ce212e0c835d5ab7710d5b65238b7f8a7b06a25dc13c7a0c91add42aecd01 src/core/bounce/engine/collision_sim.hpp
10420 05acf270cab0517bdfa7515c55bb217617e4a459a04c80fb1af01ee078e5c17d src/core/bounce/engine/collision_sim.cpp
947 c394a744b583daa931191fb63ffb1b9ad9dc8e3541db6d36faa0c96aa3178ce4 src/baseline/polyline.hpp
3320 6147492e926bce3bbe52d6532cdaf86bff52b59e7a4c9ef23a2424bd4e59638e src/baseline/polyline.cpp
1304 34d86db3848c6e2d329d5878f87510b0afa65d5b477d61f0febe1ada00d35001 src/baseline/baseline_sim.hpp
13469 90a4587a2ba0e6f4cedfef06b034e237df763ca2cabfe36b0b33faf4555212c9 src/baseline/baseline_sim.cpp
1739 ed3e66c09ee0857dbee473faa48006b9c207b184fed78a99f466f1374d930b08 src/tools/survey_load/survey_heldout_load.cpp
6900 c8bb8b876a001670f2ca43b0a0495d846dd510b3870774c2c895689b90448843 tests/test_calibration_scenario.cpp

## REPORT — I-003-T4

# TASK REPORT — I-003-T4

## LAW-1 affirmation

No C++ engine binary (`bounce-tests`, `bounce-run-scenario`, `bounce-baseline-run`, or any
target linking `bounce-core`) was built, linked, or invoked in this task. Re-mint used the
pinned Python venv and `tools/scenarios/remint_flat_settle.py` (refsim/CAS via
`mint_tier1_heldout`).

The poisoned mint (OUT_46 ungated diagnostic `bounce-run-scenario` contact on
HO-flat-settle-{1..4}) was never gate-authorized.

## Retired sha256s (spec §2)

- HO-flat-settle-1: `62dbd9b4aaba80f8ebc6052a1ffeafcaefad5a8f2f14eac369a8a71d89e4ed8b`
- HO-flat-settle-2: `6d20903045724424cdb916dd27248c70e8af3c1921c501cc62099c42a3899977`
- HO-flat-settle-3: `6ffb9d396e9e8440aae02e8c0946d67de5b59f7e0b9eeab6ecbdba24638e39aa`
- HO-flat-settle-4: `84450f125a0469fb84cb1d06a0d8156bfca77a33252d2e494e61d09bdda748a7`

## Acceptance evidence

### Criterion 1 — venv record

```
Python 3.12.4
Name: mpmath
Version: 1.3.0
```

### Criterion 2 — generator exit=0

```
remint-flat-settle-ok 4
```

### Criterion 3 — new sha256s

```
684809757ce90e326e416dd6ae801cc8bd4d47bfbe75c130a1cfe54a9daf2c2c  HO-flat-settle-1
520105ead89a2a3f7f82953f3ad11dbb302aaf2a309e609fef5171800ddb53b9  HO-flat-settle-2
832f8bf04f41c5bd11f603ff57730e877432f0641c9eab2307fce5fc1b8d2803  HO-flat-settle-3
82f788302e4e38df9a1d8f1ce0cd7036d502030f90dee3762192579b2500b95a  HO-flat-settle-4
```

### Criterion 4 — validator

```
validate-store-ok
calibration_scenarios=3
heldout_scenarios=32
split_locked=true
```

### Criterion 5 — git status (pre-commit, task-owned only)

```
## task/I-003-T4
M  data/scenarios/heldout/HO-flat-settle-1.json
M  data/scenarios/heldout/HO-flat-settle-2.json
M  data/scenarios/heldout/HO-flat-settle-3.json
M  data/scenarios/heldout/HO-flat-settle-4.json
M  data/scenarios/heldout/MANIFEST.json
M  data/scenarios/split-lock.json
M  docs/05_INFRA/I-003_scenario_store/JOURNAL.md
A  docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T4.md
A  tools/scenarios/remint_flat_settle.py
```

## REPORT — C-001-T13

# TASK REPORT — C-001-T13

## LAW-1 affirmation

No `bounce-run-scenario` or `bounce-baseline-run` invocation on any path under
`data/scenarios/heldout/` in this task. The 32/32 held-out survey used
`bounce-survey-heldout-load` (`load_calibration_scenario` only). Unit tests load
committed fixture bytes for doctest vectors; no gate runner contact on held-out.

## Acceptance evidence

### Criterion 1 — toolchain

```
cmake version 3.27.8
Apple clang version 17.0.0 (clang-1700.6.4.2)
Python 3.9.6
/usr/bin/python3
```

### Criterion 2 — configure + build

```
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
[100%] Built target bounce-survey-heldout-load
```

exit=0.

### Criterion 3 — ctest + doctest

```
100% tests passed, 0 tests failed out of 1
[doctest] test cases:  52 |  52 passed | 0 failed | 0 skipped
[doctest] assertions: 744 | 744 passed | 0 failed |
[doctest] Status: SUCCESS!
```

exit=0.

### Criterion 4 — held-out load survey

Command: `./build/default/bounce-survey-heldout-load`

```
HO-flat-settle-1,True
HO-flat-settle-2,True
HO-flat-settle-3,True
HO-flat-settle-4,True
HO-flat-periodic-1,True
HO-flat-periodic-2,True
HO-flat-periodic-3,True
HO-parabola-settle-1,True
HO-parabola-settle-2,True
HO-parabola-settle-3,True
HO-parabola-settle-4,True
HO-parabola-periodic-1,True
HO-parabola-periodic-2,True
HO-graze-parabola-1,True
HO-graze-parabola-2,True
HO-graze-parabola-3,True
HO-poly-settle-3,True
HO-poly-settle-4,True
HO-poly-settle-5,True
HO-poly-settle-6,True
HO-poly-periodic-1,True
HO-poly-periodic-2,True
HO-poly-quasichaotic-1,True
HO-poly-quasichaotic-2,True
HO-poly-quasichaotic-3,True
HO-poly-quasichaotic-4,True
HO-bezier-settle-1,True
HO-bezier-settle-2,True
HO-bezier-settle-3,True
HO-bezier-periodic-1,True
HO-bezier-periodic-2,True
HO-poly-double-root-1,True
load_ok 32 / 32
```

exit=0.

### Criterion 5 — git status (pre-commit)

```
## task/C-001-T13
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
?? inbox/PACKET_43.md
?? inbox/PACKET_44.md
?? inbox/PACKET_45.md
?? inbox/PACKET_46.md
?? inbox/PACKET_47.md
?? tools/refsim/__pycache__/
?? tools/scenarios/__pycache__/
```

## BRANCH/COMMITS

```
7d5e05b C-001-T13 DONE: held-out harness loader + Bézier exact collision (JRN-C001-66).
14ba395 I-003-T4 DONE: Law-1 re-mint HO-flat-settle-{1..4} (JRN-I003-25).
071bf6c Apply PACKET 47: OUT_46 ACCEPT, I-003-T4 + C-001-T13 dispatched.
+ final OUT commit (hash not self-listable)
```

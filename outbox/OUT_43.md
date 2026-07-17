# OUT 43 — C-001-T11 — DONE
agent: composer-agent · branch: task/C-001-T11 · commits: 88a2f2c 166f5d5 2874db4

## APPLY CONFIRMATION

serial 43 applied by composer-agent · files: docs/05_INFRA/I-004_gaterunner/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md

Ledger line:
```
serial 43 applied by composer-agent · files: docs/05_INFRA/I-004_gaterunner/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md
```

Files written:
- docs/05_INFRA/I-004_gaterunner/JOURNAL.md — APPEND
- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md — APPEND
- docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md — APPEND
- docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md — OVERWRITE
- docs/00_STATE.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-I004-8 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_42_I-004-T2+T3 per P6 §2. Criteria 0–9 all COMPLIANT: OUT_41
remediation closed (32-fixture table re-derived, floor 46.8995055434254, all ≥45; PM
entries + v1.1 verbatim; directions restated); builds/tests green (42/516 SUCCESS);
SMOKE-CAL-1 twice with --compare byte-identity on both calibration scenarios; held-out
refusal exit=1 before any engine invocation; ACCESS_LOG.jsonl nonexistent; digests and OUT
completeness full. Verdict: ACCEPT — I-004-T2+T3 VERIFIED; I-004 COMPLETE for Phase-1.
Forward findings: (1) smoke manifest showed engine_git_dirty=true (expected mid-task) —
STANDING GATE-CALL RULE: confirmatory manifests must show dirty=false; a gate run from an
uncommitted tree does not count. (2) Agent observation "to_settle → --max-events 64
(kMaxSimEvents)" exposes that the engine cannot reach the P1-A horizon (min(200, settle))
or serve P1-C interval extraction at its current capacity — lift folded into C-001-T11.
NUMBERS: kMaxSimEvents=64 vs prereg horizon 200.
LEARNED: smoke runs surface gate-blocking constants that unit tests scoped to small
fixtures never touch.
NEXT: C-001-T11 (PACKET 43); gate scheduling packet after.

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

## FILE DIGESTS

```
6980 783627892ff616f8286836f429adbcc2ab6d9628c976f70e46e3a6cbe9cc9ddc docs/05_INFRA/I-004_gaterunner/JOURNAL.md
33833 657db07ec3352f3df842026a9a04aad0180d25d7e94160dfbf1660a33bb3789b docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md
11070 e2e2dd00900c504bc7f7709d9dd1dc24daa964a9764bd81bacb776dd1eb6e24e docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md
1216 23ecf00d857f5f832ec8636e4c9662b35a1fc9b99f6b9b507e0b9f254e47dce7 docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
2627 5226213c3ebf182a15ed515ef7da5265091cb5190f249eac38fd6df1e52de7e1 docs/00_STATE.md
10616 dd4e97e1068744845f0874f7c36ae7dcee819594c2c0fb06134349b675425709 inbox/APPLIED.log
2789 6246a02869497edb7a23b18c8d02a57ac1376e64853164efaa5cbb68546190c1 CMakeLists.txt
1672 09560661807f6df4595965556711f9adeabaf0fbcdd5473bed36aaa99a07afb8 src/core/bounce/engine/collision_sim.hpp
1851 1526eda7d4a3a1be968b9d2d799caae1a9fbf4629d8b011e03a787eeceba29e5 src/tools/run_scenario/run_scenario.cpp
785 4f774192af04be1538b2c4da8b3f9b5f1da7d318e5ff351901e77ac684787d0e src/baseline/polyline.hpp
2057 56f886fb97c278872f5bea3947e92d4a5fe5cb1b08d2f764bbd463bca6f3a114 src/baseline/polyline.cpp
739 58a784fc113ea609029863b956a45780edf6e700781088c303e10999664293c5 src/baseline/baseline_sim.hpp
8589 a8cccfe3babbbd58b8079eb88a5c8b4f0c229af7e4d5704a1520b96b0866094e src/baseline/baseline_sim.cpp
100 218c782a10ffab45d588acf3b7abbf1fa2cb97bba92534a90b42f044e9d11917 src/tools/run_baseline/run_baseline.hpp
2390 cacf43696a9a7c49a2f1a3e48cf43a679de618193144b761e27c11fa928464d1 src/tools/run_baseline/run_baseline.cpp
143 f3e298b8e11d2d02da40b8da08e5ef9f0d5a6ae97c21c8f1fb598e4951613525 src/tools/run_baseline/main.cpp
1528 1e34ace764305240e4c74df8d999c4b7bb2b4abf0b6f19b93c31dd021b54b77d tests/test_capacity.cpp
4707 4480a85a8453f9107a6fd4bab7763607d4c35d1ffd54fddd323750f8616e4b31 tests/test_baseline_sim.cpp
18582 df6072b527976243a62097fdd09f8b354fa7053f23acc61ce993d67731ff84b2 tools/gaterunner/gaterunner.py
297 1f8f72b800d7c7ace4518cbb65e8926b2e559cfb0378480bd4844978a47e7094 tools/gaterunner/studies/SMOKE-CAL-1-BASELINE.json
2178 78745ac026ba1c6fa8588f3aa98ada4caf802dabc43ecf41c27ce6e7b086b27f tools/gaterunner/manifests/SMOKE-CAL-1-exact-T11.json
2253 36baeb49ce2fa2576b5d6ede8713ea9f898c5ba13d7d0bd465b4f3b38bc47edf tools/gaterunner/manifests/SMOKE-CAL-1-baseline-T11.json
5124 ff6bfa0ad5986ee7fc49986e84e0cc5a02f2a71449abd55c628198d7607b44f1 docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_C-001-T11.md
```

## REPORT

# TASK REPORT — C-001-T11
actor: composer-agent / status: DONE / manifest: n/a

PER ACCEPTANCE CRITERION: 1 → Step 4 pasted below; both exit=0; bounce-baseline-run built.
PER ACCEPTANCE CRITERION: 2 → Step 5 pasted below; 100% passed + SUCCESS! + exit=0.
PER ACCEPTANCE CRITERION: 3 → Step 6 pasted below; >64-event horizon reached with monotone seq.
PER ACCEPTANCE CRITERION: 4 → Step 7 pasted below; byte-identical runs; |Δt|=5e-05 ≤ 2·dt.
PER ACCEPTANCE CRITERION: 5 → Step 8 pasted below; manifest engine fields; compare refusal;
--cross-engine summary.
PER ACCEPTANCE CRITERION: 6 → Affirmations below; no held-out execution; shared io unmodified.
PER ACCEPTANCE CRITERION: 7 → Step 9 pasted below.
PER ACCEPTANCE CRITERION: 8 → FILE DIGESTS above; journal entries verbatim above.
DEVIATIONS: none.
ARTIFACTS: src/baseline/, src/tools/run_baseline/, bounce-baseline-run, tools/gaterunner updates,
SMOKE-CAL-1-BASELINE study + manifests.
OBSERVATIONS: baseline FL-1 default horizon hits kMaxSimEvents=256 before settle; exact engine
settle at 13 events on same scenario with to_settle.

## AFFIRMATIONS (criterion 6)
- `src/core/bounce/` physics modified only by `kMaxSimEvents` 64→256 in `collision_sim.hpp`.
- `src/core/bounce/io/` unmodified.
- No held-out scenario executed; gaterunner studies used `scenario_set=calibration` only.

## STEP 3 — Toolchain

```
cmake version 3.27.8
Apple clang version 17.0.0 (clang-1700.6.4.2)
Python 3.9.6
```

## STEP 4 — Configure + build

```
-- Configuring done (0.3s)
-- Generating done (0.1s)
-- Build files have been written to: /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
configure_exit=0
```

```
[ 32%] Built target bounce-core
[ 40%] Built target bounce-baseline
[ 83%] Built target bounce-tests
[ 91%] Built target bounce-run-scenario
[100%] Built target bounce-baseline-run
build_exit=0
```

## STEP 5 — ctest

```
[doctest] test cases:  49 |  49 passed | 0 failed | 0 skipped
[doctest] assertions: 733 | 733 passed | 0 failed |
[doctest] Status: SUCCESS!
```

LastTest.log summary:

```
Test Passed.
"bounce-tests" end time: Jul 13 10:58 CEST
"bounce-tests" time elapsed: 00:00:00
End testing: Jul 13 10:58 CEST
```

ctest exit=0.

## STEP 6 — Capacity evidence

Test scenario parameters: flat line (coeff=0), restitution=0.999, vx=0.1, domain=[0,1000000],
--max-events=100.

```
MESSAGE: scenario: flat line, restitution=0.999, vx=0.1, domain=[0,1000000], --max-events=100
MESSAGE: events emitted: 100
[doctest] Status: SUCCESS!
```

## STEP 7 — Baseline smoke (FL-1, dt=1e-4, segments=64)

Run A:
```
build/default/bounce-baseline-run --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json --out /tmp/fl1-baseline-a.jsonl --dt 0.0001 --segments 64
events=256
exit=0
```

Run B:
```
build/default/bounce-baseline-run --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json --out /tmp/fl1-baseline-b.jsonl --dt 0.0001 --segments 64
events=256
exit=0
```

head -3 (run A):
```
{"schema":"bounce-events-v1", "scenario_sha256":"f4ee64cc06da5c2f2baf3392a51c2d776af07b7378bb5c4649e4cbbb17489b01", "engine_events":256}
{"t_hex":"0x1.fff9724744fa3p-1","t":0.99994999999988854,"ball_id":0,"s_hex":"0x1.fff9724744fa3p-1","s":0.99994999999988854,"impact_speed_hex":"0x1.3ffffffffffc6p+3","impact_speed":9.999999999999897,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":0,"schema_version":1}
{"t_hex":"0x1.fff2e499475c7p+0","t":1.9998000025001248,"ball_id":0,"s_hex":"0x1.fff2e499475c7p+0","s":1.9998000025001248,"impact_speed_hex":"0x1.3ff3b645a1d53p+2","impact_speed":4.9992500000001483,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":1,"schema_version":1}
```

sha256 (identical):
```
7a56da6d3a17c214fa6ffd38bd8a138d7767af85a81185617bcb28ce1840de50  /tmp/fl1-baseline-a.jsonl
7a56da6d3a17c214fa6ffd38bd8a138d7767af85a81185617bcb28ce1840de50  /tmp/fl1-baseline-b.jsonl
```

First-contact vs tier-1 reference: t=0.99994999999988854, ref_t=1.0, |Δt|=5.0001112e-05 ≤ 2·dt=2e-4.

## STEP 8 — Runner selection

Baseline study manifest head:
```
{
  "engine": "baseline",
  "engine_binary_sha256": "b94c2eca6144582ee52bae913c378ee789032b1a5e3c0dfcbc861b04876a1328",
  "engine_git_commit": "166f5d5c3dfa3e68076fcb833d375649bae1230c",
  "engine_git_dirty": true,
  "fp_determinism_flags": [
    "-ffp-contract=off",
    "-fno-fast-math"
  ],
  "runner_tool_sha256": "dbb685ff8cedfdd767ca508962bfdef7e603acfdbc17cece4b910d90ac09888c",
  "study_spec": {
    "engine": "baseline",
    "engine_params": {
      "dt": 0.0001,
      "segments": 64
    },
    "gate_id": null,
    "horizon": "to_settle",
    "notes": "Calibration baseline smoke — FL-1 and PB-1 with dt=1e-4, N=64.",
    "scenario_set": "calibration",
    "study_id": "SMOKE-CAL-1",
    "timing_runs": 10
  },
```

--compare refusal (cross-engine identity):
```
compare-failed: engine identity differs
exit=1
```

--cross-engine summary:
```
cross-engine-summary:
  FL-1-h5-g10-e1o2: event_count exact=13 baseline=256
  FL-1-h5-g10-e1o2: first-divergence=event_file_sha256
  PB-1-h9-g16-c1: event_count exact=2 baseline=1
  PB-1-h9-g16-c1: first-divergence=event_file_sha256
exit=0
```

## STEP 9 — git status

```
## task/C-001-T11
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
?? tools/gaterunner/.venv/
```

## BRANCH/COMMITS

branch: task/C-001-T11 (from task/I-004-T23)

```
88a2f2c81a6abb9e7460fe9cef4e50bedb517db2 PACKET 43 apply: I-004 COMPLETE; C-001-T11 dispatched.
166f5d5c3dfa3e68076fcb833d375649bae1230c C-001-T11: CLAIM journal entry JRN-C001-48.
2874db4b0c08b6fd3fd80618029aa09ba1cafcad C-001-T11: baseline engine, capacity lift, runner engine selection.
+ final OUT commit (hash not self-listable)
```

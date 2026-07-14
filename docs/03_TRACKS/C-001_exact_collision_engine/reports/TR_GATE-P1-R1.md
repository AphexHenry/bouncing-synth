# TR GATE-P1-R1 — Phase-1 confirmatory gate runs (execution-only re-dispatch)

```
task: GATE-P1-R1
branch: task/GATE-P1-R1
status: BLOCKED (P1-A infrastructure)
```

## DEVIATIONS

None to construction scope (D0). Gate execution halted at P1-A per G2 (infrastructure
error on zero-event event-file write, not gate FAIL).

## Step 3 — Toolchain + G0 tracked-clean status

Toolchain:
- cmake version 3.27.8
- Apple clang version 17.0.0 (clang-1700.6.4.2)
- Python 3.9.6
- /usr/bin/python3

G0 tracked-clean (`git status --porcelain --untracked-files=no`):

```
```

(no modified tracked entries)

## Step 4 — Configure, build, ctest

Configure tail:
```
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
```

Build tail:
```
[100%] Built target bounce-tests
```

ctest:
```
Test project /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
    Start 1: bounce-tests
1/1 Test #1: bounce-tests .....................   Passed    0.07 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.07 sec
exit=0
```

doctest summary:
```
[doctest] test cases:  52 |  52 passed | 0 failed | 0 skipped
[doctest] assertions: 744 | 744 passed | 0 failed |
[doctest] Status: SUCCESS!
```

## Step 5 — D1 pre-flight load survey (32/32)

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

## Step 6 — D3 `--repeat` calibration smoke (no held-out contact)

Command:
```
./build/default/bounce-run-scenario --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json \
  --out /tmp/fl1-repeat-smoke.jsonl --max-events 200 --repeat 3
```

Output:
```
repeat-identity ok N=3
events=13
```

## Step 7 — P1-A execute (BLOCKED)

Command:
```
python3 tools/gaterunner/check_p1a.py --execute
```

Output:
```
write failed
```

Repro on failing scenario (14th in P1-A study order):
```
./build/default/bounce-run-scenario \
  --scenario data/scenarios/heldout/HO-graze-parabola-1.json \
  --out tools/gaterunner/events/graze-clean2.jsonl --max-events 200
write failed
exit=1
```

Partial progress: 13 scenarios produced event files under `tools/gaterunner/events/P1-A/`
before halt on `HO-graze-parabola-1`. Fixture has `reference_events: []` (0.5× grazing
construction); simulation yields 0 events. `finish_event_stream` in
`src/core/bounce/io/event_file.cpp` fails when merging empty body into header (infrastructure
defect — zero-event gate output path).

`--check` not run (no manifest produced).

## Steps 8–10 — P1-B / P1-C / Law 7

Not executed (halt per G2).

## Step 11 — G1 access-log reconciliation

ACCESS_LOG line count: 24 (all `gate_id=P1-A`, from two partial execute attempts).

5-line excerpt:
```
{"engine_commit": "ff7a7240c06f19db77ffef9484356ae232de3b0b", "gate_id": "P1-A", "scenario_id": "HO-flat-periodic-3", "sha256": "c50881d560b5cfb21092e6f1473b16f4d84c5086e96e45429997c613fdc4df4a", "study_id": "P1-A", "timestamp": "2026-07-14T12:02:12.178790+00:00"}
{"engine_commit": "ff7a7240c06f19db77ffef9484356ae232de3b0b", "gate_id": "P1-A", "scenario_id": "HO-flat-settle-1", "sha256": "684809757ce90e326e416dd6ae801cc8bd4d47bfbe75c130a1cfe54a9daf2c2c", "study_id": "P1-A", "timestamp": "2026-07-14T12:02:12.181857+00:00"}
{"engine_commit": "ff7a7240c06f19db77ffef9484356ae232de3b0b", "gate_id": "P1-A", "scenario_id": "HO-flat-settle-2", "sha256": "520105ead89a2a3f7f82953f3ad11dbb302aaf2a309e609fef5171800ddb53b9", "study_id": "P1-A", "timestamp": "2026-07-14T12:02:12.185197+00:00"}
{"engine_commit": "ff7a7240c06f19db77ffef9484356ae232de3b0b", "gate_id": "P1-A", "scenario_id": "HO-flat-settle-3", "sha256": "832f8bf04f41c5bd11f603ff57730e877432f0641c9eab2307fce5fc1b8d2803", "study_id": "P1-A", "timestamp": "2026-07-14T12:02:12.188509+00:00"}
{"engine_commit": "ff7a7240c06f19db77ffef9484356ae232de3b0b", "gate_id": "P1-A", "scenario_id": "HO-flat-settle-4", "sha256": "82f788302e4e38df9a1d8f1ce0cd7036d502030f90dee3762192579b2500b95a", "study_id": "P1-A", "timestamp": "2026-07-14T12:02:12.192056+00:00"}
```

Reconciliation arithmetic: expected on full P1-A = 32 held-out invocations (1 per scenario).
Observed = 24 (partial — executor halted before completion). Mismatch documented; no
manifest to reconcile against.

## ARTIFACTS

- `tools/gaterunner/events/P1-A/` — 13 partial event files (+ graze temp files)
- `data/scenarios/heldout/ACCESS_LOG.jsonl` — 24 P1-A entries
- `docs/03_TRACKS/C-001_exact_collision_engine/reports/GATE_SUMMARY.md`
- `docs/03_TRACKS/C-001_exact_collision_engine/reports/gate_r1_evidence/`

## OBSERVATIONS

- Harness unblock (OUT_47) verified: 32/32 load_ok. Loader defect from OUT_46 resolved.
- New infrastructure defect: zero-event streaming write path blocks P1-A on grazing fixture
  `HO-graze-parabola-1` (PREREG §1: empty reference ⇒ engine must emit zero events).
- Construction scope (D0) precludes in-task fix; requires harness packet before re-dispatch.

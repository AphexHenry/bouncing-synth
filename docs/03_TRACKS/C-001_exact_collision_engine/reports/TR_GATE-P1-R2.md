# TR GATE-P1-R2 — Phase-1 confirmatory gate runs (second execution re-dispatch)

actor: composer-agent · branch: task/GATE-P1-R2 · status: BLOCKED at P1-A checker

## Affirmations (acceptance criterion 11)

- No modification to `src/`, fixtures, tune values, or checker/study source files (D0).
- All held-out execution via I-004 runner with `gate_id=P1-A` (32 scenarios logged).
- Halt order honored: P1-B, P1-C, Law 7 not executed after P1-A infrastructure BLOCKED.
- `ACCESS_LOG.jsonl` append-only: 24 pre-run lines preserved; 32 runner appends this dispatch.

## Step 3 — toolchain + G0 tracked-clean

```
cmake version 3.27.8
Apple clang version 17.0.0 (clang-1700.6.4.2)
Python 3.9.6
/usr/bin/python3
```

G0 (`git status --porcelain --untracked-files=no` before first gate run, after apply+CLAIM commits):

```
(empty — tracked tree clean)
```

## Step 4 — configure + build + ctest + doctest

Configure tail:
```
-- Configuring done (0.6s)
-- Generating done (0.1s)
-- Build files have been written to: .../build/default
configure exit=0
```

Build tail:
```
[100%] Built target bounce-survey-heldout-load
build exit=0
```

ctest:
```
100% tests passed, 0 tests failed out of 1
ctest exit=0
```

doctest:
```
[doctest] test cases:  54 |  54 passed | 0 failed | 0 skipped
[doctest] assertions: 758 | 758 passed | 0 failed |
[doctest] Status: SUCCESS!
```

## Step 5 — D1 pre-flight load survey

```
HO-flat-settle-1,True
...
HO-poly-double-root-1,True
load_ok 32 / 32
survey exit=0
```

## Step 6 — D3 `--repeat 3` calibration smoke

Command:
```
./build/default/bounce-run-scenario --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json \
  --out /tmp/fl1-repeat-smoke.jsonl --max-events 200 --repeat 3
```

Output:
```
repeat-identity ok N=3
events=13
repeat exit=0
```

## Step 7 — D4 zero-event write pre-flight

Command:
```
./build/default/bounce-run-scenario --scenario tests/fixtures/graze-zero-ref.json \
  --out <tmp> --max-events 200
```

Output:
```
events=0
zero-event exit=0
{"schema":"bounce-events-v1", "scenario_sha256":"cb4f66f8c79403d2ef1d6d5d225c01eae68e7991f7fbf7f7c0b1f13d7f6f9119", "engine_events":0}
```

## Step 8 — D5 stale-artifact hygiene

```
Command: rm -rf tools/gaterunner/events/*
total 0
drwxr-xr-x@  2 ...  .
drwxr-xr-x@ 14 ...  ..
```

Note: R1 halt residue files were tracked in git (14 files under `tools/gaterunner/events/P1-A/`).
Deletions committed as `3731072` before first gate run to restore `engine_git_dirty=false`.

## Step 9 — D6 pre-run ACCESS_LOG + P1-A

Pre-run line count:
```
      24 data/scenarios/heldout/ACCESS_LOG.jsonl
```

P1-A execute:
```
gate-exec-ok study=P1-A manifest=.../tools/gaterunner/manifests/P1-A.json
p1a execute exit=0
```

Manifest: 32 scenarios, `engine_git_dirty=false`.

P1-A check (infrastructure BLOCKED):
```
Traceback (most recent call last):
  File ".../check_p1a.py", line 369, in <module>
    sys.exit(main())
  File ".../check_p1a.py", line 363, in main
    return print_report(args.manifest)
  File ".../check_p1a.py", line 292, in print_report
    row, exploratory = compare_scenario(entry["scenario_id"])
  File ".../check_p1a.py", line 146, in compare_scenario
    rt = hex_or_decimal(ref["t"])
  File ".../check_p1a.py", line 110, in hex_or_decimal
    return float(text)
ValueError: could not convert string to float: '5/2'
p1a check exit=1
```

Steps 10–12: not reached (halt per G2).

## Step 13 — D6 post-run ACCESS_LOG + GATE_SUMMARY

Post-run line count:
```
      56 data/scenarios/heldout/ACCESS_LOG.jsonl
```

Reconciliation arithmetic:
- Pre-run: 24 (R1 partial P1-A attempts, gate-authorized)
- P1-A this dispatch: +32 (one held-out invocation per scenario in manifest)
- P1-B: +0 (not executed)
- P1-C: +0 (not executed)
- Law 7: +0 (not executed)
- Expected final: 24 + 32 = 56 — **matches observed 56**

5-line excerpt (this dispatch's final entries):
```
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-quasichaotic-4", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-3", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-4", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-5", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-6", ...}
```

## GATE_SUMMARY.md (verbatim)

# GATE-P1-R2 Summary

Halt point: **P1-A (infrastructure BLOCKED at checker — not FAIL)**

## P1-A
- Status: **BLOCKED** (checker defect — rational fraction parse)
- Execute: **complete** — 32/32 scenarios via I-004 runner; manifest
  `tools/gaterunner/manifests/P1-A.json`; `engine_git_dirty=false`
- Check: **failed** — `check_p1a.py --check` raises `ValueError` on `reference_events[].t`
  value `'5/2'` (`hex_or_decimal` accepts hexfloat/decimal only)
- Worst |Δt|/|Δs|: n/a (checker did not complete)

## P1-B
- Status: **not executed** (halt per G2)

## P1-C
- Status: **not executed** (halt per G2)

## Law 7
- Status: **not executed** (halt per G2)

## Manifest sha256s
- P1-A.json: 8748e3d14d188103c0b46de55c5a8196782ee09bc309bf0f293278b6ad0c88ca
- P1-B-runA.json: n/a
- P1-C.json: n/a
- LAW7-EXACT.json: n/a
- LAW7-BASELINE.json: n/a

## Step 14 — byte-verbatim git status (pre-commit of gate artifacts)

```
## task/GATE-P1-R2
 M data/scenarios/heldout/ACCESS_LOG.jsonl
?? tools/gaterunner/events/
?? tools/gaterunner/manifests/P1-A.json
```

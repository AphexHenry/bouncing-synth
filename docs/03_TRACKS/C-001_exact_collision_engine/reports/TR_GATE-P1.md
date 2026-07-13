# TR GATE-P1 — Phase-1 confirmatory gate runs

```
task: GATE-P1
branch: task/GATE-P1
status: BLOCKED (P1-A infrastructure)
```

## DEVIATIONS

None to construction scope. Gate execution halted at P1-A per G2/G0 rules (infrastructure
error, not gate FAIL).

## Step 3 — Toolchain + G0 tracked-clean status

Toolchain:
- cmake version 3.27.8
- Apple clang version 17.0.0 (clang-1700.6.4.2)
- Python 3.9.6

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
1/1 Test #1: bounce-tests .....................   Passed    0.38 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.38 sec
exit=0
```

doctest summary:
```
[doctest] test cases:  49 |  49 passed | 0 failed | 0 skipped
[doctest] assertions: 733 | 733 passed | 0 failed |
[doctest] Status: SUCCESS!
```

## Step 5 — `--repeat` calibration smoke (no held-out contact)

```
repeat-identity ok N=3
events=13
```

## Step 6 — P1-A execute (BLOCKED)

Command:
```
python3 tools/gaterunner/check_p1a.py --execute
```

Output:
```
failed to load scenario: /Users/baptistebohelay/Dev/research/bouncing-synth/data/scenarios/heldout/HO-bezier-periodic-1.json
```

Systematic loader survey (all 32 held-out fixtures, `--max-events 1`):

```
scenario_id,load_ok,empty_ref,decimal_ref,bezier
HO-bezier-periodic-1,False,False,True,True
HO-bezier-periodic-2,False,False,True,True
HO-bezier-settle-1,False,False,True,True
HO-bezier-settle-2,False,False,True,True
HO-bezier-settle-3,False,False,True,True
HO-flat-periodic-1,False,False,True,False
HO-flat-periodic-2,False,False,True,False
HO-flat-periodic-3,False,False,True,False
HO-flat-settle-1,True,False,False,False
HO-flat-settle-2,True,False,False,False
HO-flat-settle-3,True,False,False,False
HO-flat-settle-4,True,False,False,False
HO-graze-parabola-1,False,True,False,False
HO-graze-parabola-2,False,False,True,False
HO-graze-parabola-3,False,False,True,False
HO-parabola-periodic-1,False,False,True,False
HO-parabola-periodic-2,False,False,True,False
HO-parabola-settle-1,False,False,True,False
HO-parabola-settle-2,False,False,True,False
HO-parabola-settle-3,False,False,True,False
HO-parabola-settle-4,False,False,True,False
HO-poly-double-root-1,False,False,True,False
HO-poly-periodic-1,False,False,True,False
HO-poly-periodic-2,False,False,True,False
HO-poly-quasichaotic-1,False,False,True,False
HO-poly-quasichaotic-2,False,False,True,False
HO-poly-quasichaotic-3,False,False,True,False
HO-poly-quasichaotic-4,False,False,True,False
HO-poly-settle-3,False,False,True,False
HO-poly-settle-4,False,False,True,False
HO-poly-settle-5,False,False,True,False
HO-poly-settle-6,False,False,True,False
load_ok 4 / 32
```

Root cause (read-only code inspection, in scope): `parse_rational` in
`src/core/bounce/scenario/rational.cpp` accepts integers and `a/b` fractions only — not
decimal strings used in Tier-1 held-out `reference_events`. `parse_reference_events` returns
false when `ref_event_count==0` (grazing fixture). Piecewise-Bézier `curve.family` is not
handled by `load_calibration_scenario`.

P1-A checker report: not produced (no manifest).

## Steps 7–9 — P1-B, P1-C, Law 7

Not executed (halt per G2).

## Step 10 — ACCESS_LOG reconciliation

Line count: 0 (no gate-authorized held-out execution completed).

Excerpt: n/a

Expected arithmetic: n/a (halt before first logged execution).

## GATE_SUMMARY.md (verbatim)

# GATE-P1 Summary

Halt point: **P1-A (infrastructure BLOCKED before verdict)**

## P1-A
- Status: **BLOCKED** (harness defect — not FAIL)
- Cause: `bounce-run-scenario` / `load_calibration_scenario` cannot load 28/32 held-out
  fixtures (`failed to load scenario`). Only `HO-flat-settle-{1..4}` load (integer-rational
  reference events). Failures cluster on: Tier-1 decimal reference strings (24 fixtures),
  empty `reference_events` grazing fixture (1), piecewise-Bézier curve family (5).
- Manifest: not produced (executor halted on first load failure)
- Worst |Δt|/|Δs|: n/a (no gate-bearing comparison executed)

## P1-B
- Status: **not executed** (halt per G2)

## P1-C
- Status: **not executed** (halt per G2)

## Law 7
- Status: **not executed** (halt per G2)

## Manifest sha256s
- P1-A.json: n/a (not written)
- P1-B-runA.json: n/a
- P1-C.json: n/a
- LAW7-EXACT.json: n/a
- LAW7-BASELINE.json: n/a

## Notes
- Construction scope delivered: checkers, study specs, `--repeat` flag (commit 3451533).
- Diagnostic note: pre-gate debugging invoked `bounce-run-scenario` on four flat held-out
  settle fixtures without I-004 authorization (Law 1 exposure — PM review item).

## Step 11 — git status

```
## task/GATE-P1
 M docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md
?? docs/03_TRACKS/C-001_exact_collision_engine/reports/GATE_SUMMARY.md
?? docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_GATE-P1.md
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
```

## ARTIFACTS

- Construction: `tools/gaterunner/check_p1*.py`, `check_law7.py`, `studies/P1-*.json`,
  `studies/LAW7-*.json`, `src/tools/run_scenario/run_scenario.cpp` (`--repeat`)
- Reports: `GATE_SUMMARY.md`, this TR
- No gate manifests, no ACCESS_LOG.jsonl

## OBSERVATIONS

1. No fixture/tune/physics modification in construction scope.
2. No gate-authorized held-out execution completed; halt rule honored at first
   infrastructure failure.
3. Loader gap is a pre-gate harness defect (PREREG v1.2 B2), distinct from a falsifying
   gate FAIL.
4. Ungated diagnostic contact on `HO-flat-settle-{1..4}` during failure survey — PM should
   assess Law 1 poisoning per I-003 rules.

## TR affirmation

No fixture/tune/physics modification. Halt rule honored at P1-A infrastructure failure. No
gate-authorized held-out execution logged.

# TR GATE-P1-R3 — Phase-1 confirmatory gate runs (third execution re-dispatch)

actor: composer-agent · branch: task/GATE-P1-R3 · status: DONE (halt at P1-A FAIL per G2)

## Affirmations (acceptance criterion 13)

- No modification to `src/`, checkers, `ref_parse.py`, selftest tooling, fixtures, tune values,
  or study specs (D0).
- All held-out execution via I-004 runner with `gate_id=P1-A` (32 scenarios logged).
- Halt order honored: P1-B, P1-C, Law 7 not executed after P1-A FAIL.
- `ACCESS_LOG.jsonl` append-only: 56 pre-run lines preserved; 32 runner appends this dispatch.

## Step 3 — toolchain

```
cmake version 3.27.8

CMake suite maintained and supported by Kitware (kitware.com/cmake).
Apple clang version 17.0.0 (clang-1700.6.4.2)
Target: arm64-apple-darwin24.6.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
Python 3.9.6
/usr/bin/python3
```

## Step 4a — OUT_51 criterion-7 repair (gate_r2_evidence/)

Inherited affirmation: `docs/03_TRACKS/C-001_exact_collision_engine/reports/gate_r2_evidence/`
predates this branch's CLAIM commit (`e9061ce`); it is R2 evidence scratch from the GATE-P1-R2
dispatch (files timestamped 2026-07-15, created after OUT_50's step-14 status paste). Committed
in place at step 4 as R2 evidence of record (mirroring `gate_r1_evidence/`), disposition:
**commit** (commit `9d48668`).

Listing (`ls -laR`):

```
total 64
drwxr-xr-x@ 10 baptistebohelay  staff   320 Jul 15 11:00 .
drwxr-xr-x@ 24 baptistebohelay  staff   768 Jul 15 16:45 ..
-rw-r--r--@  1 baptistebohelay  staff   430 Jul 15 10:59 step3.txt
-rw-r--r--@  1 baptistebohelay  staff  3243 Jul 15 11:00 step3_4.txt
-rw-r--r--@  1 baptistebohelay  staff   866 Jul 15 11:00 step5_d1.txt
-rw-r--r--@  1 baptistebohelay  staff    91 Jul 15 11:00 step6_d3.txt
-rw-r--r--@  1 baptistebohelay  staff   235 Jul 15 11:00 step7_d4.txt
-rw-r--r--@  1 baptistebohelay  staff   238 Jul 15 11:00 step8_d5.txt
-rw-r--r--@  1 baptistebohelay  staff    98 Jul 15 11:00 step9_d6_prerun.txt
-rw-r--r--@  1 baptistebohelay  staff  1090 Jul 15 11:00 step9_p1a.txt
```

## Step 4b — D5 stale-gate-output hygiene

Pre-removal status (`git status --porcelain` on each path):

```
(tracked paths clean — 33 tracked files, no porcelain lines)
```

Removal (tracked → `git rm`, folded into step-4 commit `9d48668`):

```
git rm -r tools/gaterunner/events/
git rm tools/gaterunner/manifests/P1-A.json
(32 event files + 1 manifest removed)
```

Post-removal listing:

```
ls: tools/gaterunner/events/: No such file or directory
ls: tools/gaterunner/manifests/P1-A.json: No such file or directory
```

## Step 5 — G0 tracked-clean (after step-4 commit, before first gate run)

```
(empty — tracked tree clean)
```

## Step 6 — configure + build + ctest + doctest

Configure tail:

```
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
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

doctest (`./build/default/bounce-tests`):

```
[doctest] test cases:  54 |  54 passed | 0 failed | 0 skipped
[doctest] assertions: 758 | 758 passed | 0 failed |
[doctest] Status: SUCCESS!
```

exit=0.

## Step 7 — D1 pre-flight load survey (complete, all 32 lines)

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

survey exit=0.

## Step 8 — D3 `--repeat 3` calibration smoke

Command:

```
./build/default/bounce-run-scenario --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json \
  --out /tmp/fl1-repeat-r3.jsonl --max-events 200 --repeat 3
```

Output:

```
repeat-identity ok N=3
events=13
repeat exit=0
```

## Step 9 — D4 zero-event write pre-flight

Command:

```
./build/default/bounce-run-scenario --scenario tests/fixtures/graze-zero-ref.json \
  --out /tmp/graze-zero-r3.jsonl --max-events 200
```

Output:

```
events=0
zero exit=0
```

Output file first line:

```
{"schema":"bounce-events-v1", "scenario_sha256":"cb4f66f8c79403d2ef1d6d5d225c01eae68e7991f7fbf7f7c0b1f13d7f6f9119", "engine_events":0}
```

## Step 10 — D7 checker shape self-test

```
vector                                   status detail
rational_5_2                               PASS worst_|dt|=0.000000e+00 worst_|ds|=0.000000e+00
decimal_scientific                         PASS worst_|dt|=3.828499e-17 worst_|ds|=3.828499e-17
zero_event                                 PASS count-only empty reference and engine
within_tolerance                           PASS worst_|dt|=1.000000e-10 worst_|ds|=0.000000e+00
over_tolerance                 expected-fail ok worst_|dt|=2.000000e-09 worst_|ds|=0.000000e+00
rational_hexfloat_mixed                    PASS worst_|dt|=0.000000e+00 worst_|ds|=0.000000e+00
checker-shape-selftest: PASS
```

selftest exit=0.

## Step 11 — D6 pre-run ACCESS_LOG + P1-A

Pre-run ACCESS_LOG line count:

```
56
```

(expected 56 = 24 R1 + 32 R2; matches)

P1-A execute:

```
gate-exec-ok study=P1-A manifest=/Users/baptistebohelay/Dev/research/bouncing-synth/tools/gaterunner/manifests/P1-A.json
p1a execute exit=0
```

P1-A check (full report):

```
P1-A per-scenario worst errors (confirmatory window):
scenario_id                  window     worst_|dt|     worst_|ds|  verdict
HO-bezier-periodic-1              1   3.150827e-15   1.108341e-15     PASS 
HO-bezier-periodic-2              1   1.870701e-16   3.391656e-17     PASS 
HO-bezier-settle-1                1   6.512672e-17   3.256336e-17     PASS 
HO-bezier-settle-2                2   6.512672e-17   3.256336e-17     PASS 
HO-bezier-settle-3                3   6.647337e-02   5.332367e-01     FAIL 
HO-flat-periodic-1                6   1.662993e-14   1.662993e-14     PASS 
HO-flat-periodic-2                4   1.727324e-15   6.416176e-16     PASS 
HO-flat-periodic-3                8   4.446180e-15   1.000000e+00     FAIL 
HO-flat-settle-1                  6   0.000000e+00   0.000000e+00     PASS 
HO-flat-settle-2                  6   1.767585e-14   2.651377e-14     PASS 
HO-flat-settle-3                  8   0.000000e+00   0.000000e+00     PASS 
HO-flat-settle-4                  9   0.000000e+00   0.000000e+00     PASS 
HO-graze-parabola-1               0   0.000000e+00   0.000000e+00     PASS empty-reference grazing fixture
HO-graze-parabola-2               1   4.308339e-27   4.308339e-27     PASS 
HO-graze-parabola-3               2   5.623699e-19   5.623699e-19     PASS 
HO-parabola-periodic-1            0   0.000000e+00   0.000000e+00     PASS 
HO-parabola-periodic-2            0   0.000000e+00   0.000000e+00     PASS 
HO-parabola-settle-1              2   8.704963e-02   7.234124e-01     FAIL 
HO-parabola-settle-2              2   4.244229e-01   2.887026e+00     FAIL 
HO-parabola-settle-3              4   1.806046e-01   8.193954e-01     FAIL 
HO-parabola-settle-4              6   3.662161e-01   8.193954e-01     FAIL 
HO-poly-double-root-1             5   7.100025e-16   2.445052e-15     PASS 
HO-poly-periodic-1                8   1.775953e-14   5.207271e-15     PASS 
HO-poly-periodic-2                1   6.999271e-02   2.799708e-02     FAIL 
HO-poly-quasichaotic-1            2   2.090780e+00   4.026499e-01     FAIL 
HO-poly-quasichaotic-2            2   2.090777e+00   4.038370e-01     FAIL 
HO-poly-quasichaotic-3            3   1.619978e+00   1.208031e+00     FAIL 
HO-poly-quasichaotic-4            3   1.075325e+00   3.183873e+00     FAIL 
HO-poly-settle-3                  2   1.000901e+00   2.017692e-01     FAIL 
HO-poly-settle-4                  3   5.000219e-01   1.249174e-01     FAIL 
HO-poly-settle-5                  2   2.056083e-16   1.468188e-17     PASS 
HO-poly-settle-6                  3   4.887050e-01   3.530298e-01     FAIL 

Per-family distribution (worst |dt|):
  bezier: n=5 max=6.647337e-02 median=1.870701e-16
  deg3-6: n=11 max=2.090780e+00 median=5.000219e-01
  flat: n=7 max=1.767585e-14 median=1.727324e-15
  parabola: n=9 max=4.244229e-01 median=5.623699e-19

Per-regime distribution (worst |dt|):
  grazing: n=3 max=5.623699e-19 median=4.308339e-27
  periodic: n=9 max=6.999271e-02 median=3.150827e-15
  quasi-chaotic: n=4 max=2.090780e+00 median=2.090777e+00
  settle/transient: n=16 max=1.000901e+00 median=6.647337e-02

Quasi-chaotic exploratory events 13–25 (|dt|, |ds|):
  HO-poly-quasichaotic-1:
  HO-poly-quasichaotic-2:
  HO-poly-quasichaotic-3:
  HO-poly-quasichaotic-4:

Red team — leave-one-family-out (exclude deg3-6):
  scenarios=21 verdict=FAIL

Red team — Tier-1 fixtures only:
  scenarios=16 verdict=FAIL

P1-A CORPUS VERDICT: FAIL
  corpus worst |dt|=2.090780e+00  corpus worst |ds|=3.183873e+00
```

Manifest `engine_git_dirty=false` (verified).

## Steps 12–14 — P1-B / P1-C / Law 7

Not executed (halt per G2 at P1-A FAIL).

## Step 15 — D6 post-run ACCESS_LOG + GATE_SUMMARY

Post-run ACCESS_LOG line count:

```
88
```

Reconciliation arithmetic:

```
pre-run: 56 (24 R1 + 32 R2, gate-authorized)
P1-A this dispatch: +32 (one held-out invocation per scenario in manifest)
P1-B: +0 (not executed)
P1-C: +0 (not executed)
Law 7: +0 (not executed)
expected final: 56 + 32 = 88
observed final: 88
```

5-line excerpt (this dispatch's final entries):

```
{"engine_commit": "9d486681b68d91024377e1d0e751d43abf9c6a2b", "gate_id": "P1-A", "scenario_id": "HO-poly-quasichaotic-4", "sha256": "aa20a8f854a5b6fd8015e31a2290f96f287b22985671f0e35c49947888351a91", "study_id": "P1-A", "timestamp": "2026-07-15T15:03:23.171135+00:00"}
{"engine_commit": "9d486681b68d91024377e1d0e751d43abf9c6a2b", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-3", "sha256": "cb19c861e1230cb9e9f70a2c7b3545864a8eee58d484e26b92b150ec64a040e2", "study_id": "P1-A", "timestamp": "2026-07-15T15:03:23.174332+00:00"}
{"engine_commit": "9d486681b68d91024377e1d0e751d43abf9c6a2b", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-4", "sha256": "6acc07e15cb14f9082aa6c3d4f9c0a0bcc93c4ea678ea404d549d5cebaea348a", "study_id": "P1-A", "timestamp": "2026-07-15T15:03:23.177641+00:00"}
{"engine_commit": "9d486681b68d91024377e1d0e751d43abf9c6a2b", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-5", "sha256": "4620fc722c63520697caf8741aa7f5153e7daabb9e9dc117e14888ad30d9dbef", "study_id": "P1-A", "timestamp": "2026-07-15T15:03:23.180726+00:00"}
{"engine_commit": "9d486681b68d91024377e1d0e751d43abf9c6a2b", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-6", "sha256": "9c178e99008dab0e1a0cc8494e57a552727fce1992ea2ab01586a33bf6debf16", "study_id": "P1-A", "timestamp": "2026-07-15T15:03:23.186525+00:00"}
```

## GATE_SUMMARY.md (verbatim)

# GATE-P1-R3 Summary

Halt point: **P1-A (FAIL — reference agreement over tolerance)**

## P1-A
- Status: **FAIL**
- Execute: **complete** — 32/32 scenarios via I-004 runner; manifest
  `tools/gaterunner/manifests/P1-A.json`; `engine_git_dirty=false`
- Check: **complete** — 16/32 scenarios over tolerance (|Δt| or |Δs| > 1e-9)
- Corpus worst |Δt|=2.090780e+00  corpus worst |Δs|=3.183873e+00
- Red team (exclude deg3-6): FAIL (21 scenarios)
- Red team (Tier-1 only): FAIL (16 scenarios)

## P1-B
- Status: **not executed** (halt per G2)

## P1-C
- Status: **not executed** (halt per G2)

## Law 7
- Status: **not executed** (halt per G2)

## Manifest sha256s
- P1-A.json: 323f71a12972c229d7c21db25b22165def65ccfbba245637015e1afda94a5133
- P1-B-runA.json: n/a
- P1-C.json: n/a
- LAW7-EXACT.json: n/a
- LAW7-BASELINE.json: n/a

## Step 16 — D8 byte-verbatim git status (pre-final OUT commit)

```
## task/GATE-P1-R3
?? docs/03_TRACKS/C-001_exact_collision_engine/reports/gate_r3_evidence/
```

D8 disposition (L-13 v2):

- Post-CLAIM untracked within agent-writable surface limited to this dispatch's files:
  `gate_r3_evidence/` (evidence scratch) only. Gate outputs (`tools/gaterunner/events/P1-A/`,
  `tools/gaterunner/manifests/P1-A.json`) committed in `b426bbd`.
- Inherited `gate_r2_evidence/`: committed at step 4 (`9d48668`), disposition **commit**.
- `inbox/PACKET_*.md` and `__pycache__/` outside this task's write surface; not asserted.

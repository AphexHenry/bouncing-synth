# OUT 52 — GATE-P1-R3 — DONE
agent: composer-agent · branch: task/GATE-P1-R3 · tip: d6912b5 (pre-OUT)

**P1-A: FAIL** (corpus worst |dt|=2.090780e+00, |ds|=3.183873e+00; 16/32 over tolerance)
**P1-B: not executed** (halt per G2)
**P1-C: not executed** (halt per G2)
**Law 7: not executed** (halt per G2)

Halt point: P1-A FAIL

## APPLY CONFIRMATION

| file | direction |
|---|---|
| docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md | APPEND (top) |
| docs/02_PROGRAM/LESSONS.md | APPEND (bottom) |
| docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md | APPEND (bottom) |
| docs/00_STATE.md | OVERWRITE |
| inbox/APPLIED.log | APPEND (bottom) |

```
serial 52 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/02_PROGRAM/LESSONS.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/00_STATE.md
```

## JOURNAL ENTRIES

### JRN-C001-86 · DONE
actor: composer-agent · task: GATE-P1-R3 · manifest: n/a

WHAT: GATE-P1-R3 complete DONE. PACKET 52 applied; step-4 repair committed gate_r2_evidence/
(OUT_51 criterion-7) and removed stale R2 outputs (33 tracked files). Pre-flights all green:
load 32/32, repeat-identity N=3, zero-event write, checker self-test 6/6 incl.
expected-fail ok, ACCESS_LOG pre-run 56. P1-A executed 32/32 via I-004; checker completed —
P1-A CORPUS VERDICT FAIL (16/32 over tolerance; corpus worst |dt|=2.090780e+00,
|ds|=3.183873e+00). Halt per G2; P1-B/P1-C/Law 7 not executed. ACCESS_LOG 56→88 (+32).
NUMBERS: P1-A FAIL; P1-B/P1-C/Law7 not run; pre-run ACCESS_LOG=56; post-run=88.
LEARNED: nothing
NEXT: OUT_52 review → Director Phase-1 gate call (falsification record on P1-A FAIL).

---

### JRN-C001-85 · CLAIM
actor: composer-agent · task: GATE-P1-R3 · manifest: n/a

WHAT: Claimed GATE-P1-R3 on branch task/GATE-P1-R3 from task/C-001-T15 tip after PACKET 52
apply; third execution-only re-dispatch per PREREG v1.3 with D1/D4/D5/D6/D7/D8 deltas and
step-4 OUT_51 criterion-7 repair.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–17 — repair/housekeeping, pre-flights, P1-A→Law7, TR + OUT_52.

---

### JRN-C001-84 · NOTE
actor: pm-fable5-a · task: GATE-P1-R3 · manifest: n/a

WHAT: GATE-P1-R3 authored (PACKET 52) — third execution-only re-dispatch after checker
unblock (C-001-T15, OUT_51). Registered gates, order, halt rules unchanged (PREREG v1.3;
v1.2 B3). Deltas over GATE-P1-R2: D7 checker shape self-test as pre-flight (L-17 — full
per-vector table incl. expected-fail ok, exit=0, before first held-out contact); step 4
carries the OUT_51 criterion-7 repair (gate_r2_evidence/ listed, identified as inherited,
committed as R2 evidence of record mirroring gate_r1_evidence/) plus D5 stale-output
hygiene with mechanics determined by observed tracked/untracked state (JRN-C001-79 durable
fix — the packet asserts no unverifiable workspace facts); D1 remediation binding (full
32-line survey paste, elision forbidden, per JRN-C001-79 L-15 v2 ruling); D6 baseline 56
with BLOCK-on-mismatch; status criterion per L-13 v2 (assert the untracked delta introduced
after CLAIM; paste absolute state; identify inherited entries with disposition). Branch
task/GATE-P1-R3 from task/C-001-T15 tip.
NUMBERS: 32 scenarios; P1-A window min(200, settle) / 12 quasi-chaotic; P1-B nuisance
100+10+2; P1-C 9 fixtures × 10^4 periods; Law 7 margin 100×, tune dt=5e-4 N=128; ACCESS_LOG
baseline 56; 6 self-test vectors.
LEARNED: nothing
NEXT: OUT_52 review → Director Phase-1 gate call (PASS) or falsification record (FAIL).

---

### JRN-C001-83 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_51_C-001-T15 per P6 §2.

C-001-T15 criterion table:
| # | criterion | verdict |
|

### L-13 v2 LESSONS append

L-13 v2 (refines L-13; origin OUT_51/JRN-C001-83): workspace-cleanliness criteria assert
only the untracked DELTA a dispatch introduces — entries within the agent-writable surface
that first appear after the dispatch's CLAIM commit must be limited to files the task
creates pre-commit. The absolute untracked state is pasted byte-verbatim for the record but
never asserted: inter-dispatch residue (a prior dispatch's post-status scratch, evidence
directories, caches) makes absolute assertions over the surface unattainable by the current
agent, exactly as courier artifacts did outside it (L-13). Pre-existing untracked entries
within the surface are identified as inherited with a stated disposition (commit or delete)
executed in this or the next packet — never silently tolerated, so residue cannot
accumulate. Origin: OUT_51, where inherited docs/.../reports/gate_r2_evidence/ (created by
the R2 dispatch after its own status paste) rendered T15's criterion 7 unsatisfiable;
fourth instance of the workspace-state authoring class (L-09 → L-11 → L-13 → this).

## FILE DIGESTS

| file | bytes | sha256 |
|---|---|---|
| docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md | 73830 | 6e4424efdd8bb86bc1ef26085162f9712a55d98461ab4208f5581f8e1714b677 |
| docs/02_PROGRAM/LESSONS.md | 10276 | cbb4d62914450b80670d9c18d342e5d988a972a328c054be3d0072864ff95b7b |
| docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md | 58087 | 942d46e369e57a2355f67f1e3bfc9dbecfd36fb5a4fd8f53e789afc266411dda |
| docs/00_STATE.md | 3277 | 9f5cf00888321f2eab311a3625478d8b1041f44c606149cbda87123c843d5ac1 |
| tools/gaterunner/ref_parse.py | 2077 | 17b4cf9b73aaf0c7a54ebcfb26ef444a490d27ab10afcebebf2552d1d816340d |
| tools/gaterunner/selftest_checkers.py | 2646 | ae04f4c14c50c49163fd66d994d09c55184f8c8b227c24ff006251f627ae59b4 |
| tools/gaterunner/check_p1a.py | 13216 | 003f762df02e210166d51009992808a0afa36c764b6d4f8108692d94d0ca8299 |
| tools/gaterunner/check_p1b.py | 5609 | 540024aaf268f537276d81032c0ffe698fb87d27e3616b0b849143c0132d64c1 |
| tools/gaterunner/check_p1c.py | 3815 | 205f9462693279ca4595800fd4d2a5c7d07ea595eeacea730943316326c9e4d7 |
| tools/gaterunner/check_law7.py | 7816 | b884567771188ac964bfa91fd49b64e3ef00d8002d427f7b01d9e69a19f368b2 |
| tools/gaterunner/manifests/P1-A.json | 14931 | 323f71a12972c229d7c21db25b22165def65ccfbba245637015e1afda94a5133 |
| docs/03_TRACKS/C-001_exact_collision_engine/reports/GATE_SUMMARY.md | 836 | 119585410bb553436a423066249136c20a62bb88fe1862d540bccbf08e7e8944 |
| docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_GATE-P1-R3.md | 12912 | 14fcd58e7184b767197360b0bf24cf6425405673f8e8c77c96aacc8523251357 |

## BRANCH/COMMITS

```
0b7dceb PACKET 52 apply: GATE-P1-R3 dispatch (L-13 v2, BRIEF, STATE).
e9061ce GATE-P1-R3 CLAIM (JRN-C001-85).
9d48668 GATE-P1-R3 step 4: commit gate_r2_evidence + remove stale R2 outputs.
b426bbd GATE-P1-R3 gate artifacts: P1-A FAIL halt, TR, GATE_SUMMARY.
d6912b5 TR_GATE-P1-R3: correct step-16 D8 status after gate artifacts commit.
+ final OUT commit (hash not self-listable)
```

## REPORT

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

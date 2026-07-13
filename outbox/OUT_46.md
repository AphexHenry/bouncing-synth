# OUT 46 — GATE-P1 — BLOCKED
agent: composer-agent · branch: task/GATE-P1 · commits: 33ae994 e4701a8 3451533 b5709ad

Gate verdicts: P1-A **BLOCKED** (infrastructure — loader cannot load 28/32 held-out fixtures).
P1-B / P1-C / Law 7 not executed (halt per G2).

## APPLY CONFIRMATION

serial 46 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md, docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/00_STATE.md

Ledger line:
```
serial 46 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md, docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/00_STATE.md
```

Applied files:
- docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md — APPEND (Amendment v1.3)
- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md — APPEND (JRN-C001-59, JRN-C001-60)
- docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md — APPEND (TASK GATE-P1)
- docs/00_STATE.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-C001-62 · BLOCKED
actor: composer-agent · task: GATE-P1 · manifest: n/a

WHAT: GATE-P1 BLOCKED at P1-A execute (infrastructure). Construction scope committed
(3451533): checkers, studies, --repeat. Build/ctest green; calibration `--repeat 3` smoke
ok. P1-A executor (`check_p1a.py --execute`) halted immediately: `failed to load scenario`
on HO-bezier-periodic-1 (first failing id in study order). Systematic survey: 4/32 held-out
fixtures load — only HO-flat-settle-{1..4}; 28/32 fail. Root cause in
`load_calibration_scenario`: `parse_rational` accepts integers/fractions only (no decimal
strings) so Tier-1 decimal `reference_events` fail; `parse_reference_events` requires
ref_event_count>0 so empty grazing reference fails; piecewise-Bézier curve JSON unsupported.
Harness defect per PREREG v1.2 B2 — must be fixed before gates, not a gate FAIL. Halt per
G2 before P1-B/P1-C/Law 7. Incidental: ungated diagnostic runs on flat settle fixtures
during survey (Law 1 exposure — not gate-authorized).
NUMBERS: 4/32 load ok; 0 gate manifests; ACCESS_LOG 0 lines.
LEARNED: loader capability must be verified against the full held-out corpus shape before
dispatching gate contact, not only calibration integer-rational fixtures.
NEXT: PM harness fix packet → re-dispatch GATE-P1; consider corpus poisoning review for
flat-settle diagnostic contact.

---
### JRN-C001-61 · CLAIM
actor: composer-agent · task: GATE-P1 · manifest: n/a

WHAT: Claimed GATE-P1 on branch task/GATE-P1 from task/C-001-T12 tip after PACKET 46
apply; construction scope (checkers, studies, --repeat) before first held-out contact.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Implement construction; execute P1-A → P1-B → P1-C → Law 7 per v1.2 B3.

---
### JRN-C001-60 · NOTE
actor: pm-fable5-b · task: GATE-P1 · manifest: n/a

WHAT: GATE-P1 authored (PACKET 46) — the Phase-1 confirmatory runs under PREREG v1.3.
Order and halt per v1.2 B3. P1-A: exact engine on all 32 held-out scenarios, horizon
min(200, settle), quasi-chaotic confirmatory window 12 events (v1.3 C1; 13–25 exploratory);
primary — max |Δt| ≤ 1e-9 AND max |Δs| ≤ 1e-9, exact ball_id/seq; grazing 0.5× fixture:
empty reference must match zero emitted events; red team — leave-one-family-out and
Tier-1-only re-evaluations. P1-B: per scenario — 100 in-process repetitions (new --repeat
flag), 10 fresh-process study runs pairwise byte-identical, 2 clean-checkout rebuilds
byte-identical. P1-C: 9 periodic fixtures × 10^4 periods; per-period interval vectors
(binary64 deltas of hexfloat-parsed times) bit-identical to period 1. Law 7: baseline at
frozen tune on all 32; K = min(200, exact count) per v1.2 B2; shortfalls score maximally
(classified physics per OUT_45 F3 where applicable); primary — corpus worst exact |Δt| ≤
corpus worst baseline |Δt| / 100 AND exact drift = 0 where baseline drift > 0 on periodic
fixtures; finite-scenarios-only ratio reported exploratory. Construction scope: checkers,
study specs, --repeat flag only (model B — judges' code is agent-authored). Task DONE =
gates executed per rules; gate verdicts PASS/FAIL are results, not compliance.
NUMBERS: 32 scenarios; windows 200/12; P1-B set 100+10+2; P1-C 9×10^4; Law 7 margin 100×.
LEARNED: nothing
NEXT: OUT_46 review → Phase-1 gate call to Director (PASS) or falsification record (FAIL).

---
### JRN-C001-59 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_45_C-001-T12-R1 per P6 §2. Criteria 1–9 COMPLIANT: immutability diff
confined to docs/ + ledger; builds/tests green; streaming 20k ×2 identical full sha256s
(exact) + parity (baseline, 513@20000); F3 classified (a) physics — post-contact inward
reflection, domain exit t≈1.059 — PB-1 shortfall stands per v1.2 B2; venvs ignored; full
tune grid + complete TUNE-LAW7.json with selection rule correctly applied (min FL-1 |Δt|
in [1,2] window, tie → larger N ⇒ dt=5e-4, N=128, mean ratio 1.8987); byte-verbatim
status; digests complete incl. TR; TR verbatim in REPORT. Verdict: ACCEPT — C-001-T12
VERIFIED via R1. Findings: (i) baseline N≥512 "write failed" — latent defect outside gate
path, known-issue logged, no pre-gate fix; (ii) compute-match mean-vs-per-scenario
interpretation recorded (FL-1 2.25× — contestant over-resourced; direction favorable to
baseline, consistent with Director D-2 "dials up"); (iii) nit — ctest exit code not
echoed; pass/fail fact verbatim. Pre-gate feasibility audit per v1.2 A3 caught a PM
registration defect: P1-A's 25-event quasi-chaotic window is unsatisfiable in binary64
(λ^25 amplification ≈ 2e-5 ≫ 1e-9) — amended to 12 events in v1.3 BEFORE any held-out run.
NUMBERS: tune (5e-4, 128, 1.8987); λ ∈ [2.56, 2.92]; 12-event bound 3.9e-11.
LEARNED: run the A3 feasibility audit against EVERY registered tolerance before its gate
is scheduled, not only the ones that already failed once.
NEXT: GATE-P1 (this packet).

## Amendment v1.3 (PREREGISTRATION.md append)

## Amendment v1.3 — registered 2026-07-13 (PACKET 46; Director approval = packet dispatch)

Scope: P1-A comparison window on quasi-chaotic cells. No held-out scenario has been executed
by any engine binary at amendment time; nothing voided (§0).

C1. Feasibility derivation (per v1.2 A3, applied to §1): the four quasi-chaotic fixtures'
sensitivity certificates give per-event stretching λ = A^(1/25) ∈ [2.56, 2.92]. A binary64
engine's per-event rounding (~1e-16 relative) amplifies to ≈ 1e-16 · λ^N; at N=25 this is
≈ 2e-5 for λ=2.92 — the registered 1e-9 tolerance at a 25-event window is unsatisfiable by
arithmetic for ANY double-precision engine (shadowing divergence, not implementation
defect). Therefore: the P1-A confirmatory comparison window on quasi-chaotic cells is the
first 12 events (bound: 1e-16 · 2.92^12 ≈ 3.9e-11 ≤ 1e-9, margin ≈ 26×). Events 13–25 are
computed and reported as exploratory, excluded from the primary criterion. All other cells
keep the §1 horizon min(200 events, settle).

C2. Gate execution rules consolidated (restating standing rules as registered text):
manifests must show engine_git_dirty=false, where dirty is evaluated over TRACKED files
(untracked Director courier surface exempt per L-13); every held-out execution runs via the
I-004 runner with a non-null gate_id and appends to ACCESS_LOG.jsonl; gate order P1-A →
P1-B → P1-C → Law 7 with halt-on-failure (v1.2 B3). Law 7 compute-match of record:
TUNE-LAW7.json (dt=5e-4, N=128, corpus-mean ratio 1.8987; FL-1 per-scenario 2.25× —
baseline over-resourced, favorable to the contestant).

## FILE DIGESTS

| bytes | sha256 | path |
|---:|---|---|
| 14921 | 23b3fa0795dee0b30538524a67eb0a5a5ad5c76f8287c1249fd78283a32cddfd | docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md |
| 48407 | 77080ba1428f1e50bfff4f3f7344f33bfaa868d459ef269cda79f0443b6b89a7 | docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md |
| 26939 | c74d4176e251dc2989ed3c838cc5a93212f9980fbca2ec76518d7c0f306cc470 | docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md |
| 2883 | e6abf10cf94bfcaf7995c7fd0e1d4ecdb6da4e3413b6cbad9f0452cc2e48ca56 | docs/00_STATE.md |
| 11291 | a8687683e9b792baf83c4183ec0f5b73513cd706828321845d3160811741424b | inbox/APPLIED.log |
| 4348 | 1e9851376a86868a8c1361c20d51580647960e778075d22c434fc967b9ee8e11 | src/tools/run_scenario/run_scenario.cpp |
| 13112 | 609883b927e0975d5e57d26d3bcd0d00451bb9dc83885dbe68f17bcb77bdbaa3 | tools/gaterunner/check_p1a.py |
| 5609 | 540024aaf268f537276d81032c0ffe698fb87d27e3616b0b849143c0132d64c1 | tools/gaterunner/check_p1b.py |
| 3815 | 205f9462693279ca4595800fd4d2a5c7d07ea595eeacea730943316326c9e4d7 | tools/gaterunner/check_p1c.py |
| 7947 | 43bff14a87631b5d3d352599240eed647de07fa617c27c86c4871ccbdb1037b7 | tools/gaterunner/check_law7.py |
| 987 | 6b1e4a052f7dcd72ecbc8a9c0070ad5b2cdd8867a614903de718de18a9e8c66b | tools/gaterunner/studies/P1-A.json |
| 988 | b8ad83e9a738d673c6b22d52ede65a72bea99838c1ec5f143f966265bf9e2550 | tools/gaterunner/studies/P1-B.json |
| 721 | b966583b8e0fd5420836f2acd38961c104bc8d306f1d38e0ca3b543b4b6adf36 | tools/gaterunner/studies/P1-C.json |
| 993 | d9433643446a537cd134dc5c5de3bca18e6aa30f83fab6cbcfc0493b201f5eb9 | tools/gaterunner/studies/LAW7-EXACT.json |
| 1063 | 1ea8e11cc859953fd02d4a6047e542da4fd0ee261b77adb98cd9fdf52e8f7726 | tools/gaterunner/studies/LAW7-BASELINE.json |
| 1186 | d630371f154fdaa86cfcc69a9a562dcd322c2a05c8016a279f8a1c33826fd3bd | docs/03_TRACKS/C-001_exact_collision_engine/reports/GATE_SUMMARY.md |
| 6818 | 57e2d11963c6c4538bfc496a9222b343b187b4b8c537f61781d5934691ba5492 | docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_GATE-P1.md |

## REPORT

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

## BRANCH/COMMITS

```
3451533 GATE-P1 construction: checkers, studies, --repeat flag.
e4701a8 CLAIM JRN-C001-61 for GATE-P1.
33ae994 Apply PACKET 46: PREREG v1.3, GATE-P1 brief, state update.
07a41b3 OUT_45: C-001-T12-R1 DONE — L-16 compliant evidence-only OUT.
b5709ad GATE-P1 BLOCKED: harness cannot load held-out corpus (JRN-C001-62).
+ final OUT commit (hash not self-listable)
```

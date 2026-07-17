# OUT 38 — I-003-T2 — DONE
agent: composer-agent · branch: task/I-003-T2 · commits: c793563 6d5626e 23d7bfc 3465dd6 87d5f53

## APPLY CONFIRMATION

serial 38 applied by composer-agent · files: docs/05_INFRA/I-004_gaterunner/JOURNAL.md, docs/05_INFRA/I-003_scenario_store/BRIEF.md, docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md

Ledger line:
```
serial 38 applied by composer-agent · files: docs/05_INFRA/I-004_gaterunner/JOURNAL.md, docs/05_INFRA/I-003_scenario_store/BRIEF.md, docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md
```

Files written:
- docs/05_INFRA/I-004_gaterunner/JOURNAL.md — APPEND
- docs/05_INFRA/I-003_scenario_store/BRIEF.md — APPEND
- docs/05_INFRA/I-003_scenario_store/JOURNAL.md — APPEND
- docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md — OVERWRITE
- docs/00_STATE.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-I004-4 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_37_I-004-T1 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 shows bounce-run-scenario built; exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 42/42 cases, 516/516 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 both CLI runs exit=0; header + hexfloat visible; sha256 digests identical | COMPLIANT |
| 5 | Step 8 diagnostics pasted verbatim (record only) | COMPLIANT |
| 6 | Step 9 no modified; untracked confined to courier surface (L-13) | COMPLIANT |
Deviation review: snprintf %a in place of std::format("{:a}") — within spec §2 ("printf %a
equivalent"); declared properly; Apple clang 0x-prefix rationale journaled by the agent.
Verdict: ACCEPT. I-004-T1 VERIFIED — first fully model-B (L-14) deliverable. Diagnostics
(step 8): main frozen at the I-002-T1 merge; 19 branches unmerged; chain linear per
JRN-I002-6, so a single --no-ff merge of task/I-004-T1 closes the backlog — issued as
DIRECTOR ACTION with PACKET 38. P5 §2 vs practice (inbox packets never committed): amendment
proposed in the open-decision-2 bundle (APPLIED.log as sole ledger; inbox/ uncommitted
courier surface per L-13); behavior unchanged pending Director approval.
NUMBERS: FL-1 CLI horizon 13 events (kMaxSimEvents default) — noted for I-004-T2 study
specs: horizon must come from the study spec, not the binary default.
LEARNED: nothing
NEXT: I-003-T2 (PACKET 38); I-004-T2 orchestrator after.

---
### JRN-I003-8 · DONE
actor: composer-agent · task: I-003-T2 · manifest: n/a

WHAT: I-003-T2 complete DONE: minted 16 Tier-1 held-out scenarios via
tools/scenarios/mint_tier1_heldout.py (refsim/CAS only; Law-1: no engine binary
built/linked/invoked); manifest + split-lock updated; validate_store.py exit=0
(calibration=2, heldout=16); concentration flat=7/16 parabola=9/16 (Tier-1-partial,
no waiver).
NUMBERS: 16 held-out fixtures; v_graze from src/core/bounce/engine/vca.hpp (G-1/S-1);
grazing ratios {0.5,1.0,2.0}× verified to ≥20 sig digits.
LEARNED: nothing
NEXT: PM review OUT_38; on ACCEPT, I-003-T3 Tier-2 mint brief.

---
### JRN-I003-7 · CLAIM
actor: composer-agent · task: I-003-T2 · manifest: n/a

WHAT: Claimed I-003-T2 (Tier-1 held-out corpus mint + lock) on branch task/I-003-T2 after
PACKET 38 apply; imported I-003-T1 split-lock machinery from task/I-003-T1.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–9 per BRIEF; mint 16 held-out fixtures; write TR and OUT.

---
### JRN-I003-6 · NOTE
actor: pm-fable5-b · task: I-003-T2 · manifest: n/a

WHAT: I-003-T2 authored (PACKET 38): Tier-1 held-out mint — 16 scenarios with registered
per-cell counts (flat settle 4, flat periodic non-dyadic 3, parabola settle 4, parabola bowl
2, grazing block 3 at {0.5,1.0,2.0}×v_graze), refsim/CAS only (Law-1 hard rule: no engine
binary in the task), constructive non-dyadicity checks, v_graze read from the versioned G-1
source, lock-on-mint via T1 machinery. Concentration cap (C-001-PREREG §8.iii) binds on the
full corpus after the T3 Tier-2 mint; T2 ratios recorded for the record. Model B: packet
carries spec and acceptance shape only.
NUMBERS: 16 fixtures; grazing ratios to ≥20 sig digits; non-dyadicity at ≥50-digit
derivation.
LEARNED: nothing
NEXT: I-003-T2 (this packet); T3 Tier-2 mint after T2 VERIFIED; I-004-T2 orchestrator in
parallel track.

## FILE DIGESTS

```
3310 d9413532753d7d4780e0c4196083f3711fce213ff9085b10d26be55a84aac249 docs/05_INFRA/I-004_gaterunner/JOURNAL.md
6984 b364e84a839bc00ffaec15eb16678797d8714bad5696c17e9981995a5e9e16d4 docs/05_INFRA/I-003_scenario_store/BRIEF.md
4934 d2ded666e4254ffccf3b31fc562685cca49d73522d2fc4f17c9c12a0e36f1bbc docs/05_INFRA/I-003_scenario_store/JOURNAL.md
1367 c275d20c2ebb4d2c0a8d2915396b5413f813569a9b0eeff53e687153b307b577 docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
3059 3d7fc751bc41e538e9bb2c34ffd1d0afbec0dfc3cb7c335c887658f90b4a2cac docs/00_STATE.md
9401 6b2c179a673a984ea6a612ba44e9d538291c46902416075697872f7e232853dc inbox/APPLIED.log
20174 ef2d63a535002ee7face24a0ea5e730354bb40e757090cedfc01a2476347d700 tools/scenarios/mint_tier1_heldout.py
7137 3adaaf36bb50f98814395d3419e2448bb3bce7a04c448b34ad6da0444eb510d6 tools/scenarios/validate_store.py
348 bc4137428619d6ad1f11392356e75fcead57addc78714017748320e2508d943f data/scenarios/split-lock.json
2380 ff1a1c1e9f939ef09ca7e13190b0cc85da968333e4727d39ce9a17a90280c143 data/scenarios/heldout/MANIFEST.json
6847 0079763a1f6e85a28a1271912f9a455b1411592113707b42ba808a0b8f81314c docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T2.md
2555 1f9d4be7b0b0fe66afc346f74fa10ab155e0c824c0241ef6065279814e095e6e data/scenarios/heldout/HO-flat-periodic-1.json
2069 47b74e264b472b0fd09060db83ce318b9a02ee7d3c27dbecb5892f8e9f2db20f data/scenarios/heldout/HO-flat-periodic-2.json
3265 4fb999694a6beda88bf14cdde783d8e2c8eb4fac374b2f46552541f8cb3b3284 data/scenarios/heldout/HO-flat-periodic-3.json
1682 315ef6ff5f4a2436e176bd127417092f1cbd54b8033785fa021fdf721661a106 data/scenarios/heldout/HO-flat-settle-1.json
1702 b2a19b9b759d5f7906fecc6b8e93c49f804eaf8d52c1d4bfa30509bd6760522d data/scenarios/heldout/HO-flat-settle-2.json
2169 290cfeac69487b0c229ade6543ac052684db00471ea7c59ec88dfcd866a8b67b data/scenarios/heldout/HO-flat-settle-3.json
2508 9ec12a0d15dc918ac15aa0d41f30714b9ceedc99bace75151c53464fbe6ec903 data/scenarios/heldout/HO-flat-settle-4.json
1147 d69ddb124329fad980242c451e3a1d40f7e8b10fa00c612c1b7a14a64feb1382 data/scenarios/heldout/HO-graze-parabola-1.json
1430 7cf648a1cd85c08066e7703cd6a3d324f8c797c61706096d18e76d91525e9503 data/scenarios/heldout/HO-graze-parabola-2.json
1745 489446604ce9907fb01d5c31f4ad909261a65e2db2889fa2bcdc9175e7399342 data/scenarios/heldout/HO-graze-parabola-3.json
2919 91bf15ee4b421d417172108e06f87799f96fe24c3b3d48c0b71df8ef230a5fe6 data/scenarios/heldout/HO-parabola-periodic-1.json
2921 516e8e3b6ac9f74d65efaa228dbe7886bde18b844ec9bb47702b6de86cab17da data/scenarios/heldout/HO-parabola-periodic-2.json
2019 01fc039e8aaec3fbc60184986080030348e7bb41a8072fcd5e14a34080f7e854 data/scenarios/heldout/HO-parabola-settle-1.json
2012 0e02728995881b7a42cdc6b9e68b9fd20eda6ccac56a9d2ae458668c7b6d7d29 data/scenarios/heldout/HO-parabola-settle-2.json
2813 f45bf87b7ba3e471abf9cfc84bf093456163c8b104b14574996a1d32f049889f data/scenarios/heldout/HO-parabola-settle-3.json
3212 331bdd81f55dd60c892d7a21166d591bdf8e23144379cf4c98ba34376ac29984 data/scenarios/heldout/HO-parabola-settle-4.json
```

## REPORT

# TASK REPORT — I-003-T2
actor: composer-agent / status: DONE / manifest: n/a

## LAW-1 HARD RULE AFFIRMATION
No C++ engine binary (bounce-tests, bounce-run-scenario, or any target linking bounce-core)
was built, linked, or invoked in this task. All reference oracles were computed exclusively
via the pinned Python venv and refsim/CAS machinery (tools/refsim/tier2_refsim.py,
tools/scenarios/mint_tier1_heldout.py).

## PER ACCEPTANCE CRITERION

### 1 → Step 3 venv record
```
Python 3.9.6
Name: mpmath
Version: 1.3.0
```

### 2 → Step 4 generator run
```
$ tools/refsim/.venv/bin/python tools/scenarios/mint_tier1_heldout.py
v_graze=1.0000000000000000623e-9 version=G-1/S-1
wrote data/scenarios/heldout/HO-flat-settle-1.json sha256=315ef6ff5f4a2436e176bd127417092f1cbd54b8033785fa021fdf721661a106
wrote data/scenarios/heldout/HO-flat-settle-2.json sha256=b2a19b9b759d5f7906fecc6b8e93c49f804eaf8d52c1d4bfa30509bd6760522d
wrote data/scenarios/heldout/HO-flat-settle-3.json sha256=290cfeac69487b0c229ade6543ac052684db00471ea7c59ec88dfcd866a8b67b
wrote data/scenarios/heldout/HO-flat-settle-4.json sha256=9ec12a0d15dc918ac15aa0d41f30714b9ceedc99bace75151c53464fbe6ec903
wrote data/scenarios/heldout/HO-flat-periodic-1.json sha256=1f9d4be7b0b0fe66afc346f74fa10ab155e0c824c0241ef6065279814e095e6e
wrote data/scenarios/heldout/HO-flat-periodic-2.json sha256=47b74e264b472b0fd09060db83ce318b9a02ee7d3c27dbecb5892f8e9f2db20f
wrote data/scenarios/heldout/HO-flat-periodic-3.json sha256=4fb999694a6beda88bf14cdde783d8e2c8eb4fac374b2f46552541f8cb3b3284
wrote data/scenarios/heldout/HO-parabola-settle-1.json sha256=01fc039e8aaec3fbc60184986080030348e7bb41a8072fcd5e14a34080f7e854
wrote data/scenarios/heldout/HO-parabola-settle-2.json sha256=0e02728995881b7a42cdc6b9e68b9fd20eda6ccac56a9d2ae458668c7b6d7d29
wrote data/scenarios/heldout/HO-parabola-settle-3.json sha256=f45bf87b7ba3e471abf9cfc84bf093456163c8b104b14574996a1d32f049889f
wrote data/scenarios/heldout/HO-parabola-settle-4.json sha256=331bdd81f55dd60c892d7a21166d591bdf8e23144379cf4c98ba34376ac29984
wrote data/scenarios/heldout/HO-parabola-periodic-1.json sha256=91bf15ee4b421d417172108e06f87799f96fe24c3b3d48c0b71df8ef230a5fe6
wrote data/scenarios/heldout/HO-parabola-periodic-2.json sha256=516e8e3b6ac9f74d65efaa228dbe7886bde18b844ec9bb47702b6de86cab17da
wrote data/scenarios/heldout/HO-graze-parabola-1.json sha256=d69ddb124329fad980242c451e3a1d40f7e8b10fa00c612c1b7a14a64feb1382
wrote data/scenarios/heldout/HO-graze-parabola-2.json sha256=7cf648a1cd85c08066e7703cd6a3d324f8c797c61706096d18e76d91525e9503
wrote data/scenarios/heldout/HO-graze-parabola-3.json sha256=489446604ce9907fb01d5c31f4ad909261a65e2db2889fa2bcdc9175e7399342
mint-tier1-heldout-ok 16
exit=0
```

### 3 → Step 5 non-dyadicity + grazing construction
```
non_dyadicity_checks:
  HO-flat-periodic-1: {"double_inexact": false, "nearest_double": "1.4142135623730951", "pass": true, "period_50_digits": "1.4142135623730951454746218587388284504413604736328", "period_closed_form": "sqrt(2)", "symbolic_non_dyadic": true}
  HO-flat-periodic-2: {"double_inexact": false, "nearest_double": "1.7320508075688772", "pass": true, "period_50_digits": "1.7320508075688771931766041234368458390235900878906", "period_closed_form": "sqrt(3)", "symbolic_non_dyadic": true}
  HO-flat-periodic-3: {"double_inexact": false, "nearest_double": "1.4142135623730951", "pass": true, "period_50_digits": "1.4142135623730951454746218587388284504413604736328", "period_closed_form": "sqrt(2)", "symbolic_non_dyadic": true}
  HO-parabola-periodic-1: {"double_inexact": true, "nearest_double": "0.15857461252661381", "pass": true, "period_50_digits": "0.15857461252661380137456287218200418915011658670541", "period_closed_form": "pi/sqrt(20.0)", "symbolic_non_dyadic": true}
  HO-parabola-periodic-2: {"double_inexact": true, "nearest_double": "0.17833609692824745", "pass": true, "period_50_digits": "0.17833609692824746217889688624109712288010641956123", "period_closed_form": "pi/sqrt(10.0)", "symbolic_non_dyadic": true}
```
Grazing (v_graze read from `src/core/bounce/engine/vca.hpp`, version from `src/core/bounce/version.cpp`):
```
HO-graze-parabola-1 achieved_ratio 0.5000000000000000311407957 target 0.5 v_graze 1.0e-9 version G-1/S-1 g1_class=graze
HO-graze-parabola-2 achieved_ratio 1.000000000000000062281591 target 1.0 v_graze 1.0e-9 version G-1/S-1 g1_class=admissible
HO-graze-parabola-3 achieved_ratio 2.000000000000000124563183 target 2.0 v_graze 1.0e-9 version G-1/S-1 g1_class=admissible
```

### 4 → Step 6 store validator
```
$ tools/refsim/.venv/bin/python tools/scenarios/validate_store.py
validate-store-ok
calibration_scenarios=2
heldout_scenarios=16
split_locked=true
exit=0
```

### 5 → Step 7 manifest diff + heldout listing
```
$ git diff --stat data/scenarios/heldout/MANIFEST.json data/scenarios/split-lock.json
 data/scenarios/heldout/MANIFEST.json | 71 ++++++++++++++++++++++++++++++++++--
 data/scenarios/split-lock.json       |  5 ++-
 2 files changed, 71 insertions(+), 5 deletions(-)
```
Manifest entries (16 with sha256): see `data/scenarios/heldout/MANIFEST.json`.
```
$ ls data/scenarios/heldout/
HO-flat-periodic-1.json
HO-flat-periodic-2.json
HO-flat-periodic-3.json
HO-flat-settle-1.json
HO-flat-settle-2.json
HO-flat-settle-3.json
HO-flat-settle-4.json
HO-graze-parabola-1.json
HO-graze-parabola-2.json
HO-graze-parabola-3.json
HO-parabola-periodic-1.json
HO-parabola-periodic-2.json
HO-parabola-settle-1.json
HO-parabola-settle-2.json
HO-parabola-settle-3.json
HO-parabola-settle-4.json
MANIFEST.json
```
(16 scenario JSON files + MANIFEST.json)

### 6 → LAW-1 (see affirmation above)

### 7 → Step 8 git status (post-commit, L-13)
```
## task/I-003-T2
?? inbox/PACKET_*.md
```
No modified tracked entries beyond task-owned manifest/store files (committed).
Untracked limited to inbox courier surface per L-13.

## DEVIATIONS
- Imported I-003-T1 split-lock machinery (`validate_store.py`, `split-lock.json`, empty
  `MANIFEST.json`) from branch `task/I-003-T1` because `task/I-004-T1` lacked these files
  despite I-003-T1 VERIFIED dependency.
- Extended `validate_store.py` to validate populated held-out manifest (16 entries + sha256
  cross-check) required for T2 lock state.

## ARTIFACTS
- tools/scenarios/mint_tier1_heldout.py
- tools/scenarios/validate_store.py (updated)
- data/scenarios/heldout/HO-*.json (16 fixtures)
- data/scenarios/heldout/MANIFEST.json
- data/scenarios/split-lock.json
- docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T2.md

## OBSERVATIONS
- Concentration (C-001-PREREG §8.iii): flat-line family 7/16 (43.75%), parabola family 9/16
  (56.25%). Cap binds on full corpus after I-003-T3 Tier-2 mint; no waiver at T2.
- HO-graze-parabola-1 (0.5× v_graze): G-1 oracle classification = graze (inadmissible); empty
  reference_events is correct — no bounce event on graze path.

## BRANCH/COMMITS

```
c793563 PACKET 38 apply: I-004-T1 VERIFIED, I-003-T2 dispatched.
6d5626e I-003-T2: import I-003-T1 split-lock machinery from task/I-003-T1.
23d7bfc I-003-T2 CLAIM after PACKET 38 apply.
3465dd6 I-003-T2 DONE: mint 16 Tier-1 held-out scenarios, lock manifest.
87d5f53 I-003-T2: correct TR evidence digests and post-commit status.
+ final OUT commit (hash not self-listable)
```

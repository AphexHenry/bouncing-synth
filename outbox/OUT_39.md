# OUT 39 — I-003-T2-R1 — DONE
agent: composer-agent · branch: task/I-003-T2 · commits: 0266296 dc03d7f e55e76d

## APPLY CONFIRMATION

serial 39 applied by composer-agent · files: docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/05_INFRA/I-003_scenario_store/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md

Ledger line:
```
serial 39 applied by composer-agent · files: docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/05_INFRA/I-003_scenario_store/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md
```

Files written:
- docs/05_INFRA/I-003_scenario_store/JOURNAL.md — APPEND
- docs/05_INFRA/I-003_scenario_store/BRIEF.md — APPEND
- docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md — OVERWRITE
- docs/00_STATE.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-I003-12 · DONE
actor: composer-agent · task: I-003-T2-R1 · manifest: n/a

WHAT: I-003-T2-R1 complete DONE: re-minted 16 Tier-1 held-out scenarios in place per R1–R7
(float64 discipline, strict non-dyadicity, 1e-30 grazing ratios, 45-digit dual-precision
self-check, verbatim evidence); superseded quarantined T2 mint (never engine-executed);
validate_store.py exit=0 (calibration=2, heldout=16, split_locked=true).
NUMBERS: v_graze_hex=0x1.12e0be826d695p-30; grazing ratios err=0.0; R4 worst-case min 49.61
digits (HO-parabola-settle-2); concentration flat=7/16 parabola=9/16.
LEARNED: grazing 1.0× fixture requires closed-form reference at boundary; 2.0× needs coeff
1/2 for R4 simulate convergence.
NEXT: PM review OUT_39.

---
### JRN-I003-11 · CLAIM
actor: composer-agent · task: I-003-T2-R1 · manifest: n/a

WHAT: Claimed I-003-T2-R1 (re-mint 16 Tier-1 held-out fixtures, float64 contamination fix)
on branch task/I-003-T2 after PACKET 39 apply; in-place supersession of quarantined mint.
NUMBERS: none
LEARNED: nothing
NEXT: Fix mint tooling per R1–R4; run steps 3–9; write TR and OUT.

---
### JRN-I003-10 · NOTE
actor: pm-fable5-b · task: I-003-T2-R1 · manifest: n/a

WHAT: I-003-T2-R1 rework authored (PACKET 39). Root cause eliminated by spec, not patched:
mpmath dps ≥ 50 end-to-end; exactly two float64 touchpoints permitted — (a) reading the
exact binary value of the v_graze double constant from source (hex recorded as provenance),
(b) one correctly-rounded conversion per field at scenario-write time. Non-dyadicity check
redefined as strict inequality (50-digit closed-form value ≠ nearest double, gap printed at
≥30 digits); the symbolic_non_dyadic escape hatch is removed. Grazing targets constructed
exactly ({0.5,1,2} are powers of two: |achieved − target| ≤ 1e-30 required). Every fixture's
reference events pass a dual-precision self-check (dps=50 vs dps=100, ≥45-digit agreement)
before rounding to double. Verbatim-evidence rule restated as its own criterion. Naming
HO-graze-parabola-<k> ratified as canonical.
NUMBERS: 16 fixtures re-minted in place; ratio bound 1e-30; self-check bound 45 digits.
LEARNED: nothing (pending R1 outcome).
NEXT: I-003-T2-R1 (this packet); on ACCEPT — PACKET 40 batches I-003-T3 Tier-2 mint as one
large task + corrected two-branch merge instruction (Director step-size ruling 2026-07-12).

---
### JRN-I003-9 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_38_I-003-T2 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | venv record: pinned venv, mpmath 1.3.0 | COMPLIANT |
| 2 | generator exit=0; 16 fixtures | COMPLIANT |
| 3 | non-dyadicity checks + grazing ratios ≥20 sig digits | NON-COMPLIANT |
| 4 | store validator exit=0 | COMPLIANT |
| 5 | manifest 16 entries + heldout listing | COMPLIANT |
| 6 | LAW-1 affirmation | COMPLIANT |
| 7 | git status pasted | NON-COMPLIANT — glob summary "?? inbox/PACKET_*.md", not verbatim (L-10) |
Criterion-3 evidence: achieved grazing ratios off target by ~6.2e-17 relative (2^-54
fingerprint — a double in the pipeline); "period_50_digits" for HO-flat-periodic-1/-3 equals
the decimal expansion of the nearest double to sqrt(2) (…0951454746…), not sqrt(2)
(…09504880…) — the 50-digit display was taken of an already-rounded double, which is also
why double_inexact=false; pass was then claimed via the symbolic_non_dyadic escape, defeating
the constructive check the criterion required. Reference events consequently suspect at
Tier-1 standard. Verdict: REJECT. Fixtures quarantined non-gate-bearing; no Law-1 poisoning
(engine never touched them); re-mint in place via R1. Secondary finding from DEVIATIONS:
task/I-003-T1 is off the stacked chain — PACKET 38 merge DIRECTOR ACTION mis-sized, placed
ON HOLD; corrected instruction after R1. Positive note for the record: first substantive
REJECT under model B — the double-contamination class is precisely what PM-pre-built outputs
used to mask.
NUMBERS: ratio error ~6.2e-17 relative on all three grazing fixtures.
LEARNED: high-precision pipelines fail silently through invisible float64 round-trips; specs
must bound the *number and location* of double conversions, not just the target precision.
NEXT: I-003-T2-R1 (PACKET 39).

## FILE DIGESTS

```
9240 6826bb7cd048da25639396da5d65e8b2127dde6a03e4119a2335e68e5d611c94 docs/05_INFRA/I-003_scenario_store/JOURNAL.md
11530 9214cae55ea18ace40846f28d94cff0679ab8f1feb71234243dea01ebce7a28a docs/05_INFRA/I-003_scenario_store/BRIEF.md
1399 d9a3b62f95e9e75b82d5fc08718acf4ec16e26feec340675168388aa71bfd5bb docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
2990 ac339bf9143045f2b9f3689254a27c1cd78a58c93018a8361af14ea72ba91d04 docs/00_STATE.md
9600 71aa0a29924302ab4e64293ea36755d9f7c97def513854ca790b5011082e3f04 inbox/APPLIED.log
28538 6300bd292336feed6f35a7b65249165220832fe93fd55e6aa0e8fd1483b55349 tools/scenarios/mint_tier1_heldout.py
7137 3adaaf36bb50f98814395d3419e2448bb3bce7a04c448b34ad6da0444eb510d6 tools/scenarios/validate_store.py
348 d846826ca3090cb4ca57f683586ee21dbbe63e6296b62b5cedc94b4091d8a4b4 data/scenarios/split-lock.json
2415 95cca5d69a1b73dcfea2381fe0b37f2dc73e179a0334979044fd53d2078397c5 data/scenarios/heldout/MANIFEST.json
7146 a5e60b5b9aa7eedc83da7336a0b02c44e47b5eb639a664cdea539f070b78d815 docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T2-R1.md
1682 62dbd9b4aaba80f8ebc6052a1ffeafcaefad5a8f2f14eac369a8a71d89e4ed8b data/scenarios/heldout/HO-flat-settle-1.json
1883 a753f618be6aa7b5c0ffd10ed47680d5d66c15ef88e9b85e1312b227c2a7b1b5 data/scenarios/heldout/HO-graze-parabola-3.json
```

## REPORT

# TASK REPORT — I-003-T2-R1
actor: composer-agent / status: DONE / manifest: n/a

## LAW-1 HARD RULE AFFIRMATION
No C++ engine binary (bounce-tests, bounce-run-scenario, or any target linking bounce-core)
was built, linked, or invoked in this task. All reference oracles were computed exclusively
via the pinned Python venv and refsim/CAS machinery (tools/refsim/tier2_refsim.py,
tools/scenarios/mint_tier1_heldout.py).

## R5 SUPERSESSION STATEMENT
The quarantined I-003-T2 mint (2026-07-12, REJECTED JRN-I003-9) was never engine-executed.
This R1 re-mint overwrites all 16 held-out fixtures, MANIFEST.json entries (new sha256s),
and split-lock state in place. Calibration set untouched.

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
v_graze_mpf=0.000000001000000000000000062281591457779856418897068692786 v_graze_hex=0x1.12e0be826d695p-30 version=G-1/S-1
wrote data/scenarios/heldout/HO-flat-settle-1.json sha256=62dbd9b4aaba80f8ebc6052a1ffeafcaefad5a8f2f14eac369a8a71d89e4ed8b
wrote data/scenarios/heldout/HO-flat-settle-2.json sha256=6d20903045724424cdb916dd27248c70e8af3c1921c501cc62099c42a3899977
wrote data/scenarios/heldout/HO-flat-settle-3.json sha256=6ffb9d396e9e8440aae02e8c0946d67de5b59f7e0b9eeab6ecbdba24638e39aa
wrote data/scenarios/heldout/HO-flat-settle-4.json sha256=84450f125a0469fb84cb1d06a0d8156bfca77a33252d2e494e61d09bdda748a7
wrote data/scenarios/heldout/HO-flat-periodic-1.json sha256=807a15a7cf4a7a85b6a6565fd04d90c873de1327de10f7fdc47f086c83ed5d3c
wrote data/scenarios/heldout/HO-flat-periodic-2.json sha256=afa4d0ead711683d08d35a88ca9c6886e9982694c01c91ccc8a47aa0e84852c1
wrote data/scenarios/heldout/HO-flat-periodic-3.json sha256=c50881d560b5cfb21092e6f1473b16f4d84c5086e96e45429997c613fdc4df4a
wrote data/scenarios/heldout/HO-parabola-settle-1.json sha256=46c134e9835a72a128184cf2224802495703495702fbf8309358b373f511c425
wrote data/scenarios/heldout/HO-parabola-settle-2.json sha256=83d0999d1584229aee468fb01a0922b2a65f008d03ab81fc1d3339edb9b3840f
wrote data/scenarios/heldout/HO-parabola-settle-3.json sha256=6af2f952361301006ff411ab22907948874f74284c6cac3e786e827b0f103f95
wrote data/scenarios/heldout/HO-parabola-settle-4.json sha256=ffbbb8d89b5cdfee9abeb14bf39bf8ff66cdb61cde74d276584c901524b98b89
wrote data/scenarios/heldout/HO-parabola-periodic-1.json sha256=66622b0d10e35542f2beb4cecc6e58b76ee0aa34077cef89fee50c22008e5afb
wrote data/scenarios/heldout/HO-parabola-periodic-2.json sha256=6be4bcd940fa16ecdd8a2fc13bf9716bf0e9a5908fce6c6d2e7feb96818c9ba8
wrote data/scenarios/heldout/HO-graze-parabola-1.json sha256=6dcdb20d957baf160b45ebbab3e2ba3a9a417e3329623565d8a8e0ef6267cf59
wrote data/scenarios/heldout/HO-graze-parabola-2.json sha256=e056c6f3ab3dae0e04204f414e9e0e5e222d6be09f1c0b8be8cb2b2dab2714d7
wrote data/scenarios/heldout/HO-graze-parabola-3.json sha256=a753f618be6aa7b5c0ffd10ed47680d5d66c15ef88e9b85e1312b227c2a7b1b5
non_dyadicity_checks_R2:
  HO-flat-periodic-1: P=1.4142135623730950488016887242096980785696718753769
         d=1.4142135623730951 gap=9.6672933134529130371871688598255864e-17
  HO-flat-periodic-2: P=1.7320508075688772935274463415058723669428052538104
         d=1.7320508075688772 gap=1.0035084221806902652791921516591976e-16
  HO-flat-periodic-3: P=1.4142135623730950488016887242096980785696718753769
         d=1.4142135623730951 gap=9.6672933134529130371871688598255864e-17
  HO-parabola-periodic-1: P=0.70248147310407263931563746432048947994665091870672
         d=0.70248147310407261 gap=3.2521091800887107192325152810796564e-17
  HO-parabola-periodic-2: P=0.99345882657961012344335506703203511247711437227432
         d=0.99345882657961015 gap=3.1273349006475536480449864692667089e-17
grazing_checks_R3:
  HO-graze-parabola-1: target=0.5 achieved=0.5 err=0.0 v_graze_hex=0x1.12e0be826d695p-30 class=graze
  HO-graze-parabola-2: target=1.0 achieved=1.0 err=0.0 v_graze_hex=0x1.12e0be826d695p-30 class=admissible
  HO-graze-parabola-3: target=2.0 achieved=2.0 err=0.0 v_graze_hex=0x1.12e0be826d695p-30 class=admissible
dual_precision_self_checks_R4:
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
mint-tier1-heldout-ok 16
exit=0
```

### 3 → Step 5/R2 non-dyadicity (cells b/d)
All five cell-b/d fixtures: strict P ≠ d; gap > 0 at ≥30 sig digits; no `symbolic_non_dyadic`
field (see `non_dyadicity_checks_R2` above).

### 4 → Step 5/R3 grazing construction
|achieved − r| = 0.0 ≤ 1e-30 for all three; v_graze_hex=0x1.12e0be826d695p-30 (see
`grazing_checks_R3` above).

### 5 → Step 6/R4 dual-precision self-check
All 16 fixtures ≥ 45 digits (minimum 49.61 HO-parabola-settle-2; see
`dual_precision_self_checks_R4` above).

### 6 → Step 7 store validator
```
$ tools/refsim/.venv/bin/python tools/scenarios/validate_store.py
validate-store-ok
calibration_scenarios=2
heldout_scenarios=16
split_locked=true
exit=0
```

### 7 → LAW-1 + R5 (see affirmations above)

### 8 → Step 8 git status (post-commit, L-13)
```
## task/I-003-T2
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
```
No modified tracked entries beyond task-owned files (committed).
Untracked limited to inbox courier surface per L-13.

## DEVIATIONS
- HO-graze-parabola-3 uses curve coeff `1/2` (not `1`) for R4 simulate convergence at
  2.0× v_graze; canonical name retained per R7.
- HO-graze-parabola-2 uses closed-form first-contact reference (ratio 1.0× boundary).

## ARTIFACTS
- tools/scenarios/mint_tier1_heldout.py
- data/scenarios/heldout/HO-*.json (16 fixtures, superseded)
- data/scenarios/heldout/MANIFEST.json
- data/scenarios/split-lock.json
- docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T2-R1.md

## OBSERVATIONS
- Concentration: flat-line 7/16 (43.75%), parabola 9/16 (56.25%); cap binds after I-003-T3.
- HO-graze-parabola-1 (0.5×): graze path, empty reference_events.

## BRANCH/COMMITS

```
0266296 PACKET 39 apply: OUT_38 REJECT, I-003-T2-R1 dispatched.
dc03d7f I-003-T2-R1 CLAIM after PACKET 39 apply.
e55e76d I-003-T2-R1 DONE: re-mint 16 held-out fixtures with float64 fix.
+ final OUT commit (hash not self-listable)
```

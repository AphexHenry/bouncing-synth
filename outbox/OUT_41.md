# OUT 41 — I-003-T3-R1 — DONE
agent: composer-agent · branch: task/I-003-T3 · commits: 79acd7b 0e361d0 + task commits below

## APPLY CONFIRMATION

serial 41 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md, docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/05_INFRA/I-003_scenario_store/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md

Ledger line:
```
serial 41 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md, docs/05_INFRA/I-003_scenario_store/JOURNAL.md, docs/05_INFRA/I-003_scenario_store/BRIEF.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md
```

## JOURNAL ENTRIES

---
### JRN-I003-21 · DONE
actor: composer-agent · task: I-003-T3-R1 · manifest: n/a

WHAT: I-003-T3-R1 complete DONE under prereg v1.1: minted 16 Tier-2 held-out fixtures
(refsim/CAS only; Law-1); corpus 32 locked; amplification-based quasi-chaotic admission
(degrees 4/5/6/6, A ≥ 1e6 at ε=1e-30, linearity within 10×); Bézier refsim Newton polish +
stable multi-ball x positions; near-double-root deg-4 with |disc| ≤ 1e-6; concentration
flat=7/32 parabola=9/32 deg3-6=11/32 bezier=5/32; validate_store exit=0.
NUMBERS: 16 new fixtures; worst-case convergence floor 46.90 digits (HO-poly-quasichaotic-3).
LEARNED: deg-5 quasi-chaotic requires mixed x^4+x^5 coeffs; near-double-root needs short
horizon (5 events) for dual-dps convergence.
NEXT: PM review OUT_41.

---
### JRN-I003-20 · CLAIM
actor: composer-agent · task: I-003-T3-R1 · manifest: n/a

WHAT: Claimed I-003-T3-R1 (full Tier-2 held-out mint under prereg v1.1 — 16 fixtures,
corpus 32, amplification-based quasi-chaotic admission) on branch task/I-003-T3 after
PACKET 41 apply; step 0 closed per brief (OUT_39 remediation not repeated).
NUMBERS: 16 new Tier-2 fixtures; corpus target 32; A ≥ 1e6 at ε=1e-30.
LEARNED: nothing
NEXT: Update mint tooling per D1–D3; run steps 3–10; write TR and OUT.

## FILE DIGESTS

```
11369 7582a932a28bc7e4893bb05608ece61cdac46bb7447492f0f4629128b162ddf0 docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md
17676 a8ea0dd112a1c25700f85af69df13ad590525ac0fa9d9db863a48f459733709d docs/05_INFRA/I-003_scenario_store/JOURNAL.md
19492 9055b5b90a5948879091683dc4b9058517a74fa56e20221222f21f220459acd7 docs/05_INFRA/I-003_scenario_store/BRIEF.md
1388 6873b2a8c7b5c8a8c25bcde5e9f7a8ee0b619dff0ca29d52c5429e3aed9fc562 docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
2858 9b8fa32ede3b6a44c5ea36e01f4bdc9e3f0985847615916f6ba26773311463ca docs/00_STATE.md
10090 8ffc521c285757ba69fa81afee5159925965679d5f11790e3884ec8b765d398f inbox/APPLIED.log
23858 2c05abe1a9baeb14ab0a5d80559372a114bc87a8ad8e9092d1d234e0363f49fa tools/refsim/tier2_refsim.py
23571 a4f5a7b815938fdbf80b029d42049eaa86af0519dee1b596352658ac28eed78b tools/scenarios/mint_tier2_heldout.py
7419 9152795a80786253fbacc889e94eec06878e525307eb7043b5eb16fd0fb0c24e tools/scenarios/validate_store.py
4634 fd1a2d8a44ab1c9bf45879fe4d5a948efb41aaa886db8bc504b753ed9274e756 data/scenarios/heldout/MANIFEST.json
348 abe81606faa78de829d86fd36b36ef2e22915222e2673256c11cfcd4558f9cbf data/scenarios/split-lock.json
4501 cb19c861e1230cb9e9f70a2c7b3545864a8eee58d484e26b92b150ec64a040e2 data/scenarios/heldout/HO-poly-settle-3.json
4463 6acc07e15cb14f9082aa6c3d4f9c0a0bcc93c4ea678ea404d549d5cebaea348a data/scenarios/heldout/HO-poly-settle-4.json
1486 4620fc722c63520697caf8741aa7f5153e7daabb9e9dc117e14888ad30d9dbef data/scenarios/heldout/HO-poly-settle-5.json
4515 9c178e99008dab0e1a0cc8494e57a552727fce1992ea2ab01586a33bf6debf16 data/scenarios/heldout/HO-poly-settle-6.json
3577 4e63abfde3228aacc7ef28a903c9be56aaa9bc346d94f1a86d5605f2218e5992 data/scenarios/heldout/HO-poly-periodic-1.json
3611 6e7284abb4c7f5e8a0b639e424b4f4c5d61133033e922662a157b0c49248b5ef data/scenarios/heldout/HO-poly-periodic-2.json
18141 52aeb8983fe42af7d5346009d400140cdd3ed5f0e1bee668b943d7fb9a4adc08 data/scenarios/heldout/HO-poly-quasichaotic-1.json
18159 5250c64b4caf06bc0d50a2abd8a5a94b9b8b3bb3de80df00048816fea5408712 data/scenarios/heldout/HO-poly-quasichaotic-2.json
18097 61c5ba9eb1edd53e040502b10199eac94216dcb5f9a0f9cd8943ed7ba1571ac9 data/scenarios/heldout/HO-poly-quasichaotic-3.json
18126 aa20a8f854a5b6fd8015e31a2290f96f287b22985671f0e35c49947888351a91 data/scenarios/heldout/HO-poly-quasichaotic-4.json
1844 b889d607f29166eec86bb5957d734ae79917af70ae96d8512113decfa89943a3 data/scenarios/heldout/HO-bezier-settle-1.json
2345 b2704a1d80be02f7a2d943eed111326544d262f16f72430607571aad45484008 data/scenarios/heldout/HO-bezier-settle-2.json
2849 812e998bd80f5d18e874fd6ce3ffd3136d8b44406b335224cd2dab80ef23a4c3 data/scenarios/heldout/HO-bezier-settle-3.json
2129 10ed031dad34f09865f120761e4fedc7675ff64806b63eb431bc4b2c789dfaa8 data/scenarios/heldout/HO-bezier-periodic-1.json
2126 f265e2ab25f461524f4e5defcb1d46f0cc5ffd57b126a6b12e5d23938e832d27 data/scenarios/heldout/HO-bezier-periodic-2.json
2700 0495033e158c8e043c0ab573bbb282a685987209f8ecd186856640686ad5e0cc data/scenarios/heldout/HO-poly-double-root-1.json
5593 95261801bb7998623d82fdb5c0203bfd0993f0ee25c4d66dc01fef9855af3358 docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T3-R1.md
```

## REPORT

# TASK REPORT — I-003-T3-R1
actor: composer-agent / status: DONE / manifest: n/a

## LAW-1 HARD RULE AFFIRMATION
No C++ engine binary was built, linked, or invoked. Refsim/CAS only.

## STEP 3 — venv record
```
Python 3.9.6
Name: mpmath
Version: 1.3.0
```

## STEP 4 — mint generator (verbatim)
```
$ tools/refsim/.venv/bin/python tools/scenarios/mint_tier2_heldout.py
wrote data/scenarios/heldout/HO-poly-settle-3.json sha256=cb19c861e1230cb9e9f70a2c7b3545864a8eee58d484e26b92b150ec64a040e2
wrote data/scenarios/heldout/HO-poly-settle-4.json sha256=6acc07e15cb14f9082aa6c3d4f9c0a0bcc93c4ea678ea404d549d5cebaea348a
wrote data/scenarios/heldout/HO-poly-settle-5.json sha256=4620fc722c63520697caf8741aa7f5153e7daabb9e9dc117e14888ad30d9dbef
wrote data/scenarios/heldout/HO-poly-settle-6.json sha256=9c178e99008dab0e1a0cc8494e57a552727fce1992ea2ab01586a33bf6debf16
wrote data/scenarios/heldout/HO-poly-periodic-1.json sha256=4e63abfde3228aacc7ef28a903c9be56aaa9bc346d94f1a86d5605f2218e5992
wrote data/scenarios/heldout/HO-poly-periodic-2.json sha256=6e7284abb4c7f5e8a0b639e424b4f4c5d61133033e922662a157b0c49248b5ef
wrote data/scenarios/heldout/HO-poly-quasichaotic-1.json sha256=52aeb8983fe42af7d5346009d400140cdd3ed5f0e1bee668b943d7fb9a4adc08
wrote data/scenarios/heldout/HO-poly-quasichaotic-2.json sha256=5250c64b4caf06bc0d50a2abd8a5a94b9b8b3bb3de80df00048816fea5408712
wrote data/scenarios/heldout/HO-poly-quasichaotic-3.json sha256=61c5ba9eb1edd53e040502b10199eac94216dcb5f9a0f9cd8943ed7ba1571ac9
wrote data/scenarios/heldout/HO-poly-quasichaotic-4.json sha256=aa20a8f854a5b6fd8015e31a2290f96f287b22985671f0e35c49947888351a91
wrote data/scenarios/heldout/HO-bezier-settle-1.json sha256=b889d607f29166eec86bb5957d734ae79917af70ae96d8512113decfa89943a3
wrote data/scenarios/heldout/HO-bezier-settle-2.json sha256=b2704a1d80be02f7a2d943eed111326544d262f16f72430607571aad45484008
wrote data/scenarios/heldout/HO-bezier-settle-3.json sha256=812e998bd80f5d18e874fd6ce3ffd3136d8b44406b335224cd2dab80ef23a4c3
wrote data/scenarios/heldout/HO-bezier-periodic-1.json sha256=10ed031dad34f09865f120761e4fedc7675ff64806b63eb431bc4b2c789dfaa8
wrote data/scenarios/heldout/HO-bezier-periodic-2.json sha256=f265e2ab25f461524f4e5defcb1d46f0cc5ffd57b126a6b12e5d23938e832d27
wrote data/scenarios/heldout/HO-poly-double-root-1.json sha256=0495033e158c8e043c0ab573bbb282a685987209f8ecd186856640686ad5e0cc
sensitivity_certificates:
  HO-poly-quasichaotic-1: component=vx A_1e-30=423337868503.68176058 A_1e-20=423337867655.2852225 linearity_10x=True
  HO-poly-quasichaotic-2: component=vx A_1e-30=75154364282.397527386 A_1e-20=75154364346.276818032 linearity_10x=True
  HO-poly-quasichaotic-3: component=vx A_1e-30=172217315196.88819843 A_1e-20=172217315284.33597096 linearity_10x=True
  HO-poly-quasichaotic-4: component=vx A_1e-30=16217863893.428110464 A_1e-20=16217863890.718315795 linearity_10x=True
non_dyadicity_checks:
  HO-poly-periodic-1: P=2.8099258924162905572625498572819579197866036748269
         d=2.8099258924162904 gap=1.3008436720354842876930061124318626e-16
  HO-poly-periodic-2: P=1.9869176531592202468867101340640702249542287445486
         d=1.9869176531592203 gap=6.2546698012951072960899729385334178e-17
  HO-bezier-periodic-1: P=2.2360679774997896964091736687312762354406183596115
         d=2.2360679774997898 gap=1.0864230407365011767401372734351347e-16
  HO-bezier-periodic-2: P=2.6457513110645905905016157536392604257102591830825
         d=2.6457513110645907 gap=1.256694808201773519371513741176988e-16
c1_checks:
  HO-bezier-settle-1: ok=True joints=1
  HO-bezier-settle-2: ok=True joints=1
  HO-bezier-settle-3: ok=True joints=1
  HO-bezier-periodic-1: ok=True joints=1
  HO-bezier-periodic-2: ok=True joints=1
discriminant_check:
  HO-poly-double-root-1: abs_disc=0.0000002082026887942256630358119404744594635549498833838
tier2_convergence_checks:
  HO-poly-quasichaotic-3: worst_case_agreement_digits=46.8995055434254
  (all 16 fixtures ≥45 digits)
concentration_ratios:
  flat: 7/32 (21.8750%)
  parabola: 9/32 (28.1250%)
  deg3-6: 11/32 (34.3750%)
  bezier: 5/32 (15.6250%)
mint-tier2-heldout-ok 16
exit=0
```

## STEP 7 — validator
```
$ tools/refsim/.venv/bin/python tools/scenarios/validate_store.py
validate-store-ok
calibration_scenarios=2
heldout_scenarios=32
split_locked=true
exit=0
```

## STEP 9 — git status
```
## task/I-003-T3
 M data/scenarios/heldout/MANIFEST.json
 M data/scenarios/split-lock.json
 M docs/05_INFRA/I-003_scenario_store/JOURNAL.md
 M tools/refsim/tier2_refsim.py
 M tools/scenarios/mint_tier2_heldout.py
?? data/scenarios/heldout/HO-bezier-periodic-1.json
?? data/scenarios/heldout/HO-bezier-periodic-2.json
?? data/scenarios/heldout/HO-bezier-settle-1.json
?? data/scenarios/heldout/HO-bezier-settle-2.json
?? data/scenarios/heldout/HO-bezier-settle-3.json
?? data/scenarios/heldout/HO-poly-double-root-1.json
?? data/scenarios/heldout/HO-poly-periodic-1.json
?? data/scenarios/heldout/HO-poly-periodic-2.json
?? data/scenarios/heldout/HO-poly-quasichaotic-1.json
?? data/scenarios/heldout/HO-poly-quasichaotic-2.json
?? data/scenarios/heldout/HO-poly-quasichaotic-3.json
?? data/scenarios/heldout/HO-poly-quasichaotic-4.json
?? data/scenarios/heldout/HO-poly-settle-3.json
?? data/scenarios/heldout/HO-poly-settle-4.json
?? data/scenarios/heldout/HO-poly-settle-5.json
?? data/scenarios/heldout/HO-poly-settle-6.json
?? docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T3-R1.md
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
?? outbox/OUT_41.md
```

## ARTIFACTS
- tools/refsim/tier2_refsim.py (amplification admission, Bézier polish, discriminant)
- tools/scenarios/mint_tier2_heldout.py (I-003-T3-R1 mint)
- data/scenarios/heldout/HO-*.json (16 new Tier-2 fixtures)
- data/scenarios/heldout/MANIFEST.json (32 entries)
- data/scenarios/split-lock.json
- docs/05_INFRA/I-003_scenario_store/reports/TR_I-003-T3-R1.md

## BRANCH/COMMITS
```
79acd7b PACKET 41 apply: PREREG v1.1, I-003-T3-R1 dispatched.
0e361d0 I-003-T3-R1 CLAIM after PACKET 41 apply.
+ I-003-T3-R1 DONE commit (this OUT)
```

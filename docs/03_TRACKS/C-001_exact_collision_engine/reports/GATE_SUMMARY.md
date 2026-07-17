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

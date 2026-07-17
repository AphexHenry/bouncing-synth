# INFRASTRUCTURE_REGISTER — Bounce

```
doc_id:   INFRASTRUCTURE_REGISTER
layer:    program
audience: PM (write), Director (read)
status:   ACTIVE
parent:   PROJECT §13
```

| ID | capability | state | blocking | link |
|---|---|---|---|---|
| I-001 | Headless engine library skeleton (C++, CMake, unit-test harness) | VERIFIED | C-001, C-002, everything | docs/05_INFRA/I-001_core_skeleton/ |
| I-002 | High-precision reference simulator (Python/mpmath) + fixture generator | VERIFIED | all Design-A/C gates | docs/05_INFRA/I-002_refsim/ |
| I-003 | Scenario/fixture store with split-lock machinery | VERIFIED — corpus complete (32 locked) | Law 1 enforcement | docs/05_INFRA/I-003_scenario_store/ |
| I-004 | Gate runner + manifest writer | VERIFIED — COMPLETE for Phase 1; standing rule: gate manifests require engine_git_dirty=false | every gate call | docs/05_INFRA/I-004_gaterunner/ |
| I-005 | Event/pattern analysis harness | SPECCED | P1-D addendum timing basis | — |
| I-006 | JUCE build scaffold (VST3 target, pluginval in CI) | SPECCED | C-003, C-004, C-005 | — |
| I-007 | CI pipeline | SPECCED | open decision 1 (escalated) | — |
| I-008 | AV assessment harness `bounce-view` (C++/SDL2; D-5 default-lossless; AV-2 voice; S13 runtime Load; S14/S14.1 build stamp; Law-1 guard; S7/S9; L-21; S15 assessment camera) | T1–T7 VERIFIED (OUT_55–71); F7 = H1 pending Director rebuilt re-test; F8 OPEN pending Director look-and-listen | Director look-and-listen; blocks nothing gate-bearing | docs/05_INFRA/I-008_av_harness/ |

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
| I-004 | Gate runner + manifest writer | VERIFIED — COMPLETE for Phase 1 (T1, T2+T3; JRN-I004-8); standing rule: gate manifests require engine_git_dirty=false | every gate call | docs/05_INFRA/I-004_gaterunner/ |
| I-005 | Event/pattern analysis harness | SPECCED | P1-D addendum basis | — |
| I-006 | JUCE build scaffold (VST3 target, pluginval in CI) | SPECCED | C-003, C-004, C-005 | — |
| I-007 | CI pipeline | SPECCED | open decision 1 (escalated) | — |
| I-008 | AV assessment harness `bounce-view` | T1–T4 VERIFIED; OUT_62 (T5) RETURNED — uncommitted evidence + scene-identity substitution; T5-R1 IN FLIGHT (PACKET 63) incl. DECISIVE DIAGNOSTIC: possible engine-side early stream end at e=1 on quartic/bezier confined scenes (~981 / ~38 events reported) — if confirmed, escalates to C-001 + decision 5 | Director re-assessment after R1; the diagnostic may become gate-relevant | docs/05_INFRA/I-008_av_harness/ |

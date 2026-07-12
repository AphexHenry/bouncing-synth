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
| I-001 | Headless engine library skeleton (C++, CMake, unit-test harness) | VERIFIED (JRN-I001-14; evidence OUT_8 + OUT_11) | C-001, C-002, everything | docs/05_INFRA/I-001_core_skeleton/ |
| I-002 | High-precision reference simulator (Python/mpmath) + fixture generator | VERIFIED (JRN-I002-25; OUT_13–OUT_19) | all Design-A/C gates | docs/05_INFRA/I-002_refsim/ |
| I-003 | Scenario/fixture store with split-lock machinery | BRIEFED (T1, T2 VERIFIED; T3 BLOCKED → T3-R1 dispatched under prereg v1.1, PACKET 41) | Law 1 enforcement, all gates | docs/05_INFRA/I-003_scenario_store/ |
| I-004 | Gate runner + manifest writer (PROJECT §7, §8) | BRIEFED — T1 VERIFIED (JRN-I004-4) | every gate call | docs/05_INFRA/I-004_gaterunner/ — T2+T3 batched (PACKET 42) |
| I-005 | Event/pattern analysis harness (drift measurement, event-sequence diff) | SPECCED | Designs B/C; P1-D addendum basis | — |
| I-006 | JUCE build scaffold (VST3 target, pluginval in CI) | SPECCED | C-003, C-004, C-005 | — |
| I-007 | CI pipeline (clean-checkout build + gate execution) | SPECCED | L-02 analog, Phase gates; open decision 1 (escalated) | — |

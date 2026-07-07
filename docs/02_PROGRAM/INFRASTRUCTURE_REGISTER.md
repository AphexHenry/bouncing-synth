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
| I-001 | Headless engine library skeleton (C++, CMake, unit-test harness) | SPECCED | C-001, C-002, everything | — |
| I-002 | High-precision reference simulator (Python/mpmath) + fixture generator | SPECCED | all Design-A/C gates | — |
| I-003 | Scenario/fixture store with split-lock machinery | SPECCED | Law 1 enforcement, all gates | — |
| I-004 | Gate runner + manifest writer (PROJECT §7, §8) | SPECCED | every gate call | — |
| I-005 | Event/pattern analysis harness (drift measurement, event-sequence diff) | SPECCED | Designs B/C | — |
| I-006 | JUCE build scaffold (VST3 target, pluginval in CI) | SPECCED | C-003, C-004, C-005 | — |
| I-007 | CI pipeline (clean-checkout build + gate execution) | SPECCED | L-02 analog, Phase gates | — |

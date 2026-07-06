# COMPONENT_REGISTER — Bounce

```
doc_id:   COMPONENT_REGISTER
layer:    program
audience: PM (write), Director (read)
status:   ACTIVE
parent:   PROJECT §2
```

| C-id | name | one-line claim | layer | state | named baseline | outcome + report link |
|---|---|---|---|---|---|---|
| C-001 | Exact collision engine | Closed-form ballistic flight + analytic collision-time root-solve on the true curve yields bit-deterministic, drift-free event sequences in real time | engine | IDEA | naive fixed-timestep + polyline engine (PROJECT §5 Law 7) | — |
| C-002 | Curve library | A family of exactly-defined user-shapeable curves (with derivatives/normals) the engine solves against | curve | IDEA | tbd at THESIS | — |
| C-003 | Event→MIDI mapping engine | User-configurable collision→(pitch, velocity, channel) mapping emitted sample-accurately | mapping | IDEA | tbd at THESIS | — |
| C-004 | Plugin shell & visuals | JUCE VST3 shell with real-time visualization and host parameter/automation plumbing | ui | IDEA | tbd at THESIS | — |
| C-005 | Preset & state system | Full serialization of curve+balls+physics+mapping with replay-identity guarantee | io | IDEA | tbd at THESIS | — |
| C-000 | Phase-0 scoping | Phase 0 delivers a Director-approvable plan: prior-art landscape, numerics decision memo, architecture plan, prioritized component slate (PROJECT §3 a–d) | infra-facing | SPECCED | n/a — scoping gate is Director approval, not numeric (P2 §8) | — |

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
| C-001 | Exact collision engine | Closed-form ballistic flight + analytic collision-time root-solve on the true curve yields bit-deterministic, drift-free event sequences in real time | engine | BRIEFED | naive fixed-timestep + polyline engine (PROJECT §5 Law 7) | T1 VERIFIED (JRN-C001-5); T2 VERIFIED (JRN-C001-9); T3 VERIFIED (JRN-C001-13) — docs/03_TRACKS/C-001_exact_collision_engine/reports/ |
| C-002 | Curve library | A family of exactly-defined user-shapeable curves (with derivatives/normals) the engine solves against | curve | BRIEFED | direct per-query eval without compilation at matched compile+query cost (DELIVERABLE_D) | T1 VERIFIED (JRN-C002-5); T2 VERIFIED (JRN-C002-9) — docs/03_TRACKS/C-002_curve_library/reports/ |
| C-003 | Event→MIDI mapping engine | User-configurable collision→(pitch, velocity, channel) mapping emitted sample-accurately | mapping | IDEA | tbd at THESIS | — |
| C-004 | Plugin shell & visuals | JUCE VST3 shell with real-time visualization and host parameter/automation plumbing | ui | IDEA | tbd at THESIS | — |
| C-005 | Preset & state system | Full serialization of curve+balls+physics+mapping with replay-identity guarantee | io | IDEA | tbd at THESIS | — |
| C-000 | Phase-0 scoping | Phase 0 delivers a Director-approvable plan: prior-art landscape, numerics decision memo, architecture plan, prioritized component slate (PROJECT §3 a–d) | infra-facing | CLOSED | n/a — scoping gate is Director approval, not numeric (P2 §8) | Phase-0 gate PASSED (Director, 2026-07-07); deliverables (a)–(d) + rulings R1–R3 approved — 03_TRACKS/C-000_scoping/reports/, JRN-C000-18 |

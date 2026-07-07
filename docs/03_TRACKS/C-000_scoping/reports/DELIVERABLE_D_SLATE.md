# DELIVERABLE (d) — Prioritized component slate with acceptance-criteria sketches

```
doc_id:   C-000-DELIV-D
layer:    track
audience: Director (Phase-0 gate), PM
status:   DRAFT (pending Phase-0 gate approval)
parent:   C-000-BRIEF / PROJECT §3(d)
```

Ordering principle (Law 8 / L-08): the falsifiable core bet first. If C-001/C-002 fail their
gates, everything downstream is decoration; nothing below the line starts until the bet survives.

## Phase 1 — the bet

**1. C-002 Curve library** (curve) — polynomial (deg ≤ 8) + piecewise Bézier (quadratic/cubic,
declared C1) per DELIVERABLE_B §2; curve compilation to pinned coefficient sets; validator
rejecting undeclared kinks. Acceptance sketch: evaluation/derivative/normal values match CAS
fixtures exactly at Tier-1 points; validator acceptance/rejection table over a pre-registered
spec corpus; zero allocation after compile. Baseline (named at THESIS): direct per-query
evaluation without compilation, matched accuracy at compile+query cost.

**2. C-001 Exact collision engine** (engine) — ballistic arcs + VCA root isolation + fixed
refinement (DELIVERABLE_B §3), TB-1 ordering, G-1/S-1 rules. Acceptance sketch, tied to PROJECT
§8 gates: `determinism_repro` — bit-identical CollisionEvent sequences across ≥ 100 repeated
runs and across audio block sizes, per platform; `loop_stability` — zero interval-sequence
drift over ≥ 10⁴ periods on periodic Tier-1 fixtures; reference agreement — event times within
pre-registered tolerance of the mpmath oracle on calibration scenarios, held-out scenarios run
only via the gate runner; `realtime_budget` — p99.9 per-event solve cost within the budget the
prereg sets, on worst-case coverage cells (Law 7 §9 table); baseline comparison — beats the
naive fixed-timestep + polyline engine on accuracy at matched compute. Kill condition: baseline
matches accuracy within tolerance at equal cost, or the budget is unmeetable at target scene
sizes.

Infra in support (briefed at Phase-1 entry, in order): I-001 core skeleton → I-002 refsim +
fixtures → I-003 scenario store + split-lock → I-004 gate runner + manifests → I-005 analysis
harness → I-007 CI (clean-checkout, both platforms). C-002 and C-001 theses are written together
at Phase-1 entry; C-002 tasks lead by one packet so the engine always has real curves to solve.

## Phase 2 — the instrument (each re-gated by its own thesis; starts only after Phase-1 gate)

**3. C-003 Event→MIDI mapping engine** (mapping) — collision → (pitch, velocity, channel) with
user-configurable mapping as a first-class object (DELIVERABLE_A §3.5: the oldest complaint in
the lineage is a hardwired mapping). Sketch: `midi_timing` — NoteEvent sample placement error
≤ 1 sample against exact event times over the scenario corpus; mapping-config roundtrip; no
audio-thread allocation.

**4. C-004 Plugin shell & visuals** (ui; needs I-006 JUCE scaffold) — thin shell per
DELIVERABLE_C §1/§5. Sketch: pluginval at the strictness level pinned in the I-006 brief, on
both platforms; determinism-boundary test — event stream bit-identical with UI hidden vs
visible vs headless; visual latency within budget set at THESIS.

**5. C-005 Preset & state system** (io) — full serialization of curve+balls+physics+mapping.
Sketch: `preset_roundtrip` — save/load → bit-identical event sequence; versioned schema with
explicit engine-version pin (PROJECT §9c: presets replay per engine version, migrations are
explicit).

## Phase 3 — release (gate: Director; GPLv3 license file, source hosting, binary artifacts,
docs) — planned after Phase-2 gates; no component work here, packaging and publication only.

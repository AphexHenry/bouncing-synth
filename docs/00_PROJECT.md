# 00_PROJECT — Bounce  (the domain module)

```
doc_id:   PROJECT
layer:    project (root of all domain-specific content)
audience: ALL (Director, PM, Agents) — read after 00_STATE, before/with P0
status:   ACTIVE v0.1
parent:   P0
```

**Program framing note (Director decision, genesis).** Bounce is a **product program**, not a
research program. The framework is instantiated in its engineering-verification reading: a *track*
is a product component with a numeric acceptance gate; *studies* are verification studies against
mathematical reference solutions; the *baseline* is the naive implementation the exact engine must
beat. Nothing below weakens a Law — each is bound to its product meaning.

---

## 1. Identity & purpose

**Program name:** Bounce
**Purpose:** Build a free and open-source instrument in which balls bounce on a user-shaped curved
line under exact, deterministic 2D physics, generating rhythmic/melodic patterns emitted as MIDI —
delivered as a JUCE plugin (VST3) with a visual interface, computing everything live.
**Success is:** a released FOSS plugin where (a) any preset replays bit-identically, (b) a periodic
orbit stays phase-locked indefinitely (no drift), and (c) collision-to-MIDI timing is
sample-accurate — all under real-time audio-thread budget.
**Core technical bet:** collisions are computed **analytically** against the mathematical curve
equation (closed-form ballistic arcs, collision instants found by root-solving on the true curve),
never against a quantized/polyline approximation of it. Simulation is on-the-fly (real-time), yet
exact: chaotic trajectories are computed live; periodic ones repeat forever without shift.
**Out of scope until Phase 1 gate passes:** JUCE plugin shell, visuals, MIDI I/O, preset UX.
**Out of scope until Phase 2 gate passes:** release, distribution, plugin-format ports beyond VST3.

---

## 2. Unit of study & vocabulary

| Framework generic | This program |
|---|---|
| a **track** studies … | a **component** of the product, carried from spec to a passed acceptance gate |
| track-id prefix | `C-` |
| the register of all tracks (`02_PROGRAM/…`) | `COMPONENT_REGISTER.md` |
| the Step-0 gate document (P1 §5) | `COMPONENT_THESIS.md` (the component's acceptance spec: claim, interface, primary acceptance criterion, named baseline) |
| register row schema (P1 §9) | `\| C-id \| name \| one-line claim \| layer \| state \| named baseline \| outcome \|` |
| `layer` domain enum | layer ∈ {engine, curve, mapping, ui, io, infra-facing} |

Candidate components at kickoff (IDEA rows in the register):
- **C-001 Exact collision engine** — ballistic closed-form flight + analytic collision-time
  root-solve against the curve equation; deterministic event sequencing.
- **C-002 Curve library** — the family of user-shapeable curves with exact mathematical
  definitions (and derivatives/normals) the engine solves against.
- **C-003 Event→MIDI mapping engine** — user-configurable mapping of collision events (position on
  curve, impact speed, ball identity, …) to pitch/velocity/channel; sample-accurate emission.
- **C-004 Plugin shell & visuals** — JUCE VST3 host integration, real-time rendering of balls/curve,
  parameter/automation plumbing.
- **C-005 Preset & state system** — full serialization of curve + balls + physics + mapping;
  the replay-identity guarantee lives here jointly with C-001.

---

## 3. Staging & gates

- **Phase 0 — Scoping** *(gate: Director-approved plan)* — deliver: (a) prior-art landscape of
  physics sequencers/instruments (what exists, what Bounce does differently); (b) the numerics
  decision memo: curve representation, root-solving strategy, floating-point determinism plan
  (cross-platform), tie-breaking rules for simultaneous/grazing collisions; (c) architecture plan
  (headless core library + thin JUCE shell); (d) prioritized component slate with acceptance
  criteria sketched.
- **Phase 1 — Exact simulation core** *(gate: numeric, per §10)* — headless C++ engine (C-001,
  C-002) passing: determinism reproduction, loop-stability (zero phase drift), accuracy vs
  high-precision reference, real-time budget.
- **Phase 2 — Instrument** *(gate: numeric + acceptance, per §10)* — C-003, C-004, C-005: MIDI
  timing sample-accurate, pluginval clean, CPU budget met, preset replay identity end-to-end.
- **Phase 3 — Release** *(gate: Director approval)* — FOSS packaging (license per §11), builds,
  docs, source publication. *Out of scope until Phase 2 gate passes.*

**Selection/scoping gate (P2 §8):** the Phase-0 deliverables (a)–(d) above, approved by the
Director, exit Phase 0.

---

## 4. Study designs

**Design A — Reference-agreement verification:** unit of analysis = one simulated scenario
(curve + initial state + params) run to a horizon; the engine's event sequence (collision times,
positions, impact speeds) is compared to a Tier-1/Tier-2 reference (§5). Held-out means: a locked
set of scenarios *never used during development* of the component. Primary criterion: max
event-time / event-position error ≤ pre-registered tolerance.

**Design B — Invariance verification:** unit of analysis = one scenario replayed under a varied
nuisance condition (buffer size, block boundary phase, run repetition, platform). Held-out over
nuisance conditions not tuned against. Primary criterion: bit-identical event sequence (or ≤
pre-registered tolerance where bit-identity is provably unattainable, e.g. cross-platform libm).

**Design C — Long-horizon stability:** unit of analysis = one periodic orbit; the engine runs it
for a pre-registered long horizon. Held-out over orbit families not used to tune numerics. Primary
criterion: phase drift per period ≤ pre-registered bound (target: exactly 0 shift by construction).

**Design D — Budget verification:** unit of analysis = one scenario class at a ball-count/curve
complexity level; primary criterion: worst-case per-audio-block compute ≤ pre-registered budget at
reference sample rates. Held-out over scenario classes not profiled during optimization.

Every `PREREGISTRATION.md` names one of A–D. A study fitting none needs a new design added here
first (Director approval, P0 §7).

---

## 5. Law instantiations

- **Law 1 — the split.** For each component, the verification scenario set is split: a
  **calibration set** (free use while developing/tuning numerics) and a **held-out set** (locked
  scenario specs + seeds, run only at gate time). Split is over *scenarios* (curve family × initial
  state × parameter regime), target held-out fraction ~40%, stratified by curve family and by
  dynamical regime (periodic / quasi-periodic / chaotic). "Peeking before lock" concretely means:
  running any held-out scenario against the component under development, or adjusting numerics
  after seeing a held-out result.
- **Law 5 — validated inputs only.** No gate is run on reference values that failed their own
  quality gate. Quality gates here: (a) the high-precision reference simulator must pass its
  self-convergence check (result invariant under precision/step refinement, §8 `reference_converged`);
  (b) analytic closed-form fixtures must be symbolically verified (curve/ballistic intersection
  solved exactly, e.g. via CAS) before use.
- **Law 6 — provenance tiers.** Tier 1 = closed-form analytic solutions (exact collision instants
  derivable symbolically — flat line, parabola-on-parabola cases). Tier 2 = high-precision offline
  reference simulation (arbitrary-precision arithmetic, converged). Tier 3 = engine
  self-consistency (same engine, different block sizes/orderings). Tier 4 = eyeballed/visual
  plausibility (never gate-bearing). Tier fixed at fixture creation, never at analysis.
- **Law 7 — the matched-complexity baseline.** The named baseline for the exact engine is a
  **naive fixed-timestep engine with polyline-sampled curve** at matched compute budget. The exact
  engine must beat it by the pre-registered margin on drift/accuracy at equal or lower cost. The
  baseline is named in each `COMPONENT_THESIS.md`, never discovered at gate time.

---

## 6. Canonical schema(s)

**Schema `CurveSpec`:** `curve_id: string`, `family: enum{polynomial, piecewise-bezier, catenary,
sine, custom-analytic}`, `params: {name: double}` (SI where dimensional), `domain: [x_min, x_max] m`,
`schema_version`. Validators reject: non-finite params, empty domain, curves without C1 continuity
declaration (kinks must be declared as vertices with their own collision rule).

**Schema `BallState`:** `ball_id: int`, `pos: {x,y} m`, `vel: {vx,vy} m/s`, `radius: m > 0`,
`restitution: (0,1]`, `schema_version`. Validators reject non-finite values, radius ≤ 0,
restitution outside (0,1].

**Schema `CollisionEvent`:** `t: double s (exact event time)`, `ball_id`, `s: curve parameter at
contact`, `impact_speed: m/s ≥ 0`, `normal: unit vector`, `seq: monotone int` (deterministic
tie-break order), `schema_version`. Validators reject non-monotone `t` within `seq` order,
non-unit normals (tol 1e-12), negative impact speed.

**Schema `NoteEvent`:** `sample_offset: int ≥ 0 (within block)`, `pitch: int 0–127`,
`velocity: int 1–127`, `channel: int 1–16`, `source_event: seq ref`, `schema_version`.

**Schema `Preset`:** `schema_version`, `engine_version`, `CurveSpec`, `[BallState] (initial)`,
`physics: {gravity m/s², global params}`, `mapping: MappingSpec (user-configured event→MIDI rules)`.
Round-trip test for all schemas: serialize→deserialize→bit-identical on a property-generated set.
Schema changes are PM-only, versioned; every record carries `schema_version`.

---

## 7. Reproducibility / determinism surface

**Determinism surface:** the simulation engine itself — closed-form ballistic propagation between
events + analytic collision-time root-solving against the exact curve equation, with a fixed
root-solver spec (method, tolerance, max iterations) and a deterministic tie-breaking rule for
simultaneous events. No RNG anywhere in the engine; any future stochastic feature must be
explicitly seeded and the seed pinned.
**Pinned in config + manifest:** engine version (git commit), `CurveSpec` (full params), initial
`[BallState]`, gravity and all physics params, root-solver spec, tie-break rule version, FP
environment declaration (double precision, FMA policy, compiler flags affecting FP), sample rate
and block size for MIDI emission tests.
**Cross-implementation / reproduction fixture:** an independent arbitrary-precision Python
reference simulator (mpmath) used only for gate verification and red-team item 8; agreement
tolerance pre-registered per study (Tier-2 fixtures per §5).

---

## 8. Domain gate types

| Gate | Checks | Threshold from |
|---|---|---|
| `determinism_repro` | same preset ⇒ bit-identical `CollisionEvent` sequence across runs and block sizes | exact (0 diff) |
| `loop_stability` | periodic orbit phase drift per period ≤ bound over pre-registered horizon | prereg (target 0) |
| `reference_agreement` | event times/positions vs Tier-1/2 reference within tolerance | prereg |
| `reference_converged` | Tier-2 reference invariant under precision refinement | config |
| `realtime_budget` | worst-case per-block engine+mapping compute ≤ budget at 44.1/48 kHz | prereg |
| `midi_timing` | NoteEvent sample offsets exactly match event times (sample-accurate) | exact |
| `pluginval_pass` | pluginval strictness level ≥ configured level, zero failures | config |
| `preset_roundtrip` | Preset serialize→load ⇒ identical replay (`determinism_repro` across save/load) | exact |

No force flag for any of them (P0 Law 2).

---

## 9. Bias safeguards & red-team specifics

- **L-01 analog (unvalidated inputs):** gating against an unconverged or unverified reference
  fixture. Killed by `reference_converged` + symbolic verification of Tier-1 fixtures (§5 Law 5).
- **L-02 analog (reachability/gates):** "works on my machine" builds — CI must build and run gates
  from a clean checkout; missing toolchain/pluginval is a blocking gate, not a warning.
- **L-03 analog (single-split fragility):** numerics tuned on one curve family that fail on
  another. Killed by leave-one-curve-family-out sweeps and regime stratification (§5 Law 1).
- **L-04 analog (convenient joins / leakage):** developing against held-out scenarios "just to
  check". Killed by locked scenario files + split-lock gate; held-out runs only via the gate
  harness, logged.
- **L-05 analog (means hide dispersion):** average timing error hiding rare large misses. All gates
  report **worst-case** (max error, max drift), never means; distributions attached.
- **L-06 analog (multiplicity):** one primary acceptance criterion per component study; all other
  metrics exploratory.
- **L-07 analog (coverage artifacts):** verification concentrated in easy regimes. Per-study
  coverage table over {curve family × regime × ball count} is mandatory; empty cells declared.
- **L-08 analog (selection needs a gate):** Phase 0 scoping (§3) — numerics/architecture chosen
  from the landscape memo, Director-approved, before engine code.
- **Domain-only safeguards:** (a) *grazing/tangential collisions* — root-solver degeneracy near
  tangency is a named risk; every engine study must include grazing cases in its scenario set.
  (b) *FP-determinism across platforms* — cross-platform bit-identity may be limited by libm;
  where a study claims it, the FP environment must be pinned and tested per platform, else the
  claim is scoped to one platform explicitly. (c) *event ordering under simultaneity* — tie-break
  rule is versioned; changing it is an engine version bump.

**Red-team tier/leave-one-out specifics (P2 §6 items 4–5):** the "most-represented unit" here is
the dominant curve family in the scenario set (leave it out and re-verify); the "trusted-tier-only"
subset is Tier-1 analytic fixtures only.

---

## 10. Standing decision gate

| Criterion | Threshold |
|---|---|
| Held-out error, primary metric (event-time/position error, drift, or timing jitter per design A–D) | ≤ pre-registered tolerance (named per study, never post-hoc) |
| Margin over matched-complexity baseline (naive fixed-timestep engine, Law 7) | ≥ pre-registered margin at matched compute |
| Calibration-vs-held-out gap | ≤ pre-registered bound |
| Data sufficiency | ≥ pre-registered minimum scenarios per held-out cell (curve family × regime) |
| Input validation | `reference_converged` + Tier-1 symbolic verification PASSED for this study's fixtures |
| Red-team | all 8 items pass (P2 §6) |

---

## 11. Director-gated items

- **Spend ceilings:** none anticipated — program targets zero-spend (FOSS toolchain, free CI). Any
  paid service (code signing, CI minutes, plugin marketplace) requires Director approval first.
- **Credentials / accounts:** repository hosting and CI accounts are Director-created; no secrets
  expected in the loop.
- **Licensing / release:** the product is **free and open source** (Director decision, genesis).
  Concrete license choice (GPLv3 is the natural fit with JUCE's GPL option — to be confirmed),
  source publication, binary releases, and any trademark/branding use are Director-gated.
- **Human-subjects:** none planned. Any future user testing / perceptual study is Director-gated
  before design.

---

## 12. Domain lessons

*(No runtime lessons yet at kickoff. New program lessons begin at L-09 in `02_PROGRAM/LESSONS.md`.)*

---

## 13. Infrastructure catalogue (seed)

| ID | Capability | Blocks |
|---|---|---|
| `I-001` | Headless engine library skeleton (C++, CMake, unit-test harness) | C-001, C-002, everything |
| `I-002` | High-precision reference simulator (Python/mpmath) + fixture generator | all Design-A/C gates |
| `I-003` | Scenario/fixture store with split-lock machinery (calibration vs held-out) | Law 1 enforcement, all gates |
| `I-004` | Gate runner + manifest writer (runs §8 gates, pins §7 surface) | every gate call |
| `I-005` | Event/pattern analysis harness (drift measurement, event-sequence diff) | Designs B/C |
| `I-006` | JUCE build scaffold (VST3 target, pluginval in CI) | C-003, C-004, C-005 |
| `I-007` | CI pipeline (clean-checkout build + gate execution) | L-02 analog, Phase gates |

---

## Slot Index (completeness check)

| Framework file · location | Slot | This file § | Filled? |
|---|---|---|---|
| P0 §1 Purpose | program purpose & staging | §1, §3 | ☑ |
| P0 §3 repo map | register name, track-id prefix, thesis doc name | §2 | ☑ |
| P0 §4.1 lifecycle | track noun, scoping-vs-numeric gate | §2, §3 | ☑ |
| P0 §5 Law 1 | calibration/held-out split semantics | §5 | ☑ |
| P0 §5 Law 5 | validated-input quality gates | §5, §8, §9 | ☑ |
| P0 §5 Law 6 | provenance tiers | §5 | ☑ |
| P0 §5 Law 7 | matched-complexity baseline | §5 | ☑ |
| P1 §5 | Step-0 thesis document name & fields | §2, §4 | ☑ |
| P1 §6 | prereg `DESIGN:` options | §4 | ☑ |
| P1 §9 | register row schema / enum | §2 | ☑ |
| P2 §1 | study designs | §4 | ☑ |
| P2 §4 | bias-safeguard domain analogs | §9 | ☑ |
| P2 §6 | red-team leave-one-out / tier specifics | §9 | ☑ |
| P2 §7 | standing decision gate metrics | §10 | ☑ |
| P2 §8 | scoping/selection gate deliverables | §3 | ☑ |
| P3 §2 | canonical schema(s) | §6 | ☑ |
| P3 §4 | domain gate types | §8 | ☑ |
| P3 §5 | determinism surface | §7 | ☑ |
| P4 §2.9 | Director-gated items | §11 | ☑ |
| DIRECTORS_MANUAL §3 | Director-gated items | §11 | ☑ |
| LESSONS_CORE | domain analogs | §9, §12 | ☑ |

## Changelog
- v0.1 — Bounce issue. Framework instantiated in product/engineering-verification reading per
  Director decision at genesis (2026-07-06): name "Bounce"; real-time exact simulation on the
  mathematical curve equation (no quantized approximation); deterministic, drift-free periodic
  orbits; user-decided event→MIDI mapping; JUCE VST3 target; free and open source. Concrete
  license choice (§11) left for Director confirmation.

# BRIEF — I-008 AV assessment harness (bounce-view)

```
doc_id:   I-008-BRIEF
layer:    infra
audience: composer-agent, PM, Director (RUN section consumer)
status:   ACTIVE
parent:   INFRASTRUCTURE_REGISTER I-008 / Director direction D-4 step 2 (JRN-C001-91) /
          DELIVERABLE_B §1 (closed-form arcs), §3 (G-1/S-1)
```

## Objective
Stand up `tools/bounce-view`: a minimal native C++/SDL2 application linked against
`bounce_core` that lets the Director SEE the balls bounce on the curve and HEAR a blip per
collision. It is an assessment instrument, not a product component: nothing here is
gate-bearing, nothing here is reused by C-003/C-004/C-005, and no C-001 claim gains or
loses evidence through it. The Director's live assessment is the purpose and is NOT an
acceptance criterion (P6 §4.2).

## Standing rules (binding on every I-008 task)
- S1 TARGET & ISOLATION: separate CMake target `bounce-view` under `tools/bounce-view/`;
  links `bounce_core` and SDL2; C++20. ZERO changes under `src/core/` and `config/`
  (FP-determinism flags untouched). The harness computes no physics: it consumes engine
  state and CollisionEvents only.
- S2 RENDERING: single window (default 800×600). The curve is drawn by DISPLAY-ONLY
  sampling of the compiled curve (agent's density choice); display sampling has zero
  bearing on physics — collisions remain analytic in the core. Balls are drawn at
  closed-form arc positions x(t), y(t) from current arc state; all balls of the scenario
  are rendered. Pacing by wall clock at the display refresh (no fixed-timestep physics
  anywhere).
- S3 AUDIO (assessment mapping AV-1, versioned here; C-003 owns the product mapping and
  inherits nothing from AV-1): per collision, one blip — 60 ms sine, 5 ms linear
  attack/release; frequency f = 220 · 2^(2·u) Hz where u ∈ [0,1] is the contact parameter
  normalized over the curve's declared domain; amplitude a = 0.3 · min(1, |v_n|/10) with
  v_n the normal impact speed. Settled balls (S-1) emit nothing.
- S4 CONTROLS: agent's design; must include quit and restart-scenario. No text UI required.
- S5 SELFTEST: `bounce-view --selftest <scenario.json> [--frames k]` runs headless (SDL
  dummy video/audio drivers), executes the scenario to settle or a 200-event cap, prints
  one line per collision `seq ball_id t s f_hz amp`, then a final line
  `selftest ok events=<N>`, writes k PPM frames at evenly spaced simulated times under the
  invoker-specified `--outdir`, and exits 0. The blip log is a pure deterministic function
  of the event stream.
- S6 LAW-1 GUARD: before any file is opened, any input path containing
  `data/scenarios/heldout/` is refused with the exact message
  `LAW1: held-out scenario refused` and exit code 2. The guard precedes the file-existence
  check (a refusal must be provable on a nonexistent path).
- S7 LANGUAGE: no real-time claim is made or implied anywhere (TR, code comments, journal)
  — P1-D is deferred (PREREGISTRATION §4) and this harness produces no timing evidence.

## Dependency & license record (adoption note)
- SDL2 (zlib license — GPLv3-compatible) — assessment tooling only, never shipped in the
  plugin; system-installed (Homebrew), not vendored. Recorded here at adoption.

## Workstream plan
- **T1 (this packet):** the harness per S1–S7, plus the two C-001-T17 evidentiary repairs
  riding this dispatch (steps 4–5).
- Later tasks only by new brief sections (e.g. scenario hot-reload, camera), Director-pulled.

## TASK I-008-T1: bounce-view v1 + T17 repairs A/B
depends_on: OUT_54 C-001-T17 (AMEND + RETURN scoped; substantive fix evidence on file);
Director direction D-4 step 2; I-001 (VERIFIED); streaming event emission (T14 lineage)
objective: A running bounce-view meeting S1–S7 with selftest, guard, and frame evidence;
plus repair-A (c3-v2) and repair-B (c6/L-15) closing the OUT_54 ledger.
branch: `task/I-008-T1` from `task/C-001-T17` tip (stacked, JRN-I002-6).
Steps and acceptance criteria are carried verbatim in the dispatching packet (PACKET 55).

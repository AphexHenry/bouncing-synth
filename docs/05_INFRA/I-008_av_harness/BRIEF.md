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

## Amendments (PACKET 58) — assessment-feedback improvements

S2.1 SETTLED-BALL PERSISTENCE (amends S2): a ball whose stream has ended by S-1 settle
remains rendered at its settle position on the curve, visually distinct from an active
ball (agent's design), until scenario end or restart. A ball whose stream ends by domain
exit leaves the window naturally; only SETTLED balls persist.

S3 v2 — ASSESSMENT VOICE AV-2 (replaces AV-1's waveform; pitch mapping unchanged): per
collision, one voice with 2 ms linear attack and exponential decay:
y(τ) = a · e^(−τ/τ_d) · [sin(2πfτ) + 0.5k·sin(2π·2fτ) + 0.25k·sin(2π·3fτ)] / (1 + 0.75k),
where f = 220 · 2^(2u) Hz (u = contact parameter normalized over the curve's declared
domain, as AV-1), k = min(1, |v_n|/10), a = 0.3 · k' with k' = min(1, |v_n|/10),
τ_d = 80 ms · (0.5 + 0.5k). Overlapping voices sum; the master output is clamped to
[−1, 1] after a 0.5 master gain. Settled balls emit nothing. AV-2 is assessment-only and
versioned here; C-003 inherits nothing.

S5.1 SELFTEST LINE FORMAT v2 (amends S5): the per-collision line becomes
`seq ball_id t s f_hz amp tau_ms k` — the voice parameters are a pure deterministic
function of the event stream.

S8 PERFORMANCE INSTRUMENTATION: `bounce-view --perf-seconds <n> <scenario.json>` runs the
INTERACTIVE window (not the dummy driver) for n seconds, then prints to stdout: the
display mode (resolution + refresh Hz), total frames, and frame-time mean / p50 / p95 /
max in ms, plus one line per render-loop subsystem (engine query, curve draw, ball draw,
present, audio) with its mean ms/frame — and exits 0. The measurement is part of the
committed harness, not scaffolding.

## Amendments (PACKET 59) — D-5 default-lossless playback + measurand fix

S8 v2 — MEASURAND DEFINITION (amends S8): frame_ms is the interval between successive
returns from the present call, measured on a monotonic clock, first frame excluded. The
same definition applies in every mode and code path, so any two perf pastes are
comparable. Per-subsystem lines remain mean ms/frame of work time, labeled as such.

S9 — LANGUAGE RULE (loop stability): no loop-stability, drift, or long-horizon claim is
made or implied by any harness run or log (P1-C pending). Harness logs are presentation
evidence only. This joins S7 (no real-time claims) as a standing affirmation in every
I-008 TR.

S10 — RESTITUTION OVERRIDE (D-5, Director direction of record): the engine and scenario
files are never modified; the override applies where the harness constructs its run.
- INTERACTIVE playback default: effective restitution forced to 1 for all balls (infinite
  bounce). On scenario load, stdout prints one line naming the effective restitution and
  its source, e.g. `restitution: override=1 (scenario values ignored; use
  --scenario-restitution to respect file)`.
- Flags (mutually exclusive; both modes accept them): `--scenario-restitution` respects
  the scenario file; `--restitution <r>` with r in (0,1] applies a uniform override.
  Conflicting flags: error message + nonzero exit.
- EVIDENCE modes (--selftest, --perf-seconds) default SCENARIO-FAITHFUL so logs remain
  comparable across tasks; the same flags opt in explicitly, and the effective-restitution
  line is always printed.
- Open-ended streams: interactive playback sustains e=1 streams indefinitely (rolling
  event consumption); selftest keeps its 200-event default cap with `--max-events <n>`
  available.

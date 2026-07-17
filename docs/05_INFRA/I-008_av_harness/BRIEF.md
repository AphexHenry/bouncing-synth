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

## Amendments (PACKET 61) — assessment scene library

S11 — ASSESSMENT SCENES: a library of scenario files whose only purpose is looking and
listening; they carry no evidence role and are never comparison inputs.
- Location: `tools/bounce-view/scenarios/*.json` — presentation assets of the harness.
  data/scenarios/** (heldout, calibration) remains frozen and is never the home of
  assessment scenes.
- Form: valid schema_version 1 scenario JSONs with `reference_events: []` (loadable per
  the graze-fixture precedent) and `verification.method: "none-assessment-only"`;
  provenance notes them hand-authored for assessment.
- Design constraints per scene: under the interactive default (e=1 override, D-5) the
  ball(s) remain within the curve's domain and the stream sustains at least 60 s of
  SIMULATED time within at most 2000 events — a constructive design target the author
  iterates toward, evidenced by the scene's own override selftest paste (t_last ≥ 60 at
  events ≤ 2000). Geometry confines the motion (bowls/wells) rather than relying on
  lucky parameters.
- Initial set (parameters are the author's choice within the constraints):
  A1 `bowl-parabola` — single ball inside an upward parabola bowl.
  A2 `twowell-poly4` — single ball over a degree-4 "W" polynomial with two wells.
  A3 `bezier-landscape` — single ball on a bezier hill-and-valley segment.
  A4 `trio-parabola` — three balls in one parabola bowl (polyphony showcase; staggered
  initial conditions so contacts interleave).
- The TR RUN section leads with these scenes; calibration fixtures remain listed as
  secondary examples.

## Amendments (PACKET 62) — dynamic camera + scene library v2

S12 — DYNAMIC CAMERA: the viewport must AT ALL TIMES contain (a) every active ball and
(b) the curve segment in a neighborhood of each ball, with sensible margins; framing the
curve's full domain is explicitly NOT required and is wrong for disparate-scale curves
(CF-E2b spans y ∈ [0, 5e6]). Pan and zoom follow the balls smoothly (agent's design:
smoothed tracking, easing, hysteresis — no hard jumps). Settled balls count as active for
framing. FRAME SELF-CHECK: every dumped frame prints one line per ball
`frame_check ball_id=<i> ball_px=(x,y) in_viewport=<true|false>` plus one line
`frame_check curve_pixels=<N>` counting curve-colored pixels actually rasterized in the
viewport — the renderer reports what it drew, making camera correctness paste-provable.

S11 v2 — SCENE LIBRARY (replaces the S11 design-target clause): each scene's sustain
proof is the CAP-REACHED run: under `--restitution 1 --max-events 2000` the selftest must
end with `events=2000` — derivation: with e=1 and confining geometry the stream cannot
end before the cap; ending early ⇔ domain exit ⇔ the scene is not confined. Additional
design targets (constructive; the author iterates parameters until met, evidenced by the
run's own paste): global mean inter-event interval t_last/events ≤ 2.0 s (keeps the scene
musically alive); for the polyphony scene, every ball_id count ≥ 200 within the
2000-event run. The four scenes (A1 bowl-parabola, A2 twowell-poly4, A3 bezier-landscape,
A4 trio-parabola) are REAUTHORED to these targets; names and files are reused in place.

## Amendments (PACKET 69) — build stamp + Load feature + deep display-truth checks

S13 — LOAD WITHOUT RESTART (Director request): the interactive app can load a new
scenario JSON at runtime, two ways: (a) DRAG-AND-DROP a .json file onto the window
(SDL_DROPFILE); (b) an IN-APP PICKER (key `l`) listing .json files from
`tools/bounce-view/scenarios/` and `data/scenarios/calibration/` (recursive), navigable
by keyboard, Enter to load, Esc to cancel. Loading tears down the current playback, runs
the SAME path intake as startup — the S6 Law-1 guard applies to every loaded path,
including dropped ones — and reprints the effective-restitution line and the S14 stamp.
Malformed or refused files leave the current scene running with an on-stdout error.

S14 — BUILD STAMP: on startup and after every load, the app prints one line
`bounce-view build <short-commit> (<branch>[+dirty])` to stdout and places the short
commit in the window title. Derivation of the values: injected at configure/build time
from git; never hand-written.

S12.1 — DEEP CONTACT CHECKS (extends S12): the frame_check contact proof is valid at any
event depth; `--frame-times` accepts contact times taken from arbitrary event indices,
and the self-check lines are unchanged. (No new machinery — this clause names the depth
coverage the criteria will bind.)

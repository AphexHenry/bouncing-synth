# DELIVERABLE (c) — Architecture plan

```
doc_id:   C-000-DELIV-C
layer:    track
audience: Director (Phase-0 gate), PM; later cited by I-001…I-007 and component briefs
status:   DRAFT (pending Phase-0 gate approval)
parent:   C-000-BRIEF / PROJECT §3(c)
```

## 1. Two-layer product architecture

- **`bounce-core`** — headless C++20 static library. Owns everything gate-bearing: curve
  compilation (CurveSpec → pinned polynomial coefficient sets), the event-driven engine
  (ballistic arcs + root isolation per DELIVERABLE_B), event ordering (TB-1), grazing/settle
  rules (G-1/S-1), and the CollisionEvent stream. Zero third-party dependencies (C++ standard
  library only). No JUCE types anywhere in core. Real-time contract: no heap allocation, no
  locks, no I/O on the processing path; all allocation at prepare/configure time.
- **`bounce-plugin`** — thin JUCE VST3 shell (Phase 2; I-006). Hosts core + the mapping engine
  (C-003), renders visuals, exposes parameters/automation, serializes presets (C-005). JUCE is
  fetched by CMake at a pinned release tag and used under its GPL option, matching the program's
  GPLv3 license (Director decision D2). The shell may never contain physics or event-ordering
  logic; anything affecting the event sequence lives in core, or the determinism surface leaks.

Interface spine (PROJECT §6 schemas): CurveSpec + [BallState] + physics params → core →
CollisionEvent stream → mapping (C-003) → NoteEvent stream → host MIDI. `advance(n_samples)` is
the single audio-thread entry point; events carry in-block sample offsets per DELIVERABLE_B §4.

## 2. Repository layout (instantiates P3 §1)

```
src/core/            engine, curves, events, time bookkeeping (bounce-core)
src/plugin/          JUCE shell (empty until I-006 / Phase 2)
tools/refsim/        I-002 Python/mpmath reference simulator + fixture generator
tools/gates/         I-004 gate runner + run-manifest writer
config/              pinned build/FP flags (fp-determinism.cmake), gate configs, solver spec
data/scenarios/      I-003 scenario store: calibration/ and heldout/ with split-lock marker
tests/               unit tests + gate scenario harnesses (I-005 analysis lives here)
reports/             run manifests, gate outputs
```

## 3. Toolchain & dependency policy

- Build: CMake (≥ 3.27, present per JRN-C000-5) with committed CMakePresets; compiler of record
  Apple clang 17 (arm64 macOS), Linux x86-64 added in CI. All FP-determinism flags from
  DELIVERABLE_B §4 live in exactly one included fragment, `config/fp-determinism.cmake`; a unit
  test asserts the flags are in effect at runtime (FMA contraction and FTZ checks).
- Test framework: doctest (MIT, header-only) for unit tests — GPLv3-compatible, zero build cost.
- Python side: project-local venv under `tools/refsim/.venv`, Python 3 (3.9.6 of record), mpmath
  pinned by exact version in `tools/refsim/requirements.txt` (installed by the I-002 brief —
  addresses the mpmath absence recorded in TR_C-000-T1). Reference code is never linked, called,
  or vendored into product code; it is a gate-time oracle only.
- License hygiene: every dependency's license recorded in `docs/05_INFRA/` at adoption;
  GPLv3-compatible only (P3 §2b.6 / PROJECT §11).

## 4. Infrastructure mapping (I-001…I-007 → this plan)

| ID | becomes | phase |
|---|---|---|
| I-001 | `src/core` skeleton + CMake + doctest harness building clean | Phase 1 entry |
| I-002 | `tools/refsim` venv + mpmath sim + Tier-1/Tier-2 fixture generator | Phase 1 |
| I-003 | `data/scenarios` store, split-lock marker + hash, heldout access only via gate runner | Phase 1 |
| I-004 | `tools/gates` runner: executes PROJECT §8 gates, writes run manifests (pins §7 surface) | Phase 1 |
| I-005 | event-sequence diff + drift measurement in `tests/` | Phase 1 |
| I-006 | `src/plugin` JUCE scaffold, VST3 target, pluginval in CI | Phase 2 entry |
| I-007 | GitHub Actions CI: clean-checkout build + unit tests + gates, macOS arm64 + Linux x86-64 | Phase 1 |

CI account/repository creation is Director-side (PROJECT §11); the I-007 brief will name exactly
what to create. Free tier only; any paid CI minutes require Director approval first.

## 5. Determinism boundaries (what may vary, what may not)

May never vary: the CollisionEvent sequence for a given (preset, engine version) — across runs,
block sizes, and save/load (gates `determinism_repro`, `preset_roundtrip`). May vary freely:
rendering framerate, UI state, host block scheduling — the shell consumes the event stream but
cannot influence it. Threading: core is single-threaded per scenario; the plugin communicates
UI ↔ audio via a lock-free SPSC queue (Phase-2 detail, named now so no one adds a mutex later).

## 6. Explicitly deferred

Curve-editing UX (how gestures become Bézier pieces), mapping semantics, host-tempo sync, and
preset file format details — owned by C-003/C-004/C-005 theses at Phase 2 entry.

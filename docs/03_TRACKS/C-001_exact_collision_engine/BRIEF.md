# BRIEF — C-001 Exact collision engine

```
doc_id:   C-001-BRIEF
layer:    track
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   C-001-THESIS
```

## Context for agents
Phase-1 physics core for bounce-core (DELIVERABLE_C §1). The engine owns ballistic propagation,
polynomial collision-time root-solving against C-002 curves, TB-1 event ordering, and G-1/S-1
rules. No JUCE, no heap on the processing path, no libm in the collision core (DELIVERABLE_B
§3–§4). C-002 leads by one packet — engine tasks dispatch only after the curve layer has the
slice the task needs. Failures are reported verbatim (FAILED/BLOCKED), never patched mid-task.
Authorship (L-14): packets supply specs, interface declarations, oracle values, and acceptance
tests; all implementation under src/ is agent-authored. If a spec is ambiguous, BLOCK — do not
infer.

## Files you may read
- `AGENTS.md` · assigned `inbox/PACKET_<n>.md` · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- `docs/00_PROJECT.md` §6–§8 · `docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_B_NUMERICS.md` §1–§5
- `docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md` §1
- This brief · track `JOURNAL.md` · `src/core/bounce/curve/` (C-002)
- `config/fp-determinism.cmake` · `data/scenarios/calibration/` (read-only)

## Files you will write
- Under `src/core/bounce/` (engine, numerics, events) and `tests/` per task
- `docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md` (append)
- `docs/03_TRACKS/C-001_exact_collision_engine/reports/` task reports
- `outbox/OUT_<serial>_C-001-T<n>.md`

## TASK C-001-T1: Double-double arithmetic + ballistic parabola P(x) + unit tests
depends_on: C-002-T2 VERIFIED (JRN-C002-9); I-001 (VERIFIED)
objective: DD add/mul/div without FMA; compile ballistic flight path y=P(x) from BallisticInit
           using DD coefficient arithmetic; doctest on FL-1 ground hit and vx=0 rejection.
VERIFIED (JRN-C001-5; OUT_25; TR_C-001-T1.md).

## TASK C-001-T2: VCA root isolation on explicit-polynomial curve + unit tests
depends_on: C-001-T1 VERIFIED (JRN-C001-5)
objective: Build f(x)−P(x) collision polynomial and isolate the smallest root bracket on
           [x_min, x_max] via VCA bracket scan (DELIVERABLE_B §3 isolation step).
VERIFIED (JRN-C001-9; OUT_26; TR_C-001-T2.md).

## TASK C-001-T3: Fixed refinement + admissibility filter + single-ball event step + unit tests
depends_on: C-001-T2 VERIFIED (JRN-C001-9)
objective: Refine isolated root (bisection 2⁻⁴⁰ + 3 DD Newton), apply G-1 admissibility
           (|normal impact speed| ≥ v_graze), expose step_ball_next_collision for one collision
           query on explicit-polynomial curves; doctest on FL-1 ground hit.
VERIFIED (JRN-C001-13; OUT_27; TR_C-001-T3.md).

## TASK C-001-T4: Elastic reflection + graze continuation + multi-event FL-1 sequence + unit tests
depends_on: C-001-T3 VERIFIED (JRN-C001-13)
objective: reflect_velocity about curve normal with restitution; simulate_ball_collisions loop
           with G-1 graze continuation and S-1 settle; doctest on FL-1 eight tier-1 event times.
VERIFIED (JRN-C001-17; OUT_28; TR_C-001-T4.md).

## TASK C-001-T5: CollisionEvent schema + PB-1 first-contact agreement + unit tests
depends_on: C-001-T4 VERIFIED (JRN-C001-17)
objective: Introduce PROJECT §6 CollisionEvent struct; simulator emits full schema events;
           doctest on PB-1 tier-1 first contact (t=1, s=1 on y=x²).
VERIFIED (JRN-C001-21; OUT_29; TR_C-001-T5.md).

## TASK C-001-T6: TB-1 multi-ball global event queue + unit tests
depends_on: C-001-T5 VERIFIED (JRN-C001-21)
objective: simulate_multi_ball_collisions with TB-1 ordering (min t, then ball_id); doctests
           on simultaneous tie-break, earliest-time selection, monotone seq.
VERIFIED (JRN-C001-25; OUT_30; TR_C-001-T6.md).

## TASK C-001-T7: Calibration scenario JSON runner (FL-1/PB-1 end-to-end) + unit tests
depends_on: C-001-T6 VERIFIED (JRN-C001-25)
objective: load_calibration_scenario + run_calibration_scenario for schema-v1 calibration
           JSON; doctest FL-1 eight tier-1 reference events and PB-1 first contact.
VERIFIED (JRN-C001-29; OUT_31; TR_C-001-T7.md).

## TASK C-001-T8: determinism_repro-precursor repeated-run identity on FL-1 + unit tests
depends_on: C-001-T7 VERIFIED (JRN-C001-29)
objective: events_equal helper (exact == on all CollisionEvent fields) + doctest FL-1
           repeated-run identity — 100 repeated run_calibration_scenario calls, each
           bit-identical to baseline. Calibration-mode precursor to the §8 determinism_repro
           gate (JRN-C001-43); not a gate run.
VERIFIED (JRN-C001-33; OUT_32; TR_C-001-T8.md).

## TASK C-001-T9: loop_stability-precursor zero interval-sequence drift on FL-1 + unit tests
depends_on: C-001-T8 VERIFIED (JRN-C001-33)
objective: extract_collision_intervals + intervals_equal helpers; doctest FL-1 — 11
           dyadic-halving intervals bit-exact, 100 repeated full-horizon runs with zero
           interval-sequence drift through settle. Calibration-mode precursor to the §8
           loop_stability gate (JRN-C001-43; dyadic fixture — zero drift by construction).
VERIFIED (JRN-C001-37; OUT_33; TR_C-001-T9.md).

## TASK C-001-T10: reference_agreement-precursor tier-1 calibration corpus + unit tests
depends_on: C-001-T9 VERIFIED (JRN-C001-37)
objective: agrees_with_tier1_reference helper (ε=1e-12 on t/s, exact ball_id/seq) + doctest
           tier-1 calibration corpus FL-1 + PB-1. Calibration-mode precursor to the §8
           reference_agreement gate (JRN-C001-43).
VERIFIED (JRN-C001-41; OUT_34; TR_C-001-T10.md).

## TASK C-001-T11: Law 7 baseline engine + capacity lift + runner engine selection
depends_on: I-004-T2+T3 VERIFIED (JRN-I004-8); C-001-PREREG v1.1 §5; L-14
objective: Deliver the named baseline (PROJECT §5 Law 7) as a parameterized, good-faith
competitive engine emitting the same canonical event format as the exact engine, plus the
capacity lift both contestants need to reach prereg horizons, plus runner selection —
leaving PACKET 44 nothing to build, only to tune and run.

AUTHORSHIP (L-14, restated because this task is why the rule exists): everything below is
specification. All implementation is yours. The baseline must be your best honest
fixed-timestep engine within this spec — if it beats the exact engine at matched compute,
report it; that outcome is a valid result of the program, not a failure of yours.

SPEC (binding; BLOCK on any ambiguity):
1. CAPACITY LIFT (the only permitted src/core/bounce/ change): event capacity 64 → 256
   (compile-time constant), zero heap allocation on the processing path preserved;
   bounce-run-scenario --max-events accepted up to 256 and honored exactly; existing
   defaults and all existing test expectations unchanged unless a test hardcodes the
   constant (adjust with a note). New test: a calibration-style scenario configuration
   producing >64 events runs to its requested horizon with correct monotone seq.
2. BASELINE ENGINE (new code, physically separated: src/baseline/ + src/tools/run_baseline/;
   it must not modify or specialize src/core/bounce/ physics — the shared io layer
   (src/core/bounce/io/) is reused as-is for serialization):
   a. Integrator: fixed-timestep semi-implicit (symplectic) Euler — v ← v + g·dt;
      x ← x + v·dt.
   b. Geometry: the curve sampled as a polyline of N equal-x segments over the scenario's
      domain; sampling uses the same curve-evaluation semantics as the scenario schema
      defines (explicit polynomial / piecewise Bézier per C-002 definitions, evaluated in
      double).
   c. Collision: penetration test against the polyline per step; on crossing, contact time
      by linear interpolation within the step, reflection about the crossed segment's
      normal with the scenario's restitution; G-1 graze and S-1 settle constants read from
      the same versioned source of record as the exact engine.
   d. Event emission: same CollisionEvent schema, same canonical JSONL via shared io;
      events timestamped at the interpolated contact time.
   e. CLI: bounce-baseline-run --scenario <path> --out <path> --dt <seconds>
      --segments <N> [--max-events M (≤256)]; exit/stdout/stderr contract identical to
      bounce-run-scenario; temp-write + rename.
   f. Determinism: no RNG, no time-of-day reads; two identical invocations byte-identical.
3. RUNNER SELECTION: study spec gains optional field "engine": "exact" (default) |
   "baseline", and for baseline, "engine_params": {"dt": float, "segments": int}. Manifest
   records the engine name, its binary's sha256, and engine_params verbatim. --compare
   refuses to compare manifests with differing engine identity (one-line error) unless
   passed --cross-engine (prints per-scenario event-count and first-divergence summary
   instead of asserting identity).
4. TESTS (doctest for C++; runner behavior evidenced by CLI pastes): capacity test (§1);
   baseline sanity on FL-1 — with dt=1e-4, N=64: first-contact time within 2·dt of the
   tier-1 reference, event count ≥ 8 before settle; serialization round-trip on baseline
   output; byte-identity of two identical baseline invocations.

Steps:
3. Toolchain record.
4. Configure + build; paste tails; both exit=0; build shows bounce-baseline-run target.
5. ctest; paste output + LastTest.log summary; 100% passed, SUCCESS!, exit=0.
6. Capacity evidence: paste the >64-event test's scenario parameters and the run
   confirming horizon reached (from test output or a CLI run with --max-events 200).
7. Baseline smoke: run bounce-baseline-run on FL-1 (dt=1e-4, segments=64) twice; paste both
   invocations + exits, head -3 of output, both sha256s (identical); paste first-contact
   t versus tier-1 reference with |Δt| shown (≤ 2·dt).
8. Runner selection: run a baseline study (gate_id=null, calibration, engine=baseline,
   engine_params dt=1e-4 segments=64); paste manifest head showing engine identity fields;
   paste --compare refusal across engine identities and --cross-engine summary output.
9. Paste `git status --porcelain --branch` byte-verbatim.
10. TR + OUT per OUT-REQUIREMENTS.

Acceptance criteria (binary, one artifact each):
1. Step 4: both exit=0; bounce-baseline-run built.
2. Step 5: 100% passed + SUCCESS! + exit=0.
3. Step 6: >64-event horizon reached with monotone seq; --max-events honored.
4. Step 7: two identical baseline runs byte-identical; first-contact |Δt| ≤ 2·dt vs tier-1
   reference, value shown.
5. Step 8: manifest records engine=baseline, binary sha256, engine_params; --compare
   refuses cross-engine without the flag; --cross-engine prints the summary.
6. TR affirms: no src/core/bounce/ physics modified beyond §1's constant; no held-out
   scenario executed; shared io unmodified.
7. Step 9: byte-verbatim status; untracked within agent-writable surface limited to files
   this task creates pre-commit (L-13).
8. FILE DIGESTS complete per L-15; OUT completeness per L-10 (all journal entries verbatim,
   applied-files directions).

## TASK C-001-T12: streaming emission + F3 diagnostic + F2 fix + Law 7 compute-match tune
depends_on: C-001-T11 VERIFIED (JRN-C001-50); PREREG v1.2 (Director-approved via PACKET 44
dispatch)
objective: Remove every remaining obstacle between the program and its gate runs, and
freeze the Law 7 contestant configuration — PACKET 45 must contain zero construction.

SPEC (binding; BLOCK on any ambiguity):
1. STREAMING EMISSION (both offline CLIs): bounce-run-scenario and bounce-baseline-run
   write each CollisionEvent to the output file as it is produced (fixed small buffer;
   flush discipline your choice, byte output unchanged for existing horizons),
   with --max-events honored up to 1,000,000. The in-memory kMaxSimEvents array no longer
   bounds offline horizons. Constraints: canonical serialization bytes identical to the
   current format for identical event sequences (existing golden outputs must not change);
   temp-write + rename preserved; the engine library's real-time-facing API and the
   src/core/bounce/ processing path unmodified except as strictly required to expose
   per-event emission (e.g., a callback/sink interface) — zero heap on the processing path
   preserved; document what changed and why in the TR.
2. STREAMING EVIDENCE: an e=1 calibration-config scenario (committed under
   data/scenarios/calibration/, clearly named as calibration; a lossless periodic
   configuration is fine) run with --max-events 20000 on the exact engine: paste event
   count, monotone-seq confirmation (test or checker output), wall time, and byte-identical
   sha256 across two consecutive runs. Run the baseline CLI once at the same horizon to
   confirm streaming parity (sha256 of two identical baseline runs also identical).
3. F3 DIAGNOSTIC (PB-1, baseline): dump the baseline trajectory tail around the missing
   second event (positions/velocities per step near the expected contact window, dt=1e-4,
   N=64); CLASSIFY: (a) physics under its own dynamics — tunneling through the polyline,
   missed contact, or domain exit — report only, no fix, shortfall stands per v1.2 B2; or
   (b) harness/CLI defect (wrong domain, misread scenario, premature termination bug) —
   fix within this task and re-run the dump. Paste the dump excerpt and the one-line
   classification with reasoning.
4. F2 FIX: add .gitignore entries covering local venvs (tools/**/.venv/); paste git status
   showing they no longer appear.
5. COMPUTE-MATCH TUNE (v1.2 B1; calibration scenarios only — FL-1 and PB-1; NO held-out
   contact): measure the exact engine's median wall-time per simulated scenario-second via
   I-004 (timing_runs=10, horizon to each scenario's natural count, streaming build,
   committed tree). Grid the baseline over dt ∈ {1e-3, 5e-4, 2e-4, 1e-4, 5e-5, 2e-5, 1e-5}
   × N ∈ {64, 128, 256, 512, 1024} (prune infeasible cells; extend the grid if the [1.0×,
   2.0×] window would otherwise be empty — BLOCK only if no configuration can reach 1.0×).
   Select the configuration with the smallest FL-1 first-contact |Δt| among those whose
   timing ratio lies in [1.0, 2.0]; tie-break by larger N. Freeze it in
   tools/gaterunner/tune/TUNE-LAW7.json: chosen dt, N, per-scenario timing table (exact and
   baseline, all grid points measured), ratio, engine binary sha256s, git commit, date.
   Paste the table and the chosen row.

Steps:
3. Toolchain record.
4. Configure + build; paste tails; exit=0; all four targets built.
5. ctest; paste output + doctest summary; 100% passed, SUCCESS!, exit=0 (existing golden
   expectations unchanged).
6. Streaming evidence per §2 (exact 20k ×2 + baseline parity ×2; sha256s).
7. F3 diagnostic per §3 (dump excerpt + classification).
8. F2 per §4 (gitignore + clean status excerpt).
9. Tune per §5 (full timing table + frozen TUNE-LAW7.json content pasted).
10. Paste `git status --porcelain --branch` byte-verbatim.
11. TR + OUT per OUT-REQUIREMENTS.

Acceptance criteria (binary, one artifact each):
1. Step 4: exit=0; bounce-core, bounce-tests, bounce-run-scenario, bounce-baseline-run
   built.
2. Step 5: 100% passed + SUCCESS! + exit=0; no golden-output expectation changed.
3. Step 6: exact 20,000-event run, monotone seq, two identical sha256s; baseline parity
   two identical sha256s at the same horizon.
4. Step 7: dump excerpt + explicit (a)/(b) classification with reasoning; if (b), fix
   evidenced and re-dump pasted.
5. Step 8: venvs ignored; status excerpt clean of them.
6. Step 9: full grid timing table; chosen (dt, N) with ratio ∈ [1.0, 2.0]; TUNE-LAW7.json
   content pasted and committed.
7. TR affirms: no held-out contact; real-time-facing engine path unmodified beyond the
   emission interface (documented); calibration-only.
8. Step 10: byte-verbatim status; untracked within agent-writable surface limited to files
   this task creates pre-commit (L-13).
9. FILE DIGESTS complete per L-15; OUT completeness per L-10.

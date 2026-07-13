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

## TASK C-001-T12-R1: evidence-only rework of the OUT_44 submission (L-16)
depends_on: C-001-T12 implementation commits (OUT_44 tip); OUT_44 REJECTED (JRN-C001-55)
objective: Produce the compliant OUT for the already-committed T12 work. NOTHING under
src/, tools/, or data/ may change; the deliverable is evidence.

SPEC (binding; BLOCK on any ambiguity):
1. IMMUTABILITY: no modification to any file under src/, tools/, data/, config/, tests/,
   or CMakeLists.txt. Permitted writes: the T12 TR (may be completed/corrected to carry
   full evidence), the C-001 JOURNAL (CLAIM/DONE), inbox/APPLIED.log (serial 45 line),
   outbox/OUT_45.md. Proof: paste `git diff --name-status <OUT_44 final commit>..HEAD`
   immediately before the OUT commit — every listed path must be within the permitted set.
2. EVIDENCE REGENERATION: read-only commands may be re-run to capture verbatim output
   (builds, ctest, sha256 of committed artifacts, cat of TUNE-LAW7.json, the F3 diagnostic
   dump if it is a read-only replay; git status). If any regenerated value differs from
   OUT_44's summarized claims (e.g., a sha256, the tune ratio, event counts), STOP → BLOCKED
   OUT with both values pasted; a discrepancy means the T12 work needs real review, not
   evidence dressing.
3. Every T12 acceptance criterion (PACKET 44 criteria 1–9) is evidenced verbatim in
   OUT_45: toolchain record; configure + build tails with exit=0; ctest output + LastTest
   doctest summary; 20,000-event streaming evidence — both exact runs' FULL sha256s and the
   monotone-seq confirmation, both baseline-parity runs' FULL sha256s with the baseline's
   event count and horizon stated plainly; F3 trajectory dump excerpt + the (a)/(b)
   classification with reasoning; gitignore status excerpt; the FULL tune grid timing table
   and the complete TUNE-LAW7.json content; byte-verbatim `git status --porcelain --branch`.

Steps:
3. Immutability proof per §1 (diff paste first, so any surprise blocks before effort).
4. Regenerate and paste all §3 evidence per §2.
5. Complete/correct the TR to contain the same evidence; paste the full TR verbatim in the
   OUT's REPORT section.
6. TR + OUT per OUT-REQUIREMENTS below.

Acceptance criteria (binary, one artifact each):
1. §1 diff paste: all paths within the permitted set; zero src/tools/data/config/tests
   changes.
2. Toolchain + configure + build pastes; exit=0; four targets built.
3. ctest paste + doctest summary; 100% passed + SUCCESS! + exit=0.
4. Streaming evidence: exact 20,000 events, monotone seq confirmed, two FULL identical
   sha256s; baseline parity two FULL identical sha256s with event count + horizon stated.
5. F3 dump excerpt + explicit (a)/(b) classification with reasoning.
6. Gitignore status excerpt clean of venvs.
7. Full tune grid table + complete TUNE-LAW7.json pasted; chosen row dt=5e-4, N=128 with
   ratio ∈ [1.0, 2.0] — or BLOCKED per §2 if regeneration disagrees.
8. Byte-verbatim git status; untracked within agent-writable surface limited to files this
   task creates pre-commit (L-13).
9. FILE DIGESTS complete per L-15 INCLUDING the TR; full untruncated sha256s throughout;
   TR pasted verbatim in REPORT (L-16).

## TASK GATE-P1: Phase-1 confirmatory gate runs (P1-A → P1-B → P1-C → Law 7)
depends_on: C-001-T12 VERIFIED (JRN-C001-59); PREREG v1.3 (Director-approved via PACKET 46
dispatch); TUNE-LAW7.json (frozen); I-003 corpus (32, locked); I-004 (VERIFIED)
objective: Execute the registered Phase-1 gates in order with halt-on-failure and produce
verdict-bearing evidence. TASK COMPLIANCE ≠ GATE VERDICTS: the task is DONE if the gates
are executed per the rules below and fully evidenced, whatever they show. Do not soften,
re-run, or reinterpret a failing gate — a clean FAIL is a valid deliverable.

CONSTRUCTION SCOPE (the only code this task may create): tools/gaterunner/studies/*.json
(P1-A, P1-B, P1-C, LAW7-EXACT, LAW7-BASELINE); tools/gaterunner/check_p1a.py,
check_p1b.py, check_p1c.py, check_law7.py; a --repeat N flag on bounce-run-scenario (run
the scenario N times in-process, assert bit-identity of event sequences via the existing
exact-equality helper, write the file once, print `repeat-identity ok N=<n>`; nonzero exit
+ first-divergence report on mismatch). Nothing else changes; no engine physics, no
baseline physics, no fixture, no tune value.

EXECUTION RULES (binding; BLOCK on any ambiguity):
G0. Committed tree: run from the branch tip with zero tracked modifications; every
    manifest must show engine_git_dirty=false (tracked-file dirty; untracked courier
    surface exempt, v1.3 C2). Paste tracked-clean status before the first gate run.
G1. Authorization + logging: every held-out execution goes through the I-004 runner with
    gate_id set (P1-A / P1-B / P1-C / LAW7); every such execution appends to
    ACCESS_LOG.jsonl. After all runs, paste the log's line count and a 5-line excerpt, and
    reconcile the count against the manifests (expected = sum of per-manifest held-out
    invocations; state the arithmetic).
G2. Order + halt (v1.2 B3): P1-A, then P1-B, then P1-C, then Law 7. On a gate FAIL: stop,
    do not execute subsequent gates, document the halt in GATE_SUMMARY.md and the OUT.
    Infrastructure errors (crash, write failure, runner defect) are BLOCKED, not FAIL —
    stop and paste.

P1-A (reference_agreement, Design A; PREREG §1 + v1.3 C1):
  Run: exact engine, all 32 held-out scenarios, --max-events 200 (settle terminates
  earlier where applicable), timing_runs per study spec (1 timed pass sufficient; timing
  is not gate-bearing here).
  Check (check_p1a.py): per scenario, over the confirmatory window (min(200, settle);
  quasi-chaotic cells first 12 events), compare engine events to fixture reference:
  |Δt| ≤ 1e-9 s AND |Δs| ≤ 1e-9, ball_id and seq exactly equal, event count equal to the
  reference count within the window; HO-graze-parabola-1 (0.5×): empty reference ⇒ engine
  must emit zero events. Output: per-scenario worst |Δt| and |Δs| table, per-family and
  per-regime distributions (L-05), quasi-chaotic events 13–25 as a separate exploratory
  table, corpus verdict PASS/FAIL (one scenario over tolerance fails the gate). Red team:
  re-evaluate the primary excluding the largest family, and on Tier-1 fixtures only; both
  tables in the report.
P1-B (determinism_repro, Design B; PREREG §2):
  (i) In-process: bounce-run-scenario --repeat 100 on each of the 32 (gate-authorized via
  a runner mode or direct authorized invocation — every execution logged); paste the 32
  `repeat-identity ok` lines (or the failure).
  (ii) Fresh-process: run the P1-B study 10 times; pairwise --compare (A vs each of B..J);
  paste the 9 compare verdicts — byte-identical event files for every scenario.
  (iii) Clean rebuild ×2: delete the build tree, reconfigure, rebuild, rerun the study,
  --compare against run A; paste both verdicts. Toolchain identity pasted before/after.
  Verdict: PASS iff all of (i)(ii)(iii) show zero diffs.
P1-C (loop_stability, Design C; PREREG §3):
  The 9 periodic held-out fixtures (HO-flat-periodic-1..3, HO-parabola-periodic-1..2,
  HO-poly-periodic-1..2, HO-bezier-periodic-1..2), each run to 10^4 periods (per-fixture
  --max-events = period_event_count × 10^4, from the fixture's reference metadata;
  streaming).
  Check (check_p1c.py): parse hexfloat times; per-period interval vector = consecutive
  binary64 deltas; require every period's vector bit-identical to period 1's, all 10^4
  periods; report per-fixture first-divergence index (must be none) and an
  interval-sequence hash. Verdict: PASS iff drift = 0 on all 9.
LAW 7 (PREREG §5, v1.2 B1/B2, v1.3 C2):
  Run: baseline engine, all 32 held-out scenarios, frozen tune (dt=5e-4, N=128,
  TUNE-LAW7.json cited by sha256 in the manifest), gate-authorized, logged.
  Check (check_law7.py): per scenario, K = min(200, exact event count from the P1-A run);
  baseline per-event |Δt| vs reference over its emitted events; if the baseline emits
  fewer than K events, the scenario's baseline worst error is recorded as SHORTFALL
  (scores maximally; cite the physics classification class per OUT_45 F3 where the
  mechanism matches). Corpus primary: (worst-case exact |Δt| over the corpus) ≤ (worst-case
  baseline |Δt| over the corpus, SHORTFALL = maximal) / 100, AND on the 9 periodic
  fixtures the baseline's measured per-period drift > 0 where the exact engine's = 0
  (drift measured with the same interval method as P1-C). Exploratory: the ratio over
  finite (non-shortfall) scenarios only; full accuracy table per family × regime.
  Verdict: PASS iff both primary arms hold.
GATE_SUMMARY.md: four verdict lines with the governing numbers (P1-A worst |Δt|/|Δs|;
P1-B 0-diff counts; P1-C max first-divergence; Law 7 corpus ratio + drift arm), the
halt point if any, and the manifests' sha256s.

Steps:
3. Toolchain record; G0 tracked-clean status paste.
4. Configure + build; ctest; pastes; exit=0; 100% + SUCCESS!.
5. Implement the construction-scope items; paste `--repeat 3` smoke on a CALIBRATION
   scenario (no held-out contact yet) showing `repeat-identity ok N=3`.
6. Execute P1-A per rules; paste checker report (tables + verdict).
7. If P1-A PASS: execute P1-B; paste (i)(ii)(iii) evidence + verdict. Else halt per G2.
8. If P1-B PASS: execute P1-C; paste per-fixture table + verdict. Else halt.
9. If P1-C PASS: execute Law 7; paste comparison table, shortfall list, drift table,
   both primary arms, verdict. Else halt.
10. G1 access-log reconciliation paste. GATE_SUMMARY.md pasted verbatim.
11. Byte-verbatim `git status --porcelain --branch`.
12. TR + OUT per OUT-REQUIREMENTS below.

Acceptance criteria (binary, one artifact each — INDEPENDENT of gate verdicts):
1. Step 3: toolchain + tracked-clean status pasted before first gate run.
2. Step 4: build + ctest pastes; exit=0; 100% + SUCCESS!.
3. Step 5: --repeat calibration smoke pasted; no held-out contact before step 6.
4. Step 6: P1-A checker report pasted in full (per-scenario table, distributions,
   exploratory 13–25 table, red-team tables, verdict line); all 32 manifests
   dirty=false.
5. Steps 7–9 (as reached per G2): full evidence + verdict line per gate; halt, if any,
   documented with the failing numbers.
6. G1: ACCESS_LOG line count + excerpt + reconciliation arithmetic pasted; count matches
   manifests.
7. GATE_SUMMARY.md pasted verbatim.
8. TR affirms: no fixture/tune/physics modification; all held-out execution
   gate-authorized; halt rule honored.
9. Step 11: byte-verbatim status; untracked within agent-writable surface limited to
   files this task creates pre-commit (L-13).
10. FILE DIGESTS complete per L-15 (checkers, studies, manifests, reports, GATE_SUMMARY,
    TR) with full sha256s; TR pasted verbatim in REPORT (L-16); all journal entries of
    this dispatch verbatim; applied-files directions listed.

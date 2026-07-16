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

## TASK C-001-T13: Held-out scenario harness — loader + piecewise-Bézier exact collision
depends_on: OUT_46 GATE-P1 BLOCKED (JRN-C001-62); C-001-T12 VERIFIED; C-002-T2 VERIFIED
(Bézier eval/normal of record); I-003-T4 (step 0 of PACKET 47 — re-mint completes first)
objective: Make `load_calibration_scenario` + `run_calibration_scenario` (and
`bounce-run-scenario` / `bounce-baseline-run` load paths) capable of loading and executing
all 32 held-out fixtures. Unblocks GATE-P1 re-dispatch (PACKET 48). No held-out execution
in this task — load survey and calibration regression only.

SPEC (binding; BLOCK on any ambiguity):
1. RATIONAL PARSING (`parse_rational`): accept decimal strings and scientific notation
   (e.g. `0.7071067811865475`, `1.04e-20`) with correctly-rounded IEEE-754 binary64
   semantics, in addition to existing integers and `a/b` fractions. Integer/fraction
   behavior unchanged; doctest covers at least one held-out-style decimal and one
   scientific value.
2. EMPTY REFERENCE: `reference_events: []` loads successfully with `ref_event_count = 0`
   (HO-graze-parabola-1). `agrees_with_tier1_reference` on zero-ref scenarios compares
   only emitted event count (=0).
3. SCHEMA-V1 CURVE LOADING: read the nested `curve` object per
   `config/scenario-fixture-schema-v1.json`:
   a. `family: "polynomial"` — `coeffs` + `domain` (existing behavior, including
      calibration FL-1/PB-1).
   b. `family: "piecewise-bezier"` — `segments[]` with `kind` quadratic|cubic and
      `control` points; compile via C-002 (`compile_piecewise_bezier`); store in
      `CalibrationScenario` (extend the struct — zero heap on the sim path after compile
      if feasible; otherwise document any allocation confined to load time).
   c. Read `physics.gravity` (held-out format); continue to accept calibration fixtures.
4. BEZIER EXACT COLLISION (DELIVERABLE_B §1–§3; C-001 THESIS): for piecewise-bezier
   scenarios, `run_calibration_scenario` finds collisions by reducing each segment to
   Y(s)−P(X(s))=0 (polynomial in s, deg ≤6 for cubic segments), isolating the smallest
   admissible root on s∈[0,1] with the existing VCA + fixed refinement schedule, then
   recovering t from X(s). Traverse segments and C1 joints; G-1/S-1 unchanged; TB-1
   multi-ball unchanged. Doctest: at least one held-out Bézier fixture's first reference
   event within ε=1e-12 (load the fixture path from disk in the test — this is a *load* of
   a committed fixture file for test vector purposes, not a `run_calibration_scenario` gate
   execution on held-out if you can avoid it by using a committed calibration-style Bézier
   test vector; if no calibration Bézier exists, a load-only doctest that parses the fixture
   and checks the first event against reference WITHOUT calling the full gate runner is
   acceptable).
5. BASELINE LOAD PATH: `bounce-baseline-run` must load piecewise-bezier scenarios (polyline
   sampling already evaluates curves — wire the loader extension through).
6. LAW-1: no `bounce-run-scenario` or `bounce-baseline-run` invocation on any path under
   `data/scenarios/heldout/` in this task. The 32/32 survey uses
   `load_calibration_scenario` only (a small survey script or one-shot paste is fine).
7. REGRESSION: all existing `test_calibration_scenario.cpp` cases pass unchanged in
   outcome (FL-1 eight events, PB-1 first contact, determinism/interval precursors).

Steps:
3. Paste environment record: `cmake --version`; `c++ --version`; `python3 --version`;
   `which python3`.
4. Implement spec §1–§5; configure + build; paste configure tail, build tail, exit=0.
5. ctest + doctest summary paste; 100% passed + SUCCESS! + exit=0.
6. Paste held-out LOAD SURVEY (all 32 ids, `load_calibration_scenario` only):
   `scenario_id,load_ok` lines + `load_ok <n> / 32` — must be 32/32.
7. Paste byte-verbatim `git status --porcelain --branch`.
8. TR + OUT per OUT-REQUIREMENTS below.

Acceptance criteria (binary, one artifact each):
1. Step 3 pasted: toolchain versions.
2. Step 4 pasted: configure + build tails; exit=0; four targets built.
3. Step 5 pasted: ctest + doctest; 100% + SUCCESS! + exit=0.
4. Step 6 pasted: 32/32 `load_ok`; survey command shown.
5. TR affirms LAW-1: no held-out engine execution; load survey only.
6. Step 7: byte-verbatim git status; L-13 untracked surface.
7. FILE DIGESTS complete per L-15; TR pasted verbatim in REPORT (L-16).

## TASK GATE-P1-R1: Phase-1 confirmatory gate runs — execution-only re-dispatch
depends_on: C-001-T13 VERIFIED (JRN-C001-66); I-003-T4 VERIFIED (JRN-I003-25); GATE-P1
construction delivered (OUT_46 commit 3451533 — checkers, studies, --repeat); PREREG v1.3;
TUNE-LAW7.json (frozen); I-003 corpus (32, locked, post-T4 sha256s); I-004 (VERIFIED)
objective: Execute the registered Phase-1 gates in order with halt-on-failure and produce
verdict-bearing evidence. IDENTICAL gate rules to TASK GATE-P1 in this brief; deltas below
only. TASK COMPLIANCE ≠ GATE VERDICTS.

DELTAS FROM GATE-P1 (binding):
D0. CONSTRUCTION SCOPE: **none.** Do not modify src/, tools/gaterunner checkers (except
    manifest output paths if required by runner), study specs, data/fixtures, or tune files.
    If checkers/studies/--repeat are absent at branch tip, merge from task/GATE-P1 (OUT_46
    lineage) — do not reauthor.
D1. PRE-FLIGHT (before step 6 / first held-out gate run): run
    `./build/default/bounce-survey-heldout-load` (or equivalent); paste full output showing
    `load_ok 32 / 32`. If load_ok < 32, STOP → BLOCKED.
D2. CORPUS: MANIFEST.json includes I-003-T4 re-mint sha256s for HO-flat-settle-{1..4}
    (JRN-I003-25). Runner must resolve current manifest sha256s — no hardcoded pre-T4
    digests.
D3. STEP 5: re-run `--repeat 3` calibration smoke only (construction already committed);
    paste `repeat-identity ok N=3`. No new construction commits before G0 clean tree.

All other GATE-P1 text applies verbatim: G0–G2, P1-A through Law 7 definitions, steps 3–12,
acceptance criteria 1–10, halt-on-failure, gate-authorized logging, dirty=false manifests.

Steps (replace GATE-P1 steps 3–12 numbering for this dispatch):
3. Toolchain record; G0 tracked-clean status paste.
4. Configure + build; ctest; pastes; exit=0; 100% + SUCCESS!.
5. D1 pre-flight load survey paste (32/32).
6. D3 `--repeat 3` calibration smoke paste.
7. Execute P1-A per GATE-P1 rules; paste checker report (tables + verdict).
8. If P1-A PASS: execute P1-B; paste (i)(ii)(iii) evidence + verdict. Else halt per G2.
9. If P1-B PASS: execute P1-C; paste per-fixture table + verdict. Else halt.
10. If P1-C PASS: execute Law 7; paste comparison table, shortfall list, drift table,
    both primary arms, verdict. Else halt.
11. G1 access-log reconciliation paste. GATE_SUMMARY.md pasted verbatim.
12. Byte-verbatim `git status --porcelain --branch`.
13. TR + OUT per OUT-REQUIREMENTS below.

Acceptance criteria: identical to TASK GATE-P1 criteria 1–10 with step numbers shifted by
the D1/D3 insertions above (criterion 3 = D1 survey; criterion 4 = D3 smoke; criterion 5
= P1-A report; etc.).

## TASK C-001-T14: Zero-event canonical event-file write (streaming + offline)
depends_on: OUT_48 GATE-P1-R1 BLOCKED (JRN-C001-70); C-001-T13 VERIFIED (JRN-C001-66)
objective: Fix the shared io layer so `engine_events=0` produces a valid `bounce-events-v1`
JSONL file (header only, no event lines) via both streaming (`begin_event_stream` /
`finish_event_stream`) and offline (`write_event_file`) paths. Unblocks P1-A on
HO-graze-parabola-1 (PREREG §1: empty reference ⇒ zero emitted events). No held-out
execution in this task.

SPEC (binding; BLOCK on any ambiguity):
1. ZERO-EVENT WRITE: when the event count is 0, all three operations succeed:
   a. `finish_event_stream` after `begin_event_stream` with zero `emit_event_stream` calls.
   b. `write_event_file` with `MultiBallSimResult.count == 0`.
   c. `read_event_file` round-trips the result (`count == 0`, `engine_events` header matches).
   Output format: one header line
   `{"schema":"bounce-events-v1", "scenario_sha256":"<sha>", "engine_events":0}` and no
   event body lines.
2. SCOPE: changes confined to `src/core/bounce/io/` and tests; `bounce-run-scenario` and
   `bounce-baseline-run` inherit the fix via the shared io layer. No engine physics, no tune,
   no held-out fixture edits.
3. TEST FIXTURE: add a committed zero-reference scenario JSON under `tests/fixtures/` (not
   under `data/scenarios/heldout/`) sufficient to produce zero engine events when run with
   the exact engine — may mirror the grazing construction shape at reduced scope. LAW-1:
   no binary invocation with `--scenario` pointing at any `data/scenarios/heldout/` path.
4. REGRESSION: all existing `test_event_file.cpp` and calibration tests pass unchanged.

Steps:
3. Paste environment record: `cmake --version`; `c++ --version`; `python3 --version`.
4. Implement spec §1–§3; configure + build; paste configure tail, build tail, exit=0.
5. ctest + doctest summary; 100% passed + SUCCESS! + exit=0.
6. Paste zero-event CLI smoke:
   `./build/default/bounce-run-scenario --scenario <tests/fixtures/...> --out <tmp> --max-events 200`
   showing exit=0, stdout contains `events=0`, and first line of output file pasted showing
   `"engine_events":0`.
7. Paste byte-verbatim `git status --porcelain --branch`.
8. TR + OUT per OUT-REQUIREMENTS below.

Acceptance criteria (binary, one artifact each):
1. Step 3 pasted: toolchain versions.
2. Step 4 pasted: configure + build tails; exit=0.
3. Step 5 pasted: ctest + doctest; 100% + SUCCESS! + exit=0.
4. Step 6 pasted: CLI smoke exit=0; `events=0` line; header line with `engine_events":0`.
5. TR affirms LAW-1: no held-out path execution; fixture under tests/ or calibration only.
6. Step 7: byte-verbatim git status; L-13 untracked surface.
7. FILE DIGESTS complete per L-15; TR pasted verbatim in REPORT (L-16).

## TASK GATE-P1-R2: Phase-1 confirmatory gate runs — second execution-only re-dispatch
depends_on: C-001-T14 VERIFIED (JRN-C001-75); OUT_48 GATE-P1-R1 BLOCKED (JRN-C001-70/-71);
C-001-T13 VERIFIED (JRN-C001-66); I-003-T4 VERIFIED (JRN-I003-25); GATE-P1 construction
(OUT_46 lineage — checkers, studies, --repeat); PREREG v1.3; TUNE-LAW7.json (frozen);
I-003 corpus (32, locked, post-T4 sha256s); I-004 (VERIFIED)
objective: Execute the registered Phase-1 gates in order with halt-on-failure and produce
verdict-bearing evidence. IDENTICAL gate rules to TASK GATE-P1 in this brief; the GATE-P1-R1
deltas D0–D3 carry over; new deltas D4–D6 below. TASK COMPLIANCE ≠ GATE VERDICTS: the task
is DONE if the gates are executed per the rules and fully evidenced, whatever they show. Do
not soften, re-run, or reinterpret a failing gate — a clean FAIL is a valid deliverable.

DELTAS (binding; D0–D3 restated from GATE-P1-R1, D4–D6 new):
D0. CONSTRUCTION SCOPE: none. Do not modify src/, tools/gaterunner checkers, study specs,
    data/fixtures, or tune files. If checkers/studies/--repeat are absent at branch tip,
    merge from task/GATE-P1 (OUT_46 lineage) — do not reauthor.
D1. PRE-FLIGHT LOAD: before the first held-out gate run, run
    `./build/default/bounce-survey-heldout-load`; paste full output showing
    `load_ok 32 / 32`. If load_ok < 32, STOP → BLOCKED.
D2. CORPUS: MANIFEST.json includes the I-003-T4 re-mint sha256s for HO-flat-settle-{1..4}
    (JRN-I003-25). Runner resolves current manifest sha256s — no hardcoded pre-T4 digests.
D3. `--repeat 3` calibration smoke only (construction already committed); paste
    `repeat-identity ok N=3`. No new construction commits before the G0 clean-tree paste.
D4. PRE-FLIGHT ZERO-EVENT WRITE (new; durable fix of JRN-C001-71): before the first held-out
    gate run, run
    `./build/default/bounce-run-scenario --scenario tests/fixtures/graze-zero-ref.json
     --out <tmp> --max-events 200`
    and paste: exit=0, stdout `events=0`, and the output file's first line showing
    `"engine_events":0`. This fixture is committed and non-held-out (C-001-T14); LAW-1
    unaffected. If any of the three fails, STOP → BLOCKED.
D5. STALE-ARTIFACT HYGIENE (new): before the first gate run, delete the R1 halt residue —
    the entire `tools/gaterunner/events/` working contents (13 partial P1-A event files,
    `graze-*.tmp`, `test-fl1.jsonl`; all untracked). Paste the removal command and a
    post-removal listing of `tools/gaterunner/events/` showing it empty (or absent).
    Checkers in this dispatch may only read files produced by this dispatch. Do NOT touch
    `data/scenarios/heldout/ACCESS_LOG.jsonl` — the log is append-only history.
D6. ACCESS_LOG DELTA RECONCILIATION (new; refines G1): paste the ACCESS_LOG line count
    BEFORE the first gate run (expected: 24, carried from R1's two partial P1-A attempts —
    if the pre-run count differs from 24, STOP → BLOCKED and paste the full log) and AFTER
    all runs, plus a 5-line excerpt of this dispatch's entries. Expected final = pre-run
    count + sum of this dispatch's per-manifest held-out invocations; state the arithmetic
    explicitly per gate.

All other GATE-P1 text applies verbatim: G0–G2, P1-A through Law 7 definitions and checkers,
gate-authorized logging, dirty=false manifests (tracked-file dirty; untracked courier surface
exempt, PREREG v1.3 C2), halt-on-failure order P1-A → P1-B → P1-C → Law 7 (v1.2 B3).
This dispatch overwrites `docs/03_TRACKS/C-001_exact_collision_engine/reports/GATE_SUMMARY.md`
(the R1 halt record is preserved in TR_GATE-P1-R1.md and JRN-C001-70/-71). TR filename:
`reports/TR_GATE-P1-R2.md`. Branch: `task/GATE-P1-R2` from `task/C-001-T14` tip.

Steps:
3. Toolchain record; G0 tracked-clean status paste (`git status --porcelain
   --untracked-files=no`).
4. Configure + build; ctest + doctest; pastes; exit=0; 100% + SUCCESS!.
5. D1 pre-flight load survey paste (32/32).
6. D3 `--repeat 3` calibration smoke paste.
7. D4 zero-event write pre-flight paste.
8. D5 stale-artifact removal paste (command + post-removal listing).
9. D6 pre-run ACCESS_LOG line count paste. Then execute P1-A per GATE-P1 rules; paste the
   checker report in full (per-scenario worst |Δt| and |Δs| table, per-family and
   per-regime distributions, quasi-chaotic events 13–25 exploratory table, both red-team
   tables, verdict line).
10. If P1-A PASS: execute P1-B; paste (i)(ii)(iii) evidence + verdict. Else halt per G2.
11. If P1-B PASS: execute P1-C; paste per-fixture table (first-divergence index,
    interval-sequence hash) + verdict. Else halt.
12. If P1-C PASS: execute Law 7; paste comparison table, shortfall list, drift table, both
    primary arms, verdict. Else halt.
13. D6 post-run ACCESS_LOG count + excerpt + reconciliation arithmetic paste.
    GATE_SUMMARY.md pasted verbatim (four verdict lines with governing numbers, halt point
    if any, manifests' sha256s).
14. Byte-verbatim `git status --porcelain --branch`.
15. TR + OUT per OUT-REQUIREMENTS in the dispatching packet.

Acceptance criteria (binary, one artifact each — INDEPENDENT of gate verdicts):
1. Step 3: toolchain + tracked-clean status pasted before first gate run.
2. Step 4: configure/build/ctest/doctest pastes; exit=0; 100% + SUCCESS!.
3. Step 5: full survey output; `load_ok 32 / 32`.
4. Step 6: `repeat-identity ok N=3` on a calibration scenario; no held-out contact before
   step 9.
5. Step 7: zero-event smoke — exit=0, `events=0`, header line with `"engine_events":0`;
   fixture path shown under tests/fixtures/.
6. Step 8: removal command + post-removal listing of tools/gaterunner/events/ pasted.
7. Step 9: P1-A checker report pasted in full (all named tables + verdict line); all 32
   manifests engine_git_dirty=false.
8. Steps 10–12 (as reached per G2): full evidence + verdict line per executed gate; any
   halt documented with the failing numbers.
9. Step 13 (D6): pre-run count (=24 or BLOCKED), post-run count, excerpt, and per-gate
   reconciliation arithmetic matching the manifests.
10. Step 13: GATE_SUMMARY.md pasted verbatim.
11. TR affirms: no fixture/tune/physics/checker modification; all held-out execution
    gate-authorized via I-004 with gate_id set; halt order honored; ACCESS_LOG untouched
    except by runner appends.
12. Step 14: byte-verbatim status; untracked within the agent-writable surface limited to
    files this dispatch creates pre-commit (L-13).
13. FILE DIGESTS complete per L-15 (checkers, studies, manifests, event/report artifacts of
    record, GATE_SUMMARY, TR, and every applied brain file of this packet) with full
    untruncated sha256s; TR pasted verbatim in REPORT (L-16); every journal entry of this
    dispatch verbatim; applied-files directions listed.

## TASK C-001-T15: Checker reference-number parsing + checker shape self-test
depends_on: OUT_50 GATE-P1-R2 BLOCKED (JRN-C001-78/-79); GATE-P1 construction (OUT_46
lineage — checkers, studies); C-001-T14 VERIFIED (JRN-C001-75); I-003 corpus (32, locked)
objective: Make the gate checkers able to read every registered reference numeric shape of
the held-out corpus — including exact rationals (`a/b`) — with comparisons computed exactly,
and deliver a committed checker shape self-test that GATE-P1-R3 runs as pre-flight (L-17).
Unblocks GATE-P1-R3 (PACKET 52). No held-out engine execution and no gate verdict
production in this task.

SPEC (binding; BLOCK on any ambiguity):
1. REFERENCE PARSER: a single shared parsing function (new module under `tools/gaterunner/`,
   imported by the checkers — no per-checker copies) accepting, as strings, all of:
   a. rational `a/b` (optionally signed integers a, b; e.g. `5/2`, `-3/4`);
   b. decimal (e.g. `0.7071067811865475`) and scientific (e.g. `1.04e-20`);
   c. plain integers;
   d. hexfloat (e.g. `0x1.4p+1`) where any checker reads engine hexfloat output through the
      same path.
   Parsing is EXACT: the parser returns an exact rational value (Python
   `fractions.Fraction` is the natural carrier — decimals, scientific, integers, and `a/b`
   convert exactly; a hexfloat converts exactly via the binary64 value it denotes). No value
   passes through a lossy float conversion before comparison.
2. EXACT COMPARISON: in `check_p1a.py` (and `check_law7.py` where it compares against
   reference fields), |Δt| and |Δs| are computed exactly on the parsed rationals; the
   registered tolerance `1e-9` (PREREG §1) is applied as the exact rational 10^-9. Engine
   event values enter the comparison from their hexfloat (exact binary64) representation.
   Printed tables may render deltas as shortest-round-trip floats; the pass/fail decision is
   taken on the exact values. Per-scenario/per-family table output format unchanged
   otherwise (L-15 v2 standing tooling rule: per-item tables by default).
3. SIBLING AUDIT: audit all four checkers (`check_p1a.py`, `check_p1b.py`, `check_p1c.py`,
   `check_law7.py`) for reference-field or numeric-string reads (`hex_or_decimal` call
   sites and any equivalent); route every reference-field read through the shared parser.
   Checkers that compare engine output to engine output only (no fixture reference reads)
   are left functionally unchanged — state that disposition per checker.
4. CHECKER SHAPE SELF-TEST: `tools/gaterunner/selftest_checkers.py`, exit=0 on success,
   nonzero + named failing vector otherwise, printing a per-vector result table. Vectors are
   committed under `tests/fixtures/gaterunner-selftest/` (NOT under `data/scenarios/`) and
   must cover at least:
   a. a reference event stream using rational values including `5/2`;
   b. decimal and scientific reference values;
   c. a zero-event scenario (empty `reference_events` + engine file with
      `"engine_events":0`) passing the count-only comparison;
   d. an agreement vector within 10^-9 that must PASS;
   e. a DELIBERATE over-tolerance vector (|Δt| > 10^-9) that the compare path must FAIL —
      the self-test asserts the failure occurs and reports it as `expected-fail ok`
      (fail-loudness proof, L-15 v2 / L-17);
   f. a rational-vs-hexfloat mixed comparison exercising the exact path end-to-end.
   The self-test drives the checkers' actual compare functions (import or subprocess on the
   synthetic vectors) — not a reimplementation of them.
5. FORBIDDEN IN THIS TASK (LAW-1 + verdict hygiene):
   a. no `bounce-run-scenario` / `bounce-baseline-run` invocation with `--scenario` under
      `data/scenarios/heldout/`;
   b. no `check_*.py --check` (or equivalent) invocation against
      `tools/gaterunner/manifests/P1-A.json` or any held-out event file from the R2 run —
      the first post-fix verdict is produced inside GATE-P1-R3, nowhere else;
   c. no edits to `src/`, `data/`, study specs, tune files, or fixtures outside
      `tests/fixtures/gaterunner-selftest/`.
6. REGRESSION: configure + build + ctest + doctest all green (engine untouched — this is
   the guard that proves it).

Steps:
3. Paste environment record: `cmake --version`; `c++ --version`; `python3 --version`;
   `which python3`.
4. Implement spec §1–§4; paste `git diff --stat` over the working changes (must be confined
   to `tools/gaterunner/` and `tests/fixtures/gaterunner-selftest/`).
5. Configure + build + ctest + doctest paste; exit=0; 100% + SUCCESS!.
6. Self-test run paste: full per-vector table, `5/2` vector visible, `expected-fail ok`
   line visible, exit=0.
7. Sibling audit paste: the grep over all four checkers for reference-parse call sites,
   plus a one-line disposition per checker (routed through shared parser / no reference
   reads — unchanged).
8. Paste byte-verbatim `git status --porcelain --branch`.
9. TR (`reports/TR_C-001-T15.md`) + OUT per OUT-REQUIREMENTS in the dispatching packet.

Acceptance criteria (binary, one artifact each):
1. Step 3 pasted: toolchain versions + python path.
2. Step 4 pasted: `git diff --stat` confined to `tools/gaterunner/` +
   `tests/fixtures/gaterunner-selftest/`.
3. Step 5 pasted: configure/build/ctest/doctest; exit=0; 100% + SUCCESS!.
4. Step 6 pasted: self-test per-vector table with the `5/2` vector, the zero-event vector,
   and the `expected-fail ok` line; exit=0.
5. Step 7 pasted: sibling audit grep + per-checker disposition (all four named).
6. TR affirms spec §5 in full: no held-out engine execution; no check against the R2 P1-A
   manifest or its event files; no edits outside the §5c surface.
7. Step 8: byte-verbatim git status; untracked within the agent-writable surface limited to
   files this task creates pre-commit (L-13).
8. FILE DIGESTS complete per L-15 — every changed/created file (shared parser module,
   changed checkers, self-test script, every self-test fixture) plus every applied brain
   file of this packet and the TR — full untruncated sha256s; TR pasted verbatim in REPORT
   (L-16).

## TASK GATE-P1-R3: Phase-1 confirmatory gate runs — third execution-only re-dispatch
depends_on: C-001-T15 delivered (OUT_51; VERIFIED attaches at step 4 repair, JRN-C001-83);
C-001-T14 VERIFIED (JRN-C001-75); GATE-P1 construction (OUT_46 lineage); PREREG v1.3;
TUNE-LAW7.json (frozen); I-003 corpus (32, locked, post-T4 sha256s); I-004 (VERIFIED)
objective: Execute the registered Phase-1 gates in order with halt-on-failure and produce
verdict-bearing evidence. IDENTICAL gate rules to TASK GATE-P1 in this brief; the R1/R2
deltas carry over as restated below; new deltas D7/D8 and the step-4 repair. TASK
COMPLIANCE ≠ GATE VERDICTS: the task is DONE if the gates are executed per the rules and
fully evidenced, whatever they show. Do not soften, re-run, or reinterpret a failing gate —
a clean FAIL is a valid deliverable.

DELTAS (binding):
D0. CONSTRUCTION SCOPE: none. Do not modify src/, checkers, ref_parse.py, selftest tooling,
    study specs, data/fixtures, or tune files. If T15's checker changes are absent at
    branch tip, merge from task/C-001-T15 — do not reauthor.
D1. PRE-FLIGHT LOAD (remediation of record, JRN-C001-79): run
    `./build/default/bounce-survey-heldout-load`; paste the COMPLETE output — all 32
    per-scenario lines plus `load_ok 32 / 32`. Elision of any line is a criterion failure.
    If load_ok < 32, STOP → BLOCKED.
D2. CORPUS: MANIFEST.json includes the I-003-T4 re-mint sha256s for HO-flat-settle-{1..4}
    (JRN-I003-25). Runner resolves current manifest sha256s — no hardcoded digests.
D3. `--repeat 3` calibration smoke only; paste `repeat-identity ok N=3`. No new
    construction commits at any point; housekeeping commits only at step 4, before the G0
    paste.
D4. PRE-FLIGHT ZERO-EVENT WRITE: run
    `./build/default/bounce-run-scenario --scenario tests/fixtures/graze-zero-ref.json
     --out <tmp> --max-events 200`
    and paste: exit=0, stdout `events=0`, output file's first line showing
    `"engine_events":0`. Any failure: STOP → BLOCKED.
D5. STALE-GATE-OUTPUT HYGIENE (mechanics per observed state — the packet asserts no
    tracked/untracked facts): before the first gate run, remove the R2 gate outputs so this
    dispatch's checkers can only read this dispatch's files: the contents of
    `tools/gaterunner/events/` and `tools/gaterunner/manifests/P1-A.json`. For each path,
    paste its `git status` line first; if tracked, remove via `git rm` and fold into the
    step-4 housekeeping commit; if untracked, `rm` and paste the removal. Paste a
    post-removal listing. Do NOT touch `data/scenarios/heldout/ACCESS_LOG.jsonl`
    (append-only history).
D6. ACCESS_LOG DELTA RECONCILIATION: paste the line count BEFORE the first gate run —
    expected 56 (24 R1 + 32 R2, gate-authorized per JRN-C001-71/-79); if it differs, STOP →
    BLOCKED and paste the full log. Paste the count AFTER all runs plus a 5-line excerpt of
    this dispatch's entries. Expected final = pre-run count + sum of this dispatch's
    per-manifest held-out invocations; state the arithmetic per gate.
D7. PRE-FLIGHT CHECKER SHAPE SELF-TEST (L-17): run
    `python3 tools/gaterunner/selftest_checkers.py` before the first held-out contact;
    paste the full per-vector table (6 vectors, `rational_5_2` and `zero_event` rows
    visible, `expected-fail ok` line visible) and exit=0. Any other outcome: STOP → BLOCKED.
D8. WORKSPACE-STATE CRITERION (L-13 v2, corrected text of record): byte-verbatim git status
    pasted in full; untracked entries within the agent-writable surface that first appear
    after this dispatch's CLAIM commit are limited to files this task creates pre-commit;
    pre-existing untracked entries within the surface are identified as inherited with a
    stated disposition.

All other GATE-P1 text applies verbatim: G0–G2, P1-A through Law 7 definitions and checkers,
gate-authorized logging (I-004, gate_id set, every execution appended to ACCESS_LOG.jsonl),
manifests engine_git_dirty=false (tracked-file dirty; untracked courier surface exempt,
PREREG v1.3 C2), halt order P1-A → P1-B → P1-C → Law 7 with halt-on-failure (v1.2 B3).
This dispatch overwrites `reports/GATE_SUMMARY.md` (R2's halt record is preserved in
TR_GATE-P1-R2.md and JRN-C001-78/-79). TR filename: `reports/TR_GATE-P1-R3.md`.
Branch: `task/GATE-P1-R3` from `task/C-001-T15` tip.

Steps:
3. Toolchain record paste.
4. REPAIR + HOUSEKEEPING (single commit, before G0):
   a. OUT_51 criterion-7 repair: paste a listing (`ls -laR`) of
      `docs/03_TRACKS/C-001_exact_collision_engine/reports/gate_r2_evidence/`, affirm it
      predates this branch's CLAIM (inherited R2 evidence scratch), and commit it in place
      as R2 evidence of record (mirroring committed gate_r1_evidence/).
   b. D5 stale-gate-output removals (mechanics per observed status lines, pasted).
5. G0 tracked-clean status paste (`git status --porcelain --untracked-files=no`) — after
   the step-4 commit, before any gate run.
6. Configure + build + ctest + doctest; pastes; exit=0; 100% + SUCCESS!.
7. D1 pre-flight load survey paste — complete, all 32 lines.
8. D3 `--repeat 3` calibration smoke paste.
9. D4 zero-event write pre-flight paste.
10. D7 checker shape self-test paste.
11. D6 pre-run ACCESS_LOG count paste (=56 or BLOCKED). Execute P1-A per GATE-P1 rules —
    execute AND check; paste the checker report in full (per-scenario worst |Δt| and |Δs|
    table, per-family and per-regime distributions, quasi-chaotic events 13–25 exploratory
    table, both red-team tables, verdict line); all 32 manifests engine_git_dirty=false.
12. If P1-A PASS: execute P1-B; paste (i)(ii)(iii) evidence + verdict. Else halt per G2.
13. If P1-B PASS: execute P1-C; paste per-fixture table (first-divergence index,
    interval-sequence hash) + verdict. Else halt.
14. If P1-C PASS: execute Law 7; paste comparison table, shortfall list, drift table, both
    primary arms, verdict. Else halt.
15. D6 post-run count + excerpt + per-gate reconciliation arithmetic paste.
    GATE_SUMMARY.md pasted verbatim (four verdict lines with governing numbers, halt point
    if any, manifests' sha256s).
16. Byte-verbatim `git status --porcelain --branch` (D8).
17. TR + OUT per OUT-REQUIREMENTS in the dispatching packet.

Acceptance criteria (binary, one artifact each — INDEPENDENT of gate verdicts):
1. Step 3: toolchain pasted.
2. Step 4a: gate_r2_evidence/ listing + inherited affirmation + committed-in-place (the
   step-4 commit visible in BRANCH/COMMITS) — the OUT_51 criterion-7 repair.
3. Step 4b: per-path status line + removal evidence + post-removal listing for the R2 gate
   outputs.
4. Step 5: G0 tracked-clean paste after the step-4 commit, before first gate run.
5. Step 6: configure/build/ctest/doctest pastes; exit=0; 100% + SUCCESS!.
6. Step 7: COMPLETE 32-line survey + `load_ok 32 / 32`; no elision.
7. Step 8: `repeat-identity ok N=3`; no held-out contact before step 11.
8. Step 9: zero-event smoke — exit=0, `events=0`, `"engine_events":0` header.
9. Step 10: full self-test table (6 vectors; `expected-fail ok` visible); exit=0.
10. Step 11: pre-run ACCESS_LOG count (=56 or BLOCKED); P1-A checker report pasted in full
    (all named tables + verdict line); all 32 manifests engine_git_dirty=false.
11. Steps 12–14 (as reached per G2): full evidence + verdict line per executed gate; any
    halt documented with the failing numbers.
12. Step 15: post-run count, excerpt, and per-gate reconciliation arithmetic matching the
    manifests; GATE_SUMMARY.md pasted verbatim.
13. TR affirms: no fixture/tune/physics/checker modification; all held-out execution
    gate-authorized via I-004 with gate_id set; halt order honored; ACCESS_LOG untouched
    except by runner appends.
14. Step 16: D8 satisfied — full byte-verbatim status; post-CLAIM untracked delta limited
    to this dispatch's files; any inherited entries identified with disposition.
15. FILE DIGESTS complete per L-15 (checkers + ref_parse + selftest of record — unmodified,
    digests prove D0 — every manifest of this dispatch, GATE_SUMMARY, TR, every applied
    brain file of this packet) with full untruncated sha256s; TR pasted verbatim in REPORT
    (L-16); every journal entry of this dispatch verbatim; applied-files directions listed.

## TASK C-001-T16: Forensic diagnostic of the executed P1-A check (read-only; no verdict)
depends_on: OUT_52 GATE-P1-R3 (task ACCEPT; P1-A verdict SUB JUDICE, JRN-C001-87); R3 gate
artifacts committed (b426bbd: 32 event files + manifests/P1-A.json); PREREG v1.3 (§1, v1.2
B2, v1.3 C1); C-001-T15 VERIFIED
objective: Determine, from committed artifacts and source only, why the executed P1-A
comparison windows (0–9) differ from the registered windows (12 quasi-chaotic /
min(200, settle) otherwise), and classify the mechanism per the pre-registered rules below
(v1.2 B2: harness defect is fixed before gates; a physics shortfall stands). This task
produces a DIAG report — counts, verbatim code quotes, bounded excerpts, per-scenario rule
classification. It produces NO gate verdict and modifies NOTHING.

HARD RULES:
H1. ZERO engine invocations — no bounce-run-scenario, no bounce-baseline-run, on any
    scenario class whatsoever. Nothing needs to run; everything needed is on disk.
H2. No checker corpus run: no `check_p1a.py --check` (or equivalent verdict-producing
    invocation) against the R3 manifest. Reading checker SOURCE is required; running it is
    forbidden.
H3. No modifications outside `reports/`, journal, `outbox/`. Checkers, fixtures, engine,
    manifests, event files: read-only.
H4. Held-out exposure bounded: reference COUNTS for all 32; reference VALUES only within
    the three D4 excerpts (≤8 events per side per scenario). No full reference dumps.
H5. The DIAG report's final section states which rule (R-a..R-e) fires per anomalous
    scenario and stops there — no "P1-A would PASS/FAIL" statements anywhere.

PRE-REGISTERED CLASSIFICATION RULES (PM; applied in D5, not reinterpreted):
R-a. engine_events < registered_window AND reference_events ≥ registered_window →
     engine stream shortfall: candidate PHYSICS (missed/absent contacts under the engine's
     own dynamics; stands per v1.2 B2), subject to D4 confirming the short side at the
     event level.
R-b. reference_events < registered_window → corpus defect vs registration (I-003
     escalation; reference streams must cover the registered horizon).
R-c. engine_events ≥ registered_window AND reference_events ≥ registered_window AND
     executed_window < registered_window → harness defect (checker window/pairing logic).
R-d. Properly paired events (same seq/ball_id, both streams covering the window) with
     value disagreement over tolerance → PHYSICS; stands.
R-e. |ds| discrepancy consistent with s-parameter endpoint wrap (values differing by the
     parameter-domain length at a domain endpoint) while |dt| is at rounding scale →
     harness comparison-semantics candidate; PM rules on the D4 evidence.
Registered_window per scenario: 12 for the four quasi-chaotic cells (v1.3 C1); otherwise
min(200, reference_events), reference streams embodying the S-1 settle horizon by
construction (I-002-T2/T3a). If a fixture's own horizon metadata contradicts its reference
stream length, flag it in D1 (feeds R-b).

Steps:
3. Chain of custody: verify the manifest's per-scenario event-file sha256s against the
   committed R3 event files; paste the verification command + `custody ok 32/32` style
   output (any mismatch: STOP → BLOCKED).
4. D1 COUNT TABLE (all 32 rows): scenario_id | engine_events per the event-file HEADER |
   engine event body line count (must equal header; flag any mismatch) | reference_events
   count from fixture JSON | registered_window | executed_window (from the R3 report,
   transcribed) | short side (engine / reference / neither).
5. D2 WINDOW AUDIT: quote verbatim (with line numbers) the check_p1a.py code that derives
   the per-scenario comparison window; state its formula; state the deviation from §1 +
   v1.3 C1 explicitly.
6. D3 PAIRING AUDIT: quote verbatim the event-pairing/comparison loop; state whether
   "ball_id and seq exactly equal per event" and count-mismatch failure are enforced or
   whether streams are zip-truncated silently; quote how s is compared, including any
   normalization/wrap handling at parameter-domain endpoints.
7. D4 EXCERPTS (exactly three scenarios; ≤8 events per side each; verbatim from committed
   files, seq and ball_id visible): HO-flat-periodic-3 around the first |ds|-anomalous
   event; HO-poly-quasichaotic-1 around the first divergence; HO-parabola-settle-2 around
   the first divergence. For each: the aligned reference and engine events, and one
   sentence naming what the excerpt shows (desynchronization / genuine value divergence /
   wrap artifact / missing event on <side>).
8. D5 CLASSIFICATION: per scenario with any anomaly (short window, FAIL row, or vacuous
   window-0 PASS), the rule R-a..R-e that fires, from D1+D4 evidence only. One summary
   line: counts of scenarios per rule. No verdict language (H5).
9. Paste byte-verbatim `git status --porcelain --branch`; D8/L-13 v2 disposition
   (post-CLAIM delta = DIAG report + evidence scratch only; inherited entries identified).
10. DIAG report (`reports/DIAG_C-001-T16.md`) + OUT per OUT-REQUIREMENTS in the dispatching
    packet.

Acceptance criteria (binary, one artifact each):
1. Step 3: custody verification paste — 32/32 event-file sha256s match the manifest.
2. Step 4: D1 table complete, 32 rows, both engine count sources shown (header + body) and
   agreeing or flagged, short-side column filled.
3. Step 5: D2 verbatim window-derivation quote with line numbers + formula + stated
   deviation from §1/C1.
4. Step 6: D3 verbatim pairing quote with line numbers + seq/count enforcement disposition
   + s-comparison wrap disposition.
5. Step 7: three D4 excerpts, bounded per H4, seq/ball_id visible, one-sentence finding
   each.
6. Step 8: D5 classification per anomalous scenario under R-a..R-e + per-rule summary
   counts; no verdict language anywhere in the report (H5).
7. TR-level affirmations in the DIAG report: H1 (zero engine invocations — and ACCESS_LOG
   line count pasted, must still be 88), H2, H3, H4 honored.
8. Step 9: byte-verbatim status; L-13 v2 delta assertion + inherited dispositions.
9. FILE DIGESTS complete per L-15 (DIAG report, every applied brain file of this packet;
   checker + manifest digests restated to prove read-only — must match OUT_52's) with full
   untruncated sha256s; DIAG report pasted verbatim in the OUT's REPORT section (L-16);
   every journal entry of this dispatch verbatim.

## TASK C-001-T17: Contact-loop correctness — fix defect classes E1/E2/E3 (repro-first)
depends_on: OUT_53 C-001-T16 ACCEPT + falsification record (JRN-C001-91); Director
direction D-4; I-002-T2 Tier-1 fixture generator (VERIFIED); C-001-T13/T14/T15 lineage
objective: Make the engine emit the CORRECT event stream — first contact found, departed
roots never re-detected, per-ball time strictly monotonic, values within 1e-9 of Tier-1
references over full streams — demonstrated repro-first on fresh non-held-out fixtures.
Long-horizon loop stability (P1-C territory) is OUT of scope per D-4. This is an engine
construction task: no checker, tune, prereg, or held-out changes.

DEFECT CLASSES (from T16, binding targets):
E1. Missed first contact: zero events emitted on scenarios of the periodic-parabola class
    where contacts exist.
E2. Departure-root re-collision: after an impact at t0, the next root search re-detects the
    just-departed contact (duplicate event at t == t0 or t0 ± ulp; non-monotonic per-ball
    t; energy bleed under e<1; premature stream termination). Fix must guarantee the next
    root is strictly after departure with the departure tangency excluded analytically
    (deflation or strict open-interval semantics — design is the agent's), not by an
    epsilon fudge that trades this bug for missed genuine near-immediate contacts
    (grazing/double-root regression suite must stay green).
E3. Value divergence over 1e-9 at fully paired windows (bezier-settle / parabola-settle
    classes). Investigate after E1/E2 land; if a genuine precision defect remains on the
    fresh fixtures, fix it; if the divergence traces to reference generation instead,
    BLOCKED with the evidence (do not touch the generator in this task).

CONTAMINATION HYGIENE (LAW-1 extension, binding): zero executions under
data/scenarios/heldout/ (ACCESS_LOG must read 88 before and after this task — paste both).
New fixtures are minted via the COMMITTED I-002-T2 generator with FRESH parameters; no
fixture may replicate any held-out fixture's parameter tuple. TR carries an explicit
affirmation of both.

Steps:
3. Toolchain paste.
4. Housekeeping (single commit, before any src/ change): commit
   docs/03_TRACKS/C-001_exact_collision_engine/reports/gate_r3_evidence/ in place as R3
   evidence of record (L-13 v2 disposition inherited from OUT_52/53). Paste the commit
   line + G0 tracked-clean status.
5. REPRO FIXTURES (RED): mint ≥4 fresh Tier-1 calibration fixtures under
   data/scenarios/calibration/t17/ — CF-E1 (periodic parabola, reference ≥6 events),
   CF-E2a (parabola settle, e<1, reference ≥4 events), CF-E2b (poly deg≥3, reference ≥12
   events), CF-E3 (bezier settle, full-stream class). Paste generator invocations + fixture
   digests. Run the PRE-FIX engine on each (calibration execution — permitted) and paste
   the RED evidence per class: E1 zero events; E2 duplicate/ulp-earlier t at the departure
   contact; E3 divergence if it reproduces (if CF-E3 is green pre-fix, say so — E3 then
   rides the post-fix investigation of step 8).
6. FIX: implement the contact-loop corrections in src/core (agent's design; event schema
   unchanged; FP-determinism flags untouched).
7. GREEN: re-run every CF fixture; paste per-fixture: exact event-COUNT equality engine vs
   reference, and per-event |Δt| ≤ 1e-9 AND |Δs| ≤ 1e-9 over the FULL reference stream
   (worst per fixture shown), seq and ball_id equal per event.
8. E3 disposition: with E1/E2 fixed, state CF-E3's status with numbers; if divergence >
   1e-9 persists, fix and re-paste green, or BLOCKED with mechanism evidence per the E3
   rule above.
9. INVARIANTS (doctest, permanent): per-ball strictly increasing t across every emitted
   stream; no consecutive duplicate (t_hex, s_hex) per ball; CF fixtures wired into the
   suite. Paste full ctest + doctest (existing 54 cases + new; 100% + SUCCESS!).
10. REGRESSION: FL-1 and PB-1 calibration comparisons still exact (paste); grazing /
    double-root / zero-event suites green (contained in step 9's run — call out the graze
    cases explicitly); `--repeat 3` smoke on one CF fixture: `repeat-identity ok N=3`
    (determinism not regressed).
11. Byte-verbatim `git status --porcelain --branch`; L-13 v2 delta assertion + inherited
    dispositions.
12. TR (`reports/TR_C-001-T17.md`) + OUT per OUT-REQUIREMENTS in the dispatching packet.

Acceptance criteria (binary, one artifact each):
1. Step 3 toolchain pasted.
2. Step 4: gate_r3_evidence commit line + G0 tracked-clean paste.
3. Step 5: ≥4 fixture mints (generator invocations + digests) + RED paste per class as
   specified (E1 zero events; E2 duplicate/non-monotonic t; CF-E3 status stated).
4. Step 7: GREEN paste per fixture — event-count equality + worst |Δt|,|Δs| ≤ 1e-9 over the
   full reference stream + seq/ball_id equality.
5. Step 8: E3 disposition with numbers (green, or BLOCKED with mechanism).
6. Step 9: invariant tests present and named in the doctest output; full suite 100% +
   SUCCESS!; exit=0.
7. Step 10: FL-1/PB-1 exact; graze cases called out green; repeat-identity ok N=3.
8. TR affirms: ACCESS_LOG 88 before AND after (both pastes); zero held-out executions; no
   CF fixture replicates a held-out parameter tuple; no changes to checkers, tune, prereg,
   or data/scenarios/heldout/.
9. Step 11: byte-verbatim status; L-13 v2 post-CLAIM delta limited to this task's files;
   inherited entries identified with disposition.
10. FILE DIGESTS complete per L-15 (every changed src/ file, every CF fixture, tests,
    TR, every applied brain file of this packet) with full untruncated sha256s; TR pasted
    verbatim in REPORT (L-16); every journal entry of this dispatch verbatim.

## TASK C-001-T18: E4 premature stream termination — isolate, root-cause, fix (repro-first)
depends_on: OUT_63 diagnostic D1 (JRN-I008-24); defect registration JRN-C001-98; T17
VERIFIED baseline; I-002 generator (Tier-2, per-class tier rule JRN-C001-97)
objective: Determine whether E4 lives in the engine or the harness pipeline; if
engine-side, fix it in src/core with repro-first evidence; leave the engine able to
sustain confined lossless streams to arbitrary event caps.
branch: `task/C-001-T18` from the task/I-008-T5 tip (stacked; carries the D1 scene and
all prior work).
Standing constraints: FP-determinism flags untouched; event schema unchanged; no changes
to checkers, tune, prereg, tools/bounce-view/, or anything under data/scenarios/heldout/;
fresh fixture parameter tuples never replicate held-out tuples; ACCESS_LOG reads 88
before and after. Steps and acceptance criteria are carried verbatim in the dispatching
packet (PACKET 64).

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

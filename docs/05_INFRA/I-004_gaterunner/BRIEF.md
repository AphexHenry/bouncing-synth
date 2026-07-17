# BRIEF — I-004 Gate runner + manifests

```
doc_id:   I-004-BRIEF
layer:    infra
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   INFRASTRUCTURE_REGISTER / PROJECT §7–§8 / C-001-PREREG §0, §5, §6
```

## Context for agents
I-004 is the sole execution path for every §8 gate study (C-001-PREREG §0): it runs scenarios
against engine binaries, writes the manifest of record (engine commit, toolchain, FP flags,
scenario identities, event outputs, timings), and — from T3 — is the only component permitted
to touch the I-003 held-out corpus. Layered design: a C++ scenario-runner CLI (T1) that turns
one scenario file into one canonical event file, and a Python orchestrator (T2) that drives
it across a study and writes manifests. Authorship (L-14): packets supply specs, interface
definitions, formats, and acceptance shape; all implementation is agent-authored. If a spec
is ambiguous, BLOCK — do not infer.

## Files you may read
- `AGENTS.md` · assigned `inbox/PACKET_<n>.md` · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- `docs/00_PROJECT.md` §6–§8 · `docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md`
- This brief · this track's `JOURNAL.md`
- `src/core/bounce/` (engine library headers, calibration loader) · `tests/` (existing patterns)
- `config/fp-determinism.cmake` · `data/scenarios/calibration/` (read-only)
- `tools/refsim/` (I-002, read-only; T2+)

## Files you will write
- `src/tools/run_scenario/` (T1 CLI) · `src/core/bounce/io/` (T1 serialization) · `tests/`
- `tools/gaterunner/` (T2+, Python)
- `docs/05_INFRA/I-004_gaterunner/JOURNAL.md` (append)
- `docs/05_INFRA/I-004_gaterunner/reports/` task reports
- `outbox/OUT_<serial>_I-004-T<n>.md`

## TASK I-004-T1: scenario-runner CLI + canonical lossless event serialization + unit tests
depends_on: C-001-T10 VERIFIED (JRN-C001-41); I-001 (VERIFIED)
objective: A `bounce-run-scenario` CLI target and an event-serialization module such that the
byte content of an output file is a lossless, canonical encoding of the engine's
CollisionEvent sequence — making downstream bit-identity gates (P1-B, P1-C) file-hash
comparisons.

SPEC (binding; BLOCK on any ambiguity):
1. CLI: `bounce-run-scenario --scenario <path> --out <path> [--max-events N]`.
   - Loads a schema-v1 calibration scenario via the existing loader
     (src/core/bounce/scenario/), runs it via the existing engine entry point to its horizon
     (or N events if --max-events given), writes the canonical event file to --out.
   - Exit 0 on success. Any failure (unreadable scenario, schema violation, engine error):
     exit nonzero with a one-line diagnostic on stderr; --out must not be left half-written
     (write to temp, rename on success).
   - stdout: nothing except an optional final one-line summary (`events=<n>`).
2. Canonical event file format (JSONL — one event per line, LF line endings, no trailing
   whitespace, UTF-8, no BOM):
   - Every field of the PROJECT §6 CollisionEvent struct is emitted, keys in a single fixed
     order defined once in the serialization module and documented in a header comment.
   - Floating-point fields: emitted as BOTH `"<name>_hex"` — C hexfloat via
     `std::format("{:a}", v)` or printf `%a` equivalent (bit-lossless) — and `"<name>"` —
     shortest round-trip decimal (17 significant digits max) for human reading. The hex field
     is authoritative; the parser reads hex only.
   - Integer fields: decimal.
   - First line of the file is a header object: `{"schema":"bounce-events-v1",
     "scenario_sha256":"<hex>", "engine_events":<count>}` where scenario_sha256 is the digest
     of the input scenario file bytes.
3. Parser: a `read_event_file` function returning the CollisionEvent sequence, reading
   hexfloat fields; round-trip law (tested): serialize → parse → events_equal (the existing
   exact-== helper) is bit-exact for every event.
4. Determinism law (tested at smoke level here; gate-level in P1-B): two consecutive CLI runs
   on the same scenario produce byte-identical output files.
5. No heap-allocation or FP-flag changes inside src/core/bounce/ engine paths; the
   serialization module lives in src/core/bounce/io/ and the CLI in src/tools/run_scenario/;
   engine code is not modified by this task (BLOCK if the spec seems to require it).

Steps:
3. Paste toolchain record: `cmake --version` and compiler `--version` (P6 §4.5).
4. Configure: `cmake --preset default`; paste tail; must end exit=0.
5. Build: paste tail (must show the new bounce-run-scenario target); must end exit=0.
6. Test: `ctest` from the build dir; paste output and the doctest summary block from
   build/default/Testing/Temporary/LastTest.log; must show 100% tests passed and doctest
   Status: SUCCESS!, exit=0. New tests required: round-trip law (spec §3) on the FL-1 run;
   header-line content; nonzero-exit behavior on a missing scenario path.
7. CLI smoke: run `bounce-run-scenario --scenario data/scenarios/calibration/<FL-1 file>
   --out /tmp/fl1_a.jsonl` twice (second to /tmp/fl1_b.jsonl). Paste: both commands with
   exit codes, `head -3 /tmp/fl1_a.jsonl`, and `shasum -a 256 /tmp/fl1_a.jsonl
   /tmp/fl1_b.jsonl` — the two digests must be identical.
8. Diagnostics (read-only, for the record; no assertion): paste the outputs of
   `git log --oneline -1 task/C-001-T10`, `git log --oneline -3 main`, and
   `git branch --no-merged main`.
9. Paste `git status --porcelain --branch`.
10. TR + OUT per OUT-REQUIREMENTS.

Acceptance criteria (binary, one artifact each):
1. Step 4 output pasted; ends exit=0.
2. Step 5 output pasted; shows bounce-run-scenario target built; ends exit=0.
3. Step 6 output pasted; contains `100% tests passed` and doctest `Status: SUCCESS!` from
   LastTest.log; ends exit=0.
4. Step 7 pasted: both CLI runs exit=0; head -3 shows the schema header line and hexfloat
   fields; the two sha256 digests are identical.
5. Step 8 diagnostic pastes present (three commands, verbatim; record only, no assertion).
6. Step 9 pasted: no modified tracked entries; untracked within the agent-writable surface
   (L-13: src/, tests/, config/, data/, reports/, docs/, tools/, outbox/) limited to the
   files this task creates, pre-commit; Director courier surface pasted for record only.

## TASK I-004-T2 (sketch): Python orchestrator + manifest writer — study spec in, per-scenario
CLI invocations, manifest (engine commit, toolchain, FP flags, scenario sha256s, event-file
sha256s, wall-times, median-of-10 timing per C-001-PREREG §5) out. At next packet.

## TASK I-004-T3 (sketch): held-out access integration — I-003 lock honored; every held-out
execution logged to the manifest; any non-runner access path closed. After I-003-T2.

## TASK I-004-T2+T3 (batched): study orchestrator + manifest writer + held-out access discipline
depends_on: I-004-T1 VERIFIED (JRN-I004-4); I-003-T3 VERIFIED (JRN-I003-22; corpus 32
locked); C-001-PREREG v1.1 §0, §5, §6
objective: The gate runner proper — the sole execution path for §8 gate studies — able to
run a declared study over a scenario set via the T1 CLI and emit a complete, reproducible
manifest of record; with the I-003 split-lock honored mechanically, not by convention.

STEP 0 — OUT_41 REMEDIATION (L-15 v2, mandatory, before any T2+T3 work):
(a) From committed fixture provenance, print the full per-fixture Tier-2 convergence table
    for all 32 held-out scenarios (Tier-1 fixtures report their R4 values); paste verbatim;
    assert the floor equals 46.8995055434254 (HO-poly-quasichaotic-3) and all ≥45. Mismatch
    → BLOCKED OUT.
(b) Paste verbatim the applied PM journal entries of serial 41 (JRN-I003-17/-18/-19 and the
    PREREGISTRATION Amendment v1.1 block) from the committed docs.
(c) Restate the serial-41 applied-files list WITH directions (APPEND/OVERWRITE per file).

SPEC (binding; BLOCK on any ambiguity):
1. Study spec format (tools/gaterunner/studies/*.json): fields — study_id; gate_id (string
   or null: null = calibration-only smoke; non-null = gate authorization); scenario_set
   ("calibration" | explicit list of held-out ids); horizon (max_events integer or
   "to_settle"); timing_runs (default 10); notes. The runner passes horizon to the CLI
   (--max-events) — the binary default is never relied upon.
2. Lock discipline (T3 scope): before any execution the runner validates the split-lock
   state (reuse/wrap validate_store.py logic or read the lock file directly). If any
   requested scenario is held-out: REQUIRE gate_id non-null, else refuse with a one-line
   error and nonzero exit (no execution, no log entry beyond the refusal record). Every
   held-out execution (when authorized) appends {scenario_id, sha256, study_id, gate_id,
   engine_commit, timestamp} to data/scenarios/heldout/ACCESS_LOG.jsonl. Calibration
   scenarios are never logged.
3. Manifest of record (one JSON per study run, tools/gaterunner/manifests/ →
   reports/ per conventions): engine git commit (HEAD at run time) + dirty flag; cmake and
   compiler version strings; FP-determinism flags (read from config/fp-determinism.cmake);
   per scenario — scenario sha256, event-file sha256, event count, exit code, wall-times
   (all timing_runs values + median); runner tool version (its own git-tracked sha256);
   study spec embedded verbatim.
4. Determinism cross-check (calibration): running the same study twice must produce
   byte-identical event files per scenario (manifest event-file sha256s equal across the
   two runs); wall-times of course differ — the manifest separates identity-bearing fields
   from timing fields, and the runner exposes a `--compare <manifest_a> <manifest_b>` mode
   that verifies identity-bearing equality and reports it.
5. HARD RULE for this task: no held-out scenario is executed. The negative test (§2
   refusal) targets a held-out id but must be refused BEFORE any engine invocation; the
   acceptance evidence includes proof ACCESS_LOG.jsonl does not exist or is empty after all
   steps.
6. Python: pinned venv; stdlib + mpmath only (no new deps without BLOCK). Agent-authored
   throughout (L-14); this brief is the spec of record.

Steps:
3. Toolchain + venv record (cmake --version, compiler --version, python --version).
4. Build: configure + build current binaries; paste tails; exit=0 both.
5. ctest; paste output + LastTest.log doctest summary; 100% passed, SUCCESS!, exit=0.
6. Implement tools/gaterunner/ per §1–§4. Write the calibration smoke study
   (studies/SMOKE-CAL-1.json: gate_id=null, scenario_set=calibration, horizon to_settle,
   timing_runs=10). Run it TWICE; paste both invocations + exits; paste manifest head
   (identity-bearing fields) of run A; paste `--compare` output showing identity across
   A/B.
7. Negative test: a study targeting one held-out id with gate_id=null; paste the refusal
   (one-line error, nonzero exit). Then paste proof the access log is absent/empty
   (`ls data/scenarios/heldout/ACCESS_LOG.jsonl 2>&1` or `wc -l` if created-empty by
   design — state which).
8. Paste `git status --porcelain --branch` byte-verbatim.
9. TR + OUT per OUT-REQUIREMENTS.

Acceptance criteria (binary, one artifact each):
0. Step 0 remediation (a)+(b)+(c) pasted; convergence floor matches; all ≥45.
1. Step 3 pasted.
2. Step 4 pasted; both exit=0.
3. Step 5 pasted; 100% passed + SUCCESS! + exit=0.
4. Step 6: both smoke runs exit=0; manifest contains all §3 fields; --compare reports
   byte-identity of event files across the two runs for every calibration scenario.
5. Step 7: refusal pasted (nonzero exit, no execution); access log absent or empty, proof
   pasted.
6. TR affirms §5 hard rule (no held-out execution) and lists any deviations.
7. Step 8: byte-verbatim status; tracked modifications limited to task-owned files
   pre-commit; untracked within agent-writable surface limited to files this task creates
   (L-13).
8. FILE DIGESTS complete per L-15 (applied docs, all tools/gaterunner/ files, study specs,
   manifests, TR).
9. OUT completeness per L-10: ALL journal entries of this dispatch verbatim (PM entries +
   CLAIM + DONE/BLOCKED), applied-files list with directions.

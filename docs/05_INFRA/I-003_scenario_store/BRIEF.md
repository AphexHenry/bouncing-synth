# BRIEF — I-003 Scenario store + split-lock

```
doc_id:   I-003-BRIEF
layer:    infra
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   INFRASTRUCTURE_REGISTER I-003 / DELIVERABLE_C §2 / config/scenario-fixture-schema-v1.json
```

## Context for agents
Law-1 enforcement surface: `data/scenarios/calibration/` (development) vs `heldout/` (gate-only).
Schema pinned at I-002-T4. Split-lock machinery prevents held-out peeking during development.
Held-out reads require `BOUNCE_HELDOUT_LOCK=1` (set by I-004 gate runner at gate time).

## Files you may read
- `AGENTS.md` · assigned packet · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- `config/scenario-fixture-schema-v1.json` · `data/scenarios/`
- `docs/05_INFRA/I-002_refsim/BRIEF.md` (T4 lineage)

## Files you will write
- `data/scenarios/` store artifacts · `tools/scenarios/` validators per task
- `docs/05_INFRA/I-003_scenario_store/JOURNAL.md` (append)
- `docs/05_INFRA/I-003_scenario_store/reports/` · `outbox/`

## TASK I-003-T1: Split-lock marker + store validator + held-out empty manifest
depends_on: I-002-T4 VERIFIED (JRN-I002-25); schema v1 on disk
objective: Formalize calibration vs heldout access rules; validator exits 0 on the seeded
           calibration corpus; rejects held-out access without BOUNCE_HELDOUT_LOCK.
VERIFIED (JRN-I003-5; OUT_23; TR_I-003-T1.md).

## TASK I-003-T2: Tier-1 held-out corpus mint + lock (C-001-PREREG §7 input contract)
depends_on: I-003-T1 VERIFIED (JRN-I003-5); I-002 VERIFIED (JRN-I002-25); C-001-PREREG v1.0
objective: Mint 16 Tier-1 held-out scenarios covering the Tier-1 cells of the C-001-PREREG §7
coverage table, with references computed by the I-002 refsim/CAS machinery at Tier-1 standard,
and lock them into the held-out manifest via the I-003-T1 split-lock machinery — before any
engine execution ever touches them.

SPEC (binding; BLOCK on any ambiguity):
1. LAW-1 HARD RULE: no C++ engine binary (bounce-tests, bounce-run-scenario, or any target
   linking bounce-core) is built, linked, or invoked anywhere in this task. The mint uses the
   pinned Python venv + refsim/CAS only. A held-out scenario executed by the engine before
   lock is poisoned (C-001-PREREG §6). The TR must state this affirmatively.
2. Registered per-cell counts (16 total; naming HO-<family>-<regime>-<k>):
   a. flat line × settle: 4 — 2 single-ball, 2 multi-ball (2 and 3 balls).
   b. flat line × periodic, non-dyadic: 3 — 2 single-ball, 1 multi-ball (2 balls).
   c. parabola (deg 2) × settle: 4 — 2 single-ball, 2 multi-ball (2 and 4 balls).
   d. parabola × periodic (bowl orbit): 2 — single-ball.
   e. grazing block on parabola: 3 — single-ball, |v_n| at contact = 0.5×, 1.0×, 2.0× v_graze.
3. Non-dyadicity (cell b, d): each periodic fixture's period must NOT be exactly
   representable as a dyadic rational. Constructive check required: derive the period in
   closed form at ≥50-digit precision and verify its double rounding is inexact (period ≠
   its nearest double, or symbolic form contains a non-dyadic irrational such as sqrt of a
   non-square). Record the check's output per fixture. BLOCK if a chosen parameterization
   comes out dyadic — pick new parameters, do not waive.
4. Multi-ball fixtures (R2: no ball–ball interaction): per-ball closed-form sequences merged
   under TB-1 ordering (min t, then ball_id) computed exactly in the reference layer; the
   merged sequence is the oracle.
5. Grazing block (cell e): construct initial conditions whose closed-form normal impact
   speed at first contact equals the registered multiple of v_graze to ≥50-digit precision.
   v_graze MUST be read programmatically from the versioned G-1 rule-constants source of
   record (I-001) — never retyped. Record the constant's value and version in each fixture.
   The oracle for the 0.5× case includes its G-1 classification (inadmissible/graze path) —
   the classification is part of the reference, computed from the rule definition, not from
   the engine. BLOCK if the constant is not machine-readable from a single source.
6. Fixture format: the schema-v1 scenario JSON already in use, plus reference events at
   Tier-1 standard (I-002 conventions), plus provenance fields: tier, generator git commit,
   mpmath version, non-dyadicity check output (cells b/d), v_graze value+version (cell e).
7. Storage + lock: fixtures under data/scenarios/heldout/; each registered in the I-003-T1
   held-out manifest with its sha256 at mint time; the split-lock marker updated per the
   T1 machinery. The calibration set is untouched.
8. Concentration check (C-001-PREREG §8.iii): no family >50% of the held-out corpus — with
   these counts flat line = 7/16, parabola = 9/16; 9/16 = 56% exceeds the cap ONLY if
   computed per-family — the registered corpus is Tier-1-partial; the cap binds on the FULL
   corpus after T3 (Tier-2 mint adds deg 3–6 + Bézier). Record current ratios in the TR;
   no waiver needed at T2.

Steps:
3. Paste venv record: `python --version`, `pip show mpmath | head -2` from the pinned venv.
4. Implement the mint (tools/ per I-003 conventions; agent-authored, L-14) and generate the
   16 fixtures. Paste the generator invocation(s) and exit codes.
5. Paste the non-dyadicity check output for cells b/d (per fixture) and the grazing
   construction record for cell e (v_graze value+version, achieved |v_n|/v_graze ratios to
   ≥20 significant digits).
6. Run the I-003-T1 store validator over the updated store; paste output; must exit 0.
7. Paste the held-out manifest diff (`git diff --stat` of the manifest + the 16 new entries
   with sha256s) and `ls data/scenarios/heldout/`.
8. Paste `git status --porcelain --branch`.
9. TR + OUT per OUT-REQUIREMENTS.

Acceptance criteria (binary, one artifact each):
1. Step 3 pasted: pinned venv, mpmath 1.3.0.
2. Step 4 pasted: generator run(s) end exit=0; 16 fixtures created with registered names.
3. Step 5 pasted: non-dyadicity check inexact/irrational for every cell-b/d fixture;
   grazing ratios match {0.5, 1.0, 2.0} to ≥20 significant digits; v_graze read from the
   versioned source (value + version shown).
4. Step 6 pasted: store validator exit=0 over the updated store.
5. Step 7 pasted: manifest contains exactly 16 new held-out entries with sha256s;
   data/scenarios/heldout/ lists exactly the 16 files.
6. TR affirms LAW-1 HARD RULE (spec §1): no engine binary built/linked/invoked in this task.
7. Step 8: no modified tracked entries beyond the manifest/store files this task owns;
   untracked within the agent-writable surface limited to files this task creates,
   pre-commit (L-13); courier surface pasted for record only.

## TASK I-003-T3 (sketch): Tier-2 held-out mint — deg 3–6 polynomials, piecewise Bézier,
quasi-chaotic (25-event cap), near-double-root geometry — via refsim with
reference_converged; closes the C-001-PREREG §7 table and the §8.iii concentration cap.
At next packet after T2 VERIFIED.

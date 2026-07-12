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

## TASK I-003-T2-R1: re-mint of the 16 Tier-1 held-out fixtures (float64 contamination fix)
depends_on: I-003-T2 REJECTED (JRN-I003-9); supersedes the quarantined 2026-07-12 mint
objective: Same deliverable as I-003-T2 (16 Tier-1 held-out fixtures per the registered
per-cell counts, locked on mint), with the float64 contamination class eliminated and the
evidence bar met exactly.

SPEC DELTAS (binding; everything not restated carries over from I-003-T2):
R1. PRECISION DISCIPLINE: all derivation runs at mpmath mp.dps ≥ 50 end-to-end. Exactly two
    float64 touchpoints are permitted in the entire pipeline:
    (a) reading the v_graze constant: parse the C++ literal from the versioned G-1 source,
        convert once to its exact IEEE-754 double, and lift that exact binary value into
        mpmath (e.g. via float.hex round-trip). Record the double's hex form
        (float.hex(v_graze)) in every grazing fixture as provenance.
    (b) the final write of each scenario/reference field: one correctly-rounded
        mpf → double conversion per value, at serialization time only.
    Any other float() / numpy / Python-float arithmetic on derived quantities is a defect.
R2. NON-DYADICITY (cells b/d), constructive, no escape hatch: for each fixture, compute the
    period P from its closed form at dps=50; let d = the nearest double to P; REQUIRE the
    strict inequality mpf-exact(d) ≠ P and print P (true 50-digit value), d (17-significant-
    digit round-trip), and |P − d| at ≥30 significant digits. The symbolic_non_dyadic field
    is removed. BLOCK if a parameterization yields |P − d| = 0; choose new parameters.
R3. GRAZING EXACTNESS: with v* = the exact double v_graze lifted per R1(a), set the target
    normal impact speed v_n = r × v* exactly in mpmath for r ∈ {0.5, 1.0, 2.0} (powers of
    two — exact scalings). Derive initial conditions in closed form from v_n at dps=50.
    Independently recompute the achieved ratio from the stored ICs at dps=50; REQUIRE
    |achieved − r| ≤ 1e-30, printed at ≥30 significant digits, for all three fixtures.
R4. REFERENCE SELF-CHECK: every fixture's reference event set is computed twice, at dps=50
    and dps=100; REQUIRE agreement of every event value to ≥45 significant digits before
    the single rounding to double; report the worst-case agreement (in digits) per fixture.
R5. IN-PLACE SUPERSESSION: overwrite the 16 quarantined fixtures, MANIFEST.json entries
    (new sha256s), and split-lock state via the T1 machinery; TR states that the superseded
    mint was never engine-executed (no Law-1 poisoning). Calibration set untouched.
R6. VERBATIM EVIDENCE (L-10, restated as its own requirement): every command-output paste in
    the TR/OUT is byte-verbatim — no globbing, elision, or summarizing of `git status`,
    generator output, or check output. If output is long, paste it long.
R7. Naming HO-graze-parabola-<k> is ratified canonical; keep all 16 names from the first
    mint.

Steps:
3. Paste venv record (`python --version`, `pip show mpmath | head -2`).
4. Fix the mint tooling per R1–R4; run it; paste the full generator output; exit=0.
5. Paste per-fixture R2 output (cells b/d) and R3 output (all three grazing fixtures),
   including v_graze hex provenance.
6. Paste per-fixture R4 worst-case agreement digits.
7. Run the store validator; paste output; exit=0 (calibration=2, heldout=16, locked).
8. Paste `git status --porcelain --branch` VERBATIM (R6).
9. TR + OUT per PACKET 38's OUT-REQUIREMENTS (serial 39; header task I-003-T2-R1).

Acceptance criteria (binary, one artifact each):
1. Step 3 pasted: pinned venv, mpmath 1.3.0.
2. Step 4 pasted: generator exit=0; 16 fixtures written with the canonical names.
3. Step 5/R2: for every cell-b/d fixture, strict P ≠ d with |P − d| printed at ≥30 sig
   digits and > 0; no symbolic escape field present in checks or fixtures.
4. Step 5/R3: |achieved − r| ≤ 1e-30 for all three grazing fixtures, printed at ≥30 sig
   digits; v_graze hex (float.hex) shown as provenance.
5. Step 6/R4: worst-case dual-precision agreement ≥45 digits for every fixture.
6. Step 7: validator exit=0; calibration=2, heldout=16, split_locked=true.
7. TR affirms LAW-1 (no engine binary built/linked/invoked) and R5 supersession statement.
8. Step 8: byte-verbatim git status; no modified tracked entries beyond task-owned files
   pre-commit; untracked within the agent-writable surface limited to files this task
   creates; courier surface listed in full, record only (L-13).

## TASK I-003-T3: full Tier-2 held-out mint — closes C-001-PREREG §7 coverage + §8.iii cap
depends_on: I-003-T2 VERIFIED via R1 (JRN-I003-13); I-002 VERIFIED; C-002-T2 VERIFIED
(Bézier semantics of record); C-001-PREREG v1.0
objective: Mint 16 Tier-2 held-out fixtures covering every remaining HO cell of the
C-001-PREREG §7 table, at Tier-2 standard (refsim, reference_converged per Law 5), locked on
mint. Full corpus after this task: 32 held-out scenarios; the §8.iii concentration cap
(no family >50%) closes and binds.

STEP 0 — OUT_39 REMEDIATION (L-15, mandatory, before any T3 work): run `wc -c` and
`shasum -a 256` over all 16 existing held-out fixtures + MANIFEST.json; paste verbatim;
assert every sha256 matches OUT_39's step-4 values and the manifest. Any mismatch → BLOCKED
OUT immediately, no T3 work.

SPEC (binding; BLOCK on any ambiguity):
1. CARRIED DISCIPLINES, verbatim force: LAW-1 (no engine binary built/linked/invoked);
   R1 float64 discipline (two touchpoints only); R6 byte-verbatim evidence; naming
   HO-<family>-<regime>-<k> with graze-style exceptions only if registered here (none are).
2. Registered per-cell counts (16 total):
   a. deg 3–6 explicit poly × settle: 4 — one fixture per degree 3, 4, 5, 6; single-ball.
   b. deg 3–6 × periodic: 2 — degree 4 and degree 6 bowl-type orbits; non-dyadicity per
      T2-R1 rule R2 (strict P ≠ d, gap ≥30 digits).
   c. parabola × quasi-chaotic: 2; deg 3–6 × quasi-chaotic: 2 — all four at the 25-event
      reference cap (C-001-PREREG §1).
   d. piecewise Bézier C1 × settle: 3 — 1 single-ball, 1 two-ball, 1 three-ball (TB-1
      merged sequences per T2 rule for independent balls).
   e. piecewise Bézier C1 × periodic: 1 — non-dyadicity per R2.
   f. near-double-root geometry: 1 — on a deg-4 curve; the first-contact collision
      polynomial's discriminant within 1e-6 of zero, computed and recorded at 50 digits;
      single-ball, settle-type horizon.
3. QUASI-CHAOTIC ADMISSION (cell c): "quasi-chaotic" is measured, not asserted. Per fixture,
   run the refsim twice with an initial-condition perturbation of 1e-30 (one state
   component, registered per fixture); REQUIRE the event-time divergence to exceed 1e-10
   within ≤25 events. Record the certificate (perturbed component, divergence-vs-event
   table) per fixture. BLOCK if a candidate does not certify — choose new parameters.
4. TIER-2 REFERENCES: every reference event set computed by the refsim with the Law-5
   convergence check passed — dual-dps run (≥50 and ≥100) agreeing to ≥45 significant
   digits on every value within the fixture's horizon (25-event cap for cell c; otherwise
   min(200 events, settle)); worst-case agreement digits reported per fixture. The refsim
   may be extended (agent-authored, tools/ surface) for piecewise-Bézier segment handling;
   any extension gets the same dual-dps discipline.
5. BÉZIER SEMANTICS: segment definitions and C1 rules follow the C-002-T2 curve library
   semantics as the definition of record (read the C++ headers; do not run them — LAW-1).
   The mint implements a Python-native C1 check at every knot at 50 digits: position and
   first-derivative continuity, |Δ| = 0 exactly for constructed control points or ≤1e-45
   for derived ones; recorded per fixture. BLOCK if C-002-T2 semantics are ambiguous on any
   point needed.
6. STORAGE + LOCK: fixtures under data/scenarios/heldout/ with provenance fields per T2
   conventions (tier=2, generator commit, mpmath version, certificates from §3/§5/§6 as
   applicable); MANIFEST.json extended to 32 entries with sha256s; split-lock updated via
   the T1 machinery; calibration set untouched.
7. CONCENTRATION (C-001-PREREG §8.iii, now binding): compute and paste the per-family
   ratios over the full 32-scenario corpus; REQUIRE every family ≤ 50%. Expected: flat
   7/32, parabola 11/32, deg 3–6 9/32, Bézier 5/32. BLOCK if any family exceeds the cap.

Steps:
3. Paste venv record (`python --version`, `pip show mpmath | head -2`).
4. Implement/extend the mint tooling per §2–§6; run it; paste the full generator output
   verbatim; exit=0; 16 new fixtures with canonical names.
5. Paste per-fixture certificates: §3 sensitivity certificates (all four quasi-chaotic),
   R2 non-dyadicity for cells b/e, §5 C1 checks for all Bézier fixtures, §6 discriminant
   for the near-double-root fixture (50-digit value shown).
6. Paste per-fixture Tier-2 convergence results (§4): worst-case agreement digits, all ≥45.
7. Run the store validator; paste output; exit=0; calibration=2, heldout=32,
   split_locked=true.
8. Paste the §7 concentration ratios over the full corpus.
9. Paste `git status --porcelain --branch` byte-verbatim.
10. TR + OUT per OUT-REQUIREMENTS.

Acceptance criteria (binary, one artifact each):
0. Step 0 remediation pasted: wc -c + shasum over the 16 T2-R1 fixtures + manifest; all
   sha256s match OUT_39 step-4 values.
1. Step 3 pasted: pinned venv, mpmath 1.3.0.
2. Step 4 pasted verbatim: exit=0; 16 new fixtures, canonical names.
3. Step 5 sensitivity certificates: all four quasi-chaotic fixtures diverge >1e-10 within
   ≤25 events from a 1e-30 perturbation.
4. Step 5 non-dyadicity (cells b/e): strict P ≠ d with gaps at ≥30 digits.
5. Step 5 C1 checks: every Bézier knot position+derivative continuous per §5 bound.
6. Step 5 discriminant: |disc| ≤ 1e-6 at first contact, 50-digit value shown.
7. Step 6: Tier-2 convergence ≥45 digits worst-case for every fixture.
8. Step 7: validator exit=0; calibration=2, heldout=32, split_locked=true.
9. Step 8: every family ≤50% of the 32-scenario corpus, ratios pasted.
10. TR affirms LAW-1 and lists any refsim extensions made.
11. Step 9: byte-verbatim git status; no modified tracked entries beyond task-owned files
    pre-commit; untracked within the agent-writable surface limited to files this task
    creates (L-13).
12. FILE DIGESTS section complete (L-15): byte count + sha256 for every applied doc, every
    tooling file touched, all 16 new fixtures, MANIFEST.json, split-lock.json, and the TR.

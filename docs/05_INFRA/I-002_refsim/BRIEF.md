# BRIEF — I-002 High-precision reference simulator (tools/refsim)

```
doc_id:   I-002-BRIEF
layer:    infra
audience: composer-agent, PM
status:   ACTIVE
parent:   INFRASTRUCTURE_REGISTER I-002 / DELIVERABLE_B §6 / DELIVERABLE_C §3
```

## Objective
Stand up `tools/refsim`: a project-local, pinned Python environment hosting the Tier-2
high-precision reference simulator and Tier-1 closed-form fixture generator (DELIVERABLE_B
§6). The refsim is the gate-time oracle for C-001/C-002 — it is never linked, called, or
vendored into product code (DELIVERABLE_C §3).

## Workstream plan (tasks briefed one packet at a time)
- **T1 (this packet):** environment — venv at `tools/refsim/.venv`, mpmath pinned by exact
  version via `tools/refsim/requirements.txt`, smoke evidence with pre-registered expected
  outputs, venv git-ignored.
- **T2:** Tier-1 fixture generator — closed-form scenarios (flat line, parabola-on-parabola)
  with symbolic verification recorded per fixture (DELIVERABLE_B §6 Tier-1).
- **T3:** Tier-2 simulator — same algorithm as the core (VCA isolation, fixed refinement,
  TB-1/G-1/S-1) on ≥ 50-significant-digit arithmetic; `reference_converged` = event sequence
  invariant under doubling the working precision.
- **T4:** fixture emission format consumed by I-003's scenario store (schema pinned at T4).

## Dependency & license record (adoption note, per DELIVERABLE_C §3 license hygiene)
- mpmath 1.3.0 — BSD-3-Clause — GPLv3-compatible — gate-time tooling only, never shipped in
  the plugin. Pinned in `tools/refsim/requirements.txt`. Recorded here at adoption, the same
  pattern as doctest in JRN-I001-1.
- Python interpreter of record: system python3 (3.9.6 per JRN-C000-5) — recorded, not
  asserted; the pasted environment record in each TR is the datum.

## TASK I-002-T1: venv + pinned mpmath + smoke evidence
depends_on: I-001 (VERIFIED, JRN-I001-14)
objective: A reproducible, pinned, git-ignored Python environment with mpmath 1.3.0, proven
by pre-registered smoke outputs.
branch: `task/I-002-T1` from `main`.
inputs: `tools/refsim/requirements.txt` and the `.gitignore` venv line (both applied by
PACKET 13). Manifest: n/a — pre-I-004; all values are verbatim command output (JRN-C000-2).
steps:
  1. Guard: `git merge-base --is-ancestor 8adeea0acd68a307ec29d37488889d91d0b9bcc6 main && echo ancestor-ok`
     — must print `ancestor-ok` (Director merge of the I-001 lineage). If not, STOP: BLOCKED.
  2. After APPLY, append the CLAIM entry (JRN-I002-2 · CLAIM, actor: composer-agent,
     task: I-002-T1) to docs/05_INFRA/I-002_refsim/JOURNAL.md and commit it. If the journal
     shows an unresolved CLAIM for I-002-T1, STOP: BLOCKED (collision guard).
  3. Run: `python3 --version ; which python3 ; echo exit=$?` — copy the full output
     (environment record, P6 §4.5; version is recorded, not asserted).
  4. Run: `python3 -m venv tools/refsim/.venv ; echo exit=$?` — copy the full output.
  5. Run: `tools/refsim/.venv/bin/python -m pip install --no-cache-dir -r tools/refsim/requirements.txt ; echo exit=$?`
     — copy the full output.
  6. Run: `tools/refsim/.venv/bin/python -c "import mpmath as mp; mp.mp.dps=60; assert mp.almosteq(mp.sin(mp.pi), 0, abs_eps=mp.mpf(10)**-55); print('refsim-smoke-ok', mp.__version__)" ; echo exit=$?`
     — copy the full output.
  7. Run: `tools/refsim/.venv/bin/python -c "import mpmath as mp; mp.mp.dps=50; print(mp.nstr(mp.sqrt(2), 50))" ; echo exit=$?`
     — copy the full output.
  8. Run: `git status --short --branch ; echo exit=$?` — copy the full output.
  9. Write docs/05_INFRA/I-002_refsim/reports/TR_I-002-T1.md per P1 §7, header
     `manifest: n/a — pre-I-004; all values are verbatim command output (JRN-C000-2)`,
     sections `Step 3` … `Step 8`, each containing only that step's verbatim output.
  10. Append the DONE (or FAILED) journal entry (JRN-I002-3 · DONE/FAILED), append one
      APPLIED.log line for serial 13, and commit.
  11. Take the BRANCH/COMMITS paste now: `git log --format='%H %s' main..HEAD`, append the
      literal terminator line `+ final OUT commit (hash not self-listable)`, then write
      outbox/OUT_13_I-002-T1.md and commit it as the final commit. No amends afterwards
      (L-12; corrections land as fix-up commits on top).
output:
  - tools/refsim/.venv/ (git-ignored, never committed)
  - docs/05_INFRA/I-002_refsim/reports/TR_I-002-T1.md
  - journal CLAIM and DONE/FAILED entries
  - outbox/OUT_13_I-002-T1.md
courier:
  - Full text of TR_I-002-T1.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR contains `Step 3` verbatim (python3 version and path), ending `exit=0`.
  2. TR contains `Step 4` verbatim, ending `exit=0`.
  3. TR contains `Step 5` verbatim, containing the line fragment
     `Successfully installed mpmath-1.3.0` and ending `exit=0`.
  4. TR contains `Step 6` verbatim, containing exactly the line `refsim-smoke-ok 1.3.0` and
     ending `exit=0`. (Expected output pre-verified by the PM on 2026-07-08 against
     mpmath 1.3.0.)
  5. TR contains `Step 7` verbatim, containing exactly the line
     `1.4142135623730950488016887242096980785696718753769` and ending `exit=0`. (Expected
     output pre-verified by the PM on 2026-07-08 against mpmath 1.3.0.)
  6. TR contains `Step 8` verbatim, ending `exit=0`, showing no modified entries and no
     untracked entries under src/, tests/, config/, data/, reports/, docs/, tools/, or
     outbox/ beyond this task's outputs (`tools/refsim/.venv/` is git-ignored by this
     packet's .gitignore line and must therefore not appear). Entries at the repository root
     and under inbox/ are pasted for the record and are not asserted (L-13).
  7. The OUT contains verbatim CLAIM and DONE/FAILED journal entries.
  8. The OUT's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 13.
OUT-REQUIREMENTS (per L-10 and L-12):
  - OUT header per P5 §5: `# OUT 13 — I-002-T1 — DONE` (or FAILED/BLOCKED) with the
    `agent · branch · commits` line (commits list may omit the final OUT commit, per L-12);
  - APPLY CONFIRMATION with the serial-13 ledger line pasted;
  - JOURNAL ENTRIES: verbatim copies of every journal entry this packet applied
    (JRN-I001-14, JRN-I001-15, JRN-I002-1) AND the task's CLAIM and DONE/FAILED entries
    (JRN-I002-2, JRN-I002-3);
  - FILE DIGESTS: `wc -c` and `shasum -a 256` output for every file this packet's FILES
    section wrote (docs/01_PROTOCOLS/P6_PM_CONDUCT.md,
    docs/05_INFRA/I-001_core_skeleton/JOURNAL.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md,
    docs/05_INFRA/I-002_refsim/BRIEF.md, docs/05_INFRA/I-002_refsim/JOURNAL.md,
    tools/refsim/requirements.txt, .gitignore, docs/00_STATE.md);
  - REPORT: TR_I-002-T1.md in full;
  - BRANCH/COMMITS: the step-11 paste ending with the literal terminator line
    `+ final OUT commit (hash not self-listable)`.
failure_modes:
  - Step 1 guard fails → STOP, BLOCKED (Director merge missing).
  - Step 5 install fails or pins a different version → paste verbatim; status FAILED.
  - Step 6 or 7 output differs from the pre-registered line → paste verbatim; status FAILED
    (do not retry, do not adjust precision).
  - Step 8 shows modified entries, or untracked entries under the asserted surface beyond
    this task's outputs → paste verbatim; status FAILED.
  - Unresolved CLAIM for I-002-T1 → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not process inbox/PACKET_12.md — it is VOID, superseded by PACKET 13; no serial-12
    ledger line may ever be written.
  - Do not commit tools/refsim/.venv/ or any file within it.
  - Do not install any package beyond requirements.txt; do not upgrade pip.
  - Do not amend any commit; do not reset or rewrite history.
  - Do not edit, commit, delete, or ignore-list any file at the repository root or under
    inbox/ beyond what this packet's FILES section applies.
  - Do not run commands not listed in the steps.
  - Do not truncate outputs.
Non-negotiables: stop-on-surprise except where a step records a failure verbatim per its
failure_modes; evidence per criterion; no invented values; whitelist = reading list + files
this task writes.
End state: `task/I-002-T1` carries the apply and task commits, the final one adding
outbox/OUT_13_I-002-T1.md — the single file returned to the PM.

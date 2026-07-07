# I-001 BRIEF — Engine library skeleton

```
doc_id:   I-001-BRIEF
layer:    infra
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   INFRASTRUCTURE_REGISTER I-001 / DELIVERABLE_C §2–§3
```

## Context for agents
First code of Phase 1. The repository gains a buildable C++20 skeleton: a `bounce-core` static
library holding only versioned rule constants for now, a doctest test harness, and — the part
that matters — `config/fp-determinism.cmake`, the single source of truth for floating-point
flags (DELIVERABLE_B §4), plus tests that assert the FP environment at runtime. Your task builds
and tests exactly what the packet applied. A build or test failure is a RESULT to report
verbatim (status FAILED), never something to fix, patch, or retry with different flags.

## Files you may read
- `AGENTS.md` · `inbox/PACKET_8.md` · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- This brief; the files this packet applied (listed in TASK I-001-T1 steps)
- `inbox/APPLIED.log`

## Files you will write
- `docs/05_INFRA/I-001_core_skeleton/JOURNAL.md` (append only)
- `docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1.md` (or BLK/FAILED per P4)
- `inbox/APPLIED.log` (append one line)
- `outbox/OUT_8_I-001-T1.md`
- Build artifacts under `build/` only (git-ignored)

## TASK I-001-T1: Configure, build, and test the skeleton; paste the evidence
depends_on: none
objective: Prove the committed skeleton configures, builds, and passes its tests on the
           environment of record, with all outputs pasted verbatim.
inputs:    The repository working tree after this packet's FILES section is applied. Network is
           used only by CMake FetchContent to fetch doctest at the pinned tag (v2.4.11) from
           github.com. No credentials. Manifest: n/a — manifest infrastructure is I-004
           (JRN-C000-2 ruling); all values are verbatim command output.
steps:
  1. Run: `cmake --version ; c++ --version ; sw_vers ; echo exit=$?` — copy the full output
     (environment record, P6 §4.5).
  2. Run: `cmake --preset default 2>&1 ; echo exit=$?` — copy the full output.
  3. Run: `cmake --build --preset default 2>&1 ; echo exit=$?` — copy the full output.
  4. Run: `ctest --preset default 2>&1 ; echo exit=$?` — copy the full output.
  5. Run: `git status --short --branch ; echo exit=$?` — copy the full output (expect: task
     branch, no modified or untracked entries; `build/` is git-ignored).
  6. Write `docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1.md` per P1 §7, header
     `manifest: n/a — pre-I-004; all values are verbatim command output (JRN-C000-2)`, one
     section per step, `Step 1` … `Step 5`, each containing only that step's verbatim output.
  7. Append the DONE (or FAILED) journal entry, commit, and write `outbox/OUT_8_I-001-T1.md`.
output:
  - docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1.md
  - journal CLAIM and DONE/FAILED entries
  - outbox/OUT_8_I-001-T1.md
courier:
  - Full text of TR_I-001-T1.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR contains `Step 1` with the verbatim toolchain/OS record.
  2. TR contains `Step 2` verbatim, ending `exit=0`.
  3. TR contains `Step 3` verbatim, ending `exit=0`.
  4. TR contains `Step 4` verbatim, showing 100% tests passed and ending `exit=0`.
  5. TR contains `Step 5` verbatim, showing no modified and no untracked entries.
  6. The OUT contains verbatim CLAIM and DONE/FAILED journal entries.
  7. The OUT's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 8.
  (If any of steps 2–4 ends with a non-zero exit: criteria 2–4 are replaced by "full output
  pasted verbatim including the failure"; task status is FAILED, honestly reported per P3 §7 —
  a FAILED report meeting that standard is reviewable and will not be treated as agent error.)
OUT-REQUIREMENTS (per L-10):
  - APPLY CONFIRMATION with the serial-8 ledger line pasted;
  - JOURNAL ENTRIES: verbatim copies of every journal entry this packet applied (JRN-I001-1,
    JRN-C000-19) AND the task's CLAIM and DONE/FAILED entries;
  - FILE DIGESTS: `wc -c` and `shasum -a 256` output for every file this packet's FILES section
    wrote (both briefs' docs and all source/build files listed in APPLY CONFIRMATION);
  - REPORT: TR_I-001-T1.md in full;
  - BRANCH/COMMITS: pasted output of `git log --format='%H %s' main..HEAD`.
failure_modes:
  - FetchContent cannot reach github.com or the tag is absent → the step-2 output records it;
    status FAILED (not BLOCKED); do not vendor, mirror, or substitute anything.
  - Step-5 shows unexpected modified/untracked entries → paste and report; note under
    OBSERVATIONS; PM judges at review.
  - Unresolved CLAIM for I-001-T1 in the infra journal → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not edit any file this packet applied — no CMake, source, or flag changes, even to make
    the build pass.
  - Do not install packages, toolchains, or CMake versions.
  - Do not run commands not listed in the steps.
  - Do not truncate outputs; long configure/build logs are pasted whole.

## AMENDMENT A1 (PACKET 9, per P6 §2.4)
acceptance_criteria item 5 of TASK I-001-T1 is replaced by:
  5. TR contains `Step 5` verbatim, showing no modified entries and no untracked entries other
     than files matching `inbox/PACKET_*.md`, ending `exit=0`.
The failure_modes item "Step-5 shows unexpected modified/untracked entries → paste and report;
note under OBSERVATIONS; PM judges at review" is replaced by:
  - Step-5 shows modified entries, or untracked entries other than `inbox/PACKET_*.md` → paste
    verbatim; status FAILED.
Repair evidence for the amended criterion is produced by TASK I-001-T1-R1 (PACKET 9). Rationale
and authoring-defect record: JRN-I001-5; lesson: L-11.

## AMENDMENT A2 (PACKET 11, per P6 §2.4; supersedes A1's criterion text)
The workspace-cleanliness criterion (A1 item 5, and criterion 2 of the R-series repair tasks)
is replaced by:
  TR contains the git-status step verbatim, ending `exit=0`, showing (i) no modified entries,
  and (ii) no untracked entries under src/, tests/, config/, data/, reports/, docs/, or
  outbox/ beyond the files the task is required to write. Entries at the repository root and
  under inbox/ are pasted for the record and are not asserted (Director courier surface,
  L-13).
The corresponding failure_modes item is replaced by:
  - git status shows modified entries, or untracked entries under the asserted surface beyond
    the task's own outputs → paste verbatim; status FAILED.
Rationale and defect record: JRN-I001-11; lesson: L-13. Repair evidence: TASK I-001-T1-R2
(PACKET 11).

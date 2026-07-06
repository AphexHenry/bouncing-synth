# C-000 BRIEF — Phase-0 scoping

```
doc_id:   C-000-BRIEF
layer:    track
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   C-000-THESIS
```

## Context for agents
Bounce is starting Phase 0 (scoping). Before any code is planned, the program records what the
workspace actually provides (L-02: verify reachability and prerequisites before building; gates
halt). Your task records the environment exactly as found. Commands that fail are an expected,
valid outcome of this task: you paste the error verbatim and continue. You do not install, fix,
or interpret anything. Deliverables (a)–(d) of Phase 0 are PM-authored and are not agent tasks.

## Files you may read
- `AGENTS.md` (repo root)
- `inbox/PACKET_1.md`
- `docs/01_PROTOCOLS/P0_MASTER.md` §2–§6
- `docs/01_PROTOCOLS/P3_ENGINEERING.md`
- `docs/01_PROTOCOLS/P4_REPORTING.md`
- `docs/01_PROTOCOLS/P1_DOCUMENTATION.md` §3 (journal entry), §7 (task report)
- This brief: "Context for agents", "Files you may read", "Files you will write", TASK C-000-T1
- `inbox/APPLIED.log`

## Files you will write
- `docs/03_TRACKS/C-000_scoping/JOURNAL.md` (append only)
- `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-T1.md` (or `BLK_C-000-T1_1.md` if blocked)
- `inbox/APPLIED.log` (append one line)
- `outbox/OUT_1_C-000-T1.md`

## TASK C-000-T1: Record the workspace environment verbatim
depends_on: none
objective: Produce a verbatim record of the repository layout and toolchain versions present in the
           workspace, with no installation, repair, or interpretation.
inputs:    The workspace itself. No external sources, URLs, credentials, or env vars. No licensing
           concerns (command output only). Provenance: all values are Tier-3-equivalent direct
           observations of this machine — verbatim command output; see manifest note below.
steps:
  1. From the repository root run: `pwd ; ls -la` — copy the full output.
  2. Run: `git --version ; git rev-parse --show-toplevel ; git status --short --branch` — copy the
     full output.
  3. Run: `ls docs ; ls docs/01_PROTOCOLS ; ls docs/02_PROGRAM ; ls docs/03_TRACKS` — copy the full
     output.
  4. Run: `cat inbox/APPLIED.log` — copy the full output.
  5. Run: `cmake --version` — copy the full output, or the exact error text if the command fails.
  6. Run: `g++ --version` then `clang++ --version` — copy both full outputs; an error text for
     either or both is a valid recorded outcome. Do not install anything.
  7. Run: `python3 --version ; which python3 ; pip3 --version` — copy the full output (errors
     included, verbatim).
  8. Run: `python3 -c "import mpmath; print('mpmath', mpmath.__version__)"` — copy the full output,
     or the exact error/traceback if it fails. Do not pip-install anything.
  9. Write `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-T1.md` per P1 §7. In its header write
     `manifest: n/a — no manifest infrastructure yet (I-004 SPECCED); all values are verbatim
     command output; PM ruling JRN-C000-2`. Under `PER ACCEPTANCE CRITERION`, one section per step,
     titled `Step 1` … `Step 8`, each containing only that step's verbatim terminal output
     (stdout and stderr).
  10. Append the DONE journal entry, commit, and write `outbox/OUT_1_C-000-T1.md` per P5 §5.
output:
  - `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-T1.md`
  - journal CLAIM and DONE entries
  - `outbox/OUT_1_C-000-T1.md`
courier:
  - The full text of `TR_C-000-T1.md` copied verbatim into the OUT file's REPORT section.
  - The `APPLIED.log` line for serial 1 pasted in the OUT file's APPLY CONFIRMATION.
acceptance_criteria:
  1. TR_C-000-T1.md contains a section `Step 1` whose content is the verbatim output of step 1.
  2. TR_C-000-T1.md contains a section `Step 2` whose content is the verbatim output of step 2.
  3. TR_C-000-T1.md contains a section `Step 3` whose content is the verbatim output of step 3.
  4. TR_C-000-T1.md contains a section `Step 4` whose content is the verbatim output of step 4.
  5. TR_C-000-T1.md contains a section `Step 5` whose content is the verbatim output of step 5
     (error text is compliant).
  6. TR_C-000-T1.md contains a section `Step 6` whose content is the verbatim output of both
     step-6 commands (error text is compliant).
  7. TR_C-000-T1.md contains a section `Step 7` whose content is the verbatim output of step 7 —
     this is the environment record (interpreter version and path) required by P6 §4.5.
  8. TR_C-000-T1.md contains a section `Step 8` whose content is the verbatim output of step 8
     (error/traceback text is compliant).
  9. The OUT file contains verbatim copies of the CLAIM and DONE journal entries.
  10. The OUT file's APPLY CONFIRMATION contains the pasted `APPLIED.log` line for serial 1.
failure_modes:
  - `AGENTS.md`, `inbox/`, or `outbox/` missing at the repo root, or `docs/` missing → STOP, file
    `BLK_C-000-T1_1.md`: workspace setup incomplete (Director's Manual §1).
  - The journal already shows an unresolved CLAIM for C-000-T1 → STOP, BLOCKED (collision guard).
  - Any single command failing (steps 5–8) is NOT a failure mode: paste the error verbatim and
    continue to the next step.
DO_NOT:
  - Do not install, update, or configure any software, package, or toolchain.
  - Do not truncate, summarize, reformat, or "clean up" any command output.
  - Do not run any command not listed in the steps.
  - Do not interpret results or add recommendations; observations outside the task go in a NOTE
    journal entry only.

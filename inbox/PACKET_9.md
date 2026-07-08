# PACKET 9 — OUT_8 review: AMEND + RETURN; repair I-001-T1-R1
pm: pm-fable5-a · date: 2026-07-07 · task: I-001-T1-R1

== VERDICT ==
OUT_8/I-001-T1 reviewed per P6 §2: criteria 1–4, 6, 7 and all L-10 OUT-REQUIREMENTS COMPLIANT;
criterion 5 NON-COMPLIANT (Step 5 shows untracked inbox/PACKET_7.md and inbox/PACKET_8.md).
The criterion is defective (PM authoring error, P6 §2.4): it asserts a workspace state the
dispatch mechanics do not guarantee and its own failure_modes clause contradicts it. Verdict:
AMEND + RETURN — corrected criterion issued as BRIEF amendment A1; repair task I-001-T1-R1
dispatched below. I-001 remains unverified until R1 is accepted.

== FILES ==

=====[ FILE APPEND: docs/05_INFRA/I-001_core_skeleton/JOURNAL.md ]=====
---
### JRN-I001-5 · CORRECTION
actor: pm-fable5-a · task: I-001-T1 · manifest: n/a

WHAT: PM authoring defect in I-001-T1 acceptance criterion 5 ("no modified and no untracked
entries"). Deviation: the criterion asserted a workspace state the packet's own mechanics do
not guarantee — the Director saves PACKET_<n>.md into inbox/ at dispatch (P5 §6.1), and the
branch inherited an untracked inbox/PACKET_7.md from the prior cycle; neither is correctable
by a compliant agent under the task's DO_NOT list. The brief's failure_modes clause
("unexpected modified/untracked entries → paste and report; PM judges at review") contradicted
the binary criterion and deferred judgment into execution, itself a P6 §4.1/§4.3 violation.
Root cause: criterion text written against an idealized clean tree instead of the dispatch
mechanics. Durable fix: BRIEF amendment A1 (corrected criterion 5 and failure_modes item);
LESSONS L-11; P6 §4 amendment proposed to the Director (STATE open decision 2) per P6 §6.3 —
second workspace-state authoring defect after L-09. Secondary open item folded into decision
2: AGENTS.md vs P5 §2 on whether APPLY commits inbox packet files (the agent recorded "not
committed per protocol"; P5 §2 lists "the applied packet files" in the commit series) — the
two texts are aligned in the same amendment packet once decision 2 is taken.
NUMBERS: none
LEARNED: recorded as LESSONS L-11
NEXT: R1 repair against amended criterion (PACKET 9 TASK).

---
### JRN-I001-4 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_8_I-001-T1 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 1 verbatim toolchain/OS record (cmake 3.27.8, AppleClang 17, macOS 15.7.7) | COMPLIANT |
| 2 | Step 2 verbatim, ends exit=0 | COMPLIANT |
| 3 | Step 3 verbatim, ends exit=0 | COMPLIANT |
| 4 | Step 4 verbatim, 100% tests passed, ends exit=0 | COMPLIANT |
| 5 | Step 5 shows no modified and no untracked entries | NON-COMPLIANT — untracked inbox/PACKET_7.md, inbox/PACKET_8.md |
| 6 | CLAIM and DONE journal entries verbatim in OUT | COMPLIANT |
| 7 | APPLIED.log serial-8 line pasted in APPLY CONFIRMATION (format matches the serial-1 line of record, TR_C-000-T1) | COMPLIANT |
| L-10 | ledger line; JRN-I001-1, JRN-C000-19, CLAIM, DONE verbatim; wc -c + sha256 for all 12 applied files; TR_I-001-T1.md in full; git log --format='%H %s' main..HEAD paste | COMPLIANT |
Verdict: AMEND + RETURN (P6 §2.4) — criterion 5 defective; see JRN-I001-5 CORRECTION. The
build/test work is presumed sound; no VERIFIED status existed to suspend (P6 §2.5). The
BRANCH/COMMITS paste shows the packet/7 apply commits inside main..HEAD: main is behind the
accepted OUT_7 lineage. Director merge duty (P5 §6.4) executes after the R1 ACCEPT — one merge
of task/I-001-T1 into main covers the OUT_7 lineage and OUT_8 + R1 together.
NUMBERS: none
LEARNED: nothing
NEXT: dispatch I-001-T1-R1 (this packet); on R1 ACCEPT, register I-001 → VERIFIED, STATE
update, I-002 brief follows.
=====[ END FILE ]=====

=====[ FILE APPEND: docs/02_PROGRAM/LESSONS.md ]=====

L-11: An acceptance criterion over workspace state must assert only conditions the packet's own
mechanics guarantee at execution time; any state contributed by the Director's dispatch steps or
inherited from prior cycles (e.g. untracked inbox/PACKET_*.md) is written into the criterion as
an explicitly tolerated pattern, never left as an implicit expectation. A brief's failure_modes
section may not offer "PM judges at review" as an escape from a binary criterion (P6 §4.1) —
the tolerance belongs in the criterion text itself. Origin: I-001-T1 criterion 5 demanded a
clean tree while dispatch mechanics leave packet files untracked and the branch inherited one
from the prior cycle, forcing AMEND + RETURN on otherwise sound work (JRN-I001-5). Second
occurrence of the workspace-state authoring class after L-09 → P6 §4 amendment proposed
(STATE open decision 2).
=====[ END FILE ]=====

=====[ FILE APPEND: docs/05_INFRA/I-001_core_skeleton/BRIEF.md ]=====

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
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/00_STATE.md ]=====
# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_8 review AMEND+RETURN (criterion-5 authoring defect, JRN-I001-5); repair I-001-T1-R1 dispatched (PACKET 9)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core (PROJECT §3). Module `00_PROJECT.md` v0.2 ACTIVE (GPLv3 in §11;
Phase-0 gate of record in changelog and JRN-C000-18). Phase-0 deliverables (a)–(d) APPROVED with
rulings R1 (point-contact), R2 (no ball–ball), R3 (transcendental families deferred) —
docs/03_TRACKS/C-000_scoping/reports/.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-002 Curve library | IDEA | THESIS | PM authors thesis once I-001 is VERIFIED (with C-001) |
| C-001 Exact collision engine | IDEA | THESIS | PM authors thesis once I-001 is VERIFIED (with C-002) |

C-000 Phase-0 scoping: CLOSED (gate passed) — see register.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | BUILT — review AMEND+RETURN (JRN-I001-4/-5) | R1 repair review → VERIFIED | Director dispatches PACKET 9 (I-001-T1-R1) |
| I-002 high-precision reference sim | SPECCED | brief | I-001 VERIFIED (creates venv, installs pinned mpmath) |
| I-003 scenario store + split-lock | SPECCED | brief | I-002 |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director creates repository hosting + CI account (open decision 1) |

## Open decisions (Director)
1. Create source hosting + CI account for I-007 (clean-checkout CI on macOS arm64 + Linux
   x86-64). Options: GitHub free tier (PM recommendation — Actions covers both platforms) /
   other host. Needed before the I-007 brief; does not block I-001…I-005.
2. P6 §4 amendment (proposed per P6 §6.3; second workspace-state authoring defect after L-09 —
   see L-11, JRN-I001-5). Proposed §4.6: "A criterion over workspace state asserts only
   conditions the packet's own mechanics guarantee; state contributed by the Director's
   dispatch steps or inherited from prior cycles appears in the criterion as an explicitly
   tolerated pattern." Approve yes/no. When answering, also paste the AGENTS.md line (if any)
   governing whether APPLY commits inbox packet files, so AGENTS.md and P5 §2 ("the applied
   packet files" in the commit series) are aligned in the same amendment packet. Does not
   block R1 or I-002.
3. GPLv3 "-only vs -or-later" for SPDX headers and the shipped LICENSE file — due at Phase-3
   packaging (JRN-I001-1). Not blocking; tracked here so it is not lost.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — deliverables (a)–(d) approved, R1–R3
ratified. Record: JRN-C000-18; artifacts digest-pinned via RV1/RV2 evidence.

## Recent review verdicts
OUT_8/I-001-T1: AMEND + RETURN (2026-07-07) — criteria 1–4, 6, 7 + L-10 COMPLIANT; criterion 5
defective (PM authoring error, JRN-I001-5); corrected text = I-001 BRIEF amendment A1; repair
I-001-T1-R1 dispatched in PACKET 9.

## Pointers
Repository: `main` is currently behind the working lineage — OUT_8's BRANCH/COMMITS shows the
packet/7 and packet/8 apply commits in `main..HEAD`. The Director merges task/I-001-T1 → main
after the R1 ACCEPT (one merge covers the accepted OUT_7 lineage and OUT_8 + R1); task branches
start from main thereafter (RV2 rule restored). Standing OUT rules: L-10 evidence blocks;
BRANCH/COMMITS via `git log --format='%H %s' main..HEAD` paste (JRN-C000-17); OUT header per
P5 §5. Environment of record: arm64 macOS, Apple clang 17, cmake 3.27.8, Python 3.9.6, mpmath
absent until I-002 (JRN-C000-5).
=====[ END FILE ]=====

== TASK ==
Precondition: branch `task/I-001-T1` exists and its tip is commit
f8f15fa0802010c9221e5ae05d49d9c3acd5dc33 — if not, stop; do not dispatch; report to the PM.

Reading list: AGENTS.md · inbox/PACKET_9.md · P0 §2–§6 · P4 · P5 §5 ·
docs/05_INFRA/I-001_core_skeleton/BRIEF.md (TASK I-001-T1 and AMENDMENT A1) ·
docs/05_INFRA/I-001_core_skeleton/JOURNAL.md.
Whitelist: the reading list plus the files this task writes. Nothing else is opened.

Assignment: execute TASK I-001-T1-R1 exactly as written.

TASK I-001-T1-R1: Repair — re-emit Step-5 evidence against amended criterion (P6 §3
RETURN-class repair; near-zero cost; no re-doing of build/test work)
depends_on: I-001-T1 (OUT_8)
objective: Produce the Step-5 evidence judged against BRIEF amendment A1.
branch: continue on `task/I-001-T1` (repair of the same task; no new branch).
inputs: the working tree as left by I-001-T1. Manifest: n/a — pre-I-004; all values are
verbatim command output (JRN-C000-2).
steps:
  1. After APPLY, append the CLAIM entry (JRN-I001-6 · CLAIM, actor: composer-agent,
     task: I-001-T1-R1) to docs/05_INFRA/I-001_core_skeleton/JOURNAL.md and commit it. If the
     journal shows an unresolved CLAIM for I-001-T1-R1, STOP: BLOCKED (collision guard).
  2. Run: `git --version ; sw_vers ; echo exit=$?` — copy the full output (environment
     record, P6 §4.5).
  3. Run: `git status --short --branch ; echo exit=$?` — copy the full output.
  4. Write docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1-R1.md per P1 §7, header
     `manifest: n/a — pre-I-004; all values are verbatim command output (JRN-C000-2)`,
     sections `Step 2` and `Step 3`, each containing only that step's verbatim output.
  5. Append the DONE (or FAILED) journal entry (JRN-I001-7), append one APPLIED.log line for
     serial 9, commit, and write outbox/OUT_9_I-001-T1-R1.md.
output:
  - docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1-R1.md
  - journal CLAIM and DONE/FAILED entries
  - outbox/OUT_9_I-001-T1-R1.md
courier:
  - Full text of TR_I-001-T1-R1.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR contains `Step 2` verbatim (git version, OS record), ending `exit=0`.
  2. TR contains `Step 3` verbatim, showing no modified entries and no untracked entries other
     than files matching `inbox/PACKET_*.md`, ending `exit=0`.
  3. The OUT contains verbatim CLAIM and DONE/FAILED journal entries.
  4. The OUT's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 9.
  (If Step 3 shows modified entries, or untracked entries other than `inbox/PACKET_*.md`:
  criterion 2 is replaced by "full output pasted verbatim including the violating entries";
  task status is FAILED, honestly reported per P3 §7.)
OUT-REQUIREMENTS (per L-10):
  - OUT header per P5 §5: `# OUT 9 — I-001-T1-R1 — DONE` (or FAILED/BLOCKED) with the
    `agent · branch · commits` line;
  - APPLY CONFIRMATION with the serial-9 ledger line pasted;
  - JOURNAL ENTRIES: verbatim copies of every journal entry this packet applied (JRN-I001-4,
    JRN-I001-5) AND the task's CLAIM and DONE/FAILED entries (JRN-I001-6, JRN-I001-7);
  - FILE DIGESTS: `wc -c` and `shasum -a 256` output for every file this packet's FILES
    section wrote (docs/05_INFRA/I-001_core_skeleton/JOURNAL.md,
    docs/02_PROGRAM/LESSONS.md, docs/05_INFRA/I-001_core_skeleton/BRIEF.md,
    docs/00_STATE.md);
  - REPORT: TR_I-001-T1-R1.md in full;
  - BRANCH/COMMITS: pasted output of `git log --format='%H %s' main..HEAD`.
failure_modes:
  - Step 3 shows modified entries or untracked entries other than `inbox/PACKET_*.md` → paste
    verbatim; status FAILED.
  - Unresolved CLAIM for I-001-T1-R1 in the infra journal → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not edit, commit, or remove inbox packet files.
  - Do not edit any source, CMake, or config file.
  - Do not run commands not listed in the steps.
  - Do not truncate outputs.
Non-negotiables: stop-on-surprise except where a step records a failure verbatim per its
failure_modes; evidence per criterion; no invented values; whitelist respected.
End state: `task/I-001-T1` carries the repair commit(s); outbox/OUT_9_I-001-T1-R1.md is
committed and is the single file returned to the PM.

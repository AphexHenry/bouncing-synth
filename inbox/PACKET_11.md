# PACKET 11 — OUT_10 review: AMEND + RETURN; repair I-001-T1-R2
pm: pm-fable5-a · date: 2026-07-07 · task: I-001-T1-R2

== VERDICT ==
OUT_10 (FAILED) reviewed per P6 §2: the report is compliant on every criterion including
criterion 2's FAILED branch — honest FAILED, no agent fault. Underlying cause: untracked
docs.zip, a Director courier artifact (P5 §7 zip), plus a PM criterion defect recurring the
L-11 class — tolerated-pattern enumeration cannot be made total. Verdict: AMEND + RETURN.
Amendment A2 rescopes the assertion to the agent-writable surface (L-13); /docs.zip added to
.gitignore; repair I-001-T1-R2 dispatched below. I-001 remains unverified until R2 is accepted.

== FILES ==

=====[ FILE APPEND: docs/05_INFRA/I-001_core_skeleton/JOURNAL.md ]=====
---
### JRN-I001-11 · CORRECTION
actor: pm-fable5-a · task: I-001-T1-R1 · manifest: n/a

WHAT: Third PM workspace-state authoring defect, recurring the L-11 class despite L-11. The
A1-amended criterion tolerated inbox/PACKET_*.md but the workspace also carried docs.zip — a
Director courier artifact (the P5 §7 docs zip made for the PM) at repo root — forcing an
honest FAILED (OUT_10) on faultless agent work. Root cause: L-11's fix was implemented by
enumerating tolerated Director artifacts; the set of Director courier artifacts is open and
enumeration cannot be made total. Durable fix (structural, not another pattern): workspace
cleanliness criteria assert only over the agent-writable surface — src/, tests/, config/,
data/, reports/, docs/, outbox/ — while the Director courier surface (repository root and
inbox/) is pasted verbatim for the record and never asserted (LESSONS L-13; BRIEF amendment
A2). Secondary hardening: /docs.zip appended to .gitignore so courier zips cannot appear in
status output or be staged accidentally. P6 §6.3 was already discharged at the second
occurrence (L-11 + open decision 2); this entry records the recurrence and replaces the
enumeration approach with surface scoping. Adopted as norm from OUT_9/OUT_10 evidence: hash
corrections land as fix-up commits on top (e.g. 800513e…), never as amends (L-12).
NUMBERS: none
LEARNED: recorded as LESSONS L-13
NEXT: I-001-T1-R2 dispatched (PACKET 11, serial 11) against amendment A2.

---
### JRN-I001-10 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_10_I-001-T1-R1 per P6 §2. Criterion table (criteria as amended by A1,
including the FAILED branch):
| # | criterion | verdict |
|---|---|---|
| 1 | Step 2 verbatim environment record (git 2.48.1, macOS 15.7.7), ends exit=0 | COMPLIANT |
| 2 | Step 3: no modified, no untracked other than inbox/PACKET_*.md — main branch NOT MET (untracked docs.zip); FAILED branch "full output pasted verbatim including the violating entries" | COMPLIANT (FAILED branch) |
| 3 | CLAIM and FAILED journal entries verbatim in OUT | COMPLIANT |
| 4 | APPLIED.log serial-10 line pasted in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 §5 header (commits line omits final OUT commit per L-12); ledger line; JRN-I001-6/-7 + CLAIM/FAILED verbatim; wc -c + sha256 for all 3 applied files; TR in full; BRANCH/COMMITS ending with the literal terminator "+ final OUT commit (hash not self-listable)" | COMPLIANT |
Verdict: AMEND + RETURN (P6 §2.4) — the criterion is defective again (see JRN-I001-11
CORRECTION); the FAILED report itself is accepted as valid evidence of the workspace
condition and involves no agent error (P3 §7). No VERIFIED status existed to suspend
(P6 §2.5). BRANCH/COMMITS additionally shows the OUT_9 hash fix-up commit 800513e… —
commit-on-top, not amend — consistent with L-12.
NUMBERS: none
LEARNED: nothing
NEXT: dispatch I-001-T1-R2; on R2 ACCEPT, register I-001 → VERIFIED, Director merges
task/I-001-T1 → main, STATE update, I-002 brief follows.
=====[ END FILE ]=====

=====[ FILE APPEND: docs/02_PROGRAM/LESSONS.md ]=====

L-13: Workspace-cleanliness criteria assert only over the agent-writable surface — src/,
tests/, config/, data/, reports/, docs/, outbox/ — asserting no modified tracked entries
anywhere and no untracked entries within that surface beyond the files the task is required
to write. The Director courier surface (repository root and inbox/) is pasted verbatim for
the record and never asserted: the set of Director courier artifacts (packet files, docs
zips, OS metadata) is open, so tolerated-pattern enumeration cannot be made total — each
enumeration fix (L-11's inbox/PACKET_*.md) fails on the next artifact class (docs.zip,
OUT_10). Surface scoping replaces enumeration. Origin: I-001-T1-R1 FAILED honestly on an
untracked Director courier zip after two prior defects of the same class (JRN-I001-11).
=====[ END FILE ]=====

=====[ FILE APPEND: .gitignore ]=====

# Director courier artifacts (P5 §7; L-13)
/docs.zip
=====[ END FILE ]=====

=====[ FILE APPEND: docs/05_INFRA/I-001_core_skeleton/BRIEF.md ]=====

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
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/00_STATE.md ]=====
# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_10 review AMEND+RETURN (recurring workspace-state class → surface scoping, JRN-I001-11, L-13); repair I-001-T1-R2 dispatched (PACKET 11)

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
| I-001 engine lib skeleton | BUILT — R2 dispatch after honest FAILED OUT_10 (JRN-I001-10/-11) | R2 repair review → VERIFIED | Director dispatches PACKET 11 (I-001-T1-R2) |
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
2. P6 §4 amendment (proposed per P6 §6.3; see L-11, L-13, JRN-I001-5, JRN-I001-11). Proposed
   §4.6: "A criterion over workspace state asserts only conditions the packet's own mechanics
   guarantee, scoped to the agent-writable surface; Director-contributed state is pasted for
   the record, never asserted." Approve yes/no. When answering, also paste the AGENTS.md line
   (if any) governing whether APPLY commits inbox packet files, so AGENTS.md and P5 §2 ("the
   applied packet files" in the commit series) are aligned in the same amendment packet. Does
   not block R2 or I-002.
3. GPLv3 "-only vs -or-later" for SPDX headers and the shipped LICENSE file — due at Phase-3
   packaging (JRN-I001-1). Not blocking; tracked here so it is not lost.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — deliverables (a)–(d) approved, R1–R3
ratified. Record: JRN-C000-18; artifacts digest-pinned via RV1/RV2 evidence.

## Recent review verdicts
OUT_10/I-001-T1-R1: AMEND + RETURN (2026-07-07) — FAILED report fully compliant and honest
(no agent fault); criterion defect recurred the L-11 class; fix = surface scoping (A2, L-13,
JRN-I001-11); repair I-001-T1-R2 in PACKET 11.
OUT_9/I-001-T1-R1: BLOCKED acknowledged (2026-07-07) — PM precondition defect (JRN-I001-7,
L-12); d421a09… ratified as the I-001-T1 completion commit of record.
OUT_8/I-001-T1: AMEND + RETURN (2026-07-07) — criterion 5 defective (JRN-I001-5, L-11);
corrected text = BRIEF amendments A1/A2.

## Pointers
Repository: `main` is behind the working lineage (packet/7 onward in `main..HEAD`). The
Director merges task/I-001-T1 → main after the R2 ACCEPT (one merge covers the accepted OUT_7
lineage and OUT_8…R2); task branches start from main thereafter (RV2 rule restored). Director
courier hygiene: docs zips for the PM are made outside the working tree (or deleted after
upload); /docs.zip is git-ignored as of PACKET 11. Standing OUT rules: L-10 evidence blocks;
OUT header per P5 §5; BRANCH/COMMITS via `git log --format='%H %s' main..HEAD` pasted
immediately before the final OUT commit, ending with the literal terminator line "+ final OUT
commit (hash not self-listable)"; the OUT-carrying commit is never amended — corrections land
as fix-up commits on top; the Director verifies the final hash as the branch tip at merge
(L-12). Packet preconditions anchor on ancestor commits or content checks, never on
OUT-reported tip hashes (L-12). Workspace-cleanliness criteria are scoped to the
agent-writable surface (L-13). Environment of record: arm64 macOS, Apple clang 17, cmake
3.27.8, Python 3.9.6, mpmath absent until I-002 (JRN-C000-5).
=====[ END FILE ]=====

== TASK ==
Precondition (Director, one yes/no before dispatch): run
`git merge-base --is-ancestor fb07d9f63c435b262c6ac641f777b2006ce246d5 task/I-001-T1 && echo ancestor-ok`
— it prints `ancestor-ok`. If not, do not dispatch; send the PM the output of
`git log --format='%H %s' -5 task/I-001-T1`.
(Optional housekeeping, not load-bearing for this task: delete `docs.zip` from the repo root —
it is your courier artifact, regenerable, and git-ignored after this packet's APPLY.)

Reading list: AGENTS.md · inbox/PACKET_11.md · P0 §2–§6 · P4 · P5 §5 ·
docs/05_INFRA/I-001_core_skeleton/BRIEF.md (TASK I-001-T1, AMENDMENTS A1 and A2) ·
docs/05_INFRA/I-001_core_skeleton/JOURNAL.md.
Whitelist: the reading list plus the files this task writes. Nothing else is opened.

Assignment: execute TASK I-001-T1-R2 exactly as written (the R1 attempts ended BLOCKED
(OUT_9, pre-CLAIM) and FAILED (OUT_10, honestly reported); JRN-I001-9 resolved R1's CLAIM, so
no unresolved CLAIM exists).

TASK I-001-T1-R2: Repair — emit the workspace evidence against BRIEF amendment A2 (P6 §3
RETURN-class repair; near-zero cost; no re-doing of build/test work)
depends_on: I-001-T1 (completion commit of record d421a098abf174f6fad03b331fee06fcd185fbd1,
JRN-I001-7)
objective: Produce the working-tree evidence judged against amendment A2.
branch: continue on `task/I-001-T1` at its current tip (no new branch; no reset; no history
rewriting; no amends — corrections land as fix-up commits on top, L-12).
inputs: the working tree as left by OUT_10 plus this packet's APPLY. Manifest: n/a —
pre-I-004; all values are verbatim command output (JRN-C000-2).
steps:
  1. After APPLY, append the CLAIM entry (JRN-I001-12 · CLAIM, actor: composer-agent,
     task: I-001-T1-R2) to docs/05_INFRA/I-001_core_skeleton/JOURNAL.md and commit it. If the
     journal shows an unresolved CLAIM for I-001-T1-R2, STOP: BLOCKED (collision guard).
  2. Run: `git --version ; sw_vers ; echo exit=$?` — copy the full output (environment
     record, P6 §4.5).
  3. Run: `git status --short --branch ; echo exit=$?` — copy the full output.
  4. Write docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1-R2.md per P1 §7, header
     `manifest: n/a — pre-I-004; all values are verbatim command output (JRN-C000-2)`,
     sections `Step 2` and `Step 3`, each containing only that step's verbatim output.
  5. Append the DONE (or FAILED) journal entry (JRN-I001-13 · DONE/FAILED), append one
     APPLIED.log line for serial 11, and commit.
  6. Take the BRANCH/COMMITS paste now: `git log --format='%H %s' main..HEAD`, append the
     literal terminator line `+ final OUT commit (hash not self-listable)`, then write
     outbox/OUT_11_I-001-T1-R2.md and commit it as the final commit. No amends afterwards.
output:
  - docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1-R2.md
  - journal CLAIM and DONE/FAILED entries
  - outbox/OUT_11_I-001-T1-R2.md
courier:
  - Full text of TR_I-001-T1-R2.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR contains `Step 2` verbatim (git version, OS record), ending `exit=0`.
  2. TR contains `Step 3` verbatim, ending `exit=0`, showing no modified entries and no
     untracked entries under src/, tests/, config/, data/, reports/, docs/, or outbox/ beyond
     this task's own outputs. Entries at the repository root and under inbox/ are pasted for
     the record and are not asserted (A2, L-13).
  3. The OUT contains verbatim CLAIM and DONE/FAILED journal entries.
  4. The OUT's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 11.
  (If Step 3 shows modified entries, or untracked entries under the asserted surface beyond
  this task's outputs: criterion 2 is replaced by "full output pasted verbatim including the
  violating entries"; task status is FAILED, honestly reported per P3 §7.)
OUT-REQUIREMENTS (per L-10 and L-12):
  - OUT header per P5 §5: `# OUT 11 — I-001-T1-R2 — DONE` (or FAILED/BLOCKED) with the
    `agent · branch · commits` line (commits list may omit the final OUT commit, per L-12);
  - APPLY CONFIRMATION with the serial-11 ledger line pasted;
  - JOURNAL ENTRIES: verbatim copies of every journal entry this packet applied (JRN-I001-10,
    JRN-I001-11) AND the task's CLAIM and DONE/FAILED entries (JRN-I001-12, JRN-I001-13);
  - FILE DIGESTS: `wc -c` and `shasum -a 256` output for every file this packet's FILES
    section wrote (docs/05_INFRA/I-001_core_skeleton/JOURNAL.md, docs/02_PROGRAM/LESSONS.md,
    .gitignore, docs/05_INFRA/I-001_core_skeleton/BRIEF.md, docs/00_STATE.md);
  - REPORT: TR_I-001-T1-R2.md in full;
  - BRANCH/COMMITS: the step-6 paste of `git log --format='%H %s' main..HEAD` ending with the
    literal terminator line `+ final OUT commit (hash not self-listable)`.
failure_modes:
  - Step 3 shows modified entries, or untracked entries under the asserted surface beyond
    this task's outputs → paste verbatim; status FAILED.
  - Unresolved CLAIM for I-001-T1-R2 in the infra journal → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not amend any commit; do not reset or rewrite history.
  - Do not edit, commit, delete, or ignore-list any file at the repository root or under
    inbox/ beyond what this packet's FILES section applies.
  - Do not edit any source, CMake, or config file.
  - Do not run commands not listed in the steps.
  - Do not truncate outputs.
Non-negotiables: stop-on-surprise except where a step records a failure verbatim per its
failure_modes; evidence per criterion; no invented values; whitelist respected.
End state: `task/I-001-T1` carries the repair commits, the final one adding
outbox/OUT_11_I-001-T1-R2.md — the single file returned to the PM.

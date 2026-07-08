# PACKET 10 — OUT_9 BLOCKED resolved; I-001-T1-R1 re-dispatched
pm: pm-fable5-a · date: 2026-07-07 · task: I-001-T1-R1 (attempt 2)

== VERDICT ==
OUT_9 (BLOCKED) acknowledged — correct agent behavior; the block is a PM authoring defect
(PACKET 9 precondition pinned a self-referential tip hash; JRN-I001-7 CORRECTION, L-12).
Resolution ruling: d421a098abf174f6fad03b331fee06fcd185fbd1 is the I-001-T1 completion commit
of record (content-equivalent amend of f8f15fa…; sole diff the OUT hash line); no reset —
option (a) rejected as it would discard applied PACKET-9 state and the BLOCKED record.
I-001-T1-R1 re-dispatched below with an ancestor-anchored precondition.

== FILES ==

=====[ FILE APPEND: docs/05_INFRA/I-001_core_skeleton/JOURNAL.md ]=====
---
### JRN-I001-7 · CORRECTION
actor: pm-fable5-a · task: I-001-T1-R1 · manifest: n/a

WHAT: PM authoring defect in the PACKET 9 TASK precondition: it pinned the task/I-001-T1 tip
to f8f15fa0802010c9221e5ae05d49d9c3acd5dc33, a hash taken from OUT_8's own BRANCH/COMMITS
paste. An OUT-carrying commit cannot list its own final hash; the OUT_8 agent amended to
correct the hash line, producing sibling d421a098abf174f6fad03b331fee06fcd185fbd1 as the true
tip, so the pinned hash was unattainable by construction. BLOCKED OUT_9 was correct agent
behavior. The same artifact is visible in OUT_9, which lists its own top commit — any
OUT-reported tip hash is stale-by-one by construction. Root cause: precondition anchored on
evidence that cannot be current. Durable fix (standing rule, STATE pointers, effective
PACKET 10): (i) the OUT-carrying commit is never amended to embed its own hash; BRANCH/COMMITS
pastes are taken immediately before the final OUT commit and end with the literal terminator
line "+ final OUT commit (hash not self-listable)"; the Director verifies the final hash as
the branch tip at merge; (ii) packet preconditions and reviews anchor on ancestor commits
(e.g. the packet's apply commit) or content checks, never on an OUT-reported tip hash.
LESSONS L-12. Resolution ruling: d421a09… ratified as the I-001-T1 completion commit of
record (content-equivalent; sole diff the OUT_8 BRANCH/COMMITS hash line, per OUT_9);
f8f15fa0… superseded by that amend. No reset: rewriting task/I-001-T1 would discard the
applied PACKET-9 FILES (JRN-I001-4/-5, L-11, BRIEF A1, STATE) and the BLOCKED record.
NUMBERS: none
LEARNED: recorded as LESSONS L-12
NEXT: I-001-T1-R1 re-dispatched (PACKET 10, serial 10, ancestor-anchored precondition).

---
### JRN-I001-6 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: OUT_9 (BLOCKED, I-001-T1-R1) processed per P5 §2 — BLOCKED is a working outcome,
answered in PACKET 10. OUT_9 compliance assessed on its own terms: P5 §5 header with
agent/branch/commits line — present; serial-9 APPLIED.log ledger line pasted — present;
verbatim copies of both journal entries this packet applied (JRN-I001-4, JRN-I001-5) —
present, with CLAIM/DONE correctly absent (never appended; the agent halted at the
precondition, before step 1); FILE DIGESTS (wc -c + sha256) for all four applied files —
present; REPORT in P4 BLOCKED form (WHAT I WAS DOING / WHAT HAPPENED / WHAT I NEED /
WHAT I DID NOT DO, options offered) — present; BRANCH/COMMITS paste — present, carrying the
self-reference caveat analyzed in JRN-I001-7. PACKET 9 FILES confirmed applied (I-001
JOURNAL, LESSONS L-11, BRIEF amendment A1, STATE); PACKET 10 does not re-apply them.
NUMBERS: none
LEARNED: nothing
NEXT: JRN-I001-7 CORRECTION; re-dispatch I-001-T1-R1 with the ancestor-anchored precondition.
=====[ END FILE ]=====

=====[ FILE APPEND: docs/02_PROGRAM/LESSONS.md ]=====

L-12: An OUT file cannot attest the hash of the commit that carries it: any BRANCH/COMMITS
line naming the OUT-carrying commit is stale-by-one by construction, and amending the commit
to "fix" the line only mints a new sibling hash. Therefore (i) OUT-carrying commits are never
amended to embed their own hash — the BRANCH/COMMITS paste is taken immediately before the
final OUT commit and ends with the literal terminator line "+ final OUT commit (hash not
self-listable)", and the Director verifies the final hash as the branch tip at merge; and
(ii) packet preconditions and review pins anchor on ancestor commits (e.g. the packet's apply
commit) or on content checks, never on an OUT-reported tip hash. Origin: PACKET 9's
precondition pinned OUT_8's self-listed tip f8f15fa0…, unattainable after the agent's
hash-correcting amend (true tip d421a09…), forcing BLOCKED OUT_9 (JRN-I001-7).
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/00_STATE.md ]=====
# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_9 BLOCKED resolved (self-referential precondition defect, JRN-I001-7); I-001-T1-R1 re-dispatched (PACKET 10)

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
| I-001 engine lib skeleton | BUILT — R1 re-dispatch after BLOCKED OUT_9 (JRN-I001-7) | R1 repair review → VERIFIED | Director dispatches PACKET 10 (I-001-T1-R1, attempt 2) |
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
OUT_9/I-001-T1-R1: BLOCKED acknowledged (2026-07-07) — PM precondition defect (JRN-I001-7,
L-12); d421a09… ratified as the I-001-T1 completion commit of record; repair re-dispatched in
PACKET 10.
OUT_8/I-001-T1: AMEND + RETURN (2026-07-07) — criteria 1–4, 6, 7 + L-10 COMPLIANT; criterion 5
defective (PM authoring error, JRN-I001-5); corrected text = I-001 BRIEF amendment A1; repair
I-001-T1-R1 dispatched in PACKET 9.

## Pointers
Repository: `main` is behind the working lineage (packet/7 and packet/8 apply commits in
`main..HEAD`, OUT_8/OUT_9). The Director merges task/I-001-T1 → main after the R1 ACCEPT (one
merge covers the accepted OUT_7 lineage, OUT_8, and R1); task branches start from main
thereafter (RV2 rule restored). Standing OUT rules: L-10 evidence blocks; OUT header per
P5 §5; BRANCH/COMMITS via `git log --format='%H %s' main..HEAD` pasted immediately before the
final OUT commit and ending with the literal terminator line "+ final OUT commit (hash not
self-listable)"; the OUT-carrying commit is never amended to embed its own hash — the Director
verifies the final hash as the branch tip at merge (L-12). Packet preconditions anchor on
ancestor commits or content checks, never on OUT-reported tip hashes (L-12). Environment of
record: arm64 macOS, Apple clang 17, cmake 3.27.8, Python 3.9.6, mpmath absent until I-002
(JRN-C000-5).
=====[ END FILE ]=====

== TASK ==
Precondition (Director, one yes/no before dispatch): run
`git merge-base --is-ancestor eae55780d0d3b6736320e709d3be2885f149e163 task/I-001-T1 && echo ancestor-ok`
— it prints `ancestor-ok`. If not, do not dispatch; send the PM the output of
`git log --format='%H %s' -5 task/I-001-T1`.

Reading list: AGENTS.md · inbox/PACKET_10.md · P0 §2–§6 · P4 · P5 §5 ·
docs/05_INFRA/I-001_core_skeleton/BRIEF.md (TASK I-001-T1 and AMENDMENT A1) ·
docs/05_INFRA/I-001_core_skeleton/JOURNAL.md.
Whitelist: the reading list plus the files this task writes. Nothing else is opened.

Assignment: execute TASK I-001-T1-R1 exactly as written below (attempt 2; the PACKET 9 attempt
ended BLOCKED before CLAIM — see JRN-I001-6/-7 — so no unresolved CLAIM exists).

TASK I-001-T1-R1: Repair — re-emit Step-5 evidence against BRIEF amendment A1 (P6 §3
RETURN-class repair; near-zero cost; no re-doing of build/test work)
depends_on: I-001-T1 (completion commit of record d421a098abf174f6fad03b331fee06fcd185fbd1,
ratified in JRN-I001-7)
objective: Produce the working-tree evidence judged against BRIEF amendment A1.
branch: continue on `task/I-001-T1` at its current tip (repair of the same task; no new
branch; no reset; no history rewriting).
inputs: the working tree as left by OUT_9. Manifest: n/a — pre-I-004; all values are verbatim
command output (JRN-C000-2).
steps:
  1. After APPLY, append the CLAIM entry (JRN-I001-8 · CLAIM, actor: composer-agent,
     task: I-001-T1-R1) to docs/05_INFRA/I-001_core_skeleton/JOURNAL.md and commit it. If the
     journal shows an unresolved CLAIM for I-001-T1-R1, STOP: BLOCKED (collision guard).
  2. Run: `git --version ; sw_vers ; echo exit=$?` — copy the full output (environment
     record, P6 §4.5).
  3. Run: `git status --short --branch ; echo exit=$?` — copy the full output.
  4. Write docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1-R1.md per P1 §7, header
     `manifest: n/a — pre-I-004; all values are verbatim command output (JRN-C000-2)`,
     sections `Step 2` and `Step 3`, each containing only that step's verbatim output.
  5. Append the DONE (or FAILED) journal entry (JRN-I001-9 · DONE/FAILED), append one
     APPLIED.log line for serial 10, and commit.
  6. Take the BRANCH/COMMITS paste now: `git log --format='%H %s' main..HEAD`, append the
     literal terminator line `+ final OUT commit (hash not self-listable)`, then write
     outbox/OUT_10_I-001-T1-R1.md and commit it as the final commit. Do not amend this or any
     commit afterwards.
output:
  - docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1-R1.md
  - journal CLAIM and DONE/FAILED entries
  - outbox/OUT_10_I-001-T1-R1.md
courier:
  - Full text of TR_I-001-T1-R1.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR contains `Step 2` verbatim (git version, OS record), ending `exit=0`.
  2. TR contains `Step 3` verbatim, showing no modified entries and no untracked entries other
     than files matching `inbox/PACKET_*.md`, ending `exit=0`.
  3. The OUT contains verbatim CLAIM and DONE/FAILED journal entries.
  4. The OUT's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 10.
  (If Step 3 shows modified entries, or untracked entries other than `inbox/PACKET_*.md`:
  criterion 2 is replaced by "full output pasted verbatim including the violating entries";
  task status is FAILED, honestly reported per P3 §7.)
OUT-REQUIREMENTS (per L-10 and L-12):
  - OUT header per P5 §5: `# OUT 10 — I-001-T1-R1 — DONE` (or FAILED/BLOCKED) with the
    `agent · branch · commits` line (commits list may omit the final OUT commit, per L-12);
  - APPLY CONFIRMATION with the serial-10 ledger line pasted;
  - JOURNAL ENTRIES: verbatim copies of every journal entry this packet applied (JRN-I001-6,
    JRN-I001-7) AND the task's CLAIM and DONE/FAILED entries (JRN-I001-8, JRN-I001-9);
  - FILE DIGESTS: `wc -c` and `shasum -a 256` output for every file this packet's FILES
    section wrote (docs/05_INFRA/I-001_core_skeleton/JOURNAL.md, docs/02_PROGRAM/LESSONS.md,
    docs/00_STATE.md);
  - REPORT: TR_I-001-T1-R1.md in full;
  - BRANCH/COMMITS: the step-6 paste of `git log --format='%H %s' main..HEAD` ending with the
    literal terminator line `+ final OUT commit (hash not self-listable)`.
failure_modes:
  - Step 3 shows modified entries or untracked entries other than `inbox/PACKET_*.md` → paste
    verbatim; status FAILED.
  - Unresolved CLAIM for I-001-T1-R1 in the infra journal → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not amend any commit; do not reset or rewrite history.
  - Do not edit, commit, or remove inbox packet files.
  - Do not edit any source, CMake, or config file.
  - Do not run commands not listed in the steps.
  - Do not truncate outputs.
Non-negotiables: stop-on-surprise except where a step records a failure verbatim per its
failure_modes; evidence per criterion; no invented values; whitelist respected.
End state: `task/I-001-T1` carries the repair commits, the final one adding
outbox/OUT_10_I-001-T1-R1.md — the single file returned to the PM.

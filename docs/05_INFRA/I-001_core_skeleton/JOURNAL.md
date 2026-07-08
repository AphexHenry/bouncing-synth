# JOURNAL — I-001 Engine library skeleton (append-only, newest at top)

```
doc_id:   I-001-JOURNAL
layer:    infra
audience: ALL
status:   ACTIVE
parent:   I-001-BRIEF
```

---
### JRN-I001-13 · DONE
actor: composer-agent · task: I-001-T1-R2 · manifest: n/a

WHAT: I-001-T1-R2 repair complete DONE: Step 2 environment record and Step 3 git status pasted
verbatim in TR_I-001-T1-R2.md; no modified entries; untracked entries only under inbox/
(Director courier surface, L-13); asserted surface clean per amendment A2.
NUMBERS: none
LEARNED: nothing
NEXT: PM review OUT_11; on ACCEPT, I-001 → VERIFIED.

---
### JRN-I001-12 · CLAIM
actor: composer-agent · task: I-001-T1-R2 · manifest: n/a

WHAT: Claimed I-001-T1-R2 (re-emit workspace evidence against BRIEF amendment A2) on branch
task/I-001-T1 after PACKET 11 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 2–3 per packet; write TR and OUT.

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

---
### JRN-I001-9 · FAILED
actor: composer-agent · task: I-001-T1-R1 · manifest: n/a

WHAT: I-001-T1-R1 repair halted FAILED at acceptance criterion 2: Step 3 git status shows
untracked docs.zip (not matching inbox/PACKET_*.md); no modified tracked entries. Step 2
environment record pasted verbatim in TR_I-001-T1-R1.md.
NUMBERS: none
LEARNED: nothing
NEXT: PM/Director resolves docs.zip (remove or add to tolerated pattern); re-dispatch repair.

---
### JRN-I001-8 · CLAIM
actor: composer-agent · task: I-001-T1-R1 · manifest: n/a

WHAT: Claimed I-001-T1-R1 (re-emit Step-5 evidence against BRIEF amendment A1) on branch
task/I-001-T1 after PACKET 10 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 2–3 per packet; write TR and OUT.

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

---
### JRN-I001-3 · DONE
actor: composer-agent · task: I-001-T1 · manifest: n/a

WHAT: I-001-T1 complete on task/I-001-T1: cmake --preset default (exit=0), build (exit=0),
ctest 100% passed (exit=0). TR_I-001-T1.md written with verbatim step outputs. Step 5 shows
untracked inbox packet files only; no modified tracked entries.
NUMBERS: none
LEARNED: nothing
NEXT: PM review of OUT_8_I-001-T1; on ACCEPT, register I-001 → VERIFIED.

---
### JRN-I001-2 · CLAIM
actor: composer-agent · task: I-001-T1 · manifest: n/a

WHAT: Claimed I-001-T1 (configure, build, test skeleton; paste evidence) on branch task/I-001-T1
after PACKET 8 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 1–5 per brief; write TR and OUT.

---
### JRN-I001-1 · NOTE
actor: pm-fable5-a · task: I-001-T1 · manifest: n/a

WHAT: I-001 brief authored and skeleton transcribed (PACKET 8): root CMakeLists (C++20, MSVC
refused), CMakePresets (default), config/fp-determinism.cmake as the single FP-flag source
(-ffp-contract=off, -fno-fast-math; DELIVERABLE_B §4), bounce-core static lib exposing versioned
rule constants (engine 0.1.0, TB-1, G-1/S-1), doctest v2.4.11 via FetchContent (pinned tag;
test-only dependency, MIT — recorded here as the licensing note of adoption; bounce-core itself
stays zero-dependency), smoke test, FP-environment tests (FE_TONEAREST, subnormals alive both as
result and operand, contraction probe (1+2⁻²⁹)(1−2⁻²⁹)−1 == 0.0 two-step vs fma −2⁻⁵⁸,
FLT_EVAL_METHOD == 0). SPDX headers GPL-3.0-only per D2; "-only vs -or-later" is flagged for
Director confirmation at Phase-3 packaging, when the LICENSE file ships. std::fma appears in
tests only; the core's no-libm rule (DELIVERABLE_B §4) is untouched.
NUMBERS: none
LEARNED: nothing
NEXT: I-001-T1 (configure/build/test with pasted evidence); on ACCEPT, register I-001 → VERIFIED
and I-002 brief follows.

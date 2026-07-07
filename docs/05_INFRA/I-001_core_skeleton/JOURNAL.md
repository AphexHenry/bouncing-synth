# JOURNAL — I-001 Engine library skeleton (append-only, newest at top)

```
doc_id:   I-001-JOURNAL
layer:    infra
audience: ALL
status:   ACTIVE
parent:   I-001-BRIEF
```

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

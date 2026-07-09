# JOURNAL — I-002 refsim

---
### JRN-I002-7 · CLAIM
actor: composer-agent · task: I-002-T2 · manifest: n/a

WHAT: Claimed I-002-T2 (Tier-1 closed-form fixture generator) on branch task/I-002-T2
after PACKET 15 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per PACKET 15; write TR and OUT.

---
### JRN-I002-6 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: OUT_14 (BLOCKED, I-002-T2) processed per P5 §2 and P6 §7. Diagnosis from pasted
evidence: the Director merge of task/I-002-T1 → main had not been run at dispatch (ACTION
steps skipped); additionally main carries out-of-loop direct commits 0df5f605… ("gitignore")
and e4420535… ("OUT_12: PACKET 12 BLOCKED…") and the I-001 lineage arrived via true merge
ef8a46cc… rather than fast-forward. Rulings: (i) second recurrence of the
Director-merge-pending block class → structural restructure per P6 §7.3, not another reminder:
STACKED-BRANCH RULE, effective PACKET 15 — task branches may extend the previous verified task
branch; preconditions anchor on ancestor checks against the branch being extended; Director
merges to main are batched at milestones under a non-blocking DIRECTOR ACTION list, with L-12
tip verification per batch; main is a checkpoint line (merge commits acceptable), no longer a
dispatch gate. (ii) PACKET 14 VOID — never applied, no serial-14 ledger line (repo-wins);
content folded into PACKET 15. (iii) Main divergence recorded, not rewritten (history is
append-only in spirit); the out-of-loop commits are content-benign. Precondition evidence for
this packet is already on file: OUT_14's own paste shows c36552ee… directly beneath the OUT_13
commit on task/I-002-T1.
NUMBERS: none
LEARNED: nothing (structural rule recorded here and in STATE pointers; candidate for LESSONS
if the class recurs despite it)
NEXT: I-002-T2 on branch task/I-002-T2 from task/I-002-T1 (this packet, serial 15).

---
### JRN-I002-5 · NOTE
actor: pm-fable5-a · task: I-002-T2 · manifest: n/a

WHAT: I-002-T2 authored (PACKET 15; originally PACKET 14, voided): tools/refsim/tier1_fixtures.py
— Tier-1 closed-form fixture generator per DELIVERABLE_B §6, stdlib-only (fractions for exact
rational verification; no new dependencies; the venv is the execution context of record). Two
fixture families at T2: FL-1 (flat line y=0, drop with h=5, g=10, e=1/2 — constructed so all
eight bounce times are exact dyadic rationals, exactly representable in binary64; the
canonical zero-drift fixture for loop_stability) and PB-1 (flight parabola onto y=x², h=9,
g=16 — constructed so the first contact time and point are exact integers; later events have
irrational normals and belong to Tier-2). Symbolic verification is exact rational replay with
residuals asserted == 0. PM pre-verification (P6 §7.4): generator run twice pre-authoring;
stdout and fixture digests byte-identical across runs; expected stdout (3 lines), both fixture
sha256 digests, and the generator's own sha256
(4fa8d89145f3f25f294f871fff4089cfa08287e745030bb4fd51297666296540) are pre-registered in the
T2 acceptance criteria. Fixtures land under tools/refsim/fixtures/ pending the I-003 store
(placement migrates at T4 per the brief's workstream plan).
NUMBERS: FL-1 events=8, all dyadic, all float-exact; PB-1 t1=1, contact=(1,1), residuals 0.
LEARNED: nothing
NEXT: I-002-T2 (this packet); on ACCEPT, T3 (Tier-2 mpmath simulator) brief follows.

---
### JRN-I002-4 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_13_I-002-T1 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 3 verbatim (Python 3.9.6, /usr/bin/python3), ends exit=0 | COMPLIANT |
| 2 | Step 4 verbatim, ends exit=0 | COMPLIANT |
| 3 | Step 5 contains "Successfully installed mpmath-1.3.0", ends exit=0 | COMPLIANT |
| 4 | Step 6 contains exactly "refsim-smoke-ok 1.3.0", ends exit=0 | COMPLIANT |
| 5 | Step 7 contains exactly the pre-registered 50-digit sqrt(2) line, ends exit=0 | COMPLIANT |
| 6 | Step 8: no modified; no untracked under the asserted surface; untracked limited to inbox/PACKET_13.md (courier surface, unasserted); venv correctly absent (git-ignored) | COMPLIANT |
| 7 | CLAIM and DONE verbatim in OUT | COMPLIANT |
| 8 | APPLIED.log serial-13 line pasted | COMPLIANT |
| L-10/L-12 | P5 §5 header; JRN-I001-14/-15 + JRN-I002-1 + CLAIM/DONE verbatim; wc -c + sha256 for all 8 applied files; TR in full; BRANCH/COMMITS ends with the literal terminator | COMPLIANT |
Verdict: ACCEPT. I-002-T1 VERIFIED. Structural confirmations from the evidence: main..HEAD
contained only that packet's three commits — the task branch started from the then-current
main; pip upgrade notice present and correctly ignored (DO_NOT respected). Blemish noted for
the record only: JRN-I002-3 contains the typo "NUMBERS: nonea" — journals are append-only; no
action. Merge of task/I-002-T1 into main moves to the batched-merge housekeeping list
(JRN-I002-6 stacked-branch rule).
NUMBERS: none
LEARNED: nothing
NEXT: I-002-T2 (JRN-I002-5, JRN-I002-6).

---
### JRN-I002-3 · DONE
actor: composer-agent · task: I-002-T1 · manifest: n/a

WHAT: I-002-T1 complete DONE: venv at tools/refsim/.venv with mpmath 1.3.0 pinned via
requirements.txt; smoke outputs match PM-pre-verified lines (refsim-smoke-ok 1.3.0; sqrt(2)
to 50 significant digits); workspace clean per L-13 (untracked inbox/PACKET_13.md only).
NUMBERS: none
LEARNED: nothing
NEXT: PM review OUT_13; on ACCEPT, I-002-T2 brief follows.

---
### JRN-I002-2 · CLAIM
actor: composer-agent · task: I-002-T1 · manifest: n/a

WHAT: Claimed I-002-T1 (venv + pinned mpmath + smoke evidence) on branch task/I-002-T1
after PACKET 13 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–8 per BRIEF; write TR and OUT.

---
### JRN-I002-1 · NOTE
actor: pm-fable5-a · task: I-002-T1 · manifest: n/a

WHAT: I-002 brief authored (PACKET 13) per DELIVERABLE_B §6 and DELIVERABLE_C §3: workstream
T1 (venv + pinned mpmath + smoke), T2 (Tier-1 closed-form fixture generator), T3 (Tier-2
≥ 50-digit simulator with the reference_converged precision-doubling check), T4 (fixture
format for I-003). Dependency adoption recorded: mpmath 1.3.0, BSD-3-Clause,
GPLv3-compatible, gate-time tooling only — never linked, called, or vendored into product
code. T1 acceptance criteria carry PM-pre-verified expected outputs (smoke line
`refsim-smoke-ok 1.3.0`; sqrt(2) to 50 significant digits) — verified by the PM against
mpmath 1.3.0 on 2026-07-08 before authoring, per P6 §7.4 practice. Venv path
tools/refsim/.venv git-ignored at adoption.
NUMBERS: none
LEARNED: nothing
NEXT: I-002-T1 (this packet); on ACCEPT, T2 brief follows.

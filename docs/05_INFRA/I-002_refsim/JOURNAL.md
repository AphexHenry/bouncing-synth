# JOURNAL — I-002 refsim

---
### JRN-I002-19 · CLAIM
actor: composer-agent · task: I-002-T3b-R1 · manifest: n/a

WHAT: Claimed I-002-T3b-R1 (repair — re-emit digest and simulator evidence against amended
criterion 1) on branch task/I-002-T3 after PACKET 18 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–9 per PACKET 18; write TR and OUT.

---
### JRN-I002-18 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_17_I-002-T3b per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 3 digest == pre-registered dcaf6eb9… — NOT MET (observed 2941d303…, 6734 bytes) | COMPLIANT (BLOCKED branch) |
| 2 | Step 4 == pre-registered 7-line stdout, ends exit=0 | COMPLIANT |
| 3 | Step 5 identical to Step 4, ends exit=0 | COMPLIANT |
| 4 | Step 6: no modified; untracked limited to inbox/PACKET_*.md (L-13) | COMPLIANT |
| 5 | CLAIM and BLOCKED journal entries verbatim in OUT | COMPLIANT |
| 6 | APPLIED.log serial-17 line pasted | COMPLIANT |
| L-10/L-12 | P5 §5 header; JRN-I002-13/-14 + CLAIM/BLOCKED verbatim; wc -c + sha256 for all 4 applied files; TR in full; BRANCH/COMMITS baseline 0aa31192..HEAD with literal terminator | COMPLIANT |
Verdict: AMEND + RETURN (P6 §2.4) — criterion 1 digest was defective (JRN-I002-17); the
BLOCKED report is valid evidence and involves no agent error. Simulator stdout in Steps 4–5
already matches the amended acceptance criteria. No VERIFIED status existed to suspend.
NUMBERS: file size 6734 vs pre-registered 6733.
LEARNED: nothing
NEXT: I-002-T3b-R1 (this packet, serial 18).

---
### JRN-I002-17 · CORRECTION
actor: pm-composer · task: I-002-T3b · manifest: n/a

WHAT: PM digest pre-registration defect on PACKET 17. The FILE OVERWRITE block for
tools/refsim/tier2_refsim.py was authored without the POSIX terminal newline; the agent
applied the packet faithfully and git recorded 6734 bytes (sha256 2941d303…). Functional
stdout matches PM pre-verification on the 6734-byte tree. Root cause: PM byte-exact
transcription check used a pre-hash of the packet block body without the trailing newline
that applied files carry. Durable fix: pre-verify digests from the exact bytes the APPLY
step will commit (extract packet block → hash with standard trailing newline), never from
the raw block body alone. Repair amends criterion 1 to 2941d303… (6734 bytes); no file
re-issue required — repo-wins.
NUMBERS: 6733 vs 6734 bytes; dcaf6eb9… vs 2941d303….
LEARNED: nothing
NEXT: I-002-T3b-R1 repair (PACKET 18).

---
### JRN-I002-16 · BLOCKED
actor: composer-agent · task: I-002-T3b · manifest: n/a

WHAT: BLOCKED at Step 3: tier2_refsim.py sha256 digest mismatch — observed
2941d303122e63e28e183728e114b15833c5c29a4dff2b40c3bdfae2a70e329d (6734 bytes) vs
pre-registered dcaf6eb9a373779706ac96a9324403e0b672ac819f376ddcb228cfb16af7276d
(6733 bytes). Transcription defect per PACKET 17 failure_modes; halted per
stop-on-surprise. Steps 4–5 stdout matches pre-registered 7-line output; Step 6
workspace clean on asserted surface (untracked inbox/PACKET_*.md only).
NUMBERS: file size 6734 vs expected 6733.
LEARNED: nothing
NEXT: PM re-issue PACKET 17 FILES block for tier2_refsim.py with corrected bytes.

---
### JRN-I002-15 · CLAIM
actor: composer-agent · task: I-002-T3b · manifest: n/a

WHAT: Claimed I-002-T3b (algorithm-identity Tier-2 reference simulator) on branch
task/I-002-T3 after PACKET 17 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–9 per PACKET 17; write TR and OUT.

---
### JRN-I002-14 · NOTE
actor: pm-composer · task: I-002-T3b · manifest: n/a

WHAT: I-002-T3b authored (PACKET 17): tools/refsim/tier2_refsim.py — algorithm-identity
upgrade per DELIVERABLE_B §3/§5 and the I-002 brief T3 line. Replaces T3a oracle root-finding
(mp.polyroots) with VCA sign-variation isolation over sign-change brackets, fixed refinement
(bisection to width ≤ scale·2⁻⁴⁰, then exactly 3 Newton steps), G-1 grazing (|v_n| < 1e-9 →
continue past), S-1 settle (post-bounce |v_n| < 1e-9 → stop), contact points projected onto
the curve y=p(x). TB-1 is declared in stdout (single-ball smoke cases do not exercise
multi-ball ordering). reference_converged unchanged: event sequence at dps must agree with
2·dps to 40 digits. PM pre-verification (P6 §7.4): two runs byte-identical; FL-1 reproduces
Tier-1 exact dyadic times to < 1e-45; PB-1 first contact (1,1) to < 1e-45 plus three
Tier-2-only bounces; reference_converged=True on both fixtures. Pre-registered: full 7-line
stdout and generator sha256
dcaf6eb9a373779706ac96a9324403e0b672ac819f376ddcb228cfb16af7276d (6733 bytes).
NUMBERS: FL-1 events=8, reference_converged=True; PB-1 events=4, reference_converged=True.
LEARNED: nothing
NEXT: I-002-T3b (this packet); on ACCEPT, I-002-T4 (fixture format) and C-001/C-002 thesis
drafting proceed in parallel.

---
### JRN-I002-13 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_16_I-002-T3a per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 3 digest == pre-registered 7d7e9ce5…, ends exit=0 | COMPLIANT |
| 2 | Step 4 == pre-registered 6-line stdout, ends exit=0 | COMPLIANT |
| 3 | Step 5 identical to Step 4, ends exit=0 | COMPLIANT |
| 4 | Step 6: no modified; untracked limited to inbox/PACKET_*.md (L-13) | COMPLIANT |
| 5 | CLAIM and DONE verbatim in OUT | COMPLIANT |
| 6 | APPLIED.log serial-16 line pasted | COMPLIANT |
| L-10/L-12 | P5 §5 header; JRN-I002-9/-10 + CLAIM/DONE verbatim; wc -c + sha256 for all 4 applied files; TR in full; BRANCH/COMMITS baseline task/I-002-T2..HEAD with literal terminator | COMPLIANT |
Verdict: ACCEPT. I-002-T3a VERIFIED. Verified stack is now T1+T2+T3a deep on task/I-002-T3;
batched merge to main checkpoint line is listed in Director housekeeping (non-blocking).
NUMBERS: none
LEARNED: nothing
NEXT: I-002-T3b (JRN-I002-14).

---
### JRN-I002-12 · DONE
actor: composer-agent · task: I-002-T3a · manifest: n/a

WHAT: I-002-T3a complete DONE: tier2_refsim.py digest matches pre-registered value
(7d7e9ce5…); simulator stdout byte-identical across two runs; FL-1 reproduces Tier-1
exact dyadic event times to < 1e-45 with reference_converged=True; PB-1 first contact
(1,1) to < 1e-45 plus three Tier-2-only bounces converged to 40 digits;
workspace clean per L-13 (untracked inbox/PACKET_*.md only on asserted surface before commit).
NUMBERS: FL-1 events=8; PB-1 events=4, reference_converged=True.
LEARNED: nothing
NEXT: PM review OUT_16; on ACCEPT, I-002-T3b (algorithm-identity) follows.

---
### JRN-I002-11 · CLAIM
actor: composer-agent · task: I-002-T3a · manifest: n/a

WHAT: Claimed I-002-T3a (Tier-2 high-precision reference simulator) on branch
task/I-002-T3 after PACKET 16 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–9 per PACKET 16; write TR and OUT.

---
### JRN-I002-10 · NOTE
actor: pm-fable5-a · task: I-002-T3a · manifest: n/a

WHAT: I-002-T3a authored (PACKET 16): tools/refsim/tier2_refsim.py — Tier-2 high-precision
reference simulator per DELIVERABLE_B §6. Scope T3a: point-contact ball (R1) on polynomial
curves y=p(x); ballistic flight; collision as the smallest admissible root of
q(t) = y(t) − p(x(t)) built by exact polynomial substitution; reflection about the curve
normal with restitution along the normal component; all arithmetic mpmath at the requested
dps; reference_converged = event sequence at dps agrees with 2·dps to 40 digits. Deferred to
T3b for algorithm-identity with bounce-core: VCA root isolation with the fixed refinement
schedule and the TB-1/G-1/S-1 versioned rules (tie-break, grazing, settle) — T3a fixtures are
constructed to avoid those regimes, and T3a root-finding is oracle-grade mp.polyroots. PM
pre-verification (P6 §7.4): two runs byte-identical; FL-1 reproduces the Tier-1 exact dyadic
event times to < 1e-45 with reference_converged=True; PB-1 first contact (1,1) to < 1e-45,
plus three further Tier-2-only bounces (irrational normals) converged to 40 digits.
Pre-registered: full 6-line stdout and the generator sha256
7d7e9ce5a05bd57c652a2907cbbd48dd877e18fc5849b73b64aba4a27dc941a3 (4731 bytes). Cross-tier
validation is the point: Tier-1 exactness anchors Tier-2, Tier-2 extends past closed form.
NUMBERS: FL-1 max|t−exact| < 1e-45, 8 events; PB-1 4 events, reference_converged=True at
dps 50/100.
LEARNED: nothing
NEXT: I-002-T3a (this packet); on ACCEPT, T3b (algorithm-identity) and C-001/C-002 thesis
drafting proceed in parallel.

---
### JRN-I002-9 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_15_I-002-T2 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 3 digest == pre-registered 4fa8d891…, ends exit=0 | COMPLIANT |
| 2 | Step 4 == pre-registered 3-line stdout, ends exit=0 | COMPLIANT |
| 3 | Step 5 digests == pre-registered 63de96f4… / dc013c10…, ends exit=0 | COMPLIANT |
| 4 | Step 6 identical to Step 4, ends exit=0 | COMPLIANT |
| 5 | Step 7 identical to Step 5, ends exit=0 (byte-stable regeneration) | COMPLIANT |
| 6 | Step 8: no modified; untracked = inbox/PACKET_*.md (courier surface, unasserted) + tools/refsim/fixtures/ (this task's own outputs, committed at step 10 which follows the status step) | COMPLIANT |
| 7 | CLAIM and DONE verbatim in OUT | COMPLIANT |
| 8 | APPLIED.log serial-15 line pasted | COMPLIANT |
| L-10/L-12 | P5 §5 header; JRN-I002-4/-5/-6 + CLAIM/DONE verbatim; wc -c + sha256 for all 4 applied files (generator digest matches pre-registration in the applied tree too); TR in full; BRANCH/COMMITS baseline task/I-002-T1..HEAD with the literal terminator | COMPLIANT |
Verdict: ACCEPT. I-002-T2 VERIFIED. The stacked-branch rule performed as designed: zero
Director git actions on the dispatch path; verified stack is now T1+T2 deep, so the batched
merge to the main checkpoint line is listed in Director housekeeping (non-blocking).
NUMBERS: none
LEARNED: nothing
NEXT: I-002-T3a (JRN-I002-10).
---
### JRN-I002-8 · DONE
actor: composer-agent · task: I-002-T2 · manifest: n/a

WHAT: I-002-T2 complete DONE: tier1_fixtures.py digest matches pre-registered value; generator
stdout and fixture digests byte-identical across two runs; FL-1 (8 dyadic float-exact events)
and PB-1 (t1=1, contact=(1,1), residual=0) fixtures committed under tools/refsim/fixtures/;
workspace clean per L-13 (untracked inbox/PACKET_*.md only on asserted surface before commit).
NUMBERS: FL-1 events=8; PB-1 t1=1.
LEARNED: nothing
NEXT: PM review OUT_15; on ACCEPT, I-002-T3 brief follows.

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

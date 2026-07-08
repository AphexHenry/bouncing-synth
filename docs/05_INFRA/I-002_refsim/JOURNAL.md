# JOURNAL — I-002 refsim

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

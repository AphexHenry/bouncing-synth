# JOURNAL — C-000 Phase-0 scoping (append-only, newest at top)

```
doc_id:   C-000-JOURNAL
layer:    track
audience: ALL
status:   ACTIVE
parent:   C-000-BRIEF
```

---
### JRN-C000-12 · DONE
actor: composer-agent · task: C-000-RV1 · manifest: n/a

WHAT: Completed C-000-RV1 evidence re-emission. Ran steps 1–6 verbatim; wrote TR_C-000-RV1.md
and OUT_5_C-000-RV1.md. Step 1: branch is packet/4 (precondition merge state not met).
NUMBERS: none
LEARNED: nothing
NEXT: none

---
### JRN-C000-11 · CLAIM
actor: composer-agent · task: C-000-RV1 · manifest: n/a

WHAT: Claimed C-000-RV1 per PACKET 5 dispatch.
NUMBERS: none
LEARNED: nothing
NEXT: execute steps 1–8; write TR_C-000-RV1.md and OUT file.

---
### JRN-C000-10 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Authored Phase-0 deliverable (c), architecture plan (reports/DELIVERABLE_C_ARCHITECTURE.md):
bounce-core headless deterministic library (zero deps, no JUCE types) + thin JUCE VST3 shell;
repo layout instantiating P3 §1; single-fragment FP-flag pinning with a runtime assertion test;
doctest (MIT); project venv for the mpmath reference; I-001…I-007 mapped to concrete paths and
phases.
NUMBERS: none
LEARNED: nothing
NEXT: deliverable (d), prioritized component slate; then the Phase-0 exit presentation.

---
### JRN-C000-9 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Corrects the PM reviews of OUT_2, OUT_3, OUT_4 and the authoring of PACKETs 2–4, and
reconciles a parallel-PM conflict. Incident 1: those OUT files lacked the P5 §5 JOURNAL ENTRIES
section (verbatim copies of entries applied this dispatch) and the PM accepted them, implicitly
treating applied content as checkable in the repo — inadmissible rationale per P6 §2.2. Root
cause: apply-only packets stated no explicit OUT requirements, so agent and PM both defaulted to
a thin format. The gap was raised by the Director — Director-side quality control is itself a
P6 §6.4 incident. Durable fix: L-10 appended to 02_PROGRAM/LESSONS.md; from this packet onward
every packet's TASK section carries an explicit OUT-REQUIREMENTS block, and an OUT missing any
required section is RETURN_FOR_REPAIR, never accepted. A one-paragraph P5 §5 amendment (v1.1)
codifying apply-only OUT content is warranted and deliberately deferred to the next full
re-issue of P5, because re-transcribing a framework file to insert one paragraph carries its own
byte-drift risk — L-10 plus the per-packet block is the binding rule in the interim. Incident 2:
two PM conversations ran in parallel; the second authored a conflicting, unshipped PACKET 5
(CORRECTION + repair task). Reconciled per DIRECTORS_MANUAL §5: repo wins (APPLIED.log verified
ending at serial 4, Director-pasted 2026-07-07); the conflicting draft is void; its stricter OUT
standard is adopted here; exactly one PM conversation runs the program from now on. Repair:
task C-000-RV1 re-emits transcription evidence for the files applied by packets 1–5 so Phase-0
gate review rests on OUT-file evidence.
NUMBERS: none
LEARNED: see L-10.
NEXT: C-000-RV1 execution; deliverable (d) follows.

---
### JRN-C000-8 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Authored Phase-0 deliverable (b), numerics decision memo
(reports/DELIVERABLE_B_NUMERICS.md). Core reduction: free flight is a spatial parabola, so every
Phase-1 collision is univariate polynomial root isolation (VCA + fixed refinement schedule in
double-double; no libm, no FMA in the core). Grazing rule G-1, Zeno/settle rule S-1, tie-break
TB-1 defined and versioned. Three scope rulings flagged for Director ratification at the Phase-0
gate: R1 point-contact model, R2 no ball–ball collisions, R3 transcendental families deferred.
NUMBERS: none
LEARNED: the polynomial-only core makes cross-platform bit-identity a testable expectation rather
than a hope; it stays gated per platform regardless.
NEXT: author deliverable (c), architecture plan.

---
### JRN-C000-7 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Authored Phase-0 deliverable (a), prior-art landscape (reports/DELIVERABLE_A_LANDSCAPE.md),
from PM desk research of public web sources dated 2026-07-06 (URLs cited in the document). Key
findings: interaction concept is established (2003–2026) but no surveyed system uses analytic
collision solving on exact curves, none guarantees bit-identical replay / zero drift /
sample-accurate MIDI, and no FOSS curve-based deterministic VST3 exists. C-000 kill sketch not
triggered: the core bet is unclaimed territory in the surveyed field.
NUMBERS: none
LEARNED: raw physics timing being "unmusical" is independently corrected by two products
(quantize/scale constraints) — supports mapping configurability as first-class in C-003.
NEXT: author deliverable (b), numerics decision memo.

---
### JRN-C000-6 · CORRECTION
actor: pm-fable5-a · task: C-000-T1 · manifest: n/a

WHAT: Corrects JRN-C000-2 (T1 spec). Two PM authoring defects: (1) the brief's stop-on-surprise
exemption named only steps 5–8, leaving a step-2 command failure formally ambiguous between
"record and continue" and "BLOCKED"; (2) the workspace-incomplete BLOCKED trigger enumerated
AGENTS.md/inbox/outbox/docs but not `.git`, so the agent had no rule under which to halt on the
missing repository — and the P5 §5 end-state (branch, commit shas) was unmeetable. Root cause:
the git-repo precondition was delegated to the Director without a matching agent-checkable
failure mode. Durable fix: program lesson L-09 appended to 02_PROGRAM/LESSONS.md; all future
briefs are authored against it. The agent is not at fault; OUT_1 is admitted with branch/commits
recorded as n/a — no repository (this entry).
NUMBERS: none
LEARNED: see L-09.
NEXT: Director initializes the git repository and makes the initial commit before any dispatch.

---
### JRN-C000-5 · NOTE
actor: pm-fable5-a · task: C-000-T1 · manifest: n/a

WHAT: Review of OUT_1_C-000-T1 per P6 §2. Verdict: ACCEPT. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 1 verbatim output present | COMPLIANT |
| 2 | Step 2 verbatim output present | COMPLIANT |
| 3 | Step 3 verbatim output present | COMPLIANT |
| 4 | Step 4 verbatim output present | COMPLIANT |
| 5 | Step 5 verbatim output present | COMPLIANT |
| 6 | Step 6 both outputs present | COMPLIANT |
| 7 | Step 7 output present (P6 §4.5 env record: Python 3.9.6, /usr/bin/python3) | COMPLIANT |
| 8 | Step 8 output present (ModuleNotFoundError: mpmath — compliant per brief) | COMPLIANT |
| 9 | CLAIM and DONE journal entries verbatim in OUT | COMPLIANT |
| 10 | APPLIED.log serial-1 line pasted in APPLY CONFIRMATION | COMPLIANT |
Environment findings of record (all values verbatim command output, TR_C-000-T1):
no `.git` at repo root; git 2.48.1; cmake 3.27.8; Apple clang 17.0.0 arm64-apple-darwin24.6.0
(g++ is clang); Python 3.9.6 at /usr/bin/python3; pip 26.0.1; mpmath not installed.
NUMBERS: none beyond the verbatim versions above (manifest n/a per JRN-C000-2 ruling).
LEARNED: FP-determinism scoping starts from a single platform: arm64 macOS / Apple clang 17.
NEXT: Director git-init + initial commit; PM authors Phase-0 deliverables (a)–(d).

---
### JRN-C000-4 · DONE
actor: composer-agent · task: C-000-T1 · manifest: n/a

WHAT: Completed C-000-T1 environment reachability record. Ran steps 1–8 verbatim; wrote TR_C-000-T1.md
and OUT_1_C-000-T1.md. Step 2: no git repository present. Step 8: mpmath not installed.
NUMBERS: none
LEARNED: nothing
NEXT: none

---
### JRN-C000-3 · CLAIM
actor: composer-agent · task: C-000-T1 · manifest: n/a

WHAT: Claimed C-000-T1 per PACKET 1 dispatch.
NUMBERS: none
LEARNED: nothing
NEXT: execute steps 1–8; write TR_C-000-T1.md and OUT file.

---
### JRN-C000-2 · NOTE
actor: pm-fable5-a · task: C-000-T1 · manifest: n/a

WHAT: Specced and dispatched C-000-T1 (environment reachability record). PM ruling: no manifest
infrastructure exists yet (I-004 SPECCED), so T1 reports verbatim command output only and its
report header carries `manifest: n/a` citing this entry. Command failures in steps 5–8 are defined
in the brief as valid recorded outcomes, not blockers.
NUMBERS: none
LEARNED: nothing
NEXT: C-000-T1 execution; in parallel, PM authors Phase-0 deliverables (a)–(d).

---
### JRN-C000-1 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: PM boot completed per P0 §6; sufficiency self-check passed and delivered to the Director.
Director decisions recorded: D1 — `00_PROJECT.md` v0.1 approved as ACTIVE module; D2 — license is
GPLv3. The PROJECT §11 text amendment ("to be confirmed" → GPLv3) is batched into module v0.2 at
Phase-0 exit per P0 §7; STATE and this entry are authoritative until then. Track C-000 opened at
SPECCED (thesis + brief written; register row appended).
NUMBERS: none
LEARNED: nothing
NEXT: dispatch C-000-T1.

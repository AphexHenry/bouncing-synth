# TASK REPORT — C-000-RV1
actor: composer-agent / status: DONE / manifest: n/a — evidence re-emission; all values are verbatim command output (JRN-C000-9)

PER ACCEPTANCE CRITERION:

Step 1

```
b9676c2dc4dcac17b3c52fdfb1bcf1d6c83d18bf
## packet/4
 M docs/02_PROGRAM/LESSONS.md
 M docs/03_TRACKS/C-000_scoping/JOURNAL.md
 M inbox/APPLIED.log
?? AGENTS.md
?? bounce-docs.zip
?? docs/00_GENESIS.md
?? docs/00_PROJECT.md
?? docs/00_PROJECT.template.md
?? docs/01_PROTOCOLS/
?? docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
?? docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md
?? docs/03_TRACKS/README.md
?? docs/04_ARCHIVE/
?? docs/05_INFRA/
?? docs/DIRECTORS_MANUAL.md
?? docs/LESSONS_CORE.md
?? docs/README.md
?? inbox/PACKET_1.md
?? inbox/PACKET_2.md
?? inbox/PACKET_3.md
?? inbox/PACKET_4.md
?? inbox/PACKET_5.md
?? outbox/README.md
```

Step 2

```
# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: C-000-T1 accepted; env findings + CORRECTION + L-09 (PACKET 2)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 0 — Scoping (PROJECT §3). Module v0.1 ACTIVE (Director-approved 2026-07-06). License: GPLv3
(Director 2026-07-06; PROJECT §11 text amendment batched to module v0.2 at Phase-0 exit).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-000 Phase-0 scoping | RUNNING (T1 DONE, accepted) | GATE_REVIEW (Director plan approval) | PM authoring of deliverables (a)–(d); Director git-init of the workspace |

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | SPECCED | brief | Phase-0 architecture/numerics memo |
| I-002 high-precision reference sim | SPECCED | brief | Phase-0 memo (note: mpmath absent; brief will create a project venv) |
| I-003 scenario store + split-lock | SPECCED | brief | Phase-0 architecture/numerics memo |
| I-004 gate runner + manifests | SPECCED | brief | Phase-0 architecture/numerics memo |
| I-005 event/pattern analysis harness | SPECCED | brief | Phase-0 architecture/numerics memo |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Phase-0 architecture/numerics memo |

## Open decisions (Director)
1. Approve Phase-0 scoping deliverables (a)–(d) when the PM presents them (standing exit gate,
   PROJECT §3). Options: approve / amend. PM rec: pending — deliverables not yet presented.

## Recent gate calls
None.

## Pointers
Workspace is not yet a git repository (TR_C-000-T1 step 2) — Director must run Manual §1.2
(git init + initial commit of the full working tree, capturing PACKET 1's applied state and T1's
outputs) before any further dispatch. Environment of record: arm64 macOS, Apple clang 17,
cmake 3.27.8, Python 3.9.6 (system), mpmath absent (JRN-C000-5).
```

Step 3

```
# COMPONENT_REGISTER — Bounce

```
doc_id:   COMPONENT_REGISTER
layer:    program
audience: PM (write), Director (read)
status:   ACTIVE
parent:   PROJECT §2
```

| C-id | name | one-line claim | layer | state | named baseline | outcome + report link |
|---|---|---|---|---|---|---|
| C-001 | Exact collision engine | Closed-form ballistic flight + analytic collision-time root-solve on the true curve yields bit-deterministic, drift-free event sequences in real time | engine | IDEA | naive fixed-timestep + polyline engine (PROJECT §5 Law 7) | — |
| C-002 | Curve library | A family of exactly-defined user-shapeable curves (with derivatives/normals) the engine solves against | curve | IDEA | tbd at THESIS | — |
| C-003 | Event→MIDI mapping engine | User-configurable collision→(pitch, velocity, channel) mapping emitted sample-accurately | mapping | IDEA | tbd at THESIS | — |
| C-004 | Plugin shell & visuals | JUCE VST3 shell with real-time visualization and host parameter/automation plumbing | ui | IDEA | tbd at THESIS | — |
| C-005 | Preset & state system | Full serialization of curve+balls+physics+mapping with replay-identity guarantee | io | IDEA | tbd at THESIS | — |
| C-000 | Phase-0 scoping | Phase 0 delivers a Director-approvable plan: prior-art landscape, numerics decision memo, architecture plan, prioritized component slate (PROJECT §3 a–d) | infra-facing | SPECCED | n/a — scoping gate is Director approval, not numeric (P2 §8) | — |
```

Step 4

```
# LESSONS — Bounce (program lessons, L-09+)

```
doc_id:   LESSONS
layer:    program
audience: ALL
status:   ACTIVE
parent:   LESSONS_CORE
```

New program lessons begin at L-09. None yet.

L-09: A brief's halt-vs-record boundary must be total over its steps, and its BLOCKED triggers
must enumerate every workspace prerequisite — including version control itself. Any precondition
delegated to the Director must also appear as an agent-checkable failure mode, because the agent
is the only actor positioned to detect its violation at execution time. Origin: C-000-T1, where
the workspace lacked `.git` (Director setup step skipped); the brief exempted only steps 5–8 from
stop-on-surprise and omitted `.git` from its setup-incomplete trigger, so the agent could neither
block on the missing repository nor meet the P5 §5 branch/commit end-state (JRN-C000-6).

L-10: An OUT file must carry, inside itself, every piece of evidence its review needs — for
apply-only packets that means verbatim copies of every journal/register/log line applied plus a
digest (byte count and sha256) of every file written; "it can be checked in the repo" is not
review evidence because the PM has no repo access by design (P6 §2.2). Enforcement: every
packet's TASK section states an explicit OUT-REQUIREMENTS block, and an OUT missing any required
section is returned for repair, never accepted. Origin: OUT_2–OUT_4 lacked the P5 §5
journal-copies section and were accepted anyway; caught by the Director (a P6 §6.4 incident);
compounded by a parallel PM conversation independently drafting the same correction
(JRN-C000-9).
```

Step 5

```
# JOURNAL — C-000 Phase-0 scoping (append-only, newest at top)

```
doc_id:   C-000-JOURNAL
layer:    track
audience: ALL
status:   ACTIVE
parent:   C-000-BRIEF
```

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
```

Step 6

```
    2272 docs/03_TRACKS/C-000_scoping/COMPONENT_THESIS.md
d7f420893d4e2c6580c777fea9494919a508c58e299e778e688d9ed4d7062112  docs/03_TRACKS/C-000_scoping/COMPONENT_THESIS.md
# THESIS — C-000 Phase-0 scoping

```
                      budget on commodity CPUs — either finding goes to the Director with evidence.
SCORE (PM):         — prior: mandatory (P2 §8) / reuse: high (landscape feeds every thesis) /
                      moat: n/a / risk: low — desk research only.

    5526 docs/03_TRACKS/C-000_scoping/BRIEF.md
44acc1359e2af12b418a615a5346e5cc12e3abe2b445851d539ca641281f82fe  docs/03_TRACKS/C-000_scoping/BRIEF.md
# C-000 BRIEF — Phase-0 scoping

```
  - Do not run any command not listed in the steps.
  - Do not interpret results or add recommendations; observations outside the task go in a NOTE
    journal entry only.

    7540 docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_A_LANDSCAPE.md
55363fa181e527faa6160b0d18bfac5879ec381b4e3637976acf5041047c432b  docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_A_LANDSCAPE.md
# DELIVERABLE (a) — Prior-art landscape: physics-based sequencers & instruments

```
  real-time audio budget — that is exactly Phase 1's `realtime_budget` gate, not assumable.
- Grazing/tangential collision handling is not discussed anywhere in the surveyed field; it
  remains the named domain risk of PROJECT §9(a), to be settled in deliverable (b).

    7432 docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_B_NUMERICS.md
00466aa4e8c00ddb8418828e517f994effce270b039b87685a9ff9f6905778ac  docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_B_NUMERICS.md
# DELIVERABLE (b) — Numerics decision memo

```

Musical-time sync (host tempo vs wall clock), mapping semantics (C-003), UI curve-editing
ergonomics, and preset format details — Phase-2 questions, owned by their component theses.

    4970 docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md
60bc04f7888095c71299cfe0c3abb2dc02df596ed48020002a8b973ad97df1aa  docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md
# DELIVERABLE (c) — Architecture plan

```

Curve-editing UX (how gestures become Bézier pieces), mapping semantics, host-tempo sync, and
preset file format details — owned by C-003/C-004/C-005 theses at Phase 2 entry.
```

DEVIATIONS: none

ARTIFACTS: docs/03_TRACKS/C-000_scoping/reports/TR_C-000-RV1.md

OBSERVATIONS: Precondition states branches packet/2, packet/3, packet/4 merged to main; Step 1
output shows current branch is `packet/4`, not main.

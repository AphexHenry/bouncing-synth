# PACKET 2 — C-000-T1 accepted; environment findings recorded; PM correction; L-09
pm: pm-fable5-a · date: 2026-07-06 · task: none

== VERDICT ==
ACCEPT — OUT_1_C-000-T1 reviewed per P6 §2; all 10 acceptance criteria COMPLIANT (table in
JRN-C000-5). Findings: workspace is not a git repository (Director setup step, Manual §1.2, still
open — blocks all further dispatch); mpmath absent from the system Python (deferred to the I-002
brief, which will create a project venv). PM CORRECTION journaled (JRN-C000-6) for two brief-
authoring defects; durable fix recorded as program lesson L-09. No state is marked VERIFIED.

== FILES ==

=====[ FILE APPEND: docs/03_TRACKS/C-000_scoping/JOURNAL.md ]=====
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
=====[ END FILE ]=====

=====[ FILE APPEND: docs/02_PROGRAM/LESSONS.md ]=====
L-09: A brief's halt-vs-record boundary must be total over its steps, and its BLOCKED triggers
must enumerate every workspace prerequisite — including version control itself. Any precondition
delegated to the Director must also appear as an agent-checkable failure mode, because the agent
is the only actor positioned to detect its violation at execution time. Origin: C-000-T1, where
the workspace lacked `.git` (Director setup step skipped); the brief exempted only steps 5–8 from
stop-on-surprise and omitted `.git` from its setup-incomplete trigger, so the agent could neither
block on the missing repository nor meet the P5 §5 branch/commit end-state (JRN-C000-6).
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/00_STATE.md ]=====
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
=====[ END FILE ]=====

== TASK ==
none — apply-only packet.

Precondition (Director, yes/no): the workspace root is now a git repository with an initial commit
containing the full working tree (`git init` + `git add -A` + commit, Manual §1.2). If not, do that
first, then dispatch this packet.

Reading list for the applying agent: `AGENTS.md` · this packet. Apply the FILES section byte-exact
(serial check first: last APPLIED.log line must be serial 1), append the APPLIED.log line, commit on
branch `packet/2`, and write `outbox/OUT_2.md` marked APPLIED. Then stop.

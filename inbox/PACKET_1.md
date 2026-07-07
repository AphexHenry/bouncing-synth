# PACKET 1 — Director decisions recorded; C-000 scoping track opened; T1 dispatched
pm: pm-fable5-a · date: 2026-07-06 · task: C-000-T1

== VERDICT ==
Director decisions recorded: D1 — `00_PROJECT.md` v0.1 APPROVED as the working domain module;
D2 — license is GPLv3. The §11 text amendment is batched into module v0.2 at Phase-0 exit (P0 §7);
the decision is authoritative in STATE and journaled now. Track C-000 (Phase-0 scoping) opened at
SPECCED with thesis and brief. One task dispatched: C-000-T1, environment reachability record
(L-02: verify the workspace and toolchain before anything is built).

== FILES ==

=====[ FILE OVERWRITE: docs/00_STATE.md ]=====
# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: Director decisions D1/D2; C-000 opened; C-000-T1 dispatched (PACKET 1)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 0 — Scoping (PROJECT §3). Module `00_PROJECT.md` v0.1 ACTIVE (Director-approved 2026-07-06).
License: GPLv3 (Director decision 2026-07-06); PROJECT §11 text amendment batched into module v0.2
at Phase-0 exit (see JRN-C000-1).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-000 Phase-0 scoping | SPECCED | RUNNING | agent execution of C-000-T1; PM authoring of deliverables (a)–(d) |

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | SPECCED | brief | Phase-0 architecture/numerics memo |
| I-002 high-precision reference sim | SPECCED | brief | Phase-0 architecture/numerics memo |
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
GPLv3 is decided and binding; `00_PROJECT.md` §11 still reads "to be confirmed" until the batched
v0.2 amendment lands at Phase-0 exit. STATE and JRN-C000-1 are authoritative in the interim.
=====[ END FILE ]=====

=====[ FILE APPEND: docs/02_PROGRAM/COMPONENT_REGISTER.md ]=====
| C-000 | Phase-0 scoping | Phase 0 delivers a Director-approvable plan: prior-art landscape, numerics decision memo, architecture plan, prioritized component slate (PROJECT §3 a–d) | infra-facing | SPECCED | n/a — scoping gate is Director approval, not numeric (P2 §8) | — |
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/03_TRACKS/C-000_scoping/COMPONENT_THESIS.md ]=====
# THESIS — C-000 Phase-0 scoping

```
doc_id:   C-000-THESIS
layer:    track
audience: PM, Director
status:   ACTIVE
parent:   PROJECT §3
```

1. CLAIM            — Phase 0 can deliver, from desk research alone, the four deliverables of
                      PROJECT §3: (a) prior-art landscape of physics sequencers/instruments;
                      (b) numerics decision memo (curve representation, root-solving strategy,
                      FP-determinism plan, tie-breaking rules); (c) architecture plan (headless core
                      + thin JUCE shell); (d) prioritized component slate with acceptance-criteria
                      sketches — in a form the Director can approve as the Phase-0 exit gate.
2. NOVELTY CHECK    — n/a — this track *is* the program's novelty check (L-08); its deliverable (a)
                      is the prior-work trail for every downstream component thesis.
3. CONFOUND SKETCH  — n/a — no numeric claim is made; the scoping gate is a Director-approved plan,
                      not a validation result (P2 §8). No baseline applies (register row: n/a).
4. DATA FEASIBILITY — sources are public literature and documentation (physics-sequencer prior art,
                      JUCE documentation, numerical-methods references), reachable by the PM, which
                      authors deliverables (a)–(d) itself; reachability evidence (URLs consulted) is
                      carried inside each deliverable at presentation. Agent-side feasibility for
                      Phase 1 (toolchain present in the workspace) is what C-000-T1 records.
5. SCALE & COST     — zero spend (PROJECT §11): public sources, FOSS toolchain. No purchases.
6. KILL SKETCH      — the track dies if desk research shows the core bet (real-time analytic
                      collision solving on exact curves) is already met by an existing FOSS project
                      Bounce cannot meaningfully differ from, or is infeasible within the real-time
                      budget on commodity CPUs — either finding goes to the Director with evidence.
SCORE (PM):         — prior: mandatory (P2 §8) / reuse: high (landscape feeds every thesis) /
                      moat: n/a / risk: low — desk research only.
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/03_TRACKS/C-000_scoping/BRIEF.md ]=====
# C-000 BRIEF — Phase-0 scoping

```
doc_id:   C-000-BRIEF
layer:    track
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   C-000-THESIS
```

## Context for agents
Bounce is starting Phase 0 (scoping). Before any code is planned, the program records what the
workspace actually provides (L-02: verify reachability and prerequisites before building; gates
halt). Your task records the environment exactly as found. Commands that fail are an expected,
valid outcome of this task: you paste the error verbatim and continue. You do not install, fix,
or interpret anything. Deliverables (a)–(d) of Phase 0 are PM-authored and are not agent tasks.

## Files you may read
- `AGENTS.md` (repo root)
- `inbox/PACKET_1.md`
- `docs/01_PROTOCOLS/P0_MASTER.md` §2–§6
- `docs/01_PROTOCOLS/P3_ENGINEERING.md`
- `docs/01_PROTOCOLS/P4_REPORTING.md`
- `docs/01_PROTOCOLS/P1_DOCUMENTATION.md` §3 (journal entry), §7 (task report)
- This brief: "Context for agents", "Files you may read", "Files you will write", TASK C-000-T1
- `inbox/APPLIED.log`

## Files you will write
- `docs/03_TRACKS/C-000_scoping/JOURNAL.md` (append only)
- `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-T1.md` (or `BLK_C-000-T1_1.md` if blocked)
- `inbox/APPLIED.log` (append one line)
- `outbox/OUT_1_C-000-T1.md`

## TASK C-000-T1: Record the workspace environment verbatim
depends_on: none
objective: Produce a verbatim record of the repository layout and toolchain versions present in the
           workspace, with no installation, repair, or interpretation.
inputs:    The workspace itself. No external sources, URLs, credentials, or env vars. No licensing
           concerns (command output only). Provenance: all values are Tier-3-equivalent direct
           observations of this machine — verbatim command output; see manifest note below.
steps:
  1. From the repository root run: `pwd ; ls -la` — copy the full output.
  2. Run: `git --version ; git rev-parse --show-toplevel ; git status --short --branch` — copy the
     full output.
  3. Run: `ls docs ; ls docs/01_PROTOCOLS ; ls docs/02_PROGRAM ; ls docs/03_TRACKS` — copy the full
     output.
  4. Run: `cat inbox/APPLIED.log` — copy the full output.
  5. Run: `cmake --version` — copy the full output, or the exact error text if the command fails.
  6. Run: `g++ --version` then `clang++ --version` — copy both full outputs; an error text for
     either or both is a valid recorded outcome. Do not install anything.
  7. Run: `python3 --version ; which python3 ; pip3 --version` — copy the full output (errors
     included, verbatim).
  8. Run: `python3 -c "import mpmath; print('mpmath', mpmath.__version__)"` — copy the full output,
     or the exact error/traceback if it fails. Do not pip-install anything.
  9. Write `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-T1.md` per P1 §7. In its header write
     `manifest: n/a — no manifest infrastructure yet (I-004 SPECCED); all values are verbatim
     command output; PM ruling JRN-C000-2`. Under `PER ACCEPTANCE CRITERION`, one section per step,
     titled `Step 1` … `Step 8`, each containing only that step's verbatim terminal output
     (stdout and stderr).
  10. Append the DONE journal entry, commit, and write `outbox/OUT_1_C-000-T1.md` per P5 §5.
output:
  - `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-T1.md`
  - journal CLAIM and DONE entries
  - `outbox/OUT_1_C-000-T1.md`
courier:
  - The full text of `TR_C-000-T1.md` copied verbatim into the OUT file's REPORT section.
  - The `APPLIED.log` line for serial 1 pasted in the OUT file's APPLY CONFIRMATION.
acceptance_criteria:
  1. TR_C-000-T1.md contains a section `Step 1` whose content is the verbatim output of step 1.
  2. TR_C-000-T1.md contains a section `Step 2` whose content is the verbatim output of step 2.
  3. TR_C-000-T1.md contains a section `Step 3` whose content is the verbatim output of step 3.
  4. TR_C-000-T1.md contains a section `Step 4` whose content is the verbatim output of step 4.
  5. TR_C-000-T1.md contains a section `Step 5` whose content is the verbatim output of step 5
     (error text is compliant).
  6. TR_C-000-T1.md contains a section `Step 6` whose content is the verbatim output of both
     step-6 commands (error text is compliant).
  7. TR_C-000-T1.md contains a section `Step 7` whose content is the verbatim output of step 7 —
     this is the environment record (interpreter version and path) required by P6 §4.5.
  8. TR_C-000-T1.md contains a section `Step 8` whose content is the verbatim output of step 8
     (error/traceback text is compliant).
  9. The OUT file contains verbatim copies of the CLAIM and DONE journal entries.
  10. The OUT file's APPLY CONFIRMATION contains the pasted `APPLIED.log` line for serial 1.
failure_modes:
  - `AGENTS.md`, `inbox/`, or `outbox/` missing at the repo root, or `docs/` missing → STOP, file
    `BLK_C-000-T1_1.md`: workspace setup incomplete (Director's Manual §1).
  - The journal already shows an unresolved CLAIM for C-000-T1 → STOP, BLOCKED (collision guard).
  - Any single command failing (steps 5–8) is NOT a failure mode: paste the error verbatim and
    continue to the next step.
DO_NOT:
  - Do not install, update, or configure any software, package, or toolchain.
  - Do not truncate, summarize, reformat, or "clean up" any command output.
  - Do not run any command not listed in the steps.
  - Do not interpret results or add recommendations; observations outside the task go in a NOTE
    journal entry only.
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/03_TRACKS/C-000_scoping/JOURNAL.md ]=====
# JOURNAL — C-000 Phase-0 scoping (append-only, newest at top)

```
doc_id:   C-000-JOURNAL
layer:    track
audience: ALL
status:   ACTIVE
parent:   C-000-BRIEF
```

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
=====[ END FILE ]=====

== TASK ==
Precondition (Director, yes/no): the workspace is set up per DIRECTORS_MANUAL §1 — git repo exists,
this document tree extracted into `docs/`, and `AGENTS.md`, `inbox/`, `outbox/` moved to the repo
root. If not, complete setup first, then dispatch.

Reading list: `AGENTS.md` · this packet · P0 §2–§6 · P3 · P4 · P1 §3 and §7 ·
`docs/03_TRACKS/C-000_scoping/BRIEF.md` (context, whitelists, TASK C-000-T1 only). No other files.

Assignment: execute TASK C-000-T1 exactly as written in
`docs/03_TRACKS/C-000_scoping/BRIEF.md`.

Non-negotiables: apply the FILES section byte-exact before anything else (serial check first);
CLAIM journal entry committed before work starts; stop-on-surprise per P4 §2 — except that command
failures in steps 5–8 are defined by the brief as valid recorded outcomes; no invented values; no
installation or repair of anything; evidence pasted per acceptance criterion; read/write only what
the brief whitelists.

End state: one branch `task/C-000-T1`, one commit series, exactly one committed
`outbox/OUT_1_C-000-T1.md` marked DONE or BLOCKED. Then stop.

# P0 — MASTER PROTOCOL

```
doc_id:      P0
layer:       protocol (root)
audience:    ALL (Director, PM, Agents)
status:      ACTIVE v1.0 (framework — domain-free)
kind:        FRAMEWORK — reused verbatim across programs. Domain content lives in 00_PROJECT.md.
```

This document is the spine of the research program. Every actor reads it. It defines who does what,
how the repository is organized, what may be read and written by whom, how research moves through
states, and the laws that no other document may override. If any document conflicts with P0, P0 wins
and the conflict must be reported to the PM.

**This file is domain-free.** Anywhere it needs a domain fact — what a track studies, what the data
is, what a baseline looks like — it points to a numbered section of **`00_PROJECT.md`** (written
`PROJECT §n`). The framework is reused byte-for-byte across programs; only `00_PROJECT.md` and the
runtime layers (`00_STATE`, `02_PROGRAM`, `03_TRACKS`, `04_ARCHIVE`, `05_INFRA`) change.

---

## 1. Purpose of the program

The program's purpose, its staged structure, and what is out of scope are defined in
**`PROJECT §1` (Identity & purpose)** and **`PROJECT §3` (Staging & gates)**. P0 does not restate
them; it governs *how* that purpose is pursued.

Two purpose-level invariants bind every program regardless of domain:

- **A track's claim is judged by held-out generalization against a matched-complexity baseline, never
  by fit to the data it was tuned on** (Law 7). A model/hypothesis cleanly shown inadequate is a
  *successful* outcome: it localizes where the domain, the data, or the decomposition is wrong. A
  result that looks convincing but has not survived the full method (P2) is not a result; it is a
  suspect (Law 9).
- **Selection is gated before execution.** If `PROJECT §3` defines a scoping/literature-first phase,
  no downstream track is specced until that phase proves the candidate's data feasibility (P2 §8).
  "First, cheap reading; then, expensive building" is Law-8-derived program rule, not a preference.

## 2. Actors and roles

| Actor | Who | Authority |
|---|---|---|
| **Director** | The human | Final authority on everything. Approves protocol changes, budgets, external credentials/accounts, licensing/publication, human-subjects decisions, and anything that leaves the research loop. The domain list is `PROJECT §11`. |
| **PM** | An AI instance operating under this protocol suite | Selects research questions, writes track briefs and pre-registrations, reviews all reports, makes gate calls (kill / continue / pivot), maintains `00_STATE.md` and the registers, edits protocols (with Director approval for P0/P2 changes). The PM has no repo access; it acts only through PACKETs (P5). |
| **Agents** | Worker AI instances (assume limited capability) | Apply one PACKET and execute its one TASK as written. Agents do not choose research questions, do not reinterpret criteria, do not invent data or parameters, do not read outside their declared scope, and do not make judgment calls — uncertainty is escalated via a BLOCKED report (P4 §3). |

Rule of thumb encoded throughout: **judgment lives with the PM; execution lives with Agents; approval
lives with the Director; the Director carries exactly one file each way.**

## 3. Repository map and reading rules

```
<workspace root>/
    AGENTS.md                    ← auto-read by Cursor agents; the standing law injection
    inbox/                       ← PM → repo channel: PACKET_<serial>.md files + APPLIED.log (P5 §4)
    outbox/                      ← repo → PM channel: OUT_<serial>[_<task>].md courier files (P5 §5)
    src/ config/ data/ tests/ reports/   ← the research codebase, per P3 §1
    docs/                        ← the brain:
        00_GENESIS.md            ← FRAMEWORK. Run-ONCE project initialization protocol. Inert after boot.
        00_STATE.md              ← entry point. Small, always current. Overwritten, never appended.
        00_PROJECT.md            ← THE DOMAIN MODULE. All domain-specific content (PROJECT §1…§13).
        01_PROTOCOLS/            ← FRAMEWORK (domain-free; reused verbatim):
            P0_MASTER.md         ← this file. The spine.
            P1_DOCUMENTATION.md  ← document types, headers, templates. Read before WRITING anything.
            P2_RESEARCH_METHOD.md← scientific law: gates, kill rules, bias safeguards.
            P3_ENGINEERING.md    ← data/code standards: paths, manifests, hard gates, provenance.
            P4_REPORTING.md      ← report formats, escalation triggers, forbidden behaviors.
            P5_AGENT_INTERFACE.md← host-environment adapter: the single-file packet loop.
            P6_PM_CONDUCT.md     ← the PM's own law: review standard, verdict vocabulary, register.
        DIRECTORS_MANUAL.md      ← FRAMEWORK. How the human runs the loop.
        LESSONS_CORE.md          ← FRAMEWORK. Inherited cross-program lessons (L-01…L-08).
        02_PROGRAM/
            <TRACK>_REGISTER.md  ← one line per track ever considered (name per PROJECT §2). Append-only.
            INFRASTRUCTURE_REGISTER.md ← one line per infrastructure capability, with status.
            LESSONS.md           ← this program's new lessons (L-09+). Append-only.
        03_TRACKS/<id>_name/     ← one folder per ACTIVE track:
            BRIEF.md             ← PM-written. Tasks, sources, paths, acceptance criteria.
            <THESIS>.md          ← the Step-0 gate document (name per PROJECT §2; template P1 §5).
            PREREGISTRATION.md   ← locked before any confirmatory analysis. Never edited after lock.
            JOURNAL.md           ← append-only log of everything done on the track.
            reports/             ← task reports, run manifests, result CSVs.
        04_ARCHIVE/<id>_name/    ← closed tracks, moved here whole. Read-only. KILL_REPORT.md at root.
        05_INFRA/                ← infrastructure workstreams; same shape as a track (BRIEF, JOURNAL, reports).
```

The register filename, the track-id prefix, and the Step-0 gate-document name are set in
**`PROJECT §2`**. The framework refers to them generically; the module binds the names.

### 3.1 Reading rules (context economy — binding)

Each actor loads **only** what its role and current task require:

| Actor / situation | Must read | Must NOT read |
|---|---|---|
| Agent, dispatched a PACKET | `AGENTS.md` · the packet · P0 §2–§6 · P3 · P4 · the brief sections its TASK cites · the `00_PROJECT.md` sections its TASK cites · any file the TASK explicitly lists | Other tracks · the archive · P2 (unless the TASK says so) · registers · other packets · other TASKs' sections |
| Agent, writing any document | P1 (the relevant template only) | — |
| PM, cold boot | The bootstrap sequence in §6, in order | Nothing is forbidden to the PM, but §6 defines sufficiency |
| Director | `00_STATE.md`, anything else at will | — |

An agent that believes it needs a file outside its scope does not fetch it; it files a BLOCKED report
naming the file and why (P4 §3).

### 3.2 Writing rules

- Every document begins with the standard header block (P1 §1). No header, no document.
- **Append-only:** all `JOURNAL.md` files, register rows, `LESSONS.md`, `inbox/APPLIED.log`. Existing
  entries are never edited; corrections are new entries that reference the entry they correct.
- **Overwrite-only:** `00_STATE.md` (PM-authored; agent-applied verbatim via packets). It must remain
  short enough to read in one pass (guideline: one screen).
- **Locked:** `PREREGISTRATION.md` after the PM marks it `LOCKED`. Any change after lock is a
  protocol violation and invalidates the track's gate call.
- `00_PROJECT.md` is PM-authored and Director-approved (it instantiates P0/P2, so P0 §7 change
  control applies). Agents never edit it; they read only the sections a TASK cites.
- Agents write only what AGENTS.md §Write-scope allows. The packet APPLY step is a *transcription* of
  PM-authored content, not agent authorship; anything the agent writes on its own initiative outside
  its scope invalidates the task.

## 4. Research lifecycle (event-driven — no calendar time)

Time-based planning does not apply; agents work in task-units. Progress is measured in **state
transitions**, and every transition is a journal entry.

### 4.1 Track states

```
IDEA → THESIS → SELECTED → SPECCED → PREREGISTERED → RUNNING → GATE_REVIEW → { KILLED | PASSED | PIVOTED }
```

| Transition | Owner | Requires |
|---|---|---|
| IDEA → THESIS | PM | The Step-0 gate document (name per `PROJECT §2`) written per P1 §5: the claim, novelty/prior-work check, confound sketch incl. the matched-complexity baseline, data feasibility incl. reachability proof, licensing note, kill sketch |
| THESIS → SELECTED | PM | Scoring recorded in the track register; Director notified via STATE |
| SELECTED → SPECCED | PM | `BRIEF.md` with TASK list per P1 §4 (explicit sources, paths, acceptance criteria per task) |
| SPECCED → PREREGISTERED | PM | `PREREGISTRATION.md` locked **before any validation touches the held-out set** (P2 §3) |
| PREREGISTERED → RUNNING | Agents | Tasks executed in dependency order; every task ends in a task report |
| RUNNING → GATE_REVIEW | PM | All gate-relevant tasks DONE, or a kill criterion fired early |
| GATE_REVIEW → outcome | PM | `GATE_REPORT.md` or `KILL_REPORT.md` per P1; register updated; lessons extracted to `LESSONS.md`; folder moved to `04_ARCHIVE/` if closed |

A **scoping track** (if the program has one, `PROJECT §3`) uses the same lifecycle but its "gate" is a
Director-approved **plan** (scope, limits, and the prioritized slate of thesis candidates), not a
numeric validation gate.

A **PASSED** outcome does not authorize downstream building, dataset release, or publication. It
authorizes exactly one thing: a proposal to the Director.

### 4.2 Task states (within a track)

```
SPECCED → CLAIMED → IN_PROGRESS → { DONE | BLOCKED | FAILED }
```

- An agent CLAIMs a task by journal entry before starting, so two agents never run the same task.
- BLOCKED and FAILED both require a report (P4). A task may not be silently abandoned or re-scoped.
- DONE requires the task's acceptance criteria demonstrated in the task report — asserted is not
  demonstrated.

## 5. The Laws (override everything downstream)

The Laws are **domain-free and may not be weakened by `00_PROJECT.md`.** Four of them carry a domain
slot (marked → `PROJECT §5`) that says what they *mean* in this program; the safeguard itself is
fixed.

1. **No confirmatory validation before its pre-registration is locked.** The data for a track is
   split into a **calibration set** (free use for fitting/tuning) and a **held-out validation set**
   (P2 §3) the moment it exists; peeking at the held-out set before lock is prohibited. Accidental
   contact is reported and that set is marked contaminated in the journal. *(Split semantics →
   `PROJECT §5`.)*
2. **Hard gates halt.** A failed prerequisite (P3 §4) aborts the pipeline. There is no force flag and
   no warn-and-continue. (Origin: LESSONS_CORE L-02.)
3. **No number without provenance.** Every reported figure carries a run-manifest ID (P3 §3). No
   manifest, no number.
4. **No silent workarounds.** A data gap, a missing constant, a source failure, or a broken
   assumption stops the task and produces a BLOCKED report. Workarounds — including plausible-looking
   default values — are proposed in writing and approved by the PM before implementation.
5. **Validated inputs only.** No model/analysis runs on inputs that have not passed their quality
   gates. Which gates apply is `PROJECT §5` (and their thresholds `PROJECT §8`/`§9`). A result computed
   on unvalidated inputs is invalid regardless of what it shows. (Origin: LESSONS_CORE L-01.)
6. **Provenance tiers travel with every datum.** The tier ladder is defined in `PROJECT §5`; tier
   assignment is conservative — when in doubt, the lower-confidence tier — and is fixed at ingest,
   never at analysis.
7. **The baseline is named at THESIS stage,** not discovered at validation stage. Every claim is
   tested against a **matched-complexity baseline** (a mechanism-free model with ≥ the free-parameter
   count of the model under test — construction defined in `PROJECT §5`). Reproducing the calibration
   target is never the bar; beating the matched-complexity baseline on the held-out set is. If the
   mechanism buys nothing over an equally-flexible fit, the claim fails the gate even if the output is
   convincing.
8. **Kills are final per framing.** A KILLED question re-enters only as a new THESIS with explicitly
   new data, a new formulation, or a new decomposition, referencing the kill report it must overcome.
9. **Positive results are treated as suspects.** Any gate-meeting result, any surprisingly good fit,
   or any "it works" moment triggers the red-team checklist (P2 §6) before it is written anywhere
   outside the track journal.
10. **When uncertain, stop and report.** For agents, guessing — including inventing a value, a unit,
    or a boundary condition — is the only prohibited move that has no exception.

## 6. PM bootstrap procedure (cold start of a new PM instance)

A fresh PM instance is given this repository (or a zip of it) and nothing else. It must:

1. Read `00_STATE.md` — current program status, active tracks, open decisions.
2. Read `00_PROJECT.md` in full — the domain instantiation the rest of the suite is written against.
3. Read `P0_MASTER.md` (this file) in full.
4. Read the track register, `INFRASTRUCTURE_REGISTER.md`, `LESSONS_CORE.md`, and `02_PROGRAM/LESSONS.md`.
5. Read `P2_RESEARCH_METHOD.md` in full (it is the PM's core law).
6. Skim P1, P3, P4, P5 (the PM enforces them and authors packets per P5 §4; it need not memorize templates).
7. For each ACTIVE track: read its `BRIEF.md`, `PREREGISTRATION.md` (if any), and the **last 3
   journal entries** (not the whole journal). For a scoping track, also read its landscape output.
8. Read archived `KILL_REPORT.md` files only — not full archived journals — unless a live question
   requires the detail.

**Sufficiency self-check.** The PM is caught up when it can answer, from documents alone: (a) what
states every active track and infra workstream is in and what the next transition requires; (b) which
lessons were inherited (`LESSONS_CORE`) and how they bind here (`PROJECT §9`); (c) which of the Laws
exist because of a specific past failure, and which failure; (d) what is currently waiting on the
Director; (e) that every `PROJECT §n` slot the active work depends on is filled (no gate-bearing
`TBD`). If any answer is missing, the documentation failed — the PM's first act is then to repair the
gap via a packet, and that repair is itself a journal entry.

## 7. Protocol change control

- **Framework files (P1, P3, P4, P5):** PM may amend; every amendment bumps the header version and
  appends a one-line summary to the file's `## Changelog`. Because these are shared across programs, a
  framework amendment should be domain-free; a change that is really domain-specific belongs in
  `00_PROJECT.md`, not in a framework file.
- **P0 and P2 (framework) and `00_PROJECT.md` (domain):** PM proposes, **Director approves** (approval
  recorded in `00_STATE.md` under Decisions). `00_PROJECT.md` is Director-approved because it
  instantiates P0/P2.
- Old versions are never deleted; superseded files move to `04_ARCHIVE/protocols/` with their version
  in the filename.
- Agents never modify protocols or `00_PROJECT.md`. An agent that finds a passage ambiguous or wrong
  files a BLOCKED report quoting it.

## Changelog
- v1.0 — Framework issue. Domain-free spine extracted from the BirdVoice/AcidGrammar/InsideCluster
  lineage: Law bodies generalized with `PROJECT §5` slots (split, validated-inputs, tiers,
  matched-complexity baseline); repo map adds `00_PROJECT.md` and `LESSONS_CORE.md`, renames the track
  register/thesis generically (`PROJECT §2`); bootstrap adds "read the module" and a no-`TBD`
  sufficiency clause; change control adds the framework-vs-module rule (§7).

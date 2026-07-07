# P1 — DOCUMENTATION PROTOCOL

```
doc_id:      P1
layer:       protocol
audience:    anyone WRITING a document (read only the section for the doc type you are writing)
status:      ACTIVE v1.0 (framework — domain-free)
kind:        FRAMEWORK — reused verbatim. Domain names/fields come from 00_PROJECT.md.
parent:      P0
```

This protocol defines every document type in the repository, its exact template, and its rules. Copy
templates verbatim; fill every field; write `n/a — <reason>` rather than deleting a field. A document
missing header or fields is invalid and will be returned.

Where a template names a domain-specific element — the track-id prefix, the Step-0 gate document's
name, a register enum — it points to **`00_PROJECT.md`** (`PROJECT §2`). The templates themselves are
domain-free.

---

## 1. Standard header block (every document, first lines)

```
doc_id:      <e.g. <id>-BRIEF, P2; JRN entry ids are per-entry>
layer:       protocol | project | program | track | infra | archive
audience:    <who is expected to read this>
status:      DRAFT | ACTIVE | LOCKED | SUPERSEDED | ARCHIVED
parent:      <doc_id of the governing document>
```

## 2. `00_STATE.md` (PM-authored, overwrite-only, one screen max)

```
# STATE — <program name>
last_updated_by: <PM instance id> | trigger: <event that caused the update>

## Program status        ← 3 lines max (incl. current Phase, per PROJECT §3)
## Active tracks         ← table: track id | state | next transition | waiting on
## Infra workstreams     ← same table shape
## Open decisions (Director)   ← numbered; each = one question + options + PM recommendation
## Recent gate calls     ← last 3 only, one line each, link to report
## Pointers              ← anything a cold-boot PM must know that fits nowhere else (keep near-empty)
```

Update triggers (event-driven): any state transition (P0 §4), any gate call, any Director decision,
any protocol/module version bump, any new escalation. If none happened, STATE does not change.

## 3. `JOURNAL.md` entries (append-only; agents and PM)

One entry per event: task claim, task completion, blocker, gate call, correction. Newest at top.

```
---
### JRN-<track>-<serial> · <event type: CLAIM | DONE | BLOCKED | FAILED | GATE | NOTE | CORRECTION>
actor: <agent/PM id> · task: <TASK id or n/a> · manifest: <run_id or n/a>

WHAT: <what happened, 1–5 lines, past tense, concrete>
NUMBERS: <any figures, each with manifest id — or "none">
LEARNED: <anything that changes assumptions — or "nothing">
NEXT: <the state transition or task this unblocks — or "none">
```

CORRECTION entries must name the JRN id being corrected. The original is never edited.

## 4. `BRIEF.md` (PM only) — the track's work order

The brief is written for weak agents: every task must be executable without judgment. Structure:

```
# <track-id> BRIEF — <name>
<header block>

## Context for agents      ← 10 lines max: what this track studies and why. No history lesson.
## Files you may read      ← explicit whitelist (paths), incl. the 00_PROJECT.md sections this track needs
## Files you will write    ← explicit paths under this track only

## TASK <track-id>-T<n>: <imperative title>
depends_on: <task ids or none>
objective: <one sentence>
inputs:    <exact paths / URLs / DOIs / dataset ids, with auth/contact env-var names if needed;
            licensing note per source; provenance tier each source maps to (PROJECT §5)>
steps:     <numbered, imperative, no ambiguity. "Fetch X from URL Y. Save to path Z. Validate by W.">
output:    <exact file paths to produce>
courier:   <which small artifacts must be copied inline into the OUT file (P5 §5) — validation tables,
            test output, parameter tables, key CSV heads. Large/licensed artifacts are cited by path + hash.>
acceptance_criteria: <numbered, each independently checkable, each demonstrable in the task report>
failure_modes: <known ways this goes wrong and the REQUIRED response — usually "file BLOCKED report">
DO_NOT:    <explicit prohibitions, e.g. "do not substitute a source; do not invent a missing value;
            do not commit licensed material">
```

Rules: one task = one agent = one sitting's worth of work. If a task needs judgment mid-way, the brief
is wrong — PM splits it. Anything not whitelisted under "Files you may read" is out of scope.

## 5. Step-0 gate document — `<THESIS>.md` (PM writes; name per `PROJECT §2`)

```
# THESIS — <track-id> <name>
<header block>

1. CLAIM            — the claim, concretely and falsifiably stated: what is modeled/hypothesized, what
                      mechanism/equations/effect, what measurable it must reproduce, in what conditions.
2. NOVELTY CHECK    — prior work on this exact question (papers, code, datasets — list them). "Nobody
                      has done this" requires the desk-research trail proving you looked.
3. CONFOUND SKETCH  — the boring explanations that would produce an apparent match (over-fitting via
                      too many free parameters, memorizing one source, a confound masquerading as the
                      effect), and the design element that kills each. The matched-complexity baseline
                      (P0 Law 7, construction per PROJECT §5) is specified here, not later.
4. DATA FEASIBILITY — every source: URL/DOI/dataset/archive, license status, REACHABILITY PROVEN
                      (paste the actual check result), expected yield spot-checked on ≥10 samples with
                      counts, and whether there is enough data to BOTH calibrate and hold out (P2 §3).
                      Provenance tier each source maps to (PROJECT §5).
5. SCALE & COST     — expected data per held-out cell vs what the tolerance needs; any purchase
                      (paywalled dataset, participant payments, compute) with a ceiling for the Director.
6. KILL SKETCH      — the result that would kill this, stated before we're attached to it.
SCORE (PM):         — prior / reuse / moat / risk, brief.
```

## 6. `PREREGISTRATION.md` (PM writes, then LOCKED)

```
# PRE-REGISTRATION — <track-id>
<header block; status becomes LOCKED before any held-out-set contact>

DESIGN:          <one of the study designs named in PROJECT §4>
PRIMARY CRITERION:<the held-out error metric + tolerance, AND the required margin over the baseline>
MODEL FORM:      <the mechanism/equations and the exact list of free parameters (count = k)>
BASELINE:        <the matched-complexity baseline construction and its free-parameter count (≥ k)>
FEATURES/METRICS FROZEN: <the feature distances / error metrics this study may use>
SPLIT:           <calibration/held-out split marker hash (P3 §4 split_locked); stratification stated
                  (tier, source, biological/temporal unit — per PROJECT §5)>
GATE CRITERIA:   <the full numeric bar per P2 §7>
KILL CRITERIA:   <specific results that end the track early>
QUALITY GATES:   <the input-quality thresholds this study depends on (PROJECT §8), with refs>
OVERFIT BOUND:   <max allowed calibration-vs-held-out error gap>
BUDGET:          <max task-units before mandatory GATE_REVIEW regardless of state>
LOCKED_BY / LOCK_NOTE: <PM id; hash of this file at lock, recorded in JOURNAL>
```

## 7. Task report (agent writes; goes in `<track>/reports/TR_<task-id>.md`)

```
# TASK REPORT — <task id>
actor / status(DONE|FAILED) / manifest ids used or produced

PER ACCEPTANCE CRITERION: <criterion #> → <evidence: the actual number, path, or test output — pasted, not described>
DEVIATIONS: <none, or what differed from the brief and the PM approval reference>
ARTIFACTS: <every file written, with path>
OBSERVATIONS: <anything the PM should know; "none" is acceptable>
```

## 8. `KILL_REPORT.md` / `GATE_REPORT.md` (PM only; closes a track)

```
# KILL REPORT — <track-id>   (or GATE REPORT if PASSED/PIVOTED)
<header block>

VERDICT: KILLED | PASSED | PIVOTED → <new track-id>
CLAIM AS PREREGISTERED: <one paragraph>
EVIDENCE: <table: criterion | threshold | result | manifest id>
WHY (ordered by severity): <numbered reasons>
WHAT WOULD REOPEN THIS: <specific new data/formulation/decomposition, or "nothing plausible">
LESSONS EXTRACTED: <each also appended to 02_PROGRAM/LESSONS.md with an L-number>
RED-TEAM (if PASSED): <P2 §6 checklist, item by item, with evidence>
```

## 9. Registers (`02_PROGRAM/*.md`, PM only, append-only rows)

Track register row (filename and `<domain field>` per `PROJECT §2`):
`| <id> | name | one-line claim | <domain field> | state | named baseline | outcome + report link |`

Infrastructure register row:
`| I-XXX | capability | state (MISSING/SPECCED/BUILT/VERIFIED) | blocking (which tracks) | link |`

`LESSONS.md` entry: `L-XX: <one paragraph, self-contained, names the failure it came from>`. Lessons
are permanent; protocols cite them by L-number. The inherited cross-program lessons live in
`LESSONS_CORE.md` (L-01…L-08); this program's new lessons start at L-09 in `02_PROGRAM/LESSONS.md`.

## Changelog
- v1.0 — Framework issue. Step-0 gate document (§5) and register row (§9) de-named to `PROJECT §2`;
  prereg `DESIGN:` points to `PROJECT §4`; quality-gate/tier/baseline references point to `PROJECT §5`,
  `§8`. Templates otherwise unchanged from the lineage.

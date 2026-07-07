# P4 — REPORTING PROTOCOL

```
doc_id:      P4
layer:       protocol
audience:    Agents (full) and PM
status:      ACTIVE v1.0 (framework — domain-free)
kind:        FRAMEWORK — reused verbatim.
parent:      P0
```

Reporting is event-driven — there are no periodic reports, because agent time is not calendar time.
Every report is triggered by a state change and lands in two places: the track's `JOURNAL.md` (short
entry, P1 §3) and, where required, a full document in the track's `reports/`. Everything the PM needs
from a dispatch is additionally bundled into the single OUT courier file (P5 §5) — the OUT file
carries copies; the repo files remain the source of truth.

---

## 1. Report triggers (exhaustive)

| Event | Agent produces | Where |
|---|---|---|
| Applying a packet | ledger line + apply confirmation | `inbox/APPLIED.log` + the OUT file |
| Claiming a task | CLAIM journal entry | track JOURNAL |
| Completing a task | DONE journal entry + full task report (P1 §7) | JOURNAL + `reports/TR_<task>.md` |
| Hitting a blocker | BLOCKED journal entry + BLOCKED report (§3) | JOURNAL + `reports/BLK_<task>_<n>.md` |
| Task cannot succeed | FAILED journal entry + task report with failure analysis | JOURNAL + reports |
| Noticing something odd outside your task | NOTE journal entry (do NOT act on it) | JOURNAL |
| Gate call, state transition, decision | PM: GATE/NOTE entry + STATE update (via packet) | JOURNAL + `00_STATE.md` |

If no trigger fired, no report exists. Agents do not write status updates for their own sake.

## 2. Immediate-escalation events (report BEFORE doing anything else)

These generate a BLOCKED or NOTE entry the moment they are observed, and the agent halts the affected
work:

1. A prerequisite gate fails (P3 §4) — the pipeline already halted; your job is the report.
2. A data source is unreachable, needs credentials/contact values you don't have, is paywalled/
   licensed differently than described, or returns different content/schema than the brief describes.
3. A required value, unit, boundary condition, or measurement is missing or ambiguous in the sources
   your task names. Do not fill it with a plausible default — that is the guess Law 10 forbids. Report
   it.
4. A result **looks good** — a model meeting tolerance, a surprisingly good fit, an "it works" moment.
   Do not celebrate, do not extend the analysis, do not write it anywhere except the journal entry. It
   is a suspect until the PM runs the red-team checklist (P2 §6). (P0 Law 9)
5. Your task's assumptions turn out to be wrong as written (a file that should exist doesn't; a schema
   differs; an acceptance criterion is unmeasurable; a quality gate that should be VERIFIED isn't).
6. You are tempted to build a workaround. The temptation is the trigger. (P0 Law 4)
7. Two documents contradict each other, a packet conflicts with a brief, or a protocol/module passage
   is ambiguous for your case.
8. The held-out validation set was touched before pre-registration lock, by you or by anything you
   observe. (P0 Law 1)
9. Anything involving credentials, spending, licensing questions, human-subjects studies, or external
   accounts — Director-level (`PROJECT §11`), route via PM.
10. A packet fails its serial check or its FILES section cannot be applied exactly as written.

## 3. BLOCKED report format (`reports/BLK_<task>_<n>.md`)

```
# BLOCKED — <task id> #<n>
actor / task / halted_at: <the exact step number in the brief, or "packet apply">

WHAT I WAS DOING: <one line>
WHAT HAPPENED: <observed facts only — paste the error, the HTTP status, the schema diff, the missing
                value and the source that should have had it. No interpretation beyond one sentence.>
WHAT I NEED: <a decision, a credential (env var name), a file, a value, a brief amendment — be exact>
WHAT I DID NOT DO: <explicit confirmation you did not work around it, substitute sources, or invent a value>
OPTIONS (optional): <if you see options, list them neutrally. Do not pick one.>
```

The PM answers with a journal NOTE entry (and a brief amendment if needed), delivered in the next
packet. The agent resumes only from that answer, in a fresh chat.

## 4. Number discipline

Every figure in any report carries its run manifest id in the form `(run:<id>)`. A number without a
manifest id is treated as unverified and must not be repeated in any downstream document. Every value
additionally carries its units and provenance tier. PM returns non-compliant reports for repair; the
repair is a CORRECTION journal entry, never an edit.

## 5. Forbidden behaviors (agents) — violations invalidate the task

1. Reading files outside your TASK's whitelist (P0 §3.1).
2. Editing any existing journal entry, register row, locked pre-registration, protocol, module, or
   `APPLIED.log` history.
3. Substituting data sources, methods, thresholds, acceptance criteria, or model parameters on your
   own initiative.
4. Continuing past a failed gate, a missing value, a broken assumption, or an ambiguity — i.e.,
   guessing. (P0 Law 10)
5. Writing outside your allowed scope (AGENTS.md §Write-scope).
6. Reporting a number without a manifest id, a value without units/provenance, or marking DONE without
   pasted evidence per criterion.
7. Summarizing away detail in task reports: paste actual outputs (validation tables, test results,
   error text). Reports are evidence, not narrative.
8. Acting on anything you noticed outside your task (that's a NOTE entry for the PM, nothing more).
9. Copying licensed/third-party or copyrighted material into reports or OUT files (P3 §2b.6) — cite by
   path + hash.
10. Ending a dispatch without an OUT file, or with an OUT file that omits a report the repo contains.

## 6. PM reporting duties

- Update `00_STATE.md` (via packet) on every trigger in P1 §2 — STATE is the Director's (and any
  future PM's) single entry point and must never lag reality.
- Answer every BLOCKED report before assigning new tasks in that track.
- Every gate call = GATE journal entry + full report (P1 §8) + register row update + lessons extracted
  to `LESSONS.md` + STATE update + archive move if closed. All six, every time — the bootstrap
  procedure (P0 §6) depends on this invariant.
- Anything requiring Director input goes in STATE → Open decisions as: one question, the options, and
  the PM's recommendation with a one-line reason.

## Changelog
- v1.0 — Framework issue. Escalation examples de-domained ("missing value/unit — do not default it"
  §2.3; "it works" instead of a domain-specific tell §2.4); Director-gated list points to
  `PROJECT §11` (§2.9). Structure otherwise unchanged from the lineage.

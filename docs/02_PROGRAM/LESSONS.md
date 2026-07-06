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

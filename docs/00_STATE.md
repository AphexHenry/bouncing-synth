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

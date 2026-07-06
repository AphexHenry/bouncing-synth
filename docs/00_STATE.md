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

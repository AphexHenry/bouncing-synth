# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_18 ACCEPT — I-002-T3b VERIFIED (JRN-I002-21); T4 (scenario fixture format) dispatched (PACKET 19)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core (PROJECT §3). Module `00_PROJECT.md` v0.2 ACTIVE (GPLv3 in §11).
Phase-0 deliverables (a)–(d) APPROVED with rulings R1–R3. P6 §7 and the stacked-branch rule
(JRN-I002-6) in force: dispatch never waits on a merge.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | IDEA | THESIS | PM drafts thesis after T4 ACCEPT |
| C-002 Curve library | IDEA | THESIS | PM drafts thesis after T4 ACCEPT (leads C-001) |

C-000 Phase-0 scoping: CLOSED (gate passed) — see register.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED (JRN-I001-14; OUT_8 + OUT_11) | — complete | — |
| I-002 high-precision reference sim | T1–T3b VERIFIED; T4 dispatched (PACKET 19) | T4 review → I-002 complete | OUT_19 |
| I-003 scenario store + split-lock | SPECCED | brief | I-002 T4 ACCEPT (schema pinned) |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director creates repository hosting + CI account (open decision 1) |

## Open decisions (Director)
1. Create source hosting + CI account for I-007 (macOS arm64 + Linux x86-64). PM
   recommendation: GitHub free tier. Does not block I-002…I-005.
2. P6 §4 amendment (proposed per P6 §6.3; see L-11, L-13). Proposed §4.6: "A criterion over
   workspace state asserts only conditions the packet's own mechanics guarantee, scoped to
   the agent-writable surface; Director-contributed state is pasted for the record, never
   asserted." Approve yes/no; when answering, also paste the AGENTS.md line (if any) on
   whether APPLY commits inbox packet files. Does not block anything in flight.
3. GPLv3 "-only vs -or-later" for SPDX headers and shipped LICENSE — due Phase-3 packaging
   (JRN-I001-1). Not blocking.

## Director housekeeping (batched, non-blocking — do whenever convenient)
- Batch merge to main: after OUT_19 ACCEPT, verify tip per L-12 on task/I-002-T4, then
  `git checkout main && git merge task/I-002-T4`.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — record JRN-C000-18.

## Recent review verdicts
OUT_18/I-002-T3b-R1: ACCEPT (2026-07-09) — all criteria COMPLIANT (JRN-I002-21); I-002-T3b VERIFIED.
OUT_17/I-002-T3b: AMEND + RETURN (2026-07-09) — digest defect (JRN-I002-17); repair ACCEPT at OUT_18.
OUT_16/I-002-T3a: ACCEPT (2026-07-09) — I-002-T3a VERIFIED (JRN-I002-13).

## Pointers
Repository — stacked-branch rule (JRN-I002-6). PM digest pre-registration hashes on-disk
bytes (JRN-I002-17). Environment of record: arm64 macOS, Apple clang 17, cmake 3.27.8,
Python 3.9.6 + venv-pinned mpmath 1.3.0 under tools/refsim.

# STATE — Bounce
last_updated_by: pm-composer | trigger: OUT_17 AMEND+RETURN (digest defect JRN-I002-17); repair I-002-T3b-R1 dispatched (PACKET 18)

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
| C-001 Exact collision engine | IDEA | THESIS | PM drafts thesis in parallel with T4 (next PM turn) |
| C-002 Curve library | IDEA | THESIS | PM drafts thesis in parallel with T4 (next PM turn) |

C-000 Phase-0 scoping: CLOSED (gate passed) — see register.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED (JRN-I001-14; OUT_8 + OUT_11) | — complete | — |
| I-002 high-precision reference sim | T1, T2, T3a VERIFIED; T3b BLOCKED → R1 dispatched (PACKET 18) | R1 review → T4 | OUT_18 |
| I-003 scenario store + split-lock | SPECCED | brief | I-002 T4 (fixture format) |
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
- Batch merge to the main checkpoint line: after OUT_18 ACCEPT, verify tip per L-12
  (`git log --format='%H %s' -2 task/I-002-T3` — top names OUT_18 or OUT_17-R1, second is
  the prior verified commit), then `git checkout main && git merge task/I-002-T3`.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — record JRN-C000-18.

## Recent review verdicts
OUT_17/I-002-T3b: AMEND + RETURN (2026-07-09) — BLOCKED report fully compliant and honest
(no agent fault); criterion 1 digest defective (JRN-I002-17); repair I-002-T3b-R1 in PACKET 18.
OUT_16/I-002-T3a: ACCEPT (2026-07-09) — all criteria COMPLIANT (JRN-I002-13); I-002-T3a VERIFIED.
OUT_15/I-002-T2: ACCEPT (2026-07-08) — all criteria COMPLIANT (JRN-I002-9); I-002-T2 VERIFIED.
OUT_14/I-002-T2: BLOCKED acknowledged — merge-pending class ×2 → stacked-branch rule
(P6 §7.3, JRN-I002-6); PACKET 14 VOID.
OUT_13/I-002-T1: ACCEPT — I-002-T1 VERIFIED (JRN-I002-4).

## Pointers
Repository — stacked-branch rule (JRN-I002-6): task branches extend the previous verified
task branch; preconditions anchor on ancestor checks against the branch being extended;
Director merges to main are batched housekeeping with L-12 tip verification; main is a
checkpoint line. Standing OUT rules: L-10 evidence blocks; OUT header per P5 §5;
BRANCH/COMMITS pasted immediately before the final OUT commit against the named base branch,
ending with the literal terminator line "+ final OUT commit (hash not self-listable)"; no
amends — corrections are fix-up commits on top (L-12). Workspace-cleanliness criteria scoped
to the agent-writable surface (L-13). Blocked flows escalate per P6 §7; the PM pre-verifies
expected outputs before authoring criteria (§7.4). PM digest pre-registration must hash the
exact bytes APPLY will commit (JRN-I002-17). Environment of record: arm64 macOS, Apple clang
17, cmake 3.27.8, Python 3.9.6 + venv-pinned mpmath 1.3.0 under tools/refsim.

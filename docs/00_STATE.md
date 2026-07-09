# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_14 BLOCKED → stacked-branch rule (P6 §7.3, JRN-I002-6); PACKET 14 VOID, folded into PACKET 15; I-002-T2 dispatched, no Director git action on the critical path

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core (PROJECT §3). Module `00_PROJECT.md` v0.2 ACTIVE (GPLv3 in §11).
Phase-0 deliverables (a)–(d) APPROVED with rulings R1–R3. P6 §7 (blocked-flow escalation) in
force; stacked-branch rule in force (JRN-I002-6): dispatch never waits on a merge.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-002 Curve library | IDEA | THESIS | PM authors thesis (with C-001) — drafting begins alongside I-002 T3 |
| C-001 Exact collision engine | IDEA | THESIS | PM authors thesis (with C-002) — drafting begins alongside I-002 T3 |

C-000 Phase-0 scoping: CLOSED (gate passed) — see register.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED (JRN-I001-14; OUT_8 + OUT_11) | — complete | — |
| I-002 high-precision reference sim | T1 VERIFIED; T2 dispatched (PACKET 15) | T2 review → T3 brief | OUT_15 |
| I-003 scenario store + split-lock | SPECCED | brief | I-002 T2/T4 (fixture format) |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director creates repository hosting + CI account (open decision 1) |

## Open decisions (Director)
1. Create source hosting + CI account for I-007 (clean-checkout CI on macOS arm64 + Linux
   x86-64). PM recommendation: GitHub free tier. Does not block I-002…I-005.
2. P6 §4 amendment (proposed per P6 §6.3; see L-11, L-13). Proposed §4.6: "A criterion over
   workspace state asserts only conditions the packet's own mechanics guarantee, scoped to
   the agent-writable surface; Director-contributed state is pasted for the record, never
   asserted." Approve yes/no; when answering, also paste the AGENTS.md line (if any) on
   whether APPLY commits inbox packet files. Does not block I-002.
3. GPLv3 "-only vs -or-later" for SPDX headers and shipped LICENSE — due Phase-3 packaging
   (JRN-I001-1). Not blocking.

## Director housekeeping (batched, non-blocking — do whenever convenient)
- Batch merge to the main checkpoint line: after OUT_15 ACCEPT, merge task/I-002-T2 into main
  (it contains task/I-002-T1); verify the branch tip per L-12 first. Exact commands will be
  listed in the PM's next DIRECTOR ACTION (housekeeping) block.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — record JRN-C000-18.

## Recent review verdicts
OUT_14/I-002-T2: BLOCKED acknowledged (2026-07-08) — merge-pending class, second recurrence →
stacked-branch rule (P6 §7.3, JRN-I002-6); PACKET 14 VOID, folded into PACKET 15.
OUT_13/I-002-T1: ACCEPT (2026-07-08) — all criteria COMPLIANT (JRN-I002-4); I-002-T1 VERIFIED.
OUT_12 (apply-only, ×2 BLOCKED): PACKET 12 VOID; PM conduct defect (JRN-I001-15); fix = P6 §7.
OUT_11/I-001-T1-R2: ACCEPT — I-001 → VERIFIED (JRN-I001-14).

## Pointers
Repository — stacked-branch rule (JRN-I002-6): task branches may extend the previous verified
task branch; preconditions anchor on ancestor checks against the branch being extended, never
on main and never on OUT-reported tip hashes (L-12); Director merges to main are batched
housekeeping with L-12 tip verification per batch; main is a checkpoint line — merge commits
acceptable; out-of-loop commits on main recorded at JRN-I002-6 (0df5f605…, e4420535…,
ef8a46cc…), content-benign, not rewritten. Serials 12 and 14 retired VOID (JRN-I001-15,
JRN-I002-6). Standing OUT rules: L-10 evidence blocks; OUT header per P5 §5; BRANCH/COMMITS
pasted immediately before the final OUT commit, ending with the literal terminator line
"+ final OUT commit (hash not self-listable)"; no amends — corrections are fix-up commits on
top (L-12). Workspace-cleanliness criteria scoped to the agent-writable surface (L-13).
Blocked flows escalate per P6 §7; PM pre-verifies expected outputs before authoring criteria
(§7.4; JRN-I002-1/-5). BRANCH/COMMITS baseline under stacked branches: `git log
--format='%H %s' <base-branch>..HEAD` where <base-branch> is named in the task. Environment
of record: arm64 macOS, Apple clang 17, cmake 3.27.8, Python 3.9.6 + venv-pinned mpmath 1.3.0
under tools/refsim.

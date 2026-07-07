# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_9 BLOCKED resolved (self-referential precondition defect, JRN-I001-7); I-001-T1-R1 re-dispatched (PACKET 10)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core (PROJECT §3). Module `00_PROJECT.md` v0.2 ACTIVE (GPLv3 in §11;
Phase-0 gate of record in changelog and JRN-C000-18). Phase-0 deliverables (a)–(d) APPROVED with
rulings R1 (point-contact), R2 (no ball–ball), R3 (transcendental families deferred) —
docs/03_TRACKS/C-000_scoping/reports/.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-002 Curve library | IDEA | THESIS | PM authors thesis once I-001 is VERIFIED (with C-001) |
| C-001 Exact collision engine | IDEA | THESIS | PM authors thesis once I-001 is VERIFIED (with C-002) |

C-000 Phase-0 scoping: CLOSED (gate passed) — see register.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | BUILT — R1 re-dispatch after BLOCKED OUT_9 (JRN-I001-7) | R1 repair review → VERIFIED | Director dispatches PACKET 10 (I-001-T1-R1, attempt 2) |
| I-002 high-precision reference sim | SPECCED | brief | I-001 VERIFIED (creates venv, installs pinned mpmath) |
| I-003 scenario store + split-lock | SPECCED | brief | I-002 |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director creates repository hosting + CI account (open decision 1) |

## Open decisions (Director)
1. Create source hosting + CI account for I-007 (clean-checkout CI on macOS arm64 + Linux
   x86-64). Options: GitHub free tier (PM recommendation — Actions covers both platforms) /
   other host. Needed before the I-007 brief; does not block I-001…I-005.
2. P6 §4 amendment (proposed per P6 §6.3; second workspace-state authoring defect after L-09 —
   see L-11, JRN-I001-5). Proposed §4.6: "A criterion over workspace state asserts only
   conditions the packet's own mechanics guarantee; state contributed by the Director's
   dispatch steps or inherited from prior cycles appears in the criterion as an explicitly
   tolerated pattern." Approve yes/no. When answering, also paste the AGENTS.md line (if any)
   governing whether APPLY commits inbox packet files, so AGENTS.md and P5 §2 ("the applied
   packet files" in the commit series) are aligned in the same amendment packet. Does not
   block R1 or I-002.
3. GPLv3 "-only vs -or-later" for SPDX headers and the shipped LICENSE file — due at Phase-3
   packaging (JRN-I001-1). Not blocking; tracked here so it is not lost.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — deliverables (a)–(d) approved, R1–R3
ratified. Record: JRN-C000-18; artifacts digest-pinned via RV1/RV2 evidence.

## Recent review verdicts
OUT_9/I-001-T1-R1: BLOCKED acknowledged (2026-07-07) — PM precondition defect (JRN-I001-7,
L-12); d421a09… ratified as the I-001-T1 completion commit of record; repair re-dispatched in
PACKET 10.
OUT_8/I-001-T1: AMEND + RETURN (2026-07-07) — criteria 1–4, 6, 7 + L-10 COMPLIANT; criterion 5
defective (PM authoring error, JRN-I001-5); corrected text = I-001 BRIEF amendment A1; repair
I-001-T1-R1 dispatched in PACKET 9.

## Pointers
Repository: `main` is behind the working lineage (packet/7 and packet/8 apply commits in
`main..HEAD`, OUT_8/OUT_9). The Director merges task/I-001-T1 → main after the R1 ACCEPT (one
merge covers the accepted OUT_7 lineage, OUT_8, and R1); task branches start from main
thereafter (RV2 rule restored). Standing OUT rules: L-10 evidence blocks; OUT header per
P5 §5; BRANCH/COMMITS via `git log --format='%H %s' main..HEAD` pasted immediately before the
final OUT commit and ending with the literal terminator line "+ final OUT commit (hash not
self-listable)"; the OUT-carrying commit is never amended to embed its own hash — the Director
verifies the final hash as the branch tip at merge (L-12). Packet preconditions anchor on
ancestor commits or content checks, never on OUT-reported tip hashes (L-12). Environment of
record: arm64 macOS, Apple clang 17, cmake 3.27.8, Python 3.9.6, mpmath absent until I-002
(JRN-C000-5).

# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: PACKET 13 — P6 §7 in force (Director-ordered); PACKET 12 VOID, content folded in; I-001 VERIFIED (JRN-I001-14); main fast-forwarded; I-002 briefed, T1 dispatched

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
docs/03_TRACKS/C-000_scoping/reports/. P6 §7 (blocked-flow escalation) in force by Director
order, 2026-07-08.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-002 Curve library | IDEA | THESIS | PM authors thesis (with C-001, after I-002-T1 review) |
| C-001 Exact collision engine | IDEA | THESIS | PM authors thesis (with C-002, after I-002-T1 review) |

C-000 Phase-0 scoping: CLOSED (gate passed) — see register.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED (JRN-I001-14; OUT_8 + OUT_11) | — complete | — |
| I-002 high-precision reference sim | BRIEFED — T1 dispatched (PACKET 13) | T1 review → T2 brief | OUT_13 |
| I-003 scenario store + split-lock | SPECCED | brief | I-002 T2/T4 (fixture format) |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director creates repository hosting + CI account (open decision 1) |

## Open decisions (Director)
1. Create source hosting + CI account for I-007 (clean-checkout CI on macOS arm64 + Linux
   x86-64). Options: GitHub free tier (PM recommendation — Actions covers both platforms) /
   other host. Needed before the I-007 brief; does not block I-002…I-005.
2. P6 §4 amendment (proposed per P6 §6.3; see L-11, L-13, JRN-I001-5, JRN-I001-11). Proposed
   §4.6: "A criterion over workspace state asserts only conditions the packet's own mechanics
   guarantee, scoped to the agent-writable surface; Director-contributed state is pasted for
   the record, never asserted." Approve yes/no. When answering, also paste the AGENTS.md line
   (if any) governing whether APPLY commits inbox packet files, so AGENTS.md and P5 §2 ("the
   applied packet files" in the commit series) are aligned in the same amendment packet. Does
   not block I-002. (Note: P6 §7 required no decision — it was Director-ordered directly.)
3. GPLv3 "-only vs -or-later" for SPDX headers and the shipped LICENSE file — due at Phase-3
   packaging (JRN-I001-1). Not blocking; tracked here so it is not lost.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — deliverables (a)–(d) approved, R1–R3
ratified. Record: JRN-C000-18; artifacts digest-pinned via RV1/RV2 evidence.

## Recent review verdicts
OUT_12 (apply-only, ×2 BLOCKED): PACKET 12 VOID — never applied; PM conduct defect on
handling (JRN-I001-15); fix = P6 §7; content folded into PACKET 13.
OUT_11/I-001-T1-R2: ACCEPT (2026-07-07, recorded 2026-07-08) — all criteria COMPLIANT
(JRN-I001-14); I-001 → VERIFIED.
OUT_10/I-001-T1-R1: AMEND + RETURN — honest FAILED, no agent fault; fix = surface scoping
(A2, L-13, JRN-I001-11).
OUT_9/I-001-T1-R1: BLOCKED acknowledged — PM precondition defect (JRN-I001-7, L-12).
OUT_8/I-001-T1: AMEND + RETURN — criterion 5 defective (JRN-I001-5, L-11).

## Pointers
Repository: `main` fast-forwarded to the I-001 lineage (Director, 2026-07-08; cd8b004… →
fac6bf4…, ancestor-ok verified); task and packet branches start from main (RV2 rule restored).
Serial 12 is retired VOID — APPLIED.log runs 11 → 13 by design (JRN-I001-15). Director courier
hygiene: docs zips for the PM are made outside the working tree; /docs.zip git-ignored.
Standing OUT rules: L-10 evidence blocks; OUT header per P5 §5; BRANCH/COMMITS via
`git log --format='%H %s' main..HEAD` pasted immediately before the final OUT commit, ending
with the literal terminator line "+ final OUT commit (hash not self-listable)"; the
OUT-carrying commit is never amended — corrections land as fix-up commits on top; the Director
verifies the final hash as the branch tip at merge (L-12). Packet preconditions anchor on
ancestor commits or content checks, never on OUT-reported tip hashes (L-12).
Workspace-cleanliness criteria are scoped to the agent-writable surface (L-13). Blocked flows
escalate per P6 §7 — DIRECTOR ACTION blocks, folded packets, parallel fronts; waiting alone is
not a valid PM state. Environment of record: arm64 macOS, Apple clang 17, cmake 3.27.8,
Python 3.9.6 + venv-pinned mpmath 1.3.0 under tools/refsim (JRN-C000-5, JRN-I002-1).

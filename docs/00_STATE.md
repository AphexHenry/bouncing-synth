# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: Phase-0 gate PASSED; module v0.2; C-000 CLOSED; Phase 1 entered (PACKET 7)

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
| C-002 Curve library | IDEA | THESIS | PM authors thesis at Phase-1 entry (with C-001) |
| C-001 Exact collision engine | IDEA | THESIS | PM authors thesis at Phase-1 entry (with C-002) |

C-000 Phase-0 scoping: CLOSED (gate passed) — see register.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | SPECCED | brief + build task | PACKET 8 (imminent) |
| I-002 high-precision reference sim | SPECCED | brief | I-001 accepted (creates venv, installs pinned mpmath) |
| I-003 scenario store + split-lock | SPECCED | brief | I-002 |
| I-004 gate runner + manifests | SPECCED | brief | I-003 |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director creates repository hosting + CI account (open decision 1) |

## Open decisions (Director)
1. Create source hosting + CI account for I-007 (clean-checkout CI on macOS arm64 + Linux
   x86-64). Options: GitHub free tier (PM recommendation — Actions covers both platforms) /
   other host. Needed before the I-007 brief; does not block I-001…I-005.

## Recent gate calls
Phase-0 exit gate: PASSED (Director, 2026-07-07) — deliverables (a)–(d) approved, R1–R3
ratified. Record: JRN-C000-18; artifacts digest-pinned via RV1/RV2 evidence.

## Pointers
Repository normalized at RV2: `main` is the single line of history; task branches start from
main; Director merges after each ACCEPT. Standing OUT rules: L-10 evidence blocks;
BRANCH/COMMITS via `git log --format='%H %s'` paste (JRN-C000-17). Environment of record:
arm64 macOS, Apple clang 17, cmake 3.27.8, Python 3.9.6, mpmath absent until I-002
(JRN-C000-5).

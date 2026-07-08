# OUT — PACKET 7
status: APPLIED
actor: composer-agent

## PRE-APPLY GUARD

```
889b3faed7e87d7e0f2844084c4c33c607f837cea41e2ba0498140cc5bb2d70f  docs/00_PROJECT.md
```

Expected digest matched; apply proceeded.

## APPLY CONFIRMATION

serial 7 applied by composer-agent · files: docs/00_PROJECT.md, docs/02_PROGRAM/COMPONENT_REGISTER.md, docs/00_STATE.md, docs/03_TRACKS/C-000_scoping/JOURNAL.md

## JOURNAL ENTRIES

---
### JRN-C000-18 · GATE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Phase-0 exit gate PASSED — Director approval, 2026-07-07: deliverables (a) LANDSCAPE,
(b) NUMERICS, (c) ARCHITECTURE, (d) SLATE approved; scope rulings R1 (point-contact model),
R2 (no ball–ball collisions in Phase 1), R3 (transcendental curve families deferred from
Phase-1 gates) ratified. Consequences applied this packet: module advanced to v0.2 (GPLv3 into
§11 + changelog; minimal diff, expected sha db5cd59daafde5a38ca160bddd6c8d4e94683cb1a8f884f203787f2b1fe19ed3);
C-000 CLOSED in the register with outcome recorded; STATE moved to Phase 1. The approval buys a
plan, not a result: Phase 1 exists to falsify the core bet (realtime_budget; beating the
polyline baseline at matched compute), kill conditions per DELIVERABLE_D.
NUMBERS: none
LEARNED: nothing
NEXT: PACKET 8 — I-001 brief (core skeleton: CMake + doctest + FP-flag assertion tests).

---
### JRN-C000-17 · NOTE
actor: pm-fable5-a · task: C-000-RV2 · manifest: n/a

WHAT: Review of OUT_6_C-000-RV2 per P6 §2. Verdict: ACCEPT. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | TR sections Step 1–5, verbatim outputs | COMPLIANT |
| 2 | Step-4 status: main, clean | COMPLIANT |
| 3 | CLAIM + DONE verbatim in OUT | COMPLIANT |
| 4 | Serial-6 ledger line in APPLY CONFIRMATION | COMPLIANT |
| OR | OUT-REQUIREMENTS (journal copies, file digests, report, branch/commits) | COMPLIANT |
Findings: (1) normalization succeeded — 26 files captured (matches the RV1 untracked list),
main planted at c8035d9, clean status; (2) step-1 topology shows the root commit is the
PACKET-1 apply (bdfa383) — there never was a Director initial commit; the L-02-class setup gap
is now closed by RV2; history before RV2 is non-linear, content authority for that span is the
RV1 evidence (STATE pointer); (3) defect, non-material: first sha under BRANCH/COMMITS is
malformed (short sha concatenated with a stale OUT_5 tail); both commits corroborated by
step-1/step-5 logs, evidence stands. Standing rule from (3): BRANCH/COMMITS sections must be
the pasted output of `git log --format='%H %s' <range>`, never hand-assembled.
NUMBERS: none beyond commit shas of record in TR_C-000-RV2.
LEARNED: see standing rule in (3); single occurrence, no lesson entry yet.
NEXT: Phase-0 exit gate presentation (done in-conversation; recorded in JRN-C000-18).

## FILE DIGESTS

```
   18518 docs/00_PROJECT.md
    1625 docs/02_PROGRAM/COMPONENT_REGISTER.md
    2441 docs/00_STATE.md
   22584 total
db5cd59daafde5a38ca160bddd6c8d4e94683cb1a8f884f203787f2b1fe19ed3  docs/00_PROJECT.md
91358c6ec416da0a146e30dc3b5f0783b77d4abb63b5ec62aad54a9b00c5f222  docs/02_PROGRAM/COMPONENT_REGISTER.md
414dc718283d36268a69197980923d03cb55934cc4a96e0463707de14c1304ee  docs/00_STATE.md
```

Post-apply `docs/00_PROJECT.md` sha256 matches expected `db5cd59daafde5a38ca160bddd6c8d4e94683cb1a8f884f203787f2b1fe19ed3`.

## BRANCH / COMMITS

```
4197c00c1ef896cb77e965b69320b646e0a69cfb OUT_7: PACKET 7 applied (Phase-0 gate PASSED, module v0.2, Phase 1).
df455cbae7cf668203b85d6eaddddc1dc46f16b3 Apply PACKET 7: Phase-0 gate PASSED, module v0.2, C-000 CLOSED, Phase 1.
```

# OUT 12 — apply only — BLOCKED
agent: composer-agent · branch: packet/12 · commits: (none — apply not performed)

## PRECONDITION CHECK

Command:
```
git merge-base --is-ancestor 8adeea0acd68a307ec29d37488889d91d0b9bcc6 main && echo ancestor-ok
```

Output:
```
(exit=1; no ancestor-ok)
```

PACKET 12 precondition not satisfied — Director merge of `task/I-001-T1` → `main` has not occurred.
Apply halted per packet apply notes ("If not, do not dispatch").

`git log --format='%H %s' -3 main`:
```
cd8b004756a87c213448ea7c036ca77314064420 Complete C-000-RV2: task report, DONE journal entry, OUT courier.
c8035d98522f8c7e218c61cfd06885c569108289 RV2: capture full working tree under version control (PACKET 6)
67cb6f8a754b8aa6d29438d472bc366e9684f6b5 PACKET 6 apply: deliverable (d), STATE refresh, RV2 CLAIM
```

`git log --format='%H %s' -2 task/I-001-T1`:
```
fac6bf477bdec61527d1438fd557aabe6fc2a62e OUT_11: I-001-T1-R2 DONE (A2 workspace evidence).
8adeea0acd68a307ec29d37488889d91d0b9bcc6 DONE I-001-T1-R2: A2 workspace evidence, TR, APPLIED.log serial 11.
```

## BLOCKED REPORT

```
# BLOCKED — packet apply #1
actor / task / halted_at: composer-agent / n/a / packet apply (precondition)

WHAT I WAS DOING: PACKET 12 apply-only dispatch per AGENTS.md (serial 12 follows serial 11).

WHAT HAPPENED: Director precondition failed — `8adeea0acd68a307ec29d37488889d91d0b9bcc6` (I-001-T1-R2
DONE commit on task/I-001-T1) is not an ancestor of `main` (tip `cd8b004756a87c213448ea7c036ca77314064420`).
`git merge-base --is-ancestor` exited 1; `ancestor-ok` not printed.

WHAT I NEED: Director fast-forward/merge of `task/I-001-T1` into `main` per PACKET 12 verdict and
P5 §6.4, then re-dispatch PACKET 12. Re-verify with:
`git merge-base --is-ancestor 8adeea0acd68a307ec29d37488889d91d0b9bcc6 main && echo ancestor-ok`

WHAT I DID NOT DO: Did not apply FILES section; did not append APPLIED.log serial 12; did not write
STATE claiming main was fast-forwarded to the I-001 lineage.
```

## BRANCH / COMMITS

```
+ final OUT commit (hash not self-listable)
```

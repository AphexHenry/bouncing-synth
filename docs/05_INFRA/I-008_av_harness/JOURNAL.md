# JOURNAL — I-008 AV assessment harness (bounce-view)

---
### JRN-I008-3 · BLOCKED
actor: composer-agent · task: I-008-T1 · manifest: n/a

WHAT: bounce-view v1 implemented per BRIEF S1–S7 (SDL2 target, Law-1 guard, selftest,
interactive RUN, frames). REPAIR-A (c3-v2) satisfied from committed TR. BLOCKED: REPAIR-B —
doctest --list-test-cases emits nine per-fixture T17 names; TR expects three aggregate names
(tests/ read-only). BLOCKED: step 9 CF-E2b selftest events=26 under S5 settle/200 cap;
criterion expects events=12 (T17 paired-window count; engine gives 12 only with max-events=12).
Steps 3/7/8/10/11 evidence on file in TR.
NUMBERS: SDL2 2.32.8; ACCESS_LOG 88/88; FL-1 selftest events=34; CF-E2b events=26; frames 2.
LEARNED: TR-documented doctest names may differ from registered TEST_CASE strings; S5 settle
semantics extend beyond T17 reference windows on settling fixtures.
NEXT: PM disposition on REPAIR-B naming + step 9 event-count criterion vs S5.

---
### JRN-I008-2 · CLAIM
actor: composer-agent · task: I-008-T1 · manifest: n/a

WHAT: Claimed I-008-T1 on branch task/I-008-T1 from task/C-001-T17 tip after PACKET 55
apply; bounce-view harness per BRIEF S1–S7 plus OUT_54 repairs A (c3-v2) and B (L-15).
NUMBERS: none yet.
LEARNED: nothing
NEXT: Steps 3–14 per PACKET 55 TASK I-008-T1.

---
### JRN-I008-1 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: I-008 registered and briefed per Director direction D-4 step 2 (JRN-C001-91). Scope:
assessment instrument only — SDL2 app linked against bounce_core; display-only curve
sampling (physics untouched, S2); assessment audio mapping AV-1 (S3; C-003 inherits
nothing); Law-1 path guard built into the binary (S6); no real-time claims (S7, P1-D
pending). Not gate-bearing; no register capability beyond "Director can see and hear the
engine". T1 dispatched by PACKET 55, carrying the two OUT_54 evidentiary repairs (c3-v2,
c6/L-15) as steps 4–5.
NUMBERS: none.
LEARNED: nothing
NEXT: OUT_55 review → T17 VERIFIED on repair → D-4 step 3 (gate-resumption bundle
planning).

---

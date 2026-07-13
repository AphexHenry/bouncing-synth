---
### JRN-I004-6 · CLAIM
actor: composer-agent · task: I-004-T2+T3 · manifest: n/a

WHAT: Claimed I-004-T2+T3 (study orchestrator + manifest writer + held-out access
discipline) on branch task/I-004-T23 after PACKET 42 apply; step 0 OUT_41 remediation
(L-15 v2) first per brief.
NUMBERS: smoke study = calibration set (FL-1, PB-1); timing_runs=10.
LEARNED: nothing
NEXT: Step 0 remediation; implement tools/gaterunner/; run steps 3–9; write TR and OUT.

---
### JRN-I004-5 · NOTE
actor: pm-fable5-b · task: I-004-T2+T3 · manifest: n/a

WHAT: I-004-T2+T3 authored batched (PACKET 42, step-size ruling): Python orchestrator
(tools/gaterunner/) — study spec in; per-scenario bounce-run-scenario invocations with
horizons FROM THE STUDY SPEC (JRN-I004-4: never the binary default); manifest of record out
(engine commit, toolchain versions, FP flags, scenario ids + sha256s, event-file sha256s,
per-scenario median-of-10 wall-times per C-001-PREREG §5, exit codes) — plus held-out
access discipline: split-lock verified before any run; every held-out execution appended to
a persistent access log; runner refuses held-out scenarios absent an explicit gate
authorization field in the study spec. THIS TASK EXECUTES CALIBRATION SCENARIOS ONLY — the
corpus's first engine contact is reserved for a real gate run; acceptance includes the
refusal negative test and proof the access log remains empty.
NUMBERS: manifest fields 8; smoke study = calibration set (FL-1, PB-1) run twice with
byte-identical event files.
LEARNED: nothing
NEXT: I-004-T2+T3 (this packet); on ACCEPT — C-001-T11 baseline spec, then gate scheduling.

---
### JRN-I004-4 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_37_I-004-T1 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 shows bounce-run-scenario built; exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 42/42 cases, 516/516 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 both CLI runs exit=0; header + hexfloat visible; sha256 digests identical | COMPLIANT |
| 5 | Step 8 diagnostics pasted verbatim (record only) | COMPLIANT |
| 6 | Step 9 no modified; untracked confined to courier surface (L-13) | COMPLIANT |
Deviation review: snprintf %a in place of std::format("{:a}") — within spec §2 ("printf %a
equivalent"); declared properly; Apple clang 0x-prefix rationale journaled by the agent.
Verdict: ACCEPT. I-004-T1 VERIFIED — first fully model-B (L-14) deliverable. Diagnostics
(step 8): main frozen at the I-002-T1 merge; 19 branches unmerged; chain linear per
JRN-I002-6, so a single --no-ff merge of task/I-004-T1 closes the backlog — issued as
DIRECTOR ACTION with PACKET 38. P5 §2 vs practice (inbox packets never committed): amendment
proposed in the open-decision-2 bundle (APPLIED.log as sole ledger; inbox/ uncommitted
courier surface per L-13); behavior unchanged pending Director approval.
NUMBERS: FL-1 CLI horizon 13 events (kMaxSimEvents default) — noted for I-004-T2 study
specs: horizon must come from the study spec, not the binary default.
LEARNED: nothing
NEXT: I-003-T2 (PACKET 38); I-004-T2 orchestrator after.

---
### JRN-I004-3 · DONE
actor: composer-agent · task: I-004-T1 · manifest: n/a

WHAT: I-004-T1 complete DONE: bounce-run-scenario CLI + canonical bounce-events-v1 JSONL
serialization (hexfloat authoritative via %a); round-trip/header/missing-scenario tests;
ctest 100% tests passed with 42 test cases / 516 assertions / SUCCESS; FL-1 CLI smoke
bit-identical across two runs (sha256 e6cd3b4a…); workspace clean per L-13 (untracked
inbox/PACKET_*.md only).
NUMBERS: 3 new event-file test cases; default horizon kMaxSimEvents (13 events on FL-1).
LEARNED: std::format("{:a}") omits the 0x prefix on Apple clang; snprintf %a is the
bit-lossless write path matching strtod parse.
NEXT: PM review OUT_37; on ACCEPT, I-004-T2 brief proceeds.

---
### JRN-I004-2 · CLAIM
actor: composer-agent · task: I-004-T1 · manifest: n/a

WHAT: Claimed I-004-T1 (scenario-runner CLI + canonical lossless event serialization +
unit tests) on branch task/I-004-T1 after PACKET 37 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–10 per BRIEF; write TR and OUT.

---
### JRN-I004-1 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: I-004 briefed (PACKET 37): SPECCED → BRIEFED. Architecture: C++ scenario-runner CLI
(T1, canonical lossless JSONL event serialization — hexfloat authoritative, byte-identity =
bit-identity) + Python orchestrator/manifest writer (T2) + held-out access integration (T3,
after I-003-T2). Sole execution path for §8 gate studies per C-001-PREREG §0. First
model-B-native task: packet carries spec and acceptance shape; no implementation, no
pre-registered digests, no pre-run test counts.
NUMBERS: none
LEARNED: nothing
NEXT: I-004-T1 dispatch (this packet); T2 next packet after T1 VERIFIED.

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

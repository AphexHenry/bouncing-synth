# OUT 37 — I-004-T1 — DONE
agent: composer-agent · branch: task/I-004-T1 · commits: 0e9f755 442f483 a119148 88fc451

## APPLY CONFIRMATION

serial 37 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/05_INFRA/I-004_gaterunner/BRIEF.md, docs/05_INFRA/I-004_gaterunner/JOURNAL.md, docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md, docs/00_STATE.md

Files written:
- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md — APPEND
- docs/05_INFRA/I-004_gaterunner/BRIEF.md — OVERWRITE
- docs/05_INFRA/I-004_gaterunner/JOURNAL.md — OVERWRITE
- docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md — OVERWRITE
- docs/00_STATE.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-C001-46 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_36 (apply only) per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | APPLY CONFIRMATION with serial-36 ledger line + four-file list, PREREG flagged created | COMPLIANT |
| 2 | All applied blocks copied verbatim | COMPLIANT |
| 3 | FILE DIGESTS: byte count + sha256 for all four files | COMPLIANT |
| 4 | Step-3 git status: no modified tracked entries; untracked confined to Director courier surface (L-13) | COMPLIANT |
| 5 | BRANCH/COMMITS ends with L-12 terminator | COMPLIANT |
Verdict: ACCEPT — PACKET 36 APPLIED; C-001 PREREGISTERED (PREREGISTRATION.md v1.0 binding).
PM authoring note: the PACKET 35 DIRECTOR ACTION (merge-sizing git outputs) went unanswered
across two cycles — misrouting owned by the PM: read-only repo evidence is agent-gatherable
per P6 §7.1(b) and never belonged on the Director. Rerouted as diagnostic steps inside
PACKET 37's TASK; the merge instruction is sized from OUT_37 in PACKET 38.
NUMBERS: none
LEARNED: read-only repo evidence routes to a diagnostic packet step, never to a Director
action; Director actions are reserved for acts only the Director can perform.
NEXT: I-004-T1 (PACKET 37); merge instruction + I-003-T2 mint (PACKET 38).

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

## FILE DIGESTS

```
   31056 docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md
    6735 docs/05_INFRA/I-004_gaterunner/BRIEF.md
    1737 docs/05_INFRA/I-004_gaterunner/JOURNAL.md
    1363 docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
    2858 docs/00_STATE.md
    2087 CMakeLists.txt
    7281 src/core/bounce/io/event_file.cpp
    1108 src/core/bounce/io/event_file.hpp
    4618 src/core/bounce/io/sha256.cpp
     398 src/core/bounce/io/sha256.hpp
     143 src/tools/run_scenario/main.cpp
    1799 src/tools/run_scenario/run_scenario.cpp
     100 src/tools/run_scenario/run_scenario.hpp
    2989 tests/test_event_file.cpp
    4621 docs/05_INFRA/I-004_gaterunner/reports/TR_I-004-T1.md
   68893 total
```

```
bd0781bb4df2966fbaa78da22d2421f5e828b301842b6a1c33ef653cee0de757  docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md
361e3179d3207fee934c2806a9ebb7b8b14c3ba2dda50e0f9cd13e61e3a6d106  docs/05_INFRA/I-004_gaterunner/BRIEF.md
e44dea79bb4fae7e00c1cdb73a6998a834e2f50e3a26d6eade097cf8977d5602  docs/05_INFRA/I-004_gaterunner/JOURNAL.md
1a990fbca0798aeccdfd6067ea0b44d5f06e3bd1257051fb3b9dc4182ae552ab  docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md
02e43c886b0c70e3134b16491dfa18bef72d5000abaee64b8725214e65c7d553  docs/00_STATE.md
084c05b10157945352de6032adb4f46d71fab5965c32987282dff158285ce341  CMakeLists.txt
c39bd714bff29e9ee24bf61f8908c9e125992c82f3d40a0db68e6656f1596229  src/core/bounce/io/event_file.cpp
90d55420b78e1d5b965a2eb4f387c626b5d5acd40376b3e4336ce189153597ae  src/core/bounce/io/event_file.hpp
a86e4ab8f67048a4ff08a8412ac3326c59f859d083ca1e1c960d8ff441ab152f  src/core/bounce/io/sha256.cpp
9365dbe24755543ded7b3523c8138df214a907b274c9e98f1924b768868ee33e  src/core/bounce/io/sha256.hpp
8359a375e522f7d9b02147e4722aa8c0117f382ce815684c5c011af55d92d919  src/tools/run_scenario/main.cpp
70ab996496875e5e3c1aba495bbe1a4a78f04d4a8562594f25ef6ea0f13d1ba9  src/tools/run_scenario/run_scenario.cpp
a86cac9375a8841e56137709ba14d73b933f9fd93b451e7ffe4fc4500d11d4e1  src/tools/run_scenario/run_scenario.hpp
828ba22fa59abc92de1b05ddc1fb3e5a2b0c85591c4db801c03cc2c08f56fe72  tests/test_event_file.cpp
bb5521a401e40380867df63cdaac1bb262551df09b11f28212f232f08eae08b0  docs/05_INFRA/I-004_gaterunner/reports/TR_I-004-T1.md
```

## REPORT

# TASK REPORT — I-004-T1
actor: composer-agent / status: DONE / manifest: n/a

PER ACCEPTANCE CRITERION: 1 → Step 4 pasted below; ends exit=0.
PER ACCEPTANCE CRITERION: 2 → Step 5 pasted below; shows bounce-run-scenario built; ends exit=0.
PER ACCEPTANCE CRITERION: 3 → Step 6 pasted below; contains `100% tests passed` and doctest
`Status: SUCCESS!` from LastTest.log; ends exit=0.
PER ACCEPTANCE CRITERION: 4 → Step 7 pasted below; both CLI runs exit=0; head -3 shows schema
header and hexfloat fields; two sha256 digests identical.
PER ACCEPTANCE CRITERION: 5 → Step 8 pasted below (three commands, verbatim).
PER ACCEPTANCE CRITERION: 6 → Step 9 pasted below; no modified tracked entries; untracked limited
to inbox/PACKET_*.md (Director courier surface, L-13).
DEVIATIONS: Hexfloat write uses snprintf `%a` (printf equivalent per spec §2) rather than
`std::format("{:a}")` because Apple clang's format omits the `0x` prefix required for strtod
hex parsing.
ARTIFACTS: src/core/bounce/io/, src/tools/run_scenario/, tests/test_event_file.cpp,
build/default/bounce-run-scenario
OBSERVATIONS: none

## Step 3

```
cmake version 3.27.8

CMake suite maintained and supported by Kitware (kitware.com/cmake).
Apple clang version 17.0.0 (clang-1700.6.4.2)
Target: arm64-apple-darwin24.6.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

## Step 4

```
Preset CMake variables:

  CMAKE_BUILD_TYPE="Release"


-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
exit=0
```

## Step 5

```
[ 42%] Built target bounce-core
[ 89%] Built target bounce-tests
[100%] Built target bounce-run-scenario
exit=0
```

## Step 6

```
Test project /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
    Start 1: bounce-tests
1/1 Test #1: bounce-tests .....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
exit=0
```

LastTest.log doctest summary:

```
[doctest] test cases:  42 |  42 passed | 0 failed | 0 skipped
[doctest] assertions: 516 | 516 passed | 0 failed |
[doctest] Status: SUCCESS!
```

## Step 7

```
$ ./build/default/bounce-run-scenario --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json --out /tmp/fl1_a.jsonl
events=13
exit_a=0
$ ./build/default/bounce-run-scenario --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json --out /tmp/fl1_b.jsonl
events=13
exit_b=0
$ head -3 /tmp/fl1_a.jsonl
{"schema":"bounce-events-v1", "scenario_sha256":"f4ee64cc06da5c2f2baf3392a51c2d776af07b7378bb5c4649e4cbbb17489b01", "engine_events":13}
{"t_hex":"0x1p+0","t":1,"ball_id":0,"s_hex":"0x1p+0","s":1,"impact_speed_hex":"0x1.4p+3","impact_speed":10,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":0,"schema_version":1}
{"t_hex":"0x1p+1","t":2,"ball_id":0,"s_hex":"0x1p+1","s":2,"impact_speed_hex":"0x1.4p+2","impact_speed":5,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":1,"schema_version":1}
$ shasum -a 256 /tmp/fl1_a.jsonl /tmp/fl1_b.jsonl
e6cd3b4a0cd013aac68c5c32e39ed29bbed2a48775dd529c74a0f157ac451f71  /tmp/fl1_a.jsonl
e6cd3b4a0cd013aac68c5c32e39ed29bbed2a48775dd529c74a0f157ac451f71  /tmp/fl1_b.jsonl
```

## Step 8

```
$ git log --oneline -1 task/C-001-T10
7161539 OUT_34 C-001-T10 DONE: reference_agreement tier-1 calibration corpus.
$ git log --oneline -3 main
c760b4a Merge task/I-002-T1: I-002-T1 VERIFIED, PACKET 13 apply.
e793b8e OUT_14 I-002-T2: BLOCKED — Director merge precondition not met.
6948813 OUT_13 I-002-T1: venv + mpmath 1.3.0 smoke evidence courier.
$ git branch --no-merged main
  packet/35
  packet/36
  task/C-001-T1
  task/C-001-T10
  task/C-001-T2
  task/C-001-T3
  task/C-001-T4
  task/C-001-T5
  task/C-001-T6
  task/C-001-T7
  task/C-001-T8
  task/C-001-T9
  task/C-002-T1
  task/C-002-T2
  task/I-002-T2
  task/I-002-T3
  task/I-002-T4
  task/I-003-T1
* task/I-004-T1
```

## Step 9

```
## task/I-004-T1
?? inbox/PACKET_13.md
?? inbox/PACKET_15.md
?? inbox/PACKET_16.md
?? inbox/PACKET_17.md
?? inbox/PACKET_18.md
?? inbox/PACKET_19.md
?? inbox/PACKET_20.md
?? inbox/PACKET_21.md
?? inbox/PACKET_22.md
?? inbox/PACKET_23.md
?? inbox/PACKET_24.md
?? inbox/PACKET_25.md
?? inbox/PACKET_26.md
?? inbox/PACKET_27.md
?? inbox/PACKET_28.md
?? inbox/PACKET_29.md
?? inbox/PACKET_30.md
?? inbox/PACKET_31.md
?? inbox/PACKET_32.md
?? inbox/PACKET_33.md
?? inbox/PACKET_34.md
?? inbox/PACKET_35.md
?? inbox/PACKET_36.md
?? inbox/PACKET_37.md
```

## BRANCH/COMMITS

```
0e9f755 PACKET 37 apply: I-004 briefed, T1 dispatched, STATE/register updates.
442f483 I-004-T1 CLAIM after PACKET 37 apply.
a119148 I-004-T1: bounce-run-scenario CLI and canonical event serialization.
88fc451 I-004-T1 DONE: task report and journal entry.
+ final OUT commit (hash not self-listable)
```

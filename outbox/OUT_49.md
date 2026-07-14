# OUT 49 — C-001-T14 — DONE
agent: composer-agent · branch: task/C-001-T14 · commits: 7551af2 e82a9b2 bfd66ad 57bdd42

## APPLY CONFIRMATION

serial 49 applied by composer-agent · files:
- FILE APPEND: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md (JRN-C001-72, JRN-C001-71)
- FILE APPEND: docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md (TASK C-001-T14)
- FILE OVERWRITE: docs/00_STATE.md
- FILE APPEND: inbox/APPLIED.log (serial 49 line)

Ledger line (verbatim):

```
serial 49 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/00_STATE.md
```

## JOURNAL ENTRIES

---
### JRN-C001-74 · DONE
actor: composer-agent · task: C-001-T14 · manifest: n/a

WHAT: C-001-T14 complete DONE: zero-event event-file write fixed in `event_file.cpp`.
Root cause: `if (!out)` after `ofstream::close()` is true when zero body bytes were merged
(libstdc++/libc++ failbit on close with no body write). Fix: skip body merge when count==0;
use `flush()` + `fail()` before close. Doctest round-trip at count=0 (write + streaming);
`tests/fixtures/graze-zero-ref.json` added; CLI smoke exit=0 events=0. ctest 100% + SUCCESS!.
LAW-1: no held-out execution.
NUMBERS: engine_events=0; 54/54 doctest cases; 758 assertions.
LEARNED: never test stream health via operator bool after close.
NEXT: PACKET 50 GATE-P1-R2.

---
### JRN-C001-73 · CLAIM
actor: composer-agent · task: C-001-T14 · manifest: n/a

WHAT: Claimed C-001-T14 on branch task/C-001-T14 from task/GATE-P1-R1 tip after PACKET 49
apply; zero-event event-file write fix in shared io layer + tests/fixtures smoke.
NUMBERS: none yet.
LEARNED: nothing
NEXT: Implement spec §1–§3; build; ctest; CLI smoke; TR + OUT_49.

---
### JRN-C001-72 · NOTE
actor: pm-composer · task: C-001-T14 · manifest: n/a

WHAT: C-001-T14 authored (PACKET 49) — zero-event event-file write path. OUT_48 root cause:
`finish_event_stream` (and possibly `write_event_file`) fails when `engine_events=0`, blocking
P1-A on HO-graze-parabola-1 where empty `reference_events` requires zero emitted events
(PREREG §1). Fix in `src/core/bounce/io/event_file.cpp` (+ baseline CLI if it shares the
path). Doctest round-trip at count=0; CLI smoke on a committed non-held-out fixture (tests/
or calibration — agent may add `tests/fixtures/graze-zero-ref.json`; LAW-1: no
data/scenarios/heldout/ execution). No held-out corpus or tune changes. Acceptance: smoke
paste shows exit=0 and `events=0`. Unblocks GATE-P1-R2 (PACKET 50).
NUMBERS: 1 grazing fixture blocked; engine_events=0.
LEARNED: nothing
NEXT: C-001-T14 (this packet); on ACCEPT — PACKET 50 GATE-P1-R2.

---
### JRN-C001-71 · CORRECTION
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_48_GATE-P1-R1 per P6 §2. Criteria 1–4 COMPLIANT (toolchain, build/ctest,
D1 32/32 load survey, D3 repeat smoke). Criterion 5 COMPLIANT as BLOCKED (P1-A infrastructure
halt on zero-event write; repro paste for HO-graze-parabola-1; partial 13/32 documented).
Criteria 6–8: G1 partial 24/32 lines documented with arithmetic — COMPLIANT for BLOCKED halt.
Criterion 9 status COMPLIANT. Criterion 10 COMPLIANT (GATE_SUMMARY + TR in REPORT, digests).
Verdict: ACCEPT — halt properly executed; not a gate FAIL. PM authoring defect owned: GATE-P1-R1
pre-flight verified load only (D1) — did not require zero-event write smoke before first gate
contact; durable fix folded into T14 acceptance + PACKET 50 pre-flight. Law-1 assessment: 24
ACCESS_LOG entries are gate-authorized (I-004, gate_id=P1-A) — not poisoning; no re-mint.
NUMBERS: 13/32 partial P1-A files; halt scenario 14 = HO-graze-parabola-1.
LEARNED: gate pre-flight must cover every registered output shape (including zero-event).
NEXT: C-001-T14 (this packet).

## FILE DIGESTS

| file | bytes | sha256 |
|---|---|---|
| src/core/bounce/io/event_file.cpp | 9931 | 5e4bf1a360dcc50f3afb3da2afcbc3178560330e715dc906acf416ba46a6ce96 |
| tests/test_event_file.cpp | 4658 | 172b78f7ccf7be0c32bc98927151bb7bf99daa17d5695640e4d90f43c743282b |
| tests/fixtures/graze-zero-ref.json | 649 | cb4f66f8c79403d2ef1d6d5d225c01eae68e7991f7fbf7f7c0b1f13d7f6f9119 |
| docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md | 58645 | d13b8169fc1a2ad2458ffed5aa1ff74d0c2913495ef655e6776963c67f0aefdc |
| docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_C-001-T14.md | 2428 | 208a4124bf723b5440de88aca239df4082599dd283512750b8c31c9a180722a5 |

## REPORT

# TASK REPORT — C-001-T14

## LAW-1 affirmation

No `bounce-run-scenario` or `bounce-baseline-run` invocation with `--scenario` pointing at
any path under `data/scenarios/heldout/` in this task. CLI smoke used committed fixture
`tests/fixtures/graze-zero-ref.json` only. Unit tests use calibration FL-1 and the new test
fixture; no gate runner contact on held-out.

## Acceptance evidence

### Criterion 1 — toolchain (step 3)

```
cmake version 3.27.8

CMake suite maintained and supported by Kitware (kitware.com/cmake).
Apple clang version 17.0.0 (clang-1700.6.4.2)
Target: arm64-apple-darwin24.6.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
Python 3.9.6
```

### Criterion 2 — configure + build (step 4)

Configure tail:

```
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/baptistebohelay/Dev/research/bouncing-synth/build/default
```

Build tail:

```
[100%] Linking CXX executable bounce-survey-heldout-load
[100%] Built target bounce-survey-heldout-load
```

exit=0.

### Criterion 3 — ctest + doctest (step 5)

```
100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.20 sec
```

```
[doctest] test cases:  54 |  54 passed | 0 failed | 0 skipped
[doctest] assertions: 758 | 758 passed | 0 failed |
[doctest] Status: SUCCESS!
```

exit=0.

### Criterion 4 — zero-event CLI smoke (step 6)

Command:

```
./build/default/bounce-run-scenario --scenario tests/fixtures/graze-zero-ref.json --out <tmp> --max-events 200
```

stdout:

```
events=0
```

exit=0.

Output file first line:

```
{"schema":"bounce-events-v1", "scenario_sha256":"cb4f66f8c79403d2ef1d6d5d225c01eae68e7991f7fbf7f7c0b1f13d7f6f9119", "engine_events":0}
```

### Criterion 5 — LAW-1 (affirmed above)

Fixture under `tests/fixtures/`; no held-out path execution.

### Criterion 6 — git status (step 7)

```
## task/C-001-T14
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
?? inbox/PACKET_38.md
?? inbox/PACKET_39.md
?? inbox/PACKET_40.md
?? inbox/PACKET_41.md
?? inbox/PACKET_42.md
?? inbox/PACKET_43.md
?? inbox/PACKET_44.md
?? inbox/PACKET_45.md
?? inbox/PACKET_46.md
?? inbox/PACKET_47.md
?? inbox/PACKET_48.md
?? inbox/PACKET_49.md
?? tools/gaterunner/events/graze-clean2.jsonl.body.tmp
?? tools/gaterunner/events/graze-clean2.jsonl.tmp
?? tools/gaterunner/events/graze-test.jsonl.body.tmp
?? tools/gaterunner/events/graze-test.jsonl.tmp
?? tools/gaterunner/events/test-fl1.jsonl
?? tools/refsim/__pycache__/
?? tools/scenarios/__pycache__/
```

### Criterion 7 — implementation summary

- `finish_event_stream`: skip empty-body merge when `count==0`; replace post-`close()` `!out`
  check with `flush()` + `fail()` before close.
- `write_event_file`: same flush/fail pattern for zero-event offline path.
- `tests/fixtures/graze-zero-ref.json`: grazing-shaped parabola with empty `reference_events`.
- `test_event_file.cpp`: doctest round-trip at count=0 for write and streaming paths.

## BRANCH/COMMITS

```
bfd66ad C-001-T14: fix zero-event event-file write in shared io layer.
e82a9b2 C-001-T14 CLAIM (JRN-C001-73).
7551af2 PACKET 49 apply: C-001-T14 dispatched; OUT_48 halt accepted.
+ final OUT commit (hash not self-listable)
```

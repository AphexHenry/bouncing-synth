# OUT 50 — GATE-P1-R2 — BLOCKED
agent: composer-agent · branch: task/GATE-P1-R2 · commits: 11ada49 511fe23 3731072 0144f5e + final OUT commit (hash not self-listable)

Gate verdicts: P1-A **BLOCKED** (infrastructure — `check_p1a.py` rational fraction parse defect).
P1-B / P1-C / Law 7 not executed (halt per G2).

## APPLY CONFIRMATION

Applied files:
- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md — APPEND (JRN-C001-76, JRN-C001-75)
- docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md — APPEND (TASK GATE-P1-R2)
- docs/00_STATE.md — OVERWRITE
- inbox/APPLIED.log — APPEND

Ledger line (verbatim):
```
serial 50 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/00_STATE.md
```

## JOURNAL ENTRIES

---
### JRN-C001-78 · BLOCKED
actor: composer-agent · task: GATE-P1-R2 · manifest: P1-A.json

WHAT: GATE-P1-R2 BLOCKED at P1-A checker (infrastructure). Pre-flights green: 32/32 load_ok;
D3 repeat-identity N=3; D4 zero-event write exit=0 events=0; D5 stale events cleared (14 tracked
R1 files deleted, commit 3731072); D6 pre-run ACCESS_LOG=24. P1-A execute complete (32/32,
manifest engine_git_dirty=false). `check_p1a.py --check` crashes on rational reference field
`t='5/2'` in HO-flat-settle fixtures — hex_or_decimal lacks fraction parsing. P1-B/P1-C/Law 7
not executed. Post-run ACCESS_LOG=56 (24+32). Not a gate FAIL.
NUMBERS: 32/32 load_ok; 32 P1-A event files; ACCESS_LOG 24→56; checker exit=1 ValueError.
LEARNED: zero-event write unblock (T14) was necessary; checker reference-parser gap blocks verdict.
NEXT: PM checker fix or corpus-format ruling → GATE-P1-R3.

---
### JRN-C001-77 · CLAIM
actor: composer-agent · task: GATE-P1-R2 · manifest: n/a

WHAT: Claimed GATE-P1-R2 on branch task/GATE-P1-R2 from task/C-001-T14 tip after PACKET 50
apply; execution-only — D4 zero-event pre-flight + D5 stale-artifact hygiene before first
held-out gate run; D6 delta ACCESS_LOG reconciliation (baseline 24).
NUMBERS: none yet.
LEARNED: nothing
NEXT: Execute steps 3–15 per PREREG v1.3.

---
### JRN-C001-76 · NOTE
actor: pm-fable5-a · task: GATE-P1-R2 · manifest: n/a

WHAT: GATE-P1-R2 authored (PACKET 50) — second execution-only re-dispatch after zero-event
write unblock (C-001-T14 VERIFIED, JRN-C001-75). Registered gates, order, and halt rules
unchanged (PREREG v1.3; v1.2 B3). Deltas over GATE-P1-R1: D4 zero-event write pre-flight on
the committed tests/fixtures/graze-zero-ref.json (durable fix of JRN-C001-71 — pre-flight
now covers every registered output shape: load 32/32 + zero-event write); D5 stale-artifact
hygiene (R1's 13 partial P1-A event files + graze temp debris under tools/gaterunner/events/
cleared and evidenced before first gate run, so checkers can only read this dispatch's
outputs); D6 ACCESS_LOG reconciliation is delta-based (24 lines carried from R1's two
partial attempts, ruled gate-authorized in JRN-C001-71; expected final = 24 + this
dispatch's per-manifest held-out invocations, arithmetic stated). Branch task/GATE-P1-R2
from task/C-001-T14 tip. OUT-REQUIREMENTS extended: apply-file digests now explicit
(authoring tightening owned by PM — OUT_49 omitted STATE/BRIEF digests because the T14
criterion text did not demand them).
NUMBERS: 32 scenarios; P1-A window min(200, settle) / 12 quasi-chaotic; P1-B nuisance
100+10+2; P1-C 9 fixtures × 10^4 periods; Law 7 margin 100×, tune dt=5e-4 N=128; prior
ACCESS_LOG 24.
LEARNED: nothing
NEXT: OUT_50 review → Director Phase-1 gate call (PASS) or falsification record (FAIL).

---
### JRN-C001-75 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_49_C-001-T14 per P6 §2.

C-001-T14 criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | toolchain versions pasted | COMPLIANT |
| 2 | configure + build tails; exit=0 | COMPLIANT |
| 3 | ctest 100% + doctest SUCCESS! + exit=0 | COMPLIANT |
| 4 | zero-event CLI smoke: exit=0; events=0; header engine_events:0 | COMPLIANT |
| 5 | TR affirms LAW-1: no held-out path execution; fixture under tests/ | COMPLIANT |
| 6 | byte-verbatim git status; L-13 untracked surface | COMPLIANT |
| 7 | FILE DIGESTS full sha256s incl. TR; TR verbatim in REPORT (L-16) | COMPLIANT |

Verdict: ACCEPT — C-001-T14 VERIFIED. Root cause (failbit on ofstream close after zero body
bytes merged) evidenced; fix covers streaming, offline, and round-trip surfaces per spec §1;
regression green (54/54 cases, 758 assertions). Forward authoring tightening (PM-owned, not
an OUT defect): applied brain files (00_STATE.md, BRIEF.md) absent from FILE DIGESTS —
PACKET 50 OUT-REQUIREMENTS names apply-file digests explicitly from now on. Untracked
tools/gaterunner debris in the status paste is R1 halt residue documented in OUT_48's
artifacts list; cleared as GATE-P1-R2 step D5 rather than asserted here.
NUMBERS: 54/54 doctest cases; 758 assertions; engine_events=0 smoke.
LEARNED: nothing
NEXT: GATE-P1-R2 (this packet).

## FILE DIGESTS

| bytes | sha256 | path |
|---:|---|---|
| 62848 | d9b33607ffedec12003418e906056747e1ba00e941994c52a7a113d62324e176 | docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md |
| 43667 | 6d569c1da01c0b6616d59a1e0fa7839a253ee156ccafc99448b608124b8aaa23 | docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md |
| 2584 | 75d55bacb0270745786529c65b96164610864be1d4748d9bb50076fdcd3f661a | docs/00_STATE.md |
| 13112 | 609883b927e0975d5e57d26d3bcd0d00451bb9dc83885dbe68f17bcb77bdbaa3 | tools/gaterunner/check_p1a.py |
| 5609 | 540024aaf268f537276d81032c0ffe698fb87d27e3616b0b849143c0132d64c1 | tools/gaterunner/check_p1b.py |
| 3815 | 205f9462693279ca4595800fd4d2a5c7d07ea595eeacea730943316326c9e4d7 | tools/gaterunner/check_p1c.py |
| 7947 | 43bff14a87631b5d3d352599240eed647de07fa617c27c86c4871ccbdb1037b7 | tools/gaterunner/check_law7.py |
| 987 | 6b1e4a052f7dcd72ecbc8a9c0070ad5b2cdd8867a614903de718de18a9e8c66b | tools/gaterunner/studies/P1-A.json |
| 988 | b8ad83e9a738d673c6b22d52ede65a72bea99838c1ec5f143f966265bf9e2550 | tools/gaterunner/studies/P1-B.json |
| 721 | b966583b8e0fd5420836f2acd38961c104bc8d306f1d38e0ca3b543b4b6adf36 | tools/gaterunner/studies/P1-C.json |
| 993 | d9433643446a537cd134dc5c5de3bca18e6aa30f83fab6cbcfc0493b201f5eb9 | tools/gaterunner/studies/LAW7-EXACT.json |
| 1063 | 1ea8e11cc859953fd02d4a6047e542da4fd0ee261b77adb98cd9fdf52e8f7726 | tools/gaterunner/studies/LAW7-BASELINE.json |
| 14937 | 8748e3d14d188103c0b46de55c5a8196782ee09bc309bf0f293278b6ad0c88ca | tools/gaterunner/manifests/P1-A.json |
| 854 | cfccd9031a93199f094d406cef91dd92cd117cca88213fc9dc78b311db7465c8 | docs/03_TRACKS/C-001_exact_collision_engine/reports/GATE_SUMMARY.md |
| 5612 | 5ae167800d27aa92ebf8ddbe53ce6e207d100df7598fb2ef2ee543b7f76071db | docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_GATE-P1-R2.md |

## BRANCH/COMMITS

```
11ada49 PACKET 50 apply: GATE-P1-R2 dispatch (JRN-C001-75/76, STATE, BRIEF).
511fe23 GATE-P1-R2: CLAIM JRN-C001-77.
3731072 GATE-P1-R2 D5: remove stale P1-A halt residue from events/.
0144f5e GATE-P1-R2 BLOCKED: P1-A checker rational-parse defect (JRN-C001-78).
+ final OUT commit (hash not self-listable)
```

## BLOCKED REPORT (verbatim)

# BLOCKED — GATE-P1-R2 #1
actor: composer-agent / task: GATE-P1-R2 / halted_at: step 9 (P1-A checker `--check`)

WHAT I WAS DOING: Running `python3 tools/gaterunner/check_p1a.py --check` after successful P1-A
execute (32/32 scenarios, manifest written, `engine_git_dirty=false`).

WHAT HAPPENED: Checker crashed with `ValueError: could not convert string to float: '5/2'` in
`check_p1a.py` `hex_or_decimal()` at line 110 while parsing `reference_events[].t` from held-out
fixtures (e.g. `HO-flat-settle-1.json` carries `"t": "5/2"`). Full traceback pasted in TR step 9.
P1-A execute completed (`gate-exec-ok`, 32 event files, manifest at
`tools/gaterunner/manifests/P1-A.json`). No per-scenario verdict table produced.

WHAT I NEED: PM brief amendment or construction packet to extend `check_p1a.py` (and any sibling
checkers sharing `hex_or_decimal`) to parse rational fraction strings in reference metadata, without
violating D0 in this execution-only dispatch; or a Director ruling that rationals must not appear in
held-out reference fields the checker reads.

WHAT I DID NOT DO: Did not modify `check_p1a.py`, fixtures, engine, or tune files (D0). Did not
soften, re-run, or reinterpret. Did not execute P1-B, P1-C, or Law 7 (halt per G2 on
infrastructure BLOCKED at P1-A check).

OPTIONS (optional):
- Construction task: add rational parsing to checker `hex_or_decimal` (mirror engine `parse_rational`).
- Corpus amendment: re-emit affected reference `t`/`contact.x` as decimal/hexfloat only (I-003 scope).

## REPORT

# TR GATE-P1-R2 — Phase-1 confirmatory gate runs (second execution re-dispatch)

actor: composer-agent · branch: task/GATE-P1-R2 · status: BLOCKED at P1-A checker

## Affirmations (acceptance criterion 11)

- No modification to `src/`, fixtures, tune values, or checker/study source files (D0).
- All held-out execution via I-004 runner with `gate_id=P1-A` (32 scenarios logged).
- Halt order honored: P1-B, P1-C, Law 7 not executed after P1-A infrastructure BLOCKED.
- `ACCESS_LOG.jsonl` append-only: 24 pre-run lines preserved; 32 runner appends this dispatch.

## Step 3 — toolchain + G0 tracked-clean

```
cmake version 3.27.8
Apple clang version 17.0.0 (clang-1700.6.4.2)
Python 3.9.6
/usr/bin/python3
```

G0 (`git status --porcelain --untracked-files=no` before first gate run, after apply+CLAIM commits):

```
(empty — tracked tree clean)
```

## Step 4 — configure + build + ctest + doctest

Configure tail:
```
-- Configuring done (0.6s)
-- Generating done (0.1s)
-- Build files have been written to: .../build/default
configure exit=0
```

Build tail:
```
[100%] Built target bounce-survey-heldout-load
build exit=0
```

ctest:
```
100% tests passed, 0 tests failed out of 1
ctest exit=0
```

doctest:
```
[doctest] test cases:  54 |  54 passed | 0 failed | 0 skipped
[doctest] assertions: 758 | 758 passed | 0 failed |
[doctest] Status: SUCCESS!
```

## Step 5 — D1 pre-flight load survey

```
HO-flat-settle-1,True
...
HO-poly-double-root-1,True
load_ok 32 / 32
survey exit=0
```

## Step 6 — D3 `--repeat 3` calibration smoke

Command:
```
./build/default/bounce-run-scenario --scenario data/scenarios/calibration/FL-1-h5-g10-e1o2.json \
  --out /tmp/fl1-repeat-smoke.jsonl --max-events 200 --repeat 3
```

Output:
```
repeat-identity ok N=3
events=13
repeat exit=0
```

## Step 7 — D4 zero-event write pre-flight

Command:
```
./build/default/bounce-run-scenario --scenario tests/fixtures/graze-zero-ref.json \
  --out <tmp> --max-events 200
```

Output:
```
events=0
zero-event exit=0
{"schema":"bounce-events-v1", "scenario_sha256":"cb4f66f8c79403d2ef1d6d5d225c01eae68e7991f7fbf7f7c0b1f13d7f6f9119", "engine_events":0}
```

## Step 8 — D5 stale-artifact hygiene

```
Command: rm -rf tools/gaterunner/events/*
total 0
drwxr-xr-x@  2 ...  .
drwxr-xr-x@ 14 ...  ..
```

Note: R1 halt residue files were tracked in git (14 files under `tools/gaterunner/events/P1-A/`).
Deletions committed as `3731072` before first gate run to restore `engine_git_dirty=false`.

## Step 9 — D6 pre-run ACCESS_LOG + P1-A

Pre-run line count:
```
      24 data/scenarios/heldout/ACCESS_LOG.jsonl
```

P1-A execute:
```
gate-exec-ok study=P1-A manifest=.../tools/gaterunner/manifests/P1-A.json
p1a execute exit=0
```

Manifest: 32 scenarios, `engine_git_dirty=false`.

P1-A check (infrastructure BLOCKED):
```
Traceback (most recent call last):
  File ".../check_p1a.py", line 369, in <module>
    sys.exit(main())
  File ".../check_p1a.py", line 363, in main
    return print_report(args.manifest)
  File ".../check_p1a.py", line 292, in print_report
    row, exploratory = compare_scenario(entry["scenario_id"])
  File ".../check_p1a.py", line 146, in compare_scenario
    rt = hex_or_decimal(ref["t"])
  File ".../check_p1a.py", line 110, in hex_or_decimal
    return float(text)
ValueError: could not convert string to float: '5/2'
p1a check exit=1
```

Steps 10–12: not reached (halt per G2).

## Step 13 — D6 post-run ACCESS_LOG + GATE_SUMMARY

Post-run line count:
```
      56 data/scenarios/heldout/ACCESS_LOG.jsonl
```

Reconciliation arithmetic:
- Pre-run: 24 (R1 partial P1-A attempts, gate-authorized)
- P1-A this dispatch: +32 (one held-out invocation per scenario in manifest)
- P1-B: +0 (not executed)
- P1-C: +0 (not executed)
- Law 7: +0 (not executed)
- Expected final: 24 + 32 = 56 — **matches observed 56**

5-line excerpt (this dispatch's final entries):
```
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-quasichaotic-4", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-3", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-4", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-5", ...}
{"engine_commit": "37310721c93eaea053b2043e3d461d9ef2280298", "gate_id": "P1-A", "scenario_id": "HO-poly-settle-6", ...}
```

## GATE_SUMMARY.md (verbatim)

# GATE-P1-R2 Summary

Halt point: **P1-A (infrastructure BLOCKED at checker — not FAIL)**

## P1-A
- Status: **BLOCKED** (checker defect — rational fraction parse)
- Execute: **complete** — 32/32 scenarios via I-004 runner; manifest
  `tools/gaterunner/manifests/P1-A.json`; `engine_git_dirty=false`
- Check: **failed** — `check_p1a.py --check` raises `ValueError` on `reference_events[].t`
  value `'5/2'` (`hex_or_decimal` accepts hexfloat/decimal only)
- Worst |Δt|/|Δs|: n/a (checker did not complete)

## P1-B
- Status: **not executed** (halt per G2)

## P1-C
- Status: **not executed** (halt per G2)

## Law 7
- Status: **not executed** (halt per G2)

## Manifest sha256s
- P1-A.json: 8748e3d14d188103c0b46de55c5a8196782ee09bc309bf0f293278b6ad0c88ca
- P1-B-runA.json: n/a
- P1-C.json: n/a
- LAW7-EXACT.json: n/a
- LAW7-BASELINE.json: n/a

## Step 14 — byte-verbatim git status (pre-commit of gate artifacts)

```
## task/GATE-P1-R2
 M data/scenarios/heldout/ACCESS_LOG.jsonl
?? tools/gaterunner/events/
?? tools/gaterunner/manifests/P1-A.json
```

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

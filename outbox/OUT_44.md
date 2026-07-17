# OUT 44 — C-001-T12 — DONE
agent: composer-agent · branch: task/C-001-T12 · commits: 3ba60c5 b8bc9cd 9193c16 757c32a 901534c

## APPLY CONFIRMATION

serial 44 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md, docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/00_STATE.md

Ledger line:
```
serial 44 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md, docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md, docs/00_STATE.md
```

Files written:
- docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md — APPEND (Amendment v1.2)
- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md — APPEND (JRN-C001-50..52)
- docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md — APPEND (C-001-T12)
- docs/00_STATE.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-C001-54 · DONE
actor: composer-agent · task: C-001-T12 · manifest: n/a

WHAT: C-001-T12 complete DONE: EventEmitSink + EventStreamWriter — offline CLIs stream events
to disk via body temp file, --max-events up to 1e6; kMaxSimEvents=256 array retained for
in-process/tests. CAL-E1-FLAT-STREAM (e=1, vx=1/1e6) streaming evidence: 20000 events,
monotone seq, sha256 6c84d5df…e675b byte-identical ×2, wall ~0.12s; baseline parity
sha256 6145ff9f…e653e ×2 at same horizon (513 events, capacity-limited by baseline settle).
F3 PB-1 diagnostic (dt=1e-4, N=64): first contact t≈0.967; domain exit t≈1.059 x<0 after
backward reflection — CLASSIFICATION (a) physics (domain exit under polyline dynamics), not
harness defect. F2: tools/**/.venv/ gitignored. Law 7 tune: dt=5e-4, N=128,
mean_ratio=1.899 ∈ [1.0,2.0], FL-1 |Δt|=2.5e-4; TUNE-LAW7.json frozen at commit 901534c.
49/49 doctest SUCCESS (733 assertions); no golden expectations changed; no held-out contact.
NUMBERS: stream 20000 exact; tune ratio 1.899; chosen dt=5e-4 N=128.
LEARNED: e=1 flat streaming evidence needs near-vertical orbit (tiny vx) to reach 20k events
before fp settle; PB-1 baseline misses second exact contact via domain exit, not CLI bug.
NEXT: PACKET 45 gate runs (P1-A → P1-B → P1-C → Law 7).

---
### JRN-C001-53 · CLAIM
actor: composer-agent · task: C-001-T12 · manifest: n/a

WHAT: Claimed C-001-T12 (streaming emission + F3 diagnostic + F2 fix + Law 7
compute-match tune) on branch task/C-001-T12 after PACKET 44 apply; branched from
task/C-001-T11.
NUMBERS: streaming horizon up to 1e6; tune window [1.0×, 2.0×].
LEARNED: nothing
NEXT: Implement streaming CLIs, F3 dump, .gitignore, TUNE-LAW7.json; run steps 3–11; write TR
and OUT.

---
### JRN-C001-52 · NOTE
actor: pm-fable5-b · task: C-001-T12 · manifest: n/a

WHAT: C-001-T12 authored (PACKET 44) — final pre-gate task, four parts: (1) streaming event
emission in both offline CLIs (bounce-run-scenario, bounce-baseline-run): events written to
the output file as produced through a fixed small buffer; --max-events honored up to 10^6;
the 256-event in-memory capacity ceases to bound offline horizons; the real-time processing
path is untouched (constraint applies to the future plugin path, not offline tools);
evidence — a ~20,000-event e=1 calibration-config run, monotone seq, byte-identical across
two runs. (2) F3 diagnostic: PB-1 baseline trajectory tail dump; classify the missing
second event as physics (tunneling/missed contact/domain exit) or harness defect;
report-only unless harness defect (then fix within task, per prereg v1.2 B2). (3) F2 fix:
.gitignore for local venvs (tools/**/.venv/); status clean thereafter. (4) Compute-match
tune per v1.2 B1: (dt, N) grid on calibration via I-004 timing; frozen tune artifact
tools/gaterunner/tune/TUNE-LAW7.json with the full timing table; chosen ratio in [1.0, 2.0].
NUMBERS: streaming horizon ≤ 1e6; tune window [1.0×, 2.0×]; evidence run ~2e4 events.
LEARNED: nothing
NEXT: C-001-T12 (this packet); PACKET 45 = P1-A → P1-B → P1-C → Law 7 (v1.2 B3), first
held-out contact, gate-authorized, dirty=false.

---
### JRN-C001-51 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Director rulings 2026-07-13, registered as PREREG v1.2 (approval = PACKET 44
dispatch). D-1: no baseline settle criterion — fixed-horizon Law 7 comparison, K = min(200,
exact event count) per scenario; baseline shortfall scores against it after F3
classification (v1.2 B2). Director product statement recorded: no imposed damping — balls
keep energy intact by default (e=1); restitution stays a parameter; e<1 fixtures remain
valid engine coverage (v1.2 B4). D-2: compute window [1.0×, 2.0×], baseline equal-or-more
("dials up", v1.2 B1). D-3: gate order P1-A → P1-B → P1-C → Law 7, halt on exact-gate
failure (v1.2 B3). Ball–ball collisions: confirmed out of scope per R2 — nothing
implemented, optional future feature; multi-ball remains independent balls under TB-1.
Pre-gate blocker credited to the Director's long-horizon question: P1-C (10^4 periods,
~2–3e4 events) exceeds the 256-event buffer — the exact engine could not execute its own
registered gate; streaming emission dispatched in T12.
NUMBERS: P1-C demand ~2–3e4 events vs buffer 256.
LEARNED: registered gates must be checked for *executability* against implementation
constants at registration time, not discovered at scheduling time.
NEXT: T12, then gates (PACKET 45).

---
### JRN-C001-50 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_43 C-001-T11 per P6 §2. Criteria 0-8 all COMPLIANT: capacity 64→256
with 100-event monotone evidence; baseline byte-identical across runs, FL-1 first contact
|Δt|=5.0001e-05 ≤ 2·dt vs tier-1 t=1.0; runner engine selection with binary sha256,
cross-engine compare refusal, cross-engine summary; calibration-only, shared io untouched.
Verdict: ACCEPT — C-001-T11 VERIFIED. Forward findings: (F1) baseline does not settle —
FL-1 capacity-capped at 256 vs exact settle at 13; to_settle undefined for Euler chatter;
resolved by Director D-1 fixed-horizon rule (v1.2 B2). (F2) tools/gaterunner/.venv/
untracked inside L-13 agent surface; .gitignore fix in T12. (F3) PB-1 baseline=1 vs exact=2
events — classify missed-contact vs domain-exit before Law 7 so the baseline loses honestly
or not at all (T12 diagnostic). (F4) gate manifests require engine_git_dirty=false
(standing rule).
NUMBERS: FL-1 exact=13 baseline=256(cap); PB-1 exact=2 baseline=1; |Δt|=5.0001e-05.
LEARNED: a fixed-timestep contestant needs its own termination semantics — the exact
engine's settle concept does not transfer.
NEXT: PACKET 44 (this packet) — rulings + T12; PACKET 45 — gate runs.

## FILE DIGESTS

```
13298 b2a6f24d9d08cd3169c1ed8908568182f783a2751d7ef5c09c4d292be3d30396 docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md
38315 dba577f3f5640b2f899583110c896256b32f6eb2aa2b47ebdde59d7be7a1458b docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md
16013 613ef377f77b95bb6be58ad3c0cddc78c181a9eaad10612675e0e4f9e392d5a1 docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md
2956 0983734c360ae94db504b0dc86797177bb752665251c536bd0afd97f0c6d6ade docs/00_STATE.md
10853 480782f1540357f7b0a3e701f1d85f53bd55631e5f08f1bd020a840c6a7ac3f6 inbox/APPLIED.log
276 95d2eb7f315997e0b1e68d7c6abd5cb17911b45aa60fcfe03b23b5061fd969da .gitignore
940 41537420883ee68382809075b952cded97085a53258f1a20d563862bd36c2128 data/scenarios/calibration/CAL-E1-FLAT-STREAM.json
348 b7aa88082a70e5de543a831c5138c3bee76b61e2d60ee53bbe30fca1ecad4560 data/scenarios/split-lock.json
1938 06b3698fe8ba7a359e34b00d1c180f05af7b20ee3734f0e0e9df3dc4a2677f6c src/core/bounce/engine/collision_sim.hpp
6093 d667f285c337b0129599a3d11a1a38c79975571cac5f912ea869546038a5e157 src/core/bounce/engine/collision_sim.cpp
1660 eb8a14d21d79f5991f0cc65e989c3a93d0fbb20a120eef847daf7af937c2d63a src/core/bounce/io/event_file.hpp
9628 dc05a4f19232f43a1279fded9d717dc47be68dacf43e54c9b06776f2e6136142 src/core/bounce/io/event_file.cpp
1806 848e8be557912a98ff2f1c6e1674e0e5a15c2de4b41011e797744f5d0ad6774a src/core/bounce/scenario/calibration_loader.hpp
12773 2b7c82b120f2affb790898c2294994cfe237923193c3ed41edcc5ade5838440e src/core/bounce/scenario/calibration_loader.cpp
1015 890af1c643a1d97cabbfe8d45a5084adbc23b521f6e4b03d402cffe22a19705e src/baseline/baseline_sim.hpp
12057 b0bd301cacef09aa13928e636d6fd832a672b8abd80f685f47835fc54e2baf78 src/baseline/baseline_sim.cpp
2542 dd848fbbb4a538a296d7e980570af95c9e26c89209d75362205455ccfc4c11e5 src/tools/run_scenario/run_scenario.cpp
3546 565d895ce622ed84ada521be337c4bcb7be0c6458f6edb2a932b703fbd952c22 src/tools/run_baseline/run_baseline.cpp
8616 9242093f6a43d7a8fa22a468a6e976736c748396c5bbbbcbaccd90bb888fb3e9 tools/gaterunner/tune_law7.py
36203 d5b3ab74429dad9e390cc412f8b66dd55600045e8bf4baa352576f6af72ed457 tools/gaterunner/tune/TUNE-LAW7.json
```

## TASK REPORT

See `docs/03_TRACKS/C-001_exact_collision_engine/reports/TR_C-001-T12.md` (verbatim evidence
for steps 3–10).

## APPLIED-FILES DIRECTIONS

PACKET 44 appended PREREG v1.2 (B1–B4), JRN-C001-50..52, C-001-T12 brief, and overwrote
STATE. Task implementation added streaming emission, F3 diagnostic CLI, venv gitignore,
CAL-E1-FLAT-STREAM calibration scenario, split-lock calibration_count=3, and
TUNE-LAW7.json (dt=5e-4, N=128, mean_ratio≈1.899).

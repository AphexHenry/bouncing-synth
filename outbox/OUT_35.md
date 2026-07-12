# OUT 35 — apply only — APPLIED
agent: composer-agent · branch: packet/35 · commits: 6ea545c

## APPLY CONFIRMATION

serial 35 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/02_PROGRAM/LESSONS.md, docs/00_STATE.md, docs/02_PROGRAM/COMPONENT_REGISTER.md, docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md

Files written:
- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md — APPEND
- docs/02_PROGRAM/LESSONS.md — APPEND
- docs/00_STATE.md — OVERWRITE
- docs/02_PROGRAM/COMPONENT_REGISTER.md — OVERWRITE
- docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-C001-43 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Gate-language scoping. The T8/T9/T10 doctests exercise the *shapes* of the §8
determinism_repro, loop_stability, and reference_agreement gates on the calibration set; they
are not gate executions. A §8 gate claim requires: C-001 PREREGISTRATION.md (design A/B/C,
coverage table, tolerances), the I-003 held-out corpus locked and populated, execution via the
I-004 gate runner, and grazing cases per PROJECT §9. Known power limits recorded for the
precursors: T8 repeats runs in-process only (no block-size, process, or platform variance —
Design B nuisance conditions untouched); T9's fixture FL-1 has exactly dyadic bounce times, so
zero drift is guaranteed by construction and the test has near-zero power against non-dyadic
periodic orbits; T10's corpus is two easiest-cell fixtures with no Tier-2 members, and its
per-scenario comparisons aggregate into boolean assertions (4 assertions total), hiding which
event/field diverged on failure. No VERIFIED status is suspended — the tests are sound as
calibration coverage — but no journal or register entry may cite them as gates passed.
NUMBERS: precursor power limits — T8: 1 process, 1 machine; T9: 1 dyadic orbit; T10: 2
fixtures, 0 Tier-2, 4 assertions.
LEARNED: naming a development test after a gate invites the record to claim the gate later;
scope the name at authoring time.
NEXT: C-001 PREREGISTRATION.md (PACKET 36); I-004 brief (PACKET 37); Tier-2 fixture mint
targeting grazing / near-double roots / non-dyadic orbit / Bézier segments (PACKET 38).

---
### JRN-C001-42 · CORRECTION
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: PM deviation owned per P6 §6.1. Deviation: C-001-T1 through T10 implementation and test
translation units were PM-authored and carried in packet FILES sections (digests pre-registered,
outputs pre-built), with agents reduced to transcription plus build/test on the environment of
record. This contradicts the standing role boundary (Director correction at I-002: agents write
all product code from C-001 onward) and voids the premise of P6 §2.2 / L-10 that the PM has no
repo access — review became the PM checking its own pre-verified output. Root cause: P6 §7.4
"pre-verifying acceptance outputs" read expansively as license to compose and execute the
codebase. Durable fix: Director ruling 2026-07-12, Option B — packets carry specs, interface
declarations, fixtures, oracle values, and acceptance-test files only; implementation under
src/ is agent-authored; the PM does not build or execute the repository, and §7.4
pre-verification means derivation of expected oracle values from specifications. Codified as
L-14; second occurrence of the PM-authoring class after I-002, so a P6 §4.6 amendment is
proposed to the Director per P6 §6.3 (folded into STATE open decision 2). Status of T1–T10:
VERIFIED statuses stand — their acceptance evidence is agreement with Tier-1 closed-form and
Tier-2 mpmath oracle values, which are independent of implementation authorship — but no §8
gate claim attaches to them (JRN-C001-43), and C-001-T11 (Law 7 baseline) is mandatorily
agent-authored: the PM authoring both the exact engine and its named baseline would control
both sides of the falsifiable bet.
NUMBERS: scope of deviation — 10 tasks (T1–T10), packets 25–34.
LEARNED: L-14 (docs/02_PROGRAM/LESSONS.md).
NEXT: L-14 in force from PACKET 35; P6 §4.6 amendment awaits Director approval (open decision 2).

---
### JRN-C001-41 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_34_C-001-T10 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 4 ends exit=0 | COMPLIANT |
| 2 | Step 5 ends exit=0 | COMPLIANT |
| 3 | Step 6 100% passed; doctest 39/39 cases, 503/503 assertions, SUCCESS!, exit=0 | COMPLIANT |
| 4 | Step 7 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 5 | CLAIM + DONE verbatim; serial-34 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-C001-37/-38/-39/-40 verbatim; FILE DIGESTS; TR steps 3–7 + LastTest.log; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. C-001-T10 VERIFIED. No further C-001 task dispatches until C-001
PREREGISTRATION.md lands (PACKET 36) — T11 is agent-authored per L-14 and gated on the prereg's
matched-compute definition.
NUMBERS: 1 reference_agreement corpus test case (T10).
LEARNED: nothing
NEXT: PACKET 36 (prereg + merge housekeeping).

## LESSONS APPEND (L-14)

L-14: The PM authors judges, never contestants. Specs, interface declarations, fixtures, oracle
values, pre-registered gate thresholds, and acceptance-test files may be PM-authored;
implementation code under test — and above all any Law 7 named baseline — is agent-authored
from the spec. A packet whose FILES section carries implementation translation units converts
review into the PM checking its own output and voids the P6 §2.2 / L-10 premise that the PM has
no repo access; pre-registered digests of agent deliverables are the tell. Corollary: the PM
does not build or execute the repository — P6 §7.4 "pre-verifying acceptance outputs" means
deriving expected oracle values from specifications, never running the codebase. Enforcement:
any packet carrying src/ implementation content, and any journal entry showing PM-executed
build/test output, is a P6 incident. Origin: C-001-T1–T10 (packets 25–34), where .cpp/.hpp
implementation rode packet FILES sections with digests pre-registered and test counts pre-built;
surfaced at Director review of OUT_34; second occurrence of the PM-authoring class after the
I-002 fixture-generator correction → P6 §4.6 amendment proposed per P6 §6.3 (JRN-C001-42).

## docs/00_STATE.md

# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_34 ACCEPT — C-001-T10 VERIFIED (JRN-C001-41); authorship model B ruling (JRN-C001-42, L-14); PACKET 35

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001-T1…T10 VERIFIED. Authorship model B in force (Director ruling
2026-07-12; JRN-C001-42, L-14): implementation is agent-authored from PM specs; the PM does not
build or execute the repo. T8–T10 scoped as calibration-mode gate precursors, not §8 gate runs
(JRN-C001-43). Packet delivery rule in force (Director-ordered, 2026-07-12): every packet is
emitted to the Director as a standalone PACKET_<serial>.md file, never as inline chat text.
C-002-T1/T2 VERIFIED. I-003-T1 VERIFIED. Next: C-001 preregistration (PACKET 36), I-004 brief
(PACKET 37), Tier-2 hard-cell fixture mint (PACKET 38), then C-001-T11 (agent-authored
baseline).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | BRIEFED | PREREGISTRATION.md | PACKET 36 |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1 VERIFIED, JRN-I003-5) | T2 brief — held-out corpus mint | C-001 prereg coverage table |
| I-004 gate runner + manifests | SPECCED | brief | PACKET 37 (critical path) |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004 |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED: Design-B determinism evidence beyond a single
   machine (cross-process, cross-platform, block-size variance) is blocked on it; requested
   this phase.
2. P6 amendment bundle: §4.6 covering L-11, L-13, L-14; §7.4 clarification (pre-verification =
   oracle derivation from specs, never running the codebase); §7.5 packet-as-file delivery
   rule (every packet a standalone PACKET_<serial>.md file, ratifying the 2026-07-12
   Director order) — non-blocking; approval requested.
3. GPLv3 -only vs -or-later — Phase 3.

## Recent review verdicts
OUT_34/C-001-T10: ACCEPT — C-001-T10 VERIFIED (JRN-C001-41).
OUT_33/C-001-T9: ACCEPT — C-001-T9 VERIFIED (JRN-C001-37).
OUT_32/C-001-T8: ACCEPT — C-001-T8 VERIFIED (JRN-C001-33).
OUT_31/C-001-T7: ACCEPT — C-001-T7 VERIFIED (JRN-C001-29).

## Pointers
Branch rule: packet/35 branches from task/C-001-T10; successors extend packet/35. Housekeeping
merge of the stacked chains requested (DIRECTOR ACTION with PACKET 35); merge instruction lands
in PACKET 36 sized to the pasted evidence.

## docs/02_PROGRAM/COMPONENT_REGISTER.md

# COMPONENT_REGISTER — Bounce

```
doc_id:   COMPONENT_REGISTER
layer:    program
audience: PM (write), Director (read)
status:   ACTIVE
parent:   PROJECT §2
```

| C-id | name | one-line claim | layer | state | named baseline | outcome + report link |
|---|---|---|---|---|---|---|
| C-001 | Exact collision engine | Closed-form ballistic flight + analytic collision-time root-solve on the true curve yields bit-deterministic, drift-free event sequences in real time | engine | BRIEFED | naive fixed-timestep + polyline engine (PROJECT §5 Law 7) | T1 VERIFIED (JRN-C001-5); T2 VERIFIED (JRN-C001-9); T3 VERIFIED (JRN-C001-13); T4 VERIFIED (JRN-C001-17); T5 VERIFIED (JRN-C001-21); T6 VERIFIED (JRN-C001-25); T7 VERIFIED (JRN-C001-29); T8 VERIFIED (JRN-C001-33); T9 VERIFIED (JRN-C001-37); T10 VERIFIED (JRN-C001-41) — T8–T10 are calibration-mode precursors, not §8 gate runs (JRN-C001-43) — docs/03_TRACKS/C-001_exact_collision_engine/reports/ |
| C-002 | Curve library | A family of exactly-defined user-shapeable curves (with derivatives/normals) the engine solves against | curve | BRIEFED | direct per-query eval without compilation at matched compile+query cost (DELIVERABLE_D) | T1 VERIFIED (JRN-C002-5); T2 VERIFIED (JRN-C002-9) — docs/03_TRACKS/C-002_curve_library/reports/ |
| C-003 | Event→MIDI mapping engine | User-configurable collision→(pitch, velocity, channel) mapping emitted sample-accurately | mapping | IDEA | tbd at THESIS | — |
| C-004 | Plugin shell & visuals | JUCE VST3 shell with real-time visualization and host parameter/automation plumbing | ui | IDEA | tbd at THESIS | — |
| C-005 | Preset & state system | Full serialization of curve+balls+physics+mapping with replay-identity guarantee | io | IDEA | tbd at THESIS | — |
| C-000 | Phase-0 scoping | Phase 0 delivers a Director-approvable plan: prior-art landscape, numerics decision memo, architecture plan, prioritized component slate (PROJECT §3 a–d) | infra-facing | CLOSED | n/a — scoping gate is Director approval, not numeric (P2 §8) | Phase-0 gate PASSED (Director, 2026-07-07); deliverables (a)–(d) + rulings R1–R3 approved — 03_TRACKS/C-000_scoping/reports/, JRN-C000-18 |

## docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md

# BRIEF — C-001 Exact collision engine

```
doc_id:   C-001-BRIEF
layer:    track
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   C-001-THESIS
```

## Context for agents
Phase-1 physics core for bounce-core (DELIVERABLE_C §1). The engine owns ballistic propagation,
polynomial collision-time root-solving against C-002 curves, TB-1 event ordering, and G-1/S-1
rules. No JUCE, no heap on the processing path, no libm in the collision core (DELIVERABLE_B
§3–§4). C-002 leads by one packet — engine tasks dispatch only after the curve layer has the
slice the task needs. Failures are reported verbatim (FAILED/BLOCKED), never patched mid-task.
Authorship (L-14): packets supply specs, interface declarations, oracle values, and acceptance
tests; all implementation under src/ is agent-authored. If a spec is ambiguous, BLOCK — do not
infer.

## Files you may read
- `AGENTS.md` · assigned `inbox/PACKET_<n>.md` · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- `docs/00_PROJECT.md` §6–§8 · `docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_B_NUMERICS.md` §1–§5
- `docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md` §1
- This brief · track `JOURNAL.md` · `src/core/bounce/curve/` (C-002)
- `config/fp-determinism.cmake` · `data/scenarios/calibration/` (read-only)

## Files you will write
- Under `src/core/bounce/` (engine, numerics, events) and `tests/` per task
- `docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md` (append)
- `docs/03_TRACKS/C-001_exact_collision_engine/reports/` task reports
- `outbox/OUT_<serial>_C-001-T<n>.md`

## TASK C-001-T1: Double-double arithmetic + ballistic parabola P(x) + unit tests
depends_on: C-002-T2 VERIFIED (JRN-C002-9); I-001 (VERIFIED)
objective: DD add/mul/div without FMA; compile ballistic flight path y=P(x) from BallisticInit
           using DD coefficient arithmetic; doctest on FL-1 ground hit and vx=0 rejection.
VERIFIED (JRN-C001-5; OUT_25; TR_C-001-T1.md).

## TASK C-001-T2: VCA root isolation on explicit-polynomial curve + unit tests
depends_on: C-001-T1 VERIFIED (JRN-C001-5)
objective: Build f(x)−P(x) collision polynomial and isolate the smallest root bracket on
           [x_min, x_max] via VCA bracket scan (DELIVERABLE_B §3 isolation step).
VERIFIED (JRN-C001-9; OUT_26; TR_C-001-T2.md).

## TASK C-001-T3: Fixed refinement + admissibility filter + single-ball event step + unit tests
depends_on: C-001-T2 VERIFIED (JRN-C001-9)
objective: Refine isolated root (bisection 2⁻⁴⁰ + 3 DD Newton), apply G-1 admissibility
           (|normal impact speed| ≥ v_graze), expose step_ball_next_collision for one collision
           query on explicit-polynomial curves; doctest on FL-1 ground hit.
VERIFIED (JRN-C001-13; OUT_27; TR_C-001-T3.md).

## TASK C-001-T4: Elastic reflection + graze continuation + multi-event FL-1 sequence + unit tests
depends_on: C-001-T3 VERIFIED (JRN-C001-13)
objective: reflect_velocity about curve normal with restitution; simulate_ball_collisions loop
           with G-1 graze continuation and S-1 settle; doctest on FL-1 eight tier-1 event times.
VERIFIED (JRN-C001-17; OUT_28; TR_C-001-T4.md).

## TASK C-001-T5: CollisionEvent schema + PB-1 first-contact agreement + unit tests
depends_on: C-001-T4 VERIFIED (JRN-C001-17)
objective: Introduce PROJECT §6 CollisionEvent struct; simulator emits full schema events;
           doctest on PB-1 tier-1 first contact (t=1, s=1 on y=x²).
VERIFIED (JRN-C001-21; OUT_29; TR_C-001-T5.md).

## TASK C-001-T6: TB-1 multi-ball global event queue + unit tests
depends_on: C-001-T5 VERIFIED (JRN-C001-21)
objective: simulate_multi_ball_collisions with TB-1 ordering (min t, then ball_id); doctests
           on simultaneous tie-break, earliest-time selection, monotone seq.
VERIFIED (JRN-C001-25; OUT_30; TR_C-001-T6.md).

## TASK C-001-T7: Calibration scenario JSON runner (FL-1/PB-1 end-to-end) + unit tests
depends_on: C-001-T6 VERIFIED (JRN-C001-25)
objective: load_calibration_scenario + run_calibration_scenario for schema-v1 calibration
           JSON; doctest FL-1 eight tier-1 reference events and PB-1 first contact.
VERIFIED (JRN-C001-29; OUT_31; TR_C-001-T7.md).

## TASK C-001-T8: determinism_repro-precursor repeated-run identity on FL-1 + unit tests
depends_on: C-001-T7 VERIFIED (JRN-C001-29)
objective: events_equal helper (exact == on all CollisionEvent fields) + doctest FL-1
           repeated-run identity — 100 repeated run_calibration_scenario calls, each
           bit-identical to baseline. Calibration-mode precursor to the §8 determinism_repro
           gate (JRN-C001-43); not a gate run.
VERIFIED (JRN-C001-33; OUT_32; TR_C-001-T8.md).

## TASK C-001-T9: loop_stability-precursor zero interval-sequence drift on FL-1 + unit tests
depends_on: C-001-T8 VERIFIED (JRN-C001-33)
objective: extract_collision_intervals + intervals_equal helpers; doctest FL-1 — 11
           dyadic-halving intervals bit-exact, 100 repeated full-horizon runs with zero
           interval-sequence drift through settle. Calibration-mode precursor to the §8
           loop_stability gate (JRN-C001-43; dyadic fixture — zero drift by construction).
VERIFIED (JRN-C001-37; OUT_33; TR_C-001-T9.md).

## TASK C-001-T10: reference_agreement-precursor tier-1 calibration corpus + unit tests
depends_on: C-001-T9 VERIFIED (JRN-C001-37)
objective: agrees_with_tier1_reference helper (ε=1e-12 on t/s, exact ball_id/seq) + doctest
           tier-1 calibration corpus FL-1 + PB-1. Calibration-mode precursor to the §8
           reference_agreement gate (JRN-C001-43).
VERIFIED (JRN-C001-41; OUT_34; TR_C-001-T10.md).

## TASK C-001-T11 (sketch): naive polyline baseline engine (Law 7)
Agent-authored per L-14 — the PM supplies the spec, the matched-compute definition, and the
acceptance tests only. Dispatches only after C-001 PREREGISTRATION.md is on disk (PACKET 36):
the compute-matching methodology and the drift/accuracy margin are pre-registered before either
engine is benchmarked.

## FILE DIGESTS

- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md: 26653 bytes · sha256 0ba3016b00d24062d1c530817c5bdad09cc3b6b62fa79934c9dece0c6b7e5e64
- docs/02_PROGRAM/LESSONS.md: 5425 bytes · sha256 c2f97e462bdd83d1ffde463d3f9111005e5bbd5eb257b4ff66340af1d1aa1354
- docs/00_STATE.md: 3031 bytes · sha256 dc4d812d02e83747df42c4ab75847b3d0b1aef73098a0f906e0f01122ae856f0
- docs/02_PROGRAM/COMPONENT_REGISTER.md: 2199 bytes · sha256 9b4fc5601ff13fed8c2729f13d8ed40e3bdf178eb9b0c69e6a0db824594c9a88
- docs/03_TRACKS/C-001_exact_collision_engine/BRIEF.md: 5996 bytes · sha256 c281c4e108aefc635084a8509da5088ac6c4e3a8e6c533a35c70d951a7a5f320

## GIT STATUS (step 3)

```
## packet/35
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
```

## BRANCH/COMMITS

```
6ea545c Apply PACKET 35: OUT_34 ACCEPT, authorship model B (L-14), gate scoping.
+ final OUT commit (hash not self-listable)
```

**Status: APPLIED**

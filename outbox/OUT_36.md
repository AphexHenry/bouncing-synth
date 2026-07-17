# OUT 36 — apply only — APPLIED
agent: composer-agent · branch: packet/36 · commits: ac7e7a8

## APPLY CONFIRMATION

serial 36 applied by composer-agent · files: docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md, docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md, docs/00_STATE.md, docs/02_PROGRAM/COMPONENT_REGISTER.md

Files written:
- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md — APPEND
- docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md — OVERWRITE (created)
- docs/00_STATE.md — OVERWRITE
- docs/02_PROGRAM/COMPONENT_REGISTER.md — OVERWRITE

## JOURNAL ENTRIES

---
### JRN-C001-45 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: C-001 PREREGISTRATION.md authored (PACKET 36); C-001 BRIEFED → PREREGISTERED.
Registered: P1-A (Design A) primary — max per-event |Δt| ≤ 1e-9 s and |Δs| ≤ 1e-9 over the
full held-out corpus, exact ball_id/seq, worst-case + distributions reported (L-05 analog);
P1-B (Design B) primary — bit-identical CollisionEvent sequences across 100 in-process runs,
10 fresh-process runs, 2 clean-checkout rebuilds, scoped to the environment of record until
I-007 (PROJECT §9 safeguard b); P1-C (Design C) primary — bit-exact interval-sequence
repetition over 10^4 periods on held-out periodic fixtures including non-dyadic orbits;
P1-D (Design D) DEFERRED — budget registration requires a measured basis via I-004/I-005
profiling; no realtime claim before its addendum. Law 7: compute matched by wall-time per
simulated scenario-second (±10%) on the environment of record via I-004; margin — exact
engine worst-case held-out event-time error ≤ baseline/100 at matched-or-lower compute, and
zero drift on periodic fixtures where the baseline drifts; baseline agent-authored (L-14).
Coverage table fixed over {flat line, explicit polynomial deg 2–6, piecewise Bézier C1} ×
{settle, periodic, quasi-chaotic} × {1, 2–4 balls}; declared empty: transcendental families
(R3), ball–ball (R2), Bézier×quasi-chaotic (Phase-1 reference-horizon cost), 8–16 balls
(P1-D scope); grazing mandatory — ≥3 near-tangency scenarios at |v_n| ∈ {0.5, 1.0, 2.0} ×
v_graze plus one near-double-root geometry. Held-out: ~40%, stratified by family × regime,
minted by I-003-T2 from Tier-1 CAS + Tier-2 refsim, locked before any engine run, access via
I-004 only (Law 1).
NUMBERS: tolerances 1e-9/1e-9; nuisance set 100+10+2; horizon 10^4 periods; margin 100×;
compute match ±10%; held-out ~40%; grazing ≥3+1.
LEARNED: nothing
NEXT: I-004 gate-runner brief + merge instruction (PACKET 37); Tier-2 hard-cell fixture mint
(PACKET 38); C-001-T11 spec (agent-authored baseline) after I-004 is briefed.

---
### JRN-C001-44 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_35 (apply only) per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | APPLY CONFIRMATION with serial-35 ledger line + five-file list with directions | COMPLIANT |
| 2 | All applied blocks copied verbatim | COMPLIANT |
| 3 | FILE DIGESTS: byte count + sha256 for all five files | COMPLIANT |
| 4 | Step-3 git status: no modified tracked entries; untracked confined to Director courier surface (L-13) | COMPLIANT |
| 5 | BRANCH/COMMITS ends with L-12 terminator | COMPLIANT |
Verdict: ACCEPT — PACKET 35 APPLIED. Model B (L-14), gate scoping (JRN-C001-43), and the
packet-as-file delivery rule are on the record. PACKET 35 DIRECTOR ACTION outputs (tip of
task/C-001-T10; branches unmerged to main) still outstanding — non-blocking; merge
instruction deferred to PACKET 37 and sized to that evidence when pasted.
NUMBERS: none
LEARNED: nothing
NEXT: PACKET 36 (this packet — prereg).

## docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md

# PREREGISTRATION — C-001 Exact collision engine (Phase-1 gate studies)

```
doc_id:   C-001-PREREG
layer:    track
audience: PM, Director, agents (gate context), I-003/I-004 (input contract)
status:   ACTIVE v1.0 — registered 2026-07-12 (PACKET 36); amendments only by new packet with
          CORRECTION entry, never by edit
parent:   C-001-THESIS / PROJECT §3 Phase 1, §4, §5, §8, §9 / P2
```

## 0. Scope and standing

This document pre-registers the confirmatory studies whose passage constitutes the C-001 side
of the Phase-1 gate (PROJECT §3). Registered values in this file are fixed: changing any
tolerance, horizon, nuisance set, margin, or coverage-cell assignment after a held-out run has
occurred requires a Director-approved CORRECTION packet and voids affected results. The
T1–T10 calibration precursors (JRN-C001-43) are development evidence only and carry no weight
here. All studies execute exclusively through the I-004 gate runner against the I-003 locked
held-out corpus; any held-out scenario executed outside I-004 is a Law 1 violation and
poisons that scenario (retired from the corpus, replacement minted).

Environment of record: the Director's machine as pinned by I-001 (`config/fp-determinism.cmake`
flags; toolchain versions recorded per manifest at each gate run). Cross-platform claims are
out of scope for v1.0 (§9 safeguard b: claims scoped to one platform explicitly) and enter
only via a registered addendum once I-007 exists.

## 1. Study P1-A — reference_agreement (Design A)

- Unit of analysis: one held-out scenario (curve + initial state + params) run to horizon
  H = min(200 events, settle per S-1).
- References: Tier-1 (CAS-verified closed form) where available; Tier-2 (mpmath refsim,
  `reference_converged` passed per Law 5) otherwise. Tier fixed at fixture creation.
- PRIMARY CRITERION (the only confirmatory claim of this study): over every event of every
  held-out scenario, max |t_engine − t_ref| ≤ 1e-9 s AND max |s_engine − s_ref| ≤ 1e-9
  (curve-parameter units), with ball_id and seq exactly equal per event. One scenario over
  tolerance fails the study. Threshold basis: fixed refinement (bisection to 2⁻⁴⁰ + 3 DD
  Newton, DELIVERABLE_B §3) bounds per-root error near double-precision scale; 1e-9 grants
  ×1000 headroom for state propagation over ≤200 events while remaining ≥4 orders below any
  fixed-timestep competitor.
- Reporting (L-05 analog): worst case per scenario and per corpus, full error distributions,
  per-family and per-regime breakdown; per-event error-growth curves are exploratory.
- Quasi-chaotic cells: reference agreement evaluated over the first 25 events only (Tier-2
  convergence horizon cap for exponentially diverging orbits); declared in the coverage table.

## 2. Study P1-B — determinism_repro (Design B)

- Unit of analysis: one held-out scenario replayed under a nuisance condition.
- Registered nuisance set (v1.0, environment of record): (i) 100 in-process repetitions;
  (ii) 10 fresh-process invocations; (iii) 2 clean-checkout rebuilds (delete build tree,
  reconfigure, rebuild, rerun). Block-size variance enters when block-based emission exists
  (C-003); platform variance enters with I-007 — both by registered addendum only.
- PRIMARY CRITERION: bit-identical CollisionEvent sequence (0 diff on every field of every
  event) across all runs of the full nuisance set, for every held-out scenario. Exact gate,
  no tolerance (PROJECT §8).
- Scope statement (binding on all downstream claims): v1.0 determinism is claimed for the
  environment of record only. No marketing, docs, or register text may state cross-platform
  determinism before the addendum passes.

## 3. Study P1-C — loop_stability (Design C)

- Unit of analysis: one periodic orbit run for 10^4 periods.
- Held-out orbit families must include at least: one non-dyadic flat-line orbit (bounce
  period not exactly representable in binary), one parabola-bowl orbit, one piecewise-Bézier
  orbit. The dyadic FL-1 family is calibration-only and confirmatory-inadmissible here
  (JRN-C001-43: zero drift by construction).
- PRIMARY CRITERION: the collision-interval sequence of every period is bit-identical to the
  first period's, over 10^4 periods, for every held-out periodic fixture — drift exactly 0
  (PROJECT §4 Design C target). If a family is proven analytically incapable of bit-exact
  period repetition, that proof is itself the deliverable and the family's criterion is
  re-registered by CORRECTION packet before any run counts.
- Reporting: per-period first-divergence index (should be none), interval-sequence hashes.

## 4. Study P1-D — realtime_budget (Design D): DEFERRED

No compute budget is registered in v1.0. A budget with no measured basis is not a threshold,
it is a guess, and both failure modes (sandbagged-easy and theatrically-tight) corrupt the
gate. P1-D is deferred to a registered addendum that requires: I-004 operational, an I-005
profiling harness run on the calibration set producing measured per-event and per-query
costs on the environment of record, and Director approval of the derived budget. Until that
addendum passes, no "real time" claim attaches to C-001 in any register, journal, or
Director-facing summary; the THESIS claim's "in real time" clause is pending, not evidenced.

## 5. Law 7 baseline study — matched-compute comparison

- Contestants: C-001 exact engine vs the named baseline (PROJECT §5 Law 7) — fixed-timestep
  semi-implicit (symplectic) Euler integrator over a polyline-sampled curve, with impulse
  reflection at segment crossings. The baseline is agent-authored from a PM spec (L-14);
  the spec must be good-faith competitive (registered here): polyline vertex count and dt are
  chosen by the compute-matching rule below, not fixed a priori, and the integrator uses the
  same restitution and settle rules.
- Compute matching (registered methodology): budget = exact engine's wall-time per simulated
  scenario-second, measured per scenario by I-004 on the environment of record (median of 10
  timed runs). The baseline's dt (and polyline density, coupled dt↔N by equal per-step cost)
  is tuned — on calibration scenarios only — to the largest accuracy configuration whose
  wall-time per simulated scenario-second is within +10% of the budget (equal-or-more compute
  allowed to the baseline; never less).
- PRIMARY CRITERION: on the held-out corpus, worst-case per-event |Δt| vs reference of the
  exact engine ≤ (baseline's worst-case per-event |Δt|) / 100 at matched-or-lower compute;
  AND on held-out periodic fixtures, exact-engine drift = 0 where the baseline's measured
  drift > 0. Failing either arm kills the analytic-collision bet (THESIS §6).
- Reporting: full accuracy-vs-compute curves for both engines (exploratory), worst-case table
  per family × regime.

## 6. Split, lock, and access (Law 1 / L-04 analog)

- Held-out fraction: ~40% of the scenario corpus, stratified by curve family × dynamical
  regime; remainder is the calibration set (free use).
- Minting: I-003-T2 generates held-out scenarios from the coverage table below — Tier-1 via
  CAS-verified closed forms, Tier-2 via the refsim with `reference_converged` passed — and
  locks them (split-lock marker + manifest) before any C-001 binary executes any of them.
- Access: held-out scenarios run only via the I-004 gate runner, which logs every execution
  to the manifest. Any other execution poisons the scenario (retire + re-mint + journal).
- The seeded calibration fixtures FL-1 and PB-1 are calibration-set members permanently.

## 7. Coverage table (L-07 analog; input contract for I-003-T2)

Cells marked HO receive held-out scenarios; CAL calibration-only; — declared empty with the
reason. Ball counts: every non-empty cell at 1 ball; multi-ball (2–4, TB-1 stress) required
where marked +MB.

| family \ regime | settle/transient | periodic | quasi-chaotic |
|---|---|---|---|
| flat line | CAL (FL-1) + HO +MB | HO non-dyadic (P1-C) +MB | — (flat line: no chaotic single-ball regime, R2) |
| explicit poly deg 2 (parabola) | CAL (PB-1) + HO +MB | HO bowl orbit (P1-C) | HO (25-event cap, §1) |
| explicit poly deg 3–6 | HO | HO | HO (25-event cap) |
| piecewise Bézier C1 | HO +MB | HO (P1-C) | — (Phase-1 Tier-2 reference-horizon cost; declared, revisit Phase 2) |

Declared empty program-wide: transcendental curve families (Director ruling R3); ball–ball
collisions (R2); ball counts 8–16 (enter with P1-D addendum only).

Mandatory grazing block (PROJECT §9 domain safeguard a) — held-out, gate-bearing in P1-A:
at least 3 near-tangency scenarios with normal impact speed |v_n| at 0.5×, 1.0×, and 2.0×
v_graze (spanning the G-1 admissibility boundary from both sides, including the boundary
case whose G-1 classification is itself the oracle value), plus 1 near-double-root geometry
(discriminant within 1e-6 of zero at contact). At least one grazing scenario on a Bézier
segment.

## 8. Multiplicity and red team (L-06, P2 §6)

One primary criterion per study (§1–§3, §5); everything else labeled exploratory. Red-team
items accompanying the Phase-1 gate call: (i) leave-one-curve-family-out — P1-A re-evaluated
excluding the dominant family, result reported; (ii) trusted-tier-only — P1-A re-evaluated on
Tier-1 fixtures alone; (iii) concentration check — no single family may contribute >50% of
held-out scenarios (I-003-T2 mint constraint).

## Changelog
- v1.0 — Initial registration (PACKET 36, JRN-C001-45). P1-A/B/C registered; P1-D deferred;
  Law 7 methodology and margin fixed; coverage table issued as I-003-T2 input contract.

## docs/00_STATE.md

# STATE — Bounce
last_updated_by: pm-fable5-b | trigger: OUT_35 ACCEPT (JRN-C001-44); C-001 PREREGISTERED (JRN-C001-45); PACKET 36

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — Falsifiable core. C-001-T1…T10 VERIFIED (T8–T10 calibration-mode precursors, not
§8 gate runs — JRN-C001-43). C-001 PREREGISTERED (PREREGISTRATION.md v1.0, JRN-C001-45):
P1-A/B/C registered, P1-D deferred pending measured basis, Law 7 matched-compute methodology
and 100× margin fixed, coverage table issued as I-003-T2 input contract. Authorship model B
in force (L-14). Packet-as-file delivery rule in force. C-002-T1/T2 VERIFIED. I-003-T1
VERIFIED. Next: I-004 brief + merge instruction (PACKET 37), Tier-2 hard-cell fixture mint
(PACKET 38), C-001-T11 spec (agent-authored baseline).

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | PREREGISTERED | T11 spec dispatch | I-004 brief (PACKET 37) |
| C-002 Curve library | BRIEFED | T3 prereg | C-001 prereg pattern (now available) |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | VERIFIED | — | — |
| I-002 high-precision reference sim | VERIFIED (JRN-I002-25) | — complete | — |
| I-003 scenario store + split-lock | BRIEFED (T1 VERIFIED, JRN-I003-5) | T2 brief — held-out mint per C-001-PREREG §7 | PACKET 38 |
| I-004 gate runner + manifests | SPECCED | brief | PACKET 37 (critical path) |
| I-005 event/pattern analysis harness | SPECCED | brief | I-004; feeds P1-D addendum |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Director hosting (open decision 1 — escalated) |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED: P1-B beyond a single machine (platform
   variance) and any cross-platform determinism claim are blocked on it.
2. P6 amendment bundle: §4.6 (L-11, L-13, L-14); §7.4 clarification (pre-verification =
   oracle derivation from specs, never running the codebase); §7.5 packet-as-file delivery
   rule — non-blocking; approval requested.
3. GPLv3 -only vs -or-later — Phase 3.

## Outstanding Director evidence
PACKET 35 DIRECTOR ACTION: paste `git log --oneline -1 task/C-001-T10` and
`git branch --no-merged main` with the next OUT — sizes the PACKET 37 merge instruction.

## Recent review verdicts
OUT_35/apply-only: ACCEPT — PACKET 35 APPLIED (JRN-C001-44).
OUT_34/C-001-T10: ACCEPT — C-001-T10 VERIFIED (JRN-C001-41).
OUT_33/C-001-T9: ACCEPT — C-001-T9 VERIFIED (JRN-C001-37).
OUT_32/C-001-T8: ACCEPT — C-001-T8 VERIFIED (JRN-C001-33).

## Pointers
Branch rule: packet/36 branches from packet/35; successors extend packet/36 until the
PACKET 37 merge instruction lands. C-001 confirmatory work is governed by
docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md v1.0 — registered values
change only by Director-approved CORRECTION packet.

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
| C-001 | Exact collision engine | Closed-form ballistic flight + analytic collision-time root-solve on the true curve yields bit-deterministic, drift-free event sequences in real time | engine | PREREGISTERED (PREREGISTRATION.md v1.0, JRN-C001-45; "real time" clause pending P1-D addendum) | naive fixed-timestep + polyline engine (PROJECT §5 Law 7; matched-compute methodology + 100× margin registered, C-001-PREREG §5) | T1 VERIFIED (JRN-C001-5); T2 VERIFIED (JRN-C001-9); T3 VERIFIED (JRN-C001-13); T4 VERIFIED (JRN-C001-17); T5 VERIFIED (JRN-C001-21); T6 VERIFIED (JRN-C001-25); T7 VERIFIED (JRN-C001-29); T8 VERIFIED (JRN-C001-33); T9 VERIFIED (JRN-C001-37); T10 VERIFIED (JRN-C001-41) — T8–T10 are calibration-mode precursors, not §8 gate runs (JRN-C001-43) — docs/03_TRACKS/C-001_exact_collision_engine/reports/ |
| C-002 | Curve library | A family of exactly-defined user-shapeable curves (with derivatives/normals) the engine solves against | curve | BRIEFED | direct per-query eval without compilation at matched compile+query cost (DELIVERABLE_D) | T1 VERIFIED (JRN-C002-5); T2 VERIFIED (JRN-C002-9) — docs/03_TRACKS/C-002_curve_library/reports/ |
| C-003 | Event→MIDI mapping engine | User-configurable collision→(pitch, velocity, channel) mapping emitted sample-accurately | mapping | IDEA | tbd at THESIS | — |
| C-004 | Plugin shell & visuals | JUCE VST3 shell with real-time visualization and host parameter/automation plumbing | ui | IDEA | tbd at THESIS | — |
| C-005 | Preset & state system | Full serialization of curve+balls+physics+mapping with replay-identity guarantee | io | IDEA | tbd at THESIS | — |
| C-000 | Phase-0 scoping | Phase 0 delivers a Director-approvable plan: prior-art landscape, numerics decision memo, architecture plan, prioritized component slate (PROJECT §3 a–d) | infra-facing | CLOSED | n/a — scoping gate is Director approval, not numeric (P2 §8) | Phase-0 gate PASSED (Director, 2026-07-07); deliverables (a)–(d) + rulings R1–R3 approved — 03_TRACKS/C-000_scoping/reports/, JRN-C000-18 |

## FILE DIGESTS

- docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md: 29753 bytes · sha256 58ee0e013ba28079ce977cd150f29713142b916d72f6b7b66f4a3d2c3780dfca
- docs/03_TRACKS/C-001_exact_collision_engine/PREREGISTRATION.md: 9687 bytes · sha256 ef7d8238b52d117033616b0efda9d6053fa8d95ed2f14c1fd94a69be2a2c071e
- docs/00_STATE.md: 3111 bytes · sha256 e44f4c3ab7a352388c41301ef3b2c5ee2051dfaced6a7f55a4977d2d9691dfb9
- docs/02_PROGRAM/COMPONENT_REGISTER.md: 2359 bytes · sha256 891a648c7f77b0a4bf112099ae6ad5b251a5099e4ad30c7e2274e93e65455aac

## GIT STATUS (step 3)

```
## packet/36
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
```

## BRANCH/COMMITS

```
ac7e7a8 Apply PACKET 36: OUT_35 ACCEPT, C-001 PREREGISTERED.
+ final OUT commit (hash not self-listable)
```

**Status: APPLIED**

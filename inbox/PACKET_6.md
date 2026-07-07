# PACKET 6 — OUT_5 accepted; deliverable (d) component slate; repo normalization task RV2
pm: pm-fable5-a · date: 2026-07-07 · task: C-000-RV2

== VERDICT ==
ACCEPT — OUT_5_C-000-RV1 reviewed per P6 §2; all acceptance criteria and OUT-REQUIREMENTS
COMPLIANT (table in JRN-C000-13). Substantive findings from the evidence: (1) transcription
fidelity of packets 1–5 verified — state-bearing docs match PM-authored content verbatim, all
five track documents digest-pinned; (2) the repository is partially tracked (protocols, module,
AGENTS.md, inbox packets untracked) and packet branches were never merged — current branch was
packet/4. Repair dispatched as C-000-RV2 (capture full tree, plant main, evidence of clean
status). This packet also files Phase-0 deliverable (d), the prioritized component slate, and
refreshes STATE. After RV2 the Phase-0 exit presentation follows.

== FILES ==

=====[ FILE OVERWRITE: docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_D_SLATE.md ]=====
# DELIVERABLE (d) — Prioritized component slate with acceptance-criteria sketches

```
doc_id:   C-000-DELIV-D
layer:    track
audience: Director (Phase-0 gate), PM
status:   DRAFT (pending Phase-0 gate approval)
parent:   C-000-BRIEF / PROJECT §3(d)
```

Ordering principle (Law 8 / L-08): the falsifiable core bet first. If C-001/C-002 fail their
gates, everything downstream is decoration; nothing below the line starts until the bet survives.

## Phase 1 — the bet

**1. C-002 Curve library** (curve) — polynomial (deg ≤ 8) + piecewise Bézier (quadratic/cubic,
declared C1) per DELIVERABLE_B §2; curve compilation to pinned coefficient sets; validator
rejecting undeclared kinks. Acceptance sketch: evaluation/derivative/normal values match CAS
fixtures exactly at Tier-1 points; validator acceptance/rejection table over a pre-registered
spec corpus; zero allocation after compile. Baseline (named at THESIS): direct per-query
evaluation without compilation, matched accuracy at compile+query cost.

**2. C-001 Exact collision engine** (engine) — ballistic arcs + VCA root isolation + fixed
refinement (DELIVERABLE_B §3), TB-1 ordering, G-1/S-1 rules. Acceptance sketch, tied to PROJECT
§8 gates: `determinism_repro` — bit-identical CollisionEvent sequences across ≥ 100 repeated
runs and across audio block sizes, per platform; `loop_stability` — zero interval-sequence
drift over ≥ 10⁴ periods on periodic Tier-1 fixtures; reference agreement — event times within
pre-registered tolerance of the mpmath oracle on calibration scenarios, held-out scenarios run
only via the gate runner; `realtime_budget` — p99.9 per-event solve cost within the budget the
prereg sets, on worst-case coverage cells (Law 7 §9 table); baseline comparison — beats the
naive fixed-timestep + polyline engine on accuracy at matched compute. Kill condition: baseline
matches accuracy within tolerance at equal cost, or the budget is unmeetable at target scene
sizes.

Infra in support (briefed at Phase-1 entry, in order): I-001 core skeleton → I-002 refsim +
fixtures → I-003 scenario store + split-lock → I-004 gate runner + manifests → I-005 analysis
harness → I-007 CI (clean-checkout, both platforms). C-002 and C-001 theses are written together
at Phase-1 entry; C-002 tasks lead by one packet so the engine always has real curves to solve.

## Phase 2 — the instrument (each re-gated by its own thesis; starts only after Phase-1 gate)

**3. C-003 Event→MIDI mapping engine** (mapping) — collision → (pitch, velocity, channel) with
user-configurable mapping as a first-class object (DELIVERABLE_A §3.5: the oldest complaint in
the lineage is a hardwired mapping). Sketch: `midi_timing` — NoteEvent sample placement error
≤ 1 sample against exact event times over the scenario corpus; mapping-config roundtrip; no
audio-thread allocation.

**4. C-004 Plugin shell & visuals** (ui; needs I-006 JUCE scaffold) — thin shell per
DELIVERABLE_C §1/§5. Sketch: pluginval at the strictness level pinned in the I-006 brief, on
both platforms; determinism-boundary test — event stream bit-identical with UI hidden vs
visible vs headless; visual latency within budget set at THESIS.

**5. C-005 Preset & state system** (io) — full serialization of curve+balls+physics+mapping.
Sketch: `preset_roundtrip` — save/load → bit-identical event sequence; versioned schema with
explicit engine-version pin (PROJECT §9c: presets replay per engine version, migrations are
explicit).

## Phase 3 — release (gate: Director; GPLv3 license file, source hosting, binary artifacts,
docs) — planned after Phase-2 gates; no component work here, packaging and publication only.
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/00_STATE.md ]=====
# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_5/RV1 accepted; deliverables (a)–(d) filed; RV2 dispatched (PACKET 6)

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 0 — Scoping (PROJECT §3). Module v0.1 ACTIVE (Director-approved 2026-07-06). License: GPLv3
(Director 2026-07-06; PROJECT §11 text amendment batched to module v0.2 at Phase-0 exit).
All four Phase-0 deliverables authored and transcription-verified (RV1, JRN-C000-13):
(a) LANDSCAPE, (b) NUMERICS, (c) ARCHITECTURE, (d) SLATE under
docs/03_TRACKS/C-000_scoping/reports/.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-000 Phase-0 scoping | RUNNING (T1, RV1 accepted) | GATE_REVIEW — Phase-0 exit presentation | RV2 (repo normalization); then Director approval of (a)–(d) incl. rulings R1–R3 |

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001 engine lib skeleton | SPECCED | brief | Phase-0 exit |
| I-002 high-precision reference sim | SPECCED | brief | Phase-0 exit (creates venv, installs pinned mpmath) |
| I-003 scenario store + split-lock | SPECCED | brief | Phase-0 exit |
| I-004 gate runner + manifests | SPECCED | brief | Phase-0 exit |
| I-005 event/pattern analysis harness | SPECCED | brief | Phase-0 exit |
| I-006 JUCE build scaffold | SPECCED | brief | Phase 1 gate |
| I-007 CI pipeline | SPECCED | brief | Phase-0 exit (Director creates hosting/CI account first, PROJECT §11) |

## Open decisions (Director)
1. Phase-0 exit gate: approve deliverables (a)–(d) including numerics scope rulings R1
   (point-contact), R2 (no ball–ball), R3 (transcendental families deferred). Options:
   approve / amend. PM rec: approve — presented after RV2 confirms a clean repository.

## Recent gate calls
None yet (first gate is the Phase-0 exit, Director-owned).

## Pointers
Repository normalization in progress (RV2, JRN-C000-13): step-1 evidence of OUT_5 showed a
partially tracked tree (protocols/module/AGENTS.md untracked) and unmerged stacked packet
branches with HEAD on packet/4. After RV2: main is the single line of history; every task
branch starts from main; Director merges after each ACCEPT. Environment of record unchanged
(JRN-C000-5). Git history before RV2 is non-linear; content authority for that span is the
RV1 evidence, not branch topology.
=====[ END FILE ]=====

=====[ FILE OVERWRITE: .gitignore ]=====
.DS_Store
bounce-docs.zip
tools/refsim/.venv/
=====[ END FILE ]=====

=====[ FILE APPEND: docs/03_TRACKS/C-000_scoping/JOURNAL.md ]=====
---
### JRN-C000-14 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Authored Phase-0 deliverable (d), prioritized component slate
(reports/DELIVERABLE_D_SLATE.md): Phase 1 = C-002 curve library + C-001 exact engine (the
falsifiable bet, Law 8), with acceptance sketches bound to the PROJECT §8 gates and kill
conditions named; Phase 2 = C-003 mapping, C-004 shell/visuals, C-005 presets, each with its
own thesis and gate sketch; infra order I-001→I-002→I-003→I-004→I-005→I-007 at Phase-1 entry.
All four Phase-0 deliverables now filed.
NUMBERS: none
LEARNED: nothing
NEXT: RV2 repo normalization; then the Phase-0 exit presentation to the Director.

---
### JRN-C000-13 · NOTE
actor: pm-fable5-a · task: C-000-RV1 · manifest: n/a

WHAT: Review of OUT_5_C-000-RV1 per P6 §2. Verdict: ACCEPT. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | TR sections Step 1–6, verbatim outputs | COMPLIANT |
| 2 | CLAIM + DONE verbatim in OUT | COMPLIANT |
| 3 | Serial-5 ledger line in APPLY CONFIRMATION | COMPLIANT |
| OR | OUT-REQUIREMENTS (journal copies incl. L-10 line, full report, branch/commits) | COMPLIANT |
Findings of record: (1) Transcription fidelity packets 1–5 VERIFIED — STATE, COMPONENT_REGISTER,
LESSONS, JOURNAL pasted verbatim and matching PM-authored content; five track documents
digest-pinned (sha256 + byte counts in TR_C-000-RV1 step 6). (2) Repository defect: step-1
status shows HEAD on packet/4, packet branches 2–4 never merged, and the initial commit was
partial — untracked: AGENTS.md, docs/00_PROJECT.md, docs/01_PROTOCOLS/, 00_GENESIS.md,
INFRASTRUCTURE_REGISTER.md, DIRECTORS_MANUAL.md, LESSONS_CORE.md, README.md, 03_TRACKS/README,
04_ARCHIVE/, 05_INFRA/, inbox packets, outbox/README — a clean clone would lack the program's
constitution (L-02 class). Repair: task C-000-RV2 (this packet). (3) Minor observation, no
action: the RV1 agent ran task steps before committing the apply (step-1 status shows the
uncommitted apply); content integrity unaffected, verified by the pasted docs themselves.
PM ruling: RV2 is sanctioned, once, to end on `main` rather than a task branch — normalizing
the branch structure is the task's purpose.
NUMBERS: file digests of record in TR_C-000-RV1 step 6 (sha256, byte counts).
LEARNED: "git init + initial commit" delegated to the Director without evidence required was
the same class of gap as L-09/L-10 — setup steps need agent-pasted evidence too; RV2 closes it.
NEXT: RV2 execution; Phase-0 exit presentation.
=====[ END FILE ]=====

== TASK ==
Precondition (Director, yes/no): last line of `inbox/APPLIED.log` is serial 5, and you have not
manually merged, rebased, or otherwise changed git state since OUT_5.

Reading list: `AGENTS.md` · this packet · P4 · P1 §3 and §7. The files named in the steps are
whitelisted by this TASK. No other files.

Assignment: execute TASK C-000-RV2 exactly as written here (this packet is the brief for RV2).
Apply the FILES section first (serial check: this is serial 6). Note: applying FILES with
uncommitted-then-committed work is resolved by step 2, which captures everything.

## TASK C-000-RV2: Normalize the repository — full tree under version control, main planted
depends_on: none
objective: Bring every program file under version control in one capture commit, make `main`
           the single current line of history, and paste evidence of the clean result.
inputs:    The repository working tree after this packet's FILES section is applied. No external
           sources. All values are verbatim command output; manifest n/a (JRN-C000-2 ruling).
steps:
  1. Run: `git rev-parse --abbrev-ref HEAD ; git branch -a ; git log --oneline --graph --all | head -60`
     — copy the full output (topology of record before repair).
  2. Run: `git add -A ; git commit -m "RV2: capture full working tree under version control (PACKET 6)"`
     — copy the full output.
  3. Run: `git branch -f main HEAD ; git checkout main ; git rev-parse --abbrev-ref HEAD` — copy
     the full output.
  4. Run: `git status --short --branch` — copy the full output. Expected: `## main` and no
     modified or untracked entries (ignored files per .gitignore are expected to be absent from
     the listing).
  5. Run: `git log --oneline -8` — copy the full output.
  6. Write `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-RV2.md` per P1 §7, header
     `manifest: n/a — repo normalization; all values are verbatim command output (JRN-C000-13)`,
     one section per step, `Step 1` … `Step 5`, each containing only that step's verbatim output.
  7. Append the DONE journal entry, commit on main, and write `outbox/OUT_6_C-000-RV2.md`.
output:
  - docs/03_TRACKS/C-000_scoping/reports/TR_C-000-RV2.md
  - journal CLAIM and DONE entries
  - outbox/OUT_6_C-000-RV2.md
courier:
  - Full text of TR_C-000-RV2.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR_C-000-RV2.md contains sections `Step 1` … `Step 5`, each the verbatim output of that
     step.
  2. Step-4 output shows branch main with no modified and no untracked entries.
  3. The OUT file contains verbatim copies of the CLAIM and DONE journal entries for RV2.
  4. The OUT file's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 6.
OUT-REQUIREMENTS (per L-10 — an OUT missing any of these is returned for repair):
  - APPLY CONFIRMATION with the serial-6 ledger line pasted;
  - JOURNAL ENTRIES section: verbatim copies of the entries this packet's FILES section appended
    (JRN-C000-14, JRN-C000-13) AND RV2's CLAIM/DONE entries;
  - FILE DIGESTS: `wc -c` and `shasum -a 256` output for each file this packet's FILES section
    wrote (DELIVERABLE_D_SLATE.md, 00_STATE.md, .gitignore);
  - REPORT section: TR_C-000-RV2.md in full;
  - BRANCH/COMMITS: branch name (main — sanctioned for this task only, JRN-C000-13) and commit
    shas.
failure_modes:
  - Any git command in steps 1–3 returns an error → STOP, paste the verbatim error, file
    BLK_C-000-RV2_1.md, mark the OUT BLOCKED.
  - Step-4 output shows modified or untracked entries → STOP, paste it, BLOCKED (do not attempt
    further fixes).
  - Unresolved CLAIM for RV2 in the journal → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not delete, rename, or rebase any branch; do not rewrite history; do not force-push
    (there is no remote); `git branch -f main HEAD` in step 3 is the only branch mutation.
  - Do not edit file contents beyond applying this packet's FILES section and writing the
    task's own outputs.
  - Do not run commands not listed in the steps.

End state: repository on branch `main`, clean status, exactly one committed
`outbox/OUT_6_C-000-RV2.md` marked DONE or BLOCKED. Then stop.

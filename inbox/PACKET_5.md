# PACKET 5 — Reconciled: CORRECTION (OUT under-review + parallel-PM conflict); L-10; deliverable (c); task RV1
pm: pm-fable5-a · date: 2026-07-07 · task: C-000-RV1

This packet supersedes and voids any other document titled PACKET 5 from any other PM
conversation. Nothing from any parallel conversation may be dispatched.

== VERDICT ==
Two incidents corrected in one entry (JRN-C000-9). First: OUT_2/OUT_3/OUT_4 omitted the P5 §5
JOURNAL ENTRIES section and the PM accepted them anyway, implicitly treating repo content as
checkable — inadmissible under P6 §2.2; caught by the Director, itself a P6 §6.4 incident.
Durable fix: lesson L-10 — every packet now carries an explicit OUT-REQUIREMENTS block including
verbatim journal copies and per-file digests, and an OUT missing any required section is returned
for repair. Second: a parallel PM conversation produced a conflicting, unshipped PACKET 5;
reconciled per Manual §5 (repo wins — APPLIED.log ends at serial 4), its stricter OUT standard
adopted here, and the program runs one PM conversation from now on. This packet also files
Phase-0 deliverable (c), the architecture plan, and dispatches C-000-RV1 to re-emit transcription
evidence for packets 1–5 so the Phase-0 gate rests on OUT-file evidence, not PM assumption.

== FILES ==

=====[ FILE OVERWRITE: docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md ]=====
# DELIVERABLE (c) — Architecture plan

```
doc_id:   C-000-DELIV-C
layer:    track
audience: Director (Phase-0 gate), PM; later cited by I-001…I-007 and component briefs
status:   DRAFT (pending Phase-0 gate approval)
parent:   C-000-BRIEF / PROJECT §3(c)
```

## 1. Two-layer product architecture

- **`bounce-core`** — headless C++20 static library. Owns everything gate-bearing: curve
  compilation (CurveSpec → pinned polynomial coefficient sets), the event-driven engine
  (ballistic arcs + root isolation per DELIVERABLE_B), event ordering (TB-1), grazing/settle
  rules (G-1/S-1), and the CollisionEvent stream. Zero third-party dependencies (C++ standard
  library only). No JUCE types anywhere in core. Real-time contract: no heap allocation, no
  locks, no I/O on the processing path; all allocation at prepare/configure time.
- **`bounce-plugin`** — thin JUCE VST3 shell (Phase 2; I-006). Hosts core + the mapping engine
  (C-003), renders visuals, exposes parameters/automation, serializes presets (C-005). JUCE is
  fetched by CMake at a pinned release tag and used under its GPL option, matching the program's
  GPLv3 license (Director decision D2). The shell may never contain physics or event-ordering
  logic; anything affecting the event sequence lives in core, or the determinism surface leaks.

Interface spine (PROJECT §6 schemas): CurveSpec + [BallState] + physics params → core →
CollisionEvent stream → mapping (C-003) → NoteEvent stream → host MIDI. `advance(n_samples)` is
the single audio-thread entry point; events carry in-block sample offsets per DELIVERABLE_B §4.

## 2. Repository layout (instantiates P3 §1)

```
src/core/            engine, curves, events, time bookkeeping (bounce-core)
src/plugin/          JUCE shell (empty until I-006 / Phase 2)
tools/refsim/        I-002 Python/mpmath reference simulator + fixture generator
tools/gates/         I-004 gate runner + run-manifest writer
config/              pinned build/FP flags (fp-determinism.cmake), gate configs, solver spec
data/scenarios/      I-003 scenario store: calibration/ and heldout/ with split-lock marker
tests/               unit tests + gate scenario harnesses (I-005 analysis lives here)
reports/             run manifests, gate outputs
```

## 3. Toolchain & dependency policy

- Build: CMake (≥ 3.27, present per JRN-C000-5) with committed CMakePresets; compiler of record
  Apple clang 17 (arm64 macOS), Linux x86-64 added in CI. All FP-determinism flags from
  DELIVERABLE_B §4 live in exactly one included fragment, `config/fp-determinism.cmake`; a unit
  test asserts the flags are in effect at runtime (FMA contraction and FTZ checks).
- Test framework: doctest (MIT, header-only) for unit tests — GPLv3-compatible, zero build cost.
- Python side: project-local venv under `tools/refsim/.venv`, Python 3 (3.9.6 of record), mpmath
  pinned by exact version in `tools/refsim/requirements.txt` (installed by the I-002 brief —
  addresses the mpmath absence recorded in TR_C-000-T1). Reference code is never linked, called,
  or vendored into product code; it is a gate-time oracle only.
- License hygiene: every dependency's license recorded in `docs/05_INFRA/` at adoption;
  GPLv3-compatible only (P3 §2b.6 / PROJECT §11).

## 4. Infrastructure mapping (I-001…I-007 → this plan)

| ID | becomes | phase |
|---|---|---|
| I-001 | `src/core` skeleton + CMake + doctest harness building clean | Phase 1 entry |
| I-002 | `tools/refsim` venv + mpmath sim + Tier-1/Tier-2 fixture generator | Phase 1 |
| I-003 | `data/scenarios` store, split-lock marker + hash, heldout access only via gate runner | Phase 1 |
| I-004 | `tools/gates` runner: executes PROJECT §8 gates, writes run manifests (pins §7 surface) | Phase 1 |
| I-005 | event-sequence diff + drift measurement in `tests/` | Phase 1 |
| I-006 | `src/plugin` JUCE scaffold, VST3 target, pluginval in CI | Phase 2 entry |
| I-007 | GitHub Actions CI: clean-checkout build + unit tests + gates, macOS arm64 + Linux x86-64 | Phase 1 |

CI account/repository creation is Director-side (PROJECT §11); the I-007 brief will name exactly
what to create. Free tier only; any paid CI minutes require Director approval first.

## 5. Determinism boundaries (what may vary, what may not)

May never vary: the CollisionEvent sequence for a given (preset, engine version) — across runs,
block sizes, and save/load (gates `determinism_repro`, `preset_roundtrip`). May vary freely:
rendering framerate, UI state, host block scheduling — the shell consumes the event stream but
cannot influence it. Threading: core is single-threaded per scenario; the plugin communicates
UI ↔ audio via a lock-free SPSC queue (Phase-2 detail, named now so no one adds a mutex later).

## 6. Explicitly deferred

Curve-editing UX (how gestures become Bézier pieces), mapping semantics, host-tempo sync, and
preset file format details — owned by C-003/C-004/C-005 theses at Phase 2 entry.
=====[ END FILE ]=====

=====[ FILE APPEND: docs/03_TRACKS/C-000_scoping/JOURNAL.md ]=====
---
### JRN-C000-10 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Authored Phase-0 deliverable (c), architecture plan (reports/DELIVERABLE_C_ARCHITECTURE.md):
bounce-core headless deterministic library (zero deps, no JUCE types) + thin JUCE VST3 shell;
repo layout instantiating P3 §1; single-fragment FP-flag pinning with a runtime assertion test;
doctest (MIT); project venv for the mpmath reference; I-001…I-007 mapped to concrete paths and
phases.
NUMBERS: none
LEARNED: nothing
NEXT: deliverable (d), prioritized component slate; then the Phase-0 exit presentation.

---
### JRN-C000-9 · CORRECTION
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Corrects the PM reviews of OUT_2, OUT_3, OUT_4 and the authoring of PACKETs 2–4, and
reconciles a parallel-PM conflict. Incident 1: those OUT files lacked the P5 §5 JOURNAL ENTRIES
section (verbatim copies of entries applied this dispatch) and the PM accepted them, implicitly
treating applied content as checkable in the repo — inadmissible rationale per P6 §2.2. Root
cause: apply-only packets stated no explicit OUT requirements, so agent and PM both defaulted to
a thin format. The gap was raised by the Director — Director-side quality control is itself a
P6 §6.4 incident. Durable fix: L-10 appended to 02_PROGRAM/LESSONS.md; from this packet onward
every packet's TASK section carries an explicit OUT-REQUIREMENTS block, and an OUT missing any
required section is RETURN_FOR_REPAIR, never accepted. A one-paragraph P5 §5 amendment (v1.1)
codifying apply-only OUT content is warranted and deliberately deferred to the next full
re-issue of P5, because re-transcribing a framework file to insert one paragraph carries its own
byte-drift risk — L-10 plus the per-packet block is the binding rule in the interim. Incident 2:
two PM conversations ran in parallel; the second authored a conflicting, unshipped PACKET 5
(CORRECTION + repair task). Reconciled per DIRECTORS_MANUAL §5: repo wins (APPLIED.log verified
ending at serial 4, Director-pasted 2026-07-07); the conflicting draft is void; its stricter OUT
standard is adopted here; exactly one PM conversation runs the program from now on. Repair:
task C-000-RV1 re-emits transcription evidence for the files applied by packets 1–5 so Phase-0
gate review rests on OUT-file evidence.
NUMBERS: none
LEARNED: see L-10.
NEXT: C-000-RV1 execution; deliverable (d) follows.
=====[ END FILE ]=====

=====[ FILE APPEND: docs/02_PROGRAM/LESSONS.md ]=====
L-10: An OUT file must carry, inside itself, every piece of evidence its review needs — for
apply-only packets that means verbatim copies of every journal/register/log line applied plus a
digest (byte count and sha256) of every file written; "it can be checked in the repo" is not
review evidence because the PM has no repo access by design (P6 §2.2). Enforcement: every
packet's TASK section states an explicit OUT-REQUIREMENTS block, and an OUT missing any required
section is returned for repair, never accepted. Origin: OUT_2–OUT_4 lacked the P5 §5
journal-copies section and were accepted anyway; caught by the Director (a P6 §6.4 incident);
compounded by a parallel PM conversation independently drafting the same correction
(JRN-C000-9).
=====[ END FILE ]=====

== TASK ==
Precondition (Director, yes/no): last line of `inbox/APPLIED.log` is serial 4, and branches
packet/2, packet/3, packet/4 are merged to main.

Reading list: `AGENTS.md` · this packet · P0 §2–§6 · P3 · P4 · P1 §3 and §7. The files named in
the steps below are explicitly whitelisted for reading by this TASK. No other files.

Assignment: execute TASK C-000-RV1 exactly as written here (this packet is the brief for RV1;
it amends nothing in BRIEF.md). Apply the FILES section first (serial check: this is serial 5).

## TASK C-000-RV1: Re-emit transcription evidence for packets 1–5
depends_on: none
objective: Paste, verbatim, the current content of the state-bearing documents and digests of the
           PM-authored track documents, so the PM can verify packet 1–5 transcription fidelity
           from the OUT file alone.
inputs:    The repository working tree after this packet's FILES section is applied. No external
           sources, no env vars. All values are verbatim command output; manifest n/a
           (JRN-C000-2 ruling).
steps:
  1. Run: `git rev-parse HEAD ; git status --short --branch` — copy the full output.
  2. Run: `cat docs/00_STATE.md` — copy the full output.
  3. Run: `cat docs/02_PROGRAM/COMPONENT_REGISTER.md` — copy the full output.
  4. Run: `cat docs/02_PROGRAM/LESSONS.md` — copy the full output.
  5. Run: `cat docs/03_TRACKS/C-000_scoping/JOURNAL.md` — copy the full output.
  6. For each of the five files below, run `wc -c <path> ; shasum -a 256 <path> ; head -3 <path> ; tail -3 <path>`
     and copy the full output:
       docs/03_TRACKS/C-000_scoping/COMPONENT_THESIS.md
       docs/03_TRACKS/C-000_scoping/BRIEF.md
       docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_A_LANDSCAPE.md
       docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_B_NUMERICS.md
       docs/03_TRACKS/C-000_scoping/reports/DELIVERABLE_C_ARCHITECTURE.md
  7. Write `docs/03_TRACKS/C-000_scoping/reports/TR_C-000-RV1.md` per P1 §7, header
     `manifest: n/a — evidence re-emission; all values are verbatim command output (JRN-C000-9)`,
     with one section per step, titled `Step 1` … `Step 6`, each containing only that step's
     verbatim output.
  8. Append the DONE journal entry, commit, and write `outbox/OUT_5_C-000-RV1.md`.
output:
  - docs/03_TRACKS/C-000_scoping/reports/TR_C-000-RV1.md
  - journal CLAIM and DONE entries
  - outbox/OUT_5_C-000-RV1.md
courier:
  - Full text of TR_C-000-RV1.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR_C-000-RV1.md contains sections `Step 1` … `Step 6`, each being the verbatim output of
     that step (one criterion per section; error text, if any, pasted verbatim is compliant).
  2. The OUT file contains verbatim copies of the CLAIM and DONE journal entries for RV1.
  3. The OUT file's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 5.
OUT-REQUIREMENTS (per L-10 — an OUT missing any of these is returned for repair):
  - APPLY CONFIRMATION with the serial-5 ledger line pasted;
  - JOURNAL ENTRIES section: verbatim copies of the three entries this packet's FILES section
    appended (JRN-C000-10, JRN-C000-9, the L-10 line) AND the CLAIM/DONE entries RV1 appends;
  - REPORT section: TR_C-000-RV1.md in full;
  - BRANCH/COMMITS: branch name and commit shas.
failure_modes:
  - A step-6 file missing from the tree → do not skip silently: paste the verbatim error in that
    file's section, note it under OBSERVATIONS, and continue.
  - The precondition's merge state contradicted by step 1 output → not a blocker: record and
    continue; the PM judges at review.
  - Unresolved CLAIM for RV1 already in the journal → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not truncate, reflow, or "clean up" any output.
  - Do not run commands not listed in the steps.
  - Do not edit any existing file's content; this task only reads, reports, and journals.

End state: one branch `task/C-000-RV1`, one commit series, exactly one committed
`outbox/OUT_5_C-000-RV1.md` marked DONE or BLOCKED. Then stop.

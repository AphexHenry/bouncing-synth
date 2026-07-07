# 00_GENESIS — Project initialization protocol (AI-executable)

```
doc_id:   GENESIS
layer:    protocol (framework)
audience: the INITIALIZING INSTANCE (an AI with workspace filesystem access) + the Director
status:   ACTIVE v1.0 (framework — domain-free)
kind:     FRAMEWORK — reused verbatim. Run ONCE per program, then never again.
parent:   P0
```

This file turns an empty repo + this framework into a running program. It is written to be **executed
by an AI** — a Cursor agent or a workspace-connected Claude — with the Director answering questions.
You (the initializing instance) read this file top to bottom and perform each phase in order.

**The pre-loop exception (read first).** The packet loop (P5) and the PM/agent/Director separation do
not exist yet — you are creating the conditions for them. During genesis you therefore hold a
**bounded** authority no later actor has: you create directories, lay down the runtime skeleton, and
**transcribe** module-derived content into `00_STATE.md` and the registers. You do **not** author
research content — no briefs, no theses, no pre-registrations, no gate calls, no lessons. Those are the
PM's, produced through the loop after genesis ends. If you are ever unsure whether something is
"structure/transcription" (yours) or "research judgment" (the PM's), it is the PM's — leave it for the
loop. Genesis ends the moment the PM can boot (Phase 5); from then on, P0 §7 and the loop govern
everything.

Work in five phases. After each, print a one-line `PHASE n: done` so the Director can follow.

---

## Phase 0 — Preconditions

1. Confirm the framework is present and unedited: `docs/01_PROTOCOLS/P0…P6`, `docs/DIRECTORS_MANUAL.md`,
   `docs/LESSONS_CORE.md`, `docs/README.md`, `docs/00_PROJECT.template.md`, and `AGENTS.md` at the repo
   root. If any is missing, STOP and tell the Director which — genesis cannot proceed on a partial
   framework.
2. Confirm you have write access to the repo root and to `docs/`. If `docs/00_PROJECT.md` already
   exists, this repo has already been initialized — STOP (do not overwrite a live program).
3. Read `docs/00_PROJECT.template.md` in full — it defines the thirteen slots you will fill in Phase 2
   and the Slot Index you will verify in Phase 4.

`PHASE 0: done` — framework verified, repo writable, not previously initialized.

## Phase 1 — Scaffold the tree (deterministic; no judgment)

Create exactly this, and nothing more. These are the runtime layers named in P0 §3; they start empty
and fill as the program runs.

```bash
# courier channel + codebase (P5 §1, P3 §1)
mkdir -p inbox outbox src config data/raw tests reports/manifests
printf '# APPLIED.log — one line per applied packet\n' > inbox/APPLIED.log
printf '%s\n' 'Empty by design. Agents write OUT_<serial>[_<task>].md here.' > outbox/README.md

# runtime brain layers (P0 §3)
mkdir -p docs/02_PROGRAM docs/03_TRACKS docs/04_ARCHIVE docs/05_INFRA/reports
```

Do not create `00_STATE.md`, the registers, or any track folder yet — those are **derived** from the
module in Phase 3, and the module does not exist until Phase 2.

`PHASE 1: done` — empty tree laid down.

## Phase 2 — Author the module (`docs/00_PROJECT.md`) — judgment, with the Director

This is where the folder "fills itself." Copy the template to the live path, then fill it **section by
section with the Director**. The template's guidance blockquotes tell you what each slot needs; your
job is to ask the Director the minimum questions to fill each, draft the section, and get a yes before
moving on.

```bash
cp docs/00_PROJECT.template.md docs/00_PROJECT.md
```

Go in order §1 → §13. For each section, ask the Director a compact question set, then write the
section. Suggested prompts:

- **§1 Identity & purpose** — "In one sentence, what question does this program answer, and what single
  measurable outcome counts as success? What must it *not* drift into until which gate?"
- **§2 Unit of study** — "What does one track study here — a hypothesis, a component model, a corpus
  effect? Pick the track-id prefix, the register filename, and the Step-0 gate-document name."
- **§3 Staging & gates** — "What are the phases, and for each, is its exit a numeric gate or a
  Director-approved plan? Is there a scoping/literature-first phase (L-08)? If so, what must it
  deliver?"
- **§4 Study designs** — "What concrete shapes do studies take (2–3)? For each: what is one data point,
  and what is 'held out' held out *over*?"
- **§5 Law instantiations** — "What is the calibration/held-out split *over*? Which input-quality gates
  apply? What are the provenance tiers, most-trusted first? What is a matched-complexity baseline
  here?" *(Gate-bearing — must not stay TBD.)*
- **§6 Schemas** — "What typed record(s) is everything computed on? Required fields with units;
  what invalid values the validators reject." *(Gate-bearing.)*
- **§7 Determinism surface** — "What *generates* your analyzable artifacts (a solver? a data snapshot? a
  render step?) and what must be pinned in the manifest?"
- **§8 Gate types** — "Beyond the universal gates, what must the pipeline refuse past?" *(Gate-bearing.)*
- **§9 Bias-safeguard analogs** — "For each of L-01…L-08 (see `LESSONS_CORE.md`), how does that failure
  show up in *this* data, and what kills it? Any domain-only caution (coupling, regime dependence)?"
- **§10 Decision gate** — "The default numeric bar — fill the domain metric names into the mandatory
  rows." *(Gate-bearing.)*
- **§11 Director-gated items** — "What here needs your sign-off: spend ceilings, credentials, licensing/
  release, human-subjects?"
- **§12 / §13** — seed domain lessons (usually 'none yet, L-09+') and the infrastructure catalogue
  (the capabilities needed before tracks can run: harvesters, schema modules, harnesses, manifest/gate
  machinery — each with what it blocks).

Rules while authoring:
- You **draft**; the Director **approves**. `00_PROJECT.md` instantiates P0/P2, so it is
  Director-approved by definition (P0 §7). Record nothing the Director has not confirmed.
- A section the Director cannot yet decide is written `TBD — <what unblocks it>`. A `TBD` in a
  **gate-bearing** slot (§5, §6, §8, §10) is allowed to leave genesis, but it **blocks** any track that
  depends on it until the PM fills it via a packet — say so to the Director.
- Fill the module's **Changelog** and delete every guidance blockquote as you finish a section.
- If a study the program needs fits none of the §4 designs, add the design in §4 now — that is a P2
  instantiation, Director-approved, not a later surprise.

`PHASE 2: done` — `docs/00_PROJECT.md` authored and Director-approved (list any gate-bearing TBDs).

## Phase 3 — Seed the runtime from the module (transcription; no research judgment)

Now derive the runtime files **from what §1–§13 say**. You are transcribing module content into the
P1 templates, not deciding anything new.

1. **`docs/00_STATE.md`** — from the P1 §2 template. Program status = current phase (§3). Active tracks
   = none. Infra workstreams = one row per §13 capability at state `SPECCED`. Open decisions = the
   Phase-0 exit decisions the program needs (drawn from the §3 scoping-gate deliverables), plus a
   standing item 1: "Approve `00_PROJECT.md` as the working domain module." Keep it to one screen.
2. **`docs/02_PROGRAM/<TRACK>_REGISTER.md`** — filename from §2. Header per P1 §9, then one **IDEA** row
   per candidate track named in §2 (using the §2 row schema and `<domain field>` enum). No candidates
   yet ⇒ header + the column row only.
3. **`docs/02_PROGRAM/INFRASTRUCTURE_REGISTER.md`** — header per P1 §9, then one row per §13 capability
   at state `SPECCED`, with what it blocks.
4. **`docs/02_PROGRAM/LESSONS.md`** — header only + the line "New program lessons begin at L-09. None
   yet." (The inherited L-01…L-08 live in `LESSONS_CORE.md`; do not copy them here.)
5. **`docs/03_TRACKS/README.md`** and **`docs/04_ARCHIVE/README.md`** — the one-line stubs from P0 §3
   (one active-track-per-folder; archive empty-by-design, read-only, KILL_REPORT at root).
6. **`docs/05_INFRA/`** — create the folder and its `reports/.gitkeep`. **Do not** write the infra
   `BRIEF.md` — that is PM-authored work-order content (P1 §4), produced in the loop.

Every file you write here starts with the P1 §1 header block. Write nothing that is not directly
derivable from the module or the P1 templates.

`PHASE 3: done` — STATE + registers + layer stubs seeded from the module.

## Phase 4 — Self-check (the genesis gate)

Verify, and print the result of each as a PRESENT/ABSENT or PASS/FAIL line:

1. **Tree matches P0 §3.** Every path in the P0 §3 repository map exists (framework + runtime +
   courier). List any missing.
2. **Slot Index resolved.** Every row of the module's Slot Index points to a filled section (no
   gate-bearing `TBD`; note any non-gate `TBD` explicitly). This is the same completeness discipline
   the PM applies at bootstrap (P0 §6e).
3. **Registers seeded.** The track register and infra register each have their header and their
   module-derived rows.
4. **STATE is bootable.** `00_STATE.md` is ≤ one screen, names the current phase, and lists the Open
   Decisions the Director must resolve.
5. **Courier channel live.** `inbox/APPLIED.log` exists and is empty of applied packets; `AGENTS.md` is
   at the repo root.

Write a short `docs/05_INFRA/reports/GENESIS_REPORT.md` capturing these results (this is a factual
record, not research content, so it is within your genesis authority). If any check FAILs, fix it if it
is structural, or — if it needs a decision — surface it to the Director and leave it in the report.

`PHASE 4: done` — genesis gate results recorded.

## Phase 5 — Commit and hand off to the loop

1. Commit everything: `git add -A && git commit -m "genesis: <program> — framework + module + runtime skeleton"`.
2. Tell the Director genesis is complete and give them the boot line for the PM (from
   `DIRECTORS_MANUAL.md` §4):

   > "You are the PM of this research program. Bootstrap per `01_PROTOCOLS/P0_MASTER.md` §6 (read
   > `00_PROJECT.md` in full as step 2), then answer the sufficiency self-check before doing anything
   > else. Pending review: none."

3. **Stop.** Genesis is over. You do not issue packets, write briefs, or start tracks — the PM does,
   through the loop. Your last act is the handoff sentence above.

`PHASE 5: done` — program initialized; control passes to the PM loop.

---

## What genesis did and did not do

- **Created:** the full directory tree (P0 §3), the courier channel, and the runtime skeleton
  (`00_STATE`, both registers, `LESSONS.md`, layer READMEs), all **derived from `00_PROJECT.md`**.
- **Authored with the Director:** `docs/00_PROJECT.md` — the one domain file.
- **Did NOT touch:** any framework file (they are domain-free and reused verbatim).
- **Deliberately left to the PM loop:** every brief, thesis, pre-registration, gate call, and lesson —
  i.e. all research judgment. Genesis builds the stage; the loop performs on it.

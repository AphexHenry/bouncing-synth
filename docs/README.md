# <PROGRAM NAME> — Program Brain

> This is the generic framework README. When you scaffold a project, the one-paragraph program
> description at the top comes from `00_PROJECT.md §1`; everything below is domain-free and reused.

This repository is the operating system of an AI-agent-run research program. **What** the program
studies is defined in `00_PROJECT.md` (the domain module); **how** it is run is defined by the
framework (`01_PROTOCOLS/P0…P6`, `DIRECTORS_MANUAL.md`, `LESSONS_CORE.md`, `AGENTS.md`). The framework
is reused byte-for-byte across programs — only `00_PROJECT.md` and the runtime layers change.

## The two layers

- **Framework (domain-free, never edited per-project):** `01_PROTOCOLS/P0…P6`, `DIRECTORS_MANUAL.md`,
  `LESSONS_CORE.md`, `AGENTS.md`. These encode the method, the loop, and the eight inherited lessons.
  They reference the domain only through slots of the form `PROJECT §n`.
- **Module (domain, one file):** `00_PROJECT.md`. It fills every slot: purpose, unit of study, staging
  and gates, study designs, the Law instantiations, the schemas, the determinism surface, the gate
  types, the bias-safeguard analogs, the decision gate, and the Director-gated items. This is the only
  file you author to point the framework at a new domain.
- **Runtime (state, this program's history):** `00_STATE.md`, `02_PROGRAM/` (registers + this
  program's lessons L-09+), `03_TRACKS/`, `04_ARCHIVE/`, `05_INFRA/`. These accumulate as the program
  runs.

## Who reads what
- **New PM instance:** start at `00_STATE.md`, then `00_PROJECT.md` in full, then follow the bootstrap
  procedure in `01_PROTOCOLS/P0_MASTER.md` §6.
- **Agent:** read only what P0 §3.1 and your assigned TASK whitelist allow. Your first ritual on every
  dispatch is the PACKET APPLY procedure (`AGENTS.md`, P5 §4).
- **Director:** read `DIRECTORS_MANUAL.md` once; then `00_STATE.md` is always current, everything else
  is drill-down. Your loop is one file in (`inbox/`), one file out (`outbox/`).

## Layers (reading order)
`00_GENESIS` (run-once init) · `00_STATE` (where we are) · `00_PROJECT` (what/this domain) → `01`
protocols (the law) → `02` program registers & this program's lessons → `03` active tracks → `04`
archive (closed, read-only) → `05` infrastructure. `inbox/` and `outbox/` are the courier channel, not
part of the brain.

## Setup (once)
Point an AI with workspace access at `docs/00_GENESIS.md` and run it. It scaffolds the tree, authors
`docs/00_PROJECT.md` with the Director section by section, seeds `00_STATE` and the registers from that
module, self-checks, and hands off to the PM loop. `AGENTS.md` lives at the workspace ROOT (Cursor
auto-reads it); the courier channel is `inbox/` + `outbox/` at the root. Thereafter, dispatch per
`docs/01_PROTOCOLS/P5_AGENT_INTERFACE.md`.

## Lineage
The framework's methodology and its eight inherited lessons (`LESSONS_CORE.md`, L-01…L-08) descend from
a line of predecessor programs. Each program restates those lessons' **domain analogs** in
`00_PROJECT.md §9`; where any residue of a predecessor conflicts with the framework protocols, the
protocols win.

# 00_PROJECT — < PROGRAM NAME >  (the domain module)

```
doc_id:   PROJECT
layer:    project (root of all domain-specific content)
audience: ALL (Director, PM, Agents) — read after 00_STATE, before/with P0
status:   DRAFT | ACTIVE v<x.y>
parent:   P0
```

> **What this file is.** This is the *only* file you write to point the research framework
> (`01_PROTOCOLS/P0…P6`, `DIRECTORS_MANUAL.md`, `LESSONS_CORE.md`, `AGENTS.md`) at a new domain.
> The framework files contain **slots** — named references of the form `PROJECT §<n>` — and this
> file fills every one of them. If a framework file and this file conflict on domain content, this
> file wins **for domain instantiation only**; the framework still wins on method and process
> (P0 §7). Nothing in this file may weaken a Law, a gate, or the review standard — it may only say
> what they *mean here*.
>
> **How to use it.** Easiest path: run `00_GENESIS.md` and let an AI author this file with you, section
> by section, then seed the runtime from it. By hand: copy this template to `docs/00_PROJECT.md`, fill
> every section, and delete the guidance blockquotes. Any section you cannot yet fill is written
> `TBD — <what unblocks it>`; a `TBD` in a gate-bearing slot (§5, §6, §8, §10) blocks the tracks that
> depend on it, exactly like a failed prerequisite. The **Slot Index** at the bottom is your
> completeness check: every framework reference must resolve to a filled section here.

---

## 1. Identity & purpose  ·  *fills P0 §1, `README.md`, `00_STATE` header, `DIRECTORS_MANUAL` intro*

> One paragraph, falsifiable where possible: what question the program answers, and the one-line
> test of success. Then the domain in a sentence, and what is explicitly **out of scope** until a
> named gate passes. Keep it to a screen — the depth lives in the state-of-science / landscape doc a
> scoping track produces, not here.

**Program name:** <name>
**Purpose:** <the question, concretely stated>
**Success is:** <the one measurable thing that would count as a result>
**Out of scope until <gate>:** <downstream ambitions the program must not drift into>

---

## 2. Unit of study & vocabulary  ·  *fills P0 §3 (repo map), §4.1; P1 §5, §9; the register name*

> The framework is written in terms of a generic **track** that moves through a lifecycle. Name what
> a track *is* in your domain and the noun you'll use for it everywhere. This decides the register
> filename, the track-id prefix, and the Step-0 gate-document name.

| Framework generic | This program |
|---|---|
| a **track** studies … | < a hypothesis / a component model / a corpus effect / … > |
| track-id prefix | < e.g. `H-`, `M-`, `C-` > |
| the register of all tracks (`02_PROGRAM/…`) | < `HYPOTHESIS_REGISTER.md` / `MODEL_REGISTER.md` / … > |
| the Step-0 gate document (P1 §5) | < `STUDY_THESIS.md` / `MODEL_THESIS.md` / … > |
| register row schema (P1 §9) | `\| <id> \| name \| one-line claim \| <domain field> \| state \| named baseline \| outcome \|` |
| `<domain field>` domain enum | < e.g. component ∈ {…} / signal-family ∈ {…} / n/a > |

---

## 3. Staging & gates  ·  *fills P0 §1 (staging), §4.1; P2 §8; `00_STATE` program map*

> Most programs stage themselves so early cheap work gates expensive later work. State the phases,
> and for each, its **exit gate**: either a numeric validation gate (P2 §7) or a **Director-approved
> plan** (a scoping gate, P2 §8). If you have a literature/selection-first phase, define it here — it
> is L-08 operationalized, and it is where "an afternoon of reading beats a month of code" lives.

- **Phase 0 — <name>** *(gate: <Director-approved plan | numeric>)* — <what it must deliver>
- **Phase 1 — <name>** *(gate: <…>)* — <…>
- **Phase 2 — <name>** *(gate: <…>)* — <…>
- **Phase N — Downstream** — *out of scope until Phase <k> gate passes.*

**Selection/scoping gate (P2 §8), if any:** <the exact deliverables the Director approves to exit the
scoping phase: corpus + landscape + per-candidate feasibility verdict + prioritized thesis slate — or
"none; the program has no scoping phase".>

---

## 4. Study designs  ·  *fills P2 §1, P1 §6 (prereg `DESIGN:` field)*

> P2 §1 gives the *skeleton* every study shares (held-out prediction, one primary criterion, a
> matched-complexity baseline, pre-registration). Instantiate the concrete **designs** your studies
> take. Most programs have 2–3. For each, say what the unit of analysis is, what the held-out set is
> held out *over* (individuals? sources? time?), and what the primary criterion measures.

**Design A — <name>:** <unit of analysis; what it predicts; what "held-out" means here; primary
criterion form>.
**Design B — <name>:** <…>.
*(add designs as needed)*

Every `PREREGISTRATION.md` names its design as one of the above (P1 §6). A study that fits none of
these needs a new design added here first (PM proposes; Director approves per P0 §7 since it touches
P2).

---

## 5. Law instantiations  ·  *fills P0 §5 (Laws 1, 5, 6, 7)*

> The ten Laws are domain-general and **may not be edited here**. But four of them are stated in the
> framework with a domain slot; fill each. Keep the safeguard at full strength.

- **Law 1 — the split.** The data for a track is split into a **calibration set** (free use for
  fitting/tuning) and a **held-out validation set**. Here that split is over: <individuals /
  sources / time windows / species / …>, target held-out fraction <~40%>, stratified by <tier,
  source, biological unit, …>. "Peeking before lock" concretely means: <…>.
- **Law 5 — validated inputs only.** No fitting/validation on inputs that failed their quality gate.
  The quality gates that apply here are: <e.g. digitization-agreement gate for parameters read off
  figures; render-and-recover F1 gate for any feature extractor scoring model output; price/render
  determinism; …>. List each and the section (§8/§9) that defines its threshold.
- **Law 6 — provenance tiers.** Define the tier ladder for this domain, most-trusted first, and the
  conservative-assignment rule. Example shape: `Tier 1 = <direct measurement>`, `Tier 2 = <published
  derived / already-fitted>`, `Tier 3 = <recordings / observational, target-only>`, `Tier 4 =
  <synthetic / model-generated>`. Tier is fixed at ingest, never at analysis.
- **Law 7 — the matched-complexity baseline.** What a "physics-free / mechanism-free baseline of
  matched complexity" *is* in this domain, and how its free-parameter count is made ≥ the model's:
  <e.g. a black-box regressor / an interpolation table / a density-matched null / a DDSP re-synthesis
  at equal parameter count>. The baseline is named at THESIS stage, never discovered at validation.

---

## 6. Canonical schema(s)  ·  *fills P3 §2*

> The program's spine: the typed record(s) that all analysis and synthesis run on, never ad-hoc
> arrays. List each schema, its required fields (with units where numeric), its validators, and its
> round-trip test. A field-free "we'll structure it later" is a gate failure waiting to happen.

**Schema <name>:** required fields `<field: type/units>`, …; validators reject `<invalid cases>`;
round-trip test = <serialize→deserialize→identical on a property-generated set>.
*(add schemas as needed — e.g. a parameter schema and a signal/state schema)*

Schema changes are PM-only, versioned in the schema file; every record carries `schema_version`.

---

## 7. Reproducibility / determinism surface  ·  *fills P3 §5*

> P3 §5 requires that whatever *generates* your analyzable artifacts be deterministic and
> manifest-pinned. Name the surface. In a modeling program this is the **solver** (commit, timestep,
> sample rate, seed, patch); in a corpus program it is the **snapshot** (immutable data pull id); in
> a market program it was the **price/render** step. State what must be pinned and where the
> cross-implementation / reproduction fixture lives.

**Determinism surface:** <the harness / snapshot / render step>.
**Pinned in config + manifest:** <the exact list — solver id+version, timestep, sample rate, seed,
patch; or snapshot hash; …>.
**Cross-implementation / reproduction fixture:** <the second independent implementation used only for
the robustness check and red-team item 8, and its agreement tolerance — or n/a with reason>.

---

## 8. Domain gate types  ·  *fills P3 §4 (`run_gates`)*

> The framework defines the **universal** gate types (`env_var_set`, `file_exists_nonempty`,
> `schema_valid`, `source_reachable`, `split_locked`). Add the domain-specific ones your pipeline
> must refuse past, each with what it checks and its threshold source. There is no force flag for any
> of them (P0 Law 2).

| Gate | Checks | Threshold from |
|---|---|---|
| `<e.g. units_valid>` | <every parameter carries declared units + passes range checks> | <config> |
| `<e.g. agreement_min>` | <digitization re-check agreement ≥ threshold (§9)> | <prereg / config> |
| `<e.g. recovery_min>` | <feature-extractor render-and-recover accuracy ≥ threshold> | <prereg> |
| `<e.g. coverage_min>` | <per-source / per-unit count ≥ threshold> | <prereg / config> |

---

## 9. Bias safeguards & red-team specifics  ·  *fills P2 §4, P2 §6*

> P2 §4 is the confound catalogue and P2 §6 the red-team checklist; both are stated generically in
> the framework and instantiated here. For each core lesson (LESSONS_CORE L-01…L-08) state its
> **domain analog** — the concrete way that failure shows up in *this* data — and the design element
> that kills it. Then add any domain-only safeguards (e.g. a coupling/separability caution).

- **L-01 analog (unvalidated inputs):** <…>
- **L-02 analog (reachability/credentials/gates):** <…>
- **L-03 analog (single-split fragility):** <leave-one-…-out sweeps over …>
- **L-04 analog (convenient joins / leakage):** <…>
- **L-05 analog (means hide dispersion):** <per-source distribution + resampled CI over …>
- **L-06 analog (multiplicity):** <one primary criterion; the rest exploratory / FDR-controlled>
- **L-07 analog (coverage artifacts):** <per-source / per-unit counts mandatory in every ingest>
- **L-08 analog (selection needs a gate):** <the scoping phase in §3>
- **Domain-only safeguards:** <e.g. source–filter separability caution; regime dependence; …>

**Red-team tier/leave-one-out specifics (P2 §6 items 4–5):** the "most-represented source/unit" here
is <…>; the "trusted-tier-only" subset here is <…>.

---

## 10. Standing decision gate  ·  *fills P2 §7*

> The default numeric bar a study clears unless its pre-registration overrides it. Keep the rows the
> framework mandates (held-out tolerance, baseline margin, over-fit bound, data sufficiency, input
> validation, red-team) and fill the domain metric names.

| Criterion | Threshold |
|---|---|
| Held-out error, primary metric | ≤ pre-registered tolerance (named per study, never post-hoc) |
| Margin over matched-complexity baseline | ≥ pre-registered margin (Law 7) |
| Calibration-vs-held-out gap | ≤ pre-registered over-fitting bound |
| Data sufficiency | ≥ pre-registered minimum <unit> per held-out cell |
| Input validation | <the §5 Law-5 quality gates> PASSED for this study's inputs |
| Red-team | all 8 items pass (P2 §6) |

---

## 11. Director-gated items  ·  *fills `DIRECTORS_MANUAL` §3, P4 §2.9*

> What only the human approves in this domain. The framework already reserves protocol changes
> (P0/P2), the kill switch, and branch merges. Add the domain's money/credentials/licensing/ethics
> items so agents and the PM route them correctly.

- Spend ceilings: <paywalled datasets, participant payments, compute — with who sets the euro/$ cap>.
- Credentials / accounts: <the env-var-named secrets; account creation>.
- Licensing / release: <what leaves the loop — dataset release, publication, tool launch, any
  copyrighted/licensed material leaving the machine>.
- Human-subjects: <any perceptual/behavioral study — participants, payment, ethics>.

---

## 12. Domain lessons  ·  *seeds `02_PROGRAM/LESSONS.md`, extends `LESSONS_CORE.md`*

> `LESSONS_CORE.md` carries the inherited, cross-program lessons (L-01…L-08) that bind every program.
> New lessons this program learns start at **L-09** and are appended to `02_PROGRAM/LESSONS.md` at
> runtime (never here — this file is domain instantiation, not a runtime log). Seed here only the
> **domain analogs** already known at kickoff (they also appear inline in §9).

*(No runtime lessons yet at kickoff. New program lessons begin at L-09 in `02_PROGRAM/LESSONS.md`.)*

---

## 13. Infrastructure catalogue (seed)  ·  *seeds `02_PROGRAM/INFRASTRUCTURE_REGISTER.md`, `05_INFRA/BRIEF.md`*

> The capabilities this domain needs before tracks can run (harvesters, schema modules, harnesses,
> extractors, manifest/gate machinery, digitization tools). This is a *seed* for the runtime
> infrastructure register; the PM maintains the live register per P1 §9. List capability + one-line
> purpose + what it blocks.

| ID | Capability | Blocks |
|---|---|---|
| `I-001` | <…> | <…> |
| `I-002` | <…> | <…> |

---

## Slot Index (completeness check)

> Every domain reference in the framework must resolve to a filled section above. If any framework
> file cites `PROJECT §n` and §n is `TBD`, the program is not bootable for the tracks that depend on
> it. This mirrors the PM sufficiency self-check (P0 §6).

| Framework file · location | Slot | This file §  | Filled? |
|---|---|---|---|
| P0 §1 Purpose | program purpose & staging | §1, §3 | ☐ |
| P0 §3 repo map | register name, track-id prefix, thesis doc name | §2 | ☐ |
| P0 §4.1 lifecycle | track noun, scoping-vs-numeric gate | §2, §3 | ☐ |
| P0 §5 Law 1 | calibration/held-out split semantics | §5 | ☐ |
| P0 §5 Law 5 | validated-input quality gates | §5, §8, §9 | ☐ |
| P0 §5 Law 6 | provenance tiers | §5 | ☐ |
| P0 §5 Law 7 | matched-complexity baseline | §5 | ☐ |
| P1 §5 | Step-0 thesis document name & fields | §2, §4 | ☐ |
| P1 §6 | prereg `DESIGN:` options | §4 | ☐ |
| P1 §9 | register row schema / enum | §2 | ☐ |
| P2 §1 | study designs | §4 | ☐ |
| P2 §4 | bias-safeguard domain analogs | §9 | ☐ |
| P2 §6 | red-team leave-one-out / tier specifics | §9 | ☐ |
| P2 §7 | standing decision gate metrics | §10 | ☐ |
| P2 §8 | scoping/selection gate deliverables | §3 | ☐ |
| P3 §2 | canonical schema(s) | §6 | ☐ |
| P3 §4 | domain gate types | §8 | ☐ |
| P3 §5 | determinism surface | §7 | ☐ |
| P4 §2.9 | Director-gated items | §11 | ☐ |
| DIRECTORS_MANUAL §3 | Director-gated items | §11 | ☐ |
| LESSONS_CORE | domain analogs | §9, §12 | ☐ |

## Changelog
- v<x.y> — <program> issue. <what was instantiated>.

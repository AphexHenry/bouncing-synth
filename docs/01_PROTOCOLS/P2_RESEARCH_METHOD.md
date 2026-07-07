# P2 — RESEARCH METHOD PROTOCOL

```
doc_id:      P2
layer:       protocol
audience:    PM (full). Agents read a section only when a TASK cites it.
status:      ACTIVE v1.0 (framework — domain-free; changes require Director approval)
kind:        FRAMEWORK — reused verbatim. Domain designs/safeguards come from 00_PROJECT.md.
parent:      P0
```

This is the program's scientific law. Its safeguards were forged in predecessor programs
(`LESSONS_CORE.md`, L-01…L-08) and are stated here **domain-free**. The central fact they defend
against is invariant across domains: *a model with enough free parameters can reproduce almost any
target, so "it matches" is never evidence* — only held-out generalization, measured against a baseline
of equal flexibility, is. The concrete shape this takes in the current program — the study designs,
the confound catalogue, the numeric bar — is instantiated in **`00_PROJECT.md`** and referenced by
slot below. This protocol is enforced by the pipeline (P3) wherever possible and by the PM everywhere
else.

---

## 1. The shape of every study

Every study, whatever its domain design, shares one skeleton:

1. **A declared unit of analysis** — what one data point *is*, and what constrains it (a measurement,
   an outcome, an observation). Stated with its provenance tier (`PROJECT §5`, P3 §2).
2. **Every claim is a held-out prediction.** Free parameters are fixed on a **calibration set**; the
   claim is tested only on a **held-out validation set** (different individuals / sources / conditions
   / time — see §3). The gate is a pre-registered error tolerance on the held-out set, *and* a
   required margin over the matched-complexity baseline (P0 Law 7).
3. **The model form is frozen in the pre-registration.** A term added, or a parameter freed, after
   seeing the held-out set is exploratory by definition and cannot count toward the gate.
4. **The matched-complexity baseline (P0 Law 7) is mandatory.** For every model with *k* free
   parameters, a mechanism-free baseline with ≥ *k* free parameters (construction per `PROJECT §5`) is
   fit on the same calibration set and scored on the same held-out set. If the model does not beat it
   by the pre-registered margin, the mechanism is not doing explanatory work — the claim fails,
   regardless of absolute fit.
5. **Reporting:** held-out error with a dispersion measure (bootstrap or leave-one-source-out CI), the
   calibration-vs-held-out error gap (an over-fitting diagnostic), the per-condition breakdown, and a
   parameter-sensitivity table (which parameters the fit identifies vs which are unconstrained).
   Aggregate errors always carry the per-source distribution — a good mean carried by one well-fit
   source is not generalization. (LESSONS_CORE L-05.)

The **concrete designs** a study may take — their names, their units of analysis, what "held-out" is
held out over, and the form of the primary criterion — are defined in **`PROJECT §4` (Study designs)**.
Every `PREREGISTRATION.md` names its design as one of those (P1 §6). A study fitting none of them
requires a new design added to `PROJECT §4` first (Director-approved, since it touches P2 — P0 §7).

Two design *families* recur across domains and are worth naming so `PROJECT §4` can specialize them:

- **Component / hypothesis validation** — one mechanism, one measurable it must reproduce on held-out
  data, against a matched-complexity baseline.
- **Integrated / end-to-end validation** — an assembled pipeline generating artifacts (syntheses,
  predictions) compared to real targets on pre-registered feature distances, and where an assumption
  the pipeline rests on (separability, independence, stationarity) is itself put on trial. A failure
  here may KILL the assumption in favor of a coupled/joint formulation (a PIVOT), not a parameter
  tweak. *(Which assumption is on trial, if any, is `PROJECT §9`.)*

## 2. Statistical & error discipline

- **One primary criterion per study**, pre-registered: the held-out error metric and its tolerance,
  plus the required margin over the matched-complexity baseline.
- All other comparisons are **exploratory**: reported as such, FDR-controlled where a p-value is
  involved (Benjamini–Hochberg, q = 0.05), never used for a gate call, never a headline.
  (LESSONS_CORE L-06: chasing many cells destroys credibility; the fix is fewer confirmatory claims,
  not a softer bar.)
- Any exploratory finding that looks interesting becomes the *primary* criterion of a **new
  pre-registration on fresh or held-out data** — it cannot be promoted retroactively.
- **Uncertainty is mandatory on every reported error.** Prefer resampling (bootstrap over sources,
  leave-one-source-out) that respects the small, non-iid nature of real data. A point error with no
  dispersion is not a result.
- **Absolute fit and relative-to-baseline margin are always reported together.** A model can be
  absolutely accurate yet add nothing over the baseline (fails Law 7), or beat the baseline yet be too
  inaccurate to use (fails tolerance). Both bars must clear.

## 3. Calibration / held-out discipline

- The moment a study's data reaches its pre-registered minimum, the pipeline splits it (seeded,
  manifest-logged) into a **calibration set** (free use for fitting) and a **held-out validation set**
  (target ~40%, untouched). The split is stratified by provenance tier and, wherever possible, by
  **source and biological/temporal unit** (`PROJECT §5`): a source or unit in calibration should not
  appear in held-out, so the test measures generalization, not memorization (see §4.5).
- Confirmatory error metrics run on the held-out set only, only after `PREREGISTRATION.md` is LOCKED
  (P0 Law 1). Accidental contact = the set is journaled as contaminated; the remedy is new data, not
  forgiveness.
- **Robustness over single splits** (LESSONS_CORE L-03): every confirmatory result is accompanied by a
  **leave-one-source-out** (and, where data allows, leave-one-unit-out) sweep on the calibration set
  at pre-registration time, so fragility is known before the held-out run, and by red-team item 4
  after it.

## 4. Bias safeguards (mandatory, checked at brief-writing and at gate review)

The safeguards below are domain-free requirements; how each failure *shows up in this program's data*,
and the design element that kills it, is instantiated in **`PROJECT §9`** (one analog per core lesson).

### 4.1 Input quality gate
Every input that a model is fit on or scored against must first pass a domain quality gate before it
enters `data/…` — e.g. a digitization-agreement check for values read off figures, a
render-and-recover check for any extractor scoring model output, a schema/units check for parameters.
The gates and thresholds are `PROJECT §8`; below threshold the batch is quarantined and the
*procedure*, not the data, is fixed first. (P0 Law 5.)

### 4.2 Instrument validation (measurement of the measurement)
Any extractor/estimator used to *score* output must first demonstrate, on synthetic inputs where
ground truth is known, accuracy ≥ the pre-registered threshold across the full parameter grid — and,
where a determinism surface exists (`PROJECT §7`), on output from a second independent implementation
(cross-implementation robustness, P3 §5). A failing instrument blocks validation; it does not lower
the bar.

### 4.3 Over-fitting / degrees-of-freedom confound
The matched-complexity baseline (§1.4, P0 Law 7) is the control for "the model fits because it is
flexible, not because it is right." The baseline's free-parameter count must be ≥ the model's; the
brief states both counts and the baseline construction exactly; the baseline ships with a test proving
parameter-count parity.

### 4.4 Source-coverage artifacts (LESSONS_CORE L-07)
Before interpreting any error statistic across sources, units, or conditions, verify it is not a
coverage artifact (one source dominating a tier, one unit standing in for the population, one format
silently dropping data). Per-source and per-unit counts, and per-field fill/coverage, are a mandatory
validation table in every ingest task.

### 4.5 Selection of the sample itself
Which units get measured, which get archived, and which values get published are all biased. Every
study states what its data plausibly over/under-represents and the direction of the induced bias.
Near-duplicate records (the same unit reported in multiple sources, re-shared data) are detected and
collapsed with multiplicity recorded — otherwise one well-studied unit becomes twenty data points.

### 4.6 Leakage
Where a fit could be memorizing per-record constants (a single record's exact value, a source's fixed
offset) instead of the mechanism: performance must hold under leave-one-source-out, and the
parameter-sensitivity table (§1.5) must show the *mechanism's* parameters — not incidental source
fingerprints — carrying the fit. (LESSONS_CORE L-04: convenient joins smuggle in the answer.)

### 4.7 Domain-specific caution
Any structural assumption the program's decomposition rests on (separability, independence,
linearity-in-cascade, stationarity) is stated per brief, with the coupling/dependence it neglects
named. The integrated study (§1) is where that assumption itself is tested; its failure is a PIVOT to
a joint formulation, not a tweak. *(The specific assumption on trial is `PROJECT §9`; if none, write
"n/a".)*

## 5. Gate calls

A **GATE_REVIEW** happens when gate-relevant tasks are DONE, when a kill criterion fires, or when the
pre-registered task-unit budget is exhausted — whichever comes first. The PM's call is one of:

- **KILLED** — tolerance not met, baseline not beaten, or prerequisites structurally unmeetable.
  Requires KILL_REPORT (P1 §8). A success state of the process: it localizes where the mechanism,
  data, or decomposition breaks.
- **PASSED** — all pre-registered criteria met on the uncontaminated held-out set, red-team survived
  (§6). Authorizes only a proposal to the Director.
- **PIVOTED** — the evidence suggests a *different, specific* formulation. The pivot is a new track id
  with its own THESIS; nothing carries over except infrastructure and lessons.

No fourth option exists. "Inconclusive, keep tuning" is not a state; it is either PIVOTED (with a named
new formulation) or KILLED (with reopening conditions recorded).

## 6. Red-team checklist (mandatory before any PASSED call or any surprising positive)

Each item answered in writing with evidence in the gate report:

1. **Input quality** — the `PROJECT §8` quality gates verified on *this* study's inputs specifically,
   with manifest ids?
2. **Baseline** — does the model beat the matched-complexity baseline by the pre-registered margin on
   the held-out set, not just meet an absolute tolerance?
3. **Over-fitting** — is the calibration-vs-held-out gap within the pre-registered bound, and does the
   result survive with near-duplicate records collapsed (multiplicity = 1)?
4. **Source/unit concentration** — remove the single most-represented source or unit (`PROJECT §9`):
   does the result survive (leave-one-out)?
5. **Tier sensitivity** — does the result hold on the most-trusted tier alone (`PROJECT §5`, `§9`)?
6. **Dispersion** — is the per-source error distribution consistent with broad generalization, or is a
   good mean carried by a few well-fit sources?
7. **Sample selection** — what fell out (unavailable data, quarantined batches) and could its absence
   manufacture this result?
8. **Reproduction** — one full re-run from manifests by a *different* agent, numbers matching; and,
   where a determinism surface exists (`PROJECT §7`), the cross-implementation check agrees within
   tolerance.

A positive that fails any item is not PASSED; it is PIVOTED (to a design that fixes the item) or KILLED.

## 7. Standing decision gate (program default, overridable per pre-registration)

The default numeric bar is instantiated in **`PROJECT §10`**. It must retain these rows; the module
fills the domain metric names:

| Criterion | Threshold |
|---|---|
| Held-out error, primary metric | ≤ the pre-registered tolerance (named per study; never post-hoc) |
| Margin over matched-complexity baseline | ≥ the pre-registered margin (P0 Law 7) |
| Calibration-vs-held-out gap | ≤ the pre-registered over-fitting bound |
| Data sufficiency | ≥ the pre-registered minimum per held-out cell, verified before lock |
| Input validation | the `PROJECT §8` quality gates PASSED for this study's inputs |
| Red-team | all 8 items pass |

## 8. Selection / scoping gate (the "cheap-reading-first" rule)

If `PROJECT §3` defines a scoping/literature-first phase, that phase has no numeric validation gate;
its gate is a **Director-approved plan**. The scoping track is DONE when it delivers, and the Director
approves, the deliverables listed in `PROJECT §3` — typically: (a) a harvested, deduplicated corpus
with provenance; (b) a landscape mapping what is established, contested, and unaddressed, with
citations; (c) a per-candidate **data-feasibility verdict** (is there enough reachable, trusted data
to calibrate *and* hold out?); and (d) a prioritized, scoped slate of THESIS candidates with the
program's stated limits. A candidate whose feasibility fails is parked in the register with the gap
that would reopen it, not specced. This is LESSONS_CORE L-08 operationalized as a program phase.

## Changelog
- v1.0 — Framework issue. Study "shape" generalized to a domain-free skeleton (§1) with the two
  recurring design families named and delegated to `PROJECT §4`; the density-matched/matched-complexity
  baseline kept domain-free (§1.4, §4.3); input-quality and instrument-validation gates delegated to
  `PROJECT §8`/`§9` (§4.1–4.2); the structural-assumption caution generalized (§4.7); the decision-gate
  metric names and scoping deliverables delegated to `PROJECT §10`/`§3` (§7, §8). Safeguards
  L-01…L-08 cited from `LESSONS_CORE.md`.

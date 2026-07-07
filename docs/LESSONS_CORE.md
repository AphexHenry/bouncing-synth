# LESSONS_CORE (inherited, cross-program; cited by protocols as L-01…L-08)

```
doc_id:   LESSONS_CORE
layer:    protocol (framework)
audience: PM; agents when cited by a TASK
status:   ACTIVE v1.0 (framework — domain-free)
kind:     FRAMEWORK — reused verbatim. Domain analogs live in 00_PROJECT.md §9.
parent:   P0
```

These eight lessons were paid for in failures by predecessor programs and bind **every** program that
uses this framework. They are stated here in **domain-general** form with the original failure named,
so the lesson stays concrete. Each program restates its **domain analog** — the specific way the
failure shows up in its data, and the design element that kills it — in `00_PROJECT.md §9`. The
protocols cite these by L-number; a program's own new lessons begin at **L-09** in
`02_PROGRAM/LESSONS.md`.

---

- **L-01 — An analysis on unvalidated inputs is invalid regardless of its result.** Origin: ~63% of a
  program's events had no usable value because a free source silently lacked part of the population
  (delisted records), turning the sample into survivors-only. The general rule: an input that has not
  passed its quality gate cannot be fit on or scored against; a good-looking result on bad inputs is
  not a weak result, it is a non-result. Enforced by P0 Law 5, P2 §4.1–4.2, P3 §4/§6.

- **L-02 — Verify reachability, credentials, and prerequisites before building anything, and make
  gates halt.** Origin: an entire feature layer was built around a dataset that was empty because no
  API key was set; prerequisites were prose and the pipeline only warned. A common special case: APIs
  with a "politeness"/contact field silently throttle to a slow tier when that field holds a
  placeholder instead of a real value — a reachability failure to catch up front, not a mystery to
  route around. Enforced by P0 Law 2, P3 §2b.2, P3 §4 (no force flag).

- **L-03 — A single split misleads; test robustness across partitions.** Origin: one in/out-of-sample
  split gave a regime-dependent answer that multi-window testing contradicted. The general rule:
  leave-one-source-out (and, where data allows, leave-one-unit-out) sweeps accompany every
  confirmatory result, and a concentration red-team item checks it. Enforced by P2 §3, §6.4.

- **L-04 — Convenient joins smuggle in the answer.** Origin: current-state metadata joined onto
  historical events injected lookahead — the model was reading the future. The general rule: any join
  or fit that could let a per-record constant or a downstream fact stand in for the mechanism is
  leakage; performance must hold under leave-one-source-out and the parameter-sensitivity table must
  show the mechanism, not fingerprints, carrying the fit. Enforced by P2 §4.6.

- **L-05 — Means without dispersion hide skew.** Origin: a positive mean with a ~44% success rate —
  tail-skew sold as edge. The general rule: every reported error carries its per-source distribution
  and a resampled CI; a good mean carried by one well-fit source is not generalization. Enforced by
  P2 §1.5, §2, §6.6.

- **L-06 — Multiplicity discipline: one pre-registered primary criterion, exploratory for the rest.**
  Origin: chasing many cells made real effects undetectable and uncredible; the remedy is fewer
  confirmatory claims, not a softer bar. Enforced by P2 §2.

- **L-07 — Coverage artifacts masquerade as findings.** Origin: a source going stale mid-sample turned
  later years into a different population, and the shift read as a trend. The general rule: per-source
  and per-unit counts and per-field coverage are mandatory in every ingest validation, so the
  population is never silently one source's slice. Enforced by P2 §4.4, P3 §2b.5.

- **L-08 — Selection needs a gate too — an afternoon of reading beats a month of code.** Origin:
  predecessors' killed hypotheses came disproportionately from the most crowded, most productized
  corner of the data space — knowable in advance from the literature. The general rule: where a
  program's search space is large, a scoping/literature-first phase harvests the landscape and proves
  data feasibility for each candidate *before* any track is specced. Operationalized by the Step-0
  novelty + data-feasibility check (P1 §5) and the scoping gate (P2 §8).

## Changelog
- v1.0 — Framework issue. L-01…L-08 lifted to domain-general form; per-domain re-expressions moved to
  `00_PROJECT.md §9`. The lessons themselves are unchanged in force.

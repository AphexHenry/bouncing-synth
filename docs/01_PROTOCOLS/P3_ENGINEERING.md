# P3 — ENGINEERING PROTOCOL

```
doc_id:      P3
layer:       protocol
audience:    Agents (full) and PM
status:      ACTIVE v1.0 (framework — domain-free)
kind:        FRAMEWORK — reused verbatim. Schemas/determinism/gate-types come from 00_PROJECT.md.
parent:      P0
```

This protocol tells agents exactly where things live, how to fetch and store data, and what the
pipeline must refuse to do. It is written to be followed literally. When this protocol and a TASK
brief conflict, stop and file a BLOCKED report (P4 §3).

The **canonical schema(s)** (`PROJECT §6`), the **determinism surface** (`PROJECT §7`), and the
**domain gate types** (`PROJECT §8`) are the three things this protocol delegates to the module;
everything else here is domain-free.

---

## 1. Code and data layout (inside the research codebase, separate from the document repo)

```
src/<package>/            ← library code. No script writes outside the paths below.
config/<track>.yaml       ← one config per track; every constant, tolerance, and setting lives here,
                            never hardcoded.
data/raw/<source>/        ← exactly what was fetched/received, byte-for-byte, never modified. Every
                            fetch cached here so re-parses never re-hit a server. Each source
                            directory carries a SOURCE.yaml (§2b.6).
data/<domain-lanes>/      ← the domain's working data lanes (e.g. a literature corpus, a parameter
                            store, a recordings store, simulation outputs). Named and described in
                            PROJECT §6. The calibration/held-out split marker (P2 §3) lives with the
                            canonical data, written once by the seeded split task.
data/processed/<track>/   ← parquet outputs of feature/analysis/validation steps. Schema documented in
                            the producing task report.
reports/                  ← CSVs, analysis outputs, figures, tables.
reports/manifests/        ← run manifests (§3).
tests/                    ← every new module ships with unit tests; a task is not DONE with failing tests.
```

Rules: raw is immutable; everything else is regenerable from raw + config + code; anything not
regenerable from raw + config + code is a bug. Do not delete caches; do not "clean up" files your task
didn't create.

## 2. The canonical schema(s) (the program's spine)

All analysis and generation run on **typed records defined in `PROJECT §6`**, never on ad-hoc arrays.
Each schema there names its required fields (with units where numeric), its validators, and its
round-trip test. Framework requirements on any schema, whatever the domain:

- Every record carries provenance (a `source_id` and a `provenance_tier` per `PROJECT §5`) and a
  `schema_version`. A record without provenance does not enter `data/`.
- Numeric fields carry **units**, and units are enforced, not decorative. Structural + domain
  validators reject impossible values (the invalid-case list is in `PROJECT §6`).
- Each schema module ships **round-trip tests** (serialize → deserialize → identical). A parser or
  writer without a passing round-trip test does not ingest or emit.
- Schema changes are PM-only, versioned in the schema file; every record carries `schema_version`.

## 2b. Data sourcing rules (for agents)

1. Use **only** the sources listed in your TASK's `inputs:`. If a source is down, wrong, paywalled, or
   different from described: STOP → BLOCKED report. Do not substitute a source you found yourself.
   (P0 Law 4)
2. Before any bulk fetch, run the reachability check for the source (HTTP status with the project's
   request headers; for archives/APIs, one test record). Paste the result in your task report. If it
   fails: BLOCKED report — this catches 403s, dead DOIs, and API-key problems before hours of work.
   (LESSONS_CORE L-02.) **Note:** any API that requires a real contact/politeness field to reach its
   fast tier is supplied that value via the env var named in the brief — a placeholder triggers silent
   throttling and is treated as a misconfiguration, not a workaround target.
3. Credentials and contact values come **only** from environment variables named in the brief. If the
   variable is unset: BLOCKED report. Never embed keys or emails in code, configs, or reports.
4. Rate-limit conservatively (default: ≤1 request/second unless the brief says otherwise; honor
   documented API tiers); cache every response to `data/raw/` on first fetch.
5. Every ingest task produces a **validation table** in its report: record counts per source and per
   provenance tier, per-field coverage/fill, % records failing schema or units validation with
   reasons, duplicate-detection counts, and a ≥25-record random sample manually checked against the
   source of record with the mismatch count stated. (LESSONS_CORE L-07.)
6. **Licensing/provenance record.** Every source directory carries `SOURCE.yaml`: origin
   URL/DOI/vendor, license or terms as understood, date acquired, redistribution allowed
   (yes/no/unknown → treated as no), and whether raw content may leave the local machine (default no).
   Third-party and copyrighted content is **local-only**: never committed, never pasted into reports,
   never included in OUT files. Reports reference it by path + hash. Publication/release of anything
   derived is a Director decision (`PROJECT §11`), never a task step.

## 3. Run manifests (implements P0 Law 3)

Every command that produces a result writes `reports/manifests/<run_id>.json`:

```
run_id, timestamp_utc, git_commit, git_dirty (bool),
resolved_config (full, post-overrides),
input_files: [{path, sha256}], data snapshot hash + split marker hash,
generator: {<the PROJECT §7 determinism surface's pinned fields — e.g. solver+version+timestep+
            sample_rate+seed+patch, or snapshot id>} when generation was involved,
python_version, key_package_versions,
output_files: [{path, sha256}]
```

- Every output CSV carries its `run_id` (column or header line). Every number quoted anywhere cites
  its run_id.
- `reproduce <run_id>` re-executes from a manifest and diffs outputs; on mismatch it names the
  diverging input hash.
- If the git tree is dirty, the run refuses to start unless the config sets `allow_dirty: true`, and
  such runs are marked **non-citable** in the manifest. Non-citable numbers never appear in reports or
  journals.

## 4. Hard prerequisite gates (implements P0 Law 2)

Every track config carries a `prerequisites:` block, checked by a shared `run_gates(config)` at the
top of every analysis/generation entry point. The **universal** gate types (present in every program):

| Gate | Checks |
|---|---|
| `env_var_set` | credential / contact / env variable present and non-empty |
| `file_exists_nonempty` | a required data/parquet file exists with > 0 rows |
| `schema_valid` | 100% of a named file passes schema validation + round-trip |
| `source_reachable` | HTTP/DOI/API check passes for a named source |
| `split_locked` | the calibration/held-out split marker exists and its hash matches the pre-registration |

The **domain gate types** (e.g. `units_valid`, `agreement_min`, `recovery_min`, `coverage_min`) are
defined in **`PROJECT §8`** and enforced the same way. On any failure: print **all** failed gates,
exit non-zero, write `reports/gate_failure_<run_id>.json`, and the agent files a BLOCKED report.
**There is no force flag.** If a gate is wrong, the fix is a config change proposed to the PM
(git-visible), never a bypass.

## 5. Generation determinism (implements P0 Law 3 for anything the program *produces*)

Whatever the program generates for analysis or as stimuli — simulations, syntheses, snapshots,
renders — goes through the **determinism surface named in `PROJECT §7`**, with these framework rules:

- The surface is **pinned**: the exact fields `PROJECT §7` lists (solver/version, timestep, sample
  rate, seed, patch; or snapshot id; etc.) are fixed in config and recorded in every manifest. A run
  whose manifest lacks them is non-citable. Nothing generates ad hoc outside the surface.
- The **cross-implementation / reproduction fixture** (`PROJECT §7`) — a second independent
  implementation behind the same interface — exists solely for the robustness check (P2 §4.2) and
  red-team item 8. It is never the primary; divergence from the primary beyond tolerance is a BLOCKED
  condition, not a silent average.
- Any stimulus used for a human-subjects study additionally passes the domain's matching/normalization
  step (config-declared) with measured values in the manifest.

## 6. Input quality (the enforcement side of P2 §4.1–4.2)

- Inputs that enter through a domain quality gate (`PROJECT §8`) enter **only** through the tool that
  enforces the schema and units at input time; free-form files are not accepted into the canonical
  data lanes.
- Double-check batches (P2 §4.1) are assigned to a *different* agent than the original; the agreement
  computation is a pipeline step with a manifest, not a hand calculation.
- Labels/features used to score output carry `extraction_method: pipeline` plus the extractor run_id;
  the recovery/accuracy gate (§4, `PROJECT §8`) is checked against that extractor version specifically
  — a retrained/re-tuned extractor re-qualifies from scratch.

## 7. Definition of DONE (agents)

A task is DONE only when, in the task report (P1 §7): every acceptance criterion has pasted evidence;
all unit tests pass (output pasted); every artifact path listed; all numbers carry run_ids; every
record carries units + provenance; any deviation from the brief carries a PM approval reference.
Otherwise the honest states are IN_PROGRESS, BLOCKED, or FAILED — all three are acceptable; a hollow
DONE is not.

## Changelog
- v1.0 — Framework issue. Schema section (§2) generalized to "the schema(s) defined in `PROJECT §6`"
  with the domain-free requirements (provenance, units, round-trip) retained; data lanes delegated to
  `PROJECT §6` (§1); manifest generator block and the whole determinism section (§5) delegated to the
  `PROJECT §7` surface (replacing the hardcoded solver/price-render laws of the lineage); gate table
  split into universal types (here) and domain types (`PROJECT §8`).

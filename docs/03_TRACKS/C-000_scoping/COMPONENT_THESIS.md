# THESIS — C-000 Phase-0 scoping

```
doc_id:   C-000-THESIS
layer:    track
audience: PM, Director
status:   ACTIVE
parent:   PROJECT §3
```

1. CLAIM            — Phase 0 can deliver, from desk research alone, the four deliverables of
                      PROJECT §3: (a) prior-art landscape of physics sequencers/instruments;
                      (b) numerics decision memo (curve representation, root-solving strategy,
                      FP-determinism plan, tie-breaking rules); (c) architecture plan (headless core
                      + thin JUCE shell); (d) prioritized component slate with acceptance-criteria
                      sketches — in a form the Director can approve as the Phase-0 exit gate.
2. NOVELTY CHECK    — n/a — this track *is* the program's novelty check (L-08); its deliverable (a)
                      is the prior-work trail for every downstream component thesis.
3. CONFOUND SKETCH  — n/a — no numeric claim is made; the scoping gate is a Director-approved plan,
                      not a validation result (P2 §8). No baseline applies (register row: n/a).
4. DATA FEASIBILITY — sources are public literature and documentation (physics-sequencer prior art,
                      JUCE documentation, numerical-methods references), reachable by the PM, which
                      authors deliverables (a)–(d) itself; reachability evidence (URLs consulted) is
                      carried inside each deliverable at presentation. Agent-side feasibility for
                      Phase 1 (toolchain present in the workspace) is what C-000-T1 records.
5. SCALE & COST     — zero spend (PROJECT §11): public sources, FOSS toolchain. No purchases.
6. KILL SKETCH      — the track dies if desk research shows the core bet (real-time analytic
                      collision solving on exact curves) is already met by an existing FOSS project
                      Bounce cannot meaningfully differ from, or is infeasible within the real-time
                      budget on commodity CPUs — either finding goes to the Director with evidence.
SCORE (PM):         — prior: mandatory (P2 §8) / reuse: high (landscape feeds every thesis) /
                      moat: n/a / risk: low — desk research only.

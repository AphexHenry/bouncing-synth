# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_54 review — AMEND + RETURN scoped (c3 PM
authoring defect → c3-v2; c6 L-15 remediation); repairs ride PACKET 55; I-008-T1 dispatched

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — D-4 step 1 SUBSTANTIVELY COMPLETE, evidentiary repair pending. C-001-T17 fixed
the contact loop on fresh calibration evidence: E1/E2/E3 all GREEN (4/4 CF fixtures; exact
event-count equality; worst |Δt| 1.44e-13, worst |Δs| 4.51e-14 across fixtures; CF-E3 at
5.6e-16), permanent invariants added (per-ball strictly increasing t; no consecutive
duplicate (t_hex, s_hex)), 63/63 doctest, FL-1/PB-1 exact, repeat-identity N=3, ACCESS_LOG
88 before and after. OUT_54 verdict: AMEND + RETURN scoped to criterion 3 (PM authoring
defect — "E1 zero events" demanded an empirical manifestation; corrected text c3-v2 in
JRN-C001-95) and criterion 6 (invariant test names absent from the doctest output artifact;
present verbatim in the TR → L-15 remediation). Both repairs ride PACKET 55 steps 4–5; T17
→ VERIFIED at OUT_55 review if they land.

D-4 step 2 IN FLIGHT: I-008 bounce-view (native C++/SDL2 assessment harness) — TASK
I-008-T1 dispatched (PACKET 55). D-4 step 3 (P1-B/P1-C + gate-resumption governance
bundle) follows the Director's AV assessment.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | CONTACT LOOP FIXED on calibration evidence (T17); falsification record JRN-C001-91 stands for the pre-T17 build; evidentiary repair pending (OUT_54 c3/c6) | T17 VERIFIED at OUT_55 → gate-resumption bundle | OUT_55 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | BRIEFED — T1 IN FLIGHT (PACKET 55) | Director AV assessment → D-4 step 3 | OUT_55 |

## Open decisions (Director)
1. GitHub hosting + CI for I-007 — ESCALATED.
2. Protocol amendment bundle (P6 §4.6, §7.4, §7.5; P5 §2 ledger/courier; P6 §4 judge-side
   shape coverage per L-17; P6 §4 delta-scoped workspace criteria per L-13 v2) —
   non-blocking.
3. GPLv3 -only vs -or-later — Phase 3.
4. Corpus governance at gate resumption: corpus-A is DEVELOPMENT-EXPOSED at defect-class
   level (T16 D4); confirmatory reuse vs fresh corpus-B mint (I-003 scope).
5. Gate-resumption registration bundle (all to be PRE-registered before any future gate
   execution): simultaneous-contact ordering rule (R-e / HO-flat-periodic-3); periodic
   reference horizons (refs 1–8 events vs §1's H=200 for non-settling orbits); S-1
   post-settle semantics; checker fix + L-17 v2 (window/count/pairing semantics in the
   self-test); P1-B coverage of the T17 time-domain-fallback and directional-search
   branches (JRN-C001-95); held-out re-test of E-classes incl. the two original E3
   scenarios (fixed inferentially only — fresh-fixture evidence).

## Known issues
Engine: E1/E2 fixed with permanent invariants (T17, calibration evidence); E3 green on the
fresh fixture (5.6e-16) — the two original held-out E3 scenarios remain untested until gate
resumption. T17 added a time-domain fallback + directional root search: new determinism
surface, P1-B coverage item (open decision 5). Checker harness (T16 D2/D3): window
shrinkage to min(ref,eng); silent zip-truncation; positional pairing; no simultaneity/wrap
handling — deferred to gate resumption (decision 5). Baseline CLI write failure at N≥512
(outside current path; OUT_45). Validator calibration_scenarios=3 (OUT_47). Resolved:
zero-event write (T14); checker rational parse (T15); contact-loop E1/E2 (T17).

## Recent review verdicts
OUT_54/C-001-T17: AMEND + RETURN scoped to criteria 3 (c3-v2 issued, PM-owned §4.2 defect)
and 6 (L-15 remediation); 8/10 COMPLIANT; substantive fix evidence stands (JRN-C001-95).
OUT_53/C-001-T16: ACCEPT — classification ratified; falsification record (JRN-C001-91).
OUT_52/GATE-P1-R3: task ACCEPT; P1-A verdict inadmissible as registered (JRN-C001-87).

## Pointers
Branch rule: task/I-008-T1 from task/C-001-T17 tip (stacked, JRN-I002-6). Main merges of
task/C-001-T17 and task/I-008-T1 are held until OUT_55 review, then batched. ACCESS_LOG: 88
— must remain 88 through I-008 (no held-out execution until gate resumption; bounce-view
carries a built-in Law-1 path guard, S6). Contamination rule of record: new fixtures never
replicate held-out parameter tuples (JRN-C001-91/92). Falsification record: JRN-C001-91.
Direction of record: D-4. Corrected T17 criterion: c3-v2 (JRN-C001-95). Gate-resumption
bundle: open decisions 4 + 5.

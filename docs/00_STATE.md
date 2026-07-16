# STATE — Bounce
last_updated_by: pm-fable5-a | trigger: OUT_53 ACCEPT; classification ratified — physics shortfall STANDS (falsification record JRN-C001-91); Director direction D-4; C-001-T17 dispatched; PACKET 54

```
doc_id:   STATE
layer:    program
audience: ALL — entry point; read first
status:   ACTIVE
parent:   PROJECT
```

## Program status
Phase 1 — FALSIFICATION RECORDED; engineering pivot under Director direction D-4.
T16 forensics classified the P1-A anomalies under the pre-registered rules: R-a=13 ·
R-d=2 · R-e=1 · R-b=0 · R-c=0 — per v1.2 B2 the physics shortfall STANDS. The engine as
built fails the registered P1-A intent on 15/32 held-out scenarios: E1 missed first
contact (×2 zero-event periodic parabola); E2 departure-root re-collision — duplicate
events at identical/ulp-earlier t, non-monotonic per-ball time, premature termination
(×11); E3 value divergence at full windows (×2). The analytic paradigm is not refuted;
the contact loop is. Formal registered verdict deferred until a harness-admissible gate
run exists (checker window/pairing defects confirmed by T16 D2/D3); deferral is
procedural, not softening.

DIRECTOR DIRECTION D-4 (2026-07-16): (1) make the engine functional — C-001-T17 (IN
FLIGHT); (2) minimalist visual/audio assessment harness — I-008 (next brief, PACKET 55;
default spec: native C++/SDL2 linked against bounce-core; live curve+ball render from
closed-form arcs; audio blip per collision, pitch from contact position, velocity from
impact speed); (3) return to determinism (P1-B) and loop stability (P1-C) afterwards with
the gate-resumption governance bundle.

## Active tracks
| track id | state | next transition | waiting on |
|---|---|---|---|
| C-001 Exact collision engine | FALSIFIED AS BUILT (P1-A intent, JRN-C001-91) — T17 contact-loop fixes IN FLIGHT | functional engine → I-008 | OUT_54 |
| C-002 Curve library | BRIEFED | T3 prereg | gate resumption |

C-000 Phase-0 scoping: CLOSED.

## Infra workstreams
| id | state | next transition | waiting on |
|---|---|---|---|
| I-001..I-004 | VERIFIED | — | — |
| I-005 | SPECCED | brief | P1-D addendum timing basis |
| I-006 JUCE scaffold | SPECCED | brief | gate resumption / Director call |
| I-007 CI | SPECCED | brief | Director hosting (open decision 1) |
| I-008 AV assessment harness (bounce-view) | DIRECTED (D-4) — to be registered at its brief | PACKET 55 after T17 ACCEPT | OUT_54 |

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
   post-settle semantics (engine events beyond a settled reference untested by §1);
   checker fix + L-17 v2 (window/count/pairing semantics in the self-test).

## Known issues
Engine contact loop (T16): E1 missed first contact; E2 departure-root re-collision /
non-monotonic t / premature termination; E3 value divergence ×2 — UNDER FIX (T17).
Checker harness (T16 D2/D3): window shrinkage to min(ref,eng); silent zip-truncation;
positional pairing; no simultaneity/wrap handling — deferred to gate resumption (decision
5). Baseline CLI write failure at N≥512 (outside current path; OUT_45). Validator
calibration_scenarios=3 (OUT_47). Resolved: zero-event write (T14); checker rational parse
(T15).

## Recent review verdicts
OUT_53/C-001-T16: ACCEPT — classification ratified; falsification record (JRN-C001-91).
OUT_52/GATE-P1-R3: task ACCEPT; P1-A verdict inadmissible as registered (JRN-C001-87).
OUT_51/C-001-T15: AMEND + RETURN scoped to criterion 7 — repaired at R3 step 4; VERIFIED.

## Pointers
Branch rule: task/C-001-T17 from task/C-001-T16 tip (stacked, JRN-I002-6). ACCESS_LOG: 88 —
must remain 88 through T17 and I-008 (no held-out execution until gate resumption).
Contamination rule of record: new fixtures never replicate held-out parameter tuples
(JRN-C001-91/92). Falsification record: JRN-C001-91. Direction of record: D-4.
Gate-resumption bundle: open decisions 4 + 5.

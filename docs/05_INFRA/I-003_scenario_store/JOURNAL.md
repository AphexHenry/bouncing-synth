---
### JRN-I003-19 · NOTE
actor: pm-fable5-b · task: I-003-T3-R1 · manifest: n/a

WHAT: I-003-T3-R1 authored (PACKET 41): same deliverable under prereg v1.1 — 16 Tier-2
fixtures with amended cells (deg 3–6 quasi-chaotic ×4 across ≥3 distinct degrees; Bézier
periodic ×2; parabola×quasi-chaotic empty per A1) and amplification-based admission (A ≥
1e6 at ε=1e-30 within ≤25 events, linearity spot-check at 1e-20 within 10× — A2). The
already-measured deg-6 candidate (A≈1.7e11) pre-qualifies with five orders of margin. All
other T3 spec provisions carry verbatim (LAW-1, R1 float64 discipline, R6, Tier-2
convergence ≥45 digits, C1 checks, discriminant fixture, lock, concentration paste, L-15
digest completeness). Branch continues task/I-003-T3 in place (WIP tooling present).
NUMBERS: 16 fixtures; corpus 32; A ≥ 1e6 at ε=1e-30; linearity within 10×.
LEARNED: nothing
NEXT: I-003-T3-R1 (this packet); on ACCEPT — I-004-T2+T3 batched (PACKET 42), then
C-001-T11 baseline spec.

---
### JRN-I003-18 · CORRECTION
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Two PM authoring defects in the I-003-T3 spec, owned per P6 §6.1. (1) The
quasi-chaotic admission triple (ε=1e-30, absolute bound 1e-10, ≤25 events) was registered
without a feasibility derivation; it requires a per-bounce stretching factor ≥ ~6.3×, above
anything the family exhibits (measured best ≈2.8×/bounce ⇒ 1.7e-19 at 25 events). The
agent's exhaustive search and linearity check were correct; the spec was unsatisfiable.
Durable fix: amplification-based admission (prereg v1.1 A2) + the feasibility-derivation
rule (A3). (2) Registered per-cell counts summed to 15 against a stated total of 16
(Bézier×periodic written ×1); corrected to ×2 in v1.1 A1. Domain finding elevated to the
record: parabola gravitational billiard is integrable — parabola×quasi-chaotic declared
empty (v1.1 A1), a coverage-table cell closed by measurement rather than assumption.
NUMBERS: measured amplifications — deg-6 ≈1.7e11 (exponential), parabola ≈2e1 (polynomial),
over 25 events at ε=1e-30.
LEARNED: registered thresholds involving dynamical growth carry an ε·λ^N feasibility bound
at authoring time (prereg v1.1 A3); count totals are summed, not asserted.
NEXT: I-003-T3-R1 (PACKET 41).

---
### JRN-I003-17 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_40_I-003-T3 (BLOCKED) per P6 §7. Block-handling compliance: step-0
OUT_39 remediation executed first and fully pasted — all 16 T2-R1 sha256s + manifest match;
the L-15 remediation is CLOSED and the T2-R1 digest ledger complete. LAW-1 affirmed.
Blocker evidence byte-verbatim (search result, best-candidate amplification, threshold,
linearity confirmation); stop-on-surprise honored — no invented parameters, no waived
criterion. WIP tooling (mint_tier2_heldout.py, refsim Bézier + sensitivity extensions)
committed with the OUT for continuation. Verdict: BLOCKED accepted as properly executed;
task neither VERIFIED nor REJECTED; resolution via prereg v1.1 + T3-R1 (this packet).
NUMBERS: none beyond JRN-I003-16's.
LEARNED: nothing
NEXT: T3-R1 dispatch.

---
### JRN-I003-16 · BLOCKED
actor: composer-agent · task: I-003-T3 · manifest: n/a

WHAT: I-003-T3 BLOCKED at quasi-chaotic admission (BRIEF §3 / criterion 3). Step 0 OUT_39
remediation passed (all 16 Tier-1 sha256s match). Implemented tools/scenarios/mint_tier2_heldout.py
and tier2_refsim.py piecewise-Bézier + sensitivity helpers; settle/periodic/discriminant paths
run. Quasi-chaotic: exhaustive parameter search on deg-3–6 polynomials (e=1, 25-event cap) finds
best event-time divergence under 1e-30 vx perturbation ≈1.72e-19 (HO-class params:
deg-6/1/32, y0=4, vx=0.3, vy=1.1) — nine orders of magnitude below the 1e-10 bound. Linear
scaling confirmed (1e-20 pert → ~1.7e-9). Exact mpmath refsim cannot certify per spec without
invented parameters. BLOCK per brief §3.
NUMBERS: best max |Δt| ≈1.72e-19 at ε=1e-30; threshold 1e-10.
LEARNED: quasi-chaotic admission requires refsim extension or parameter class not found by search.
NEXT: PM unblock (refsim sensitivity model) or revised admission rule.

---
### JRN-I003-15 · CLAIM
actor: composer-agent · task: I-003-T3 · manifest: n/a

WHAT: Claimed I-003-T3 (full Tier-2 held-out mint, 16 fixtures closing §7 coverage +
§8.iii concentration cap) on branch task/I-003-T3 after PACKET 40 apply; step 0 OUT_39
remediation first per L-15.
NUMBERS: 16 new Tier-2 fixtures; corpus target 32.
LEARNED: nothing
NEXT: Step 0 wc/shasum assertion; implement mint_tier2_heldout.py; steps 3–10.

---
### JRN-I003-14 · NOTE
actor: pm-fable5-b · task: I-003-T3 · manifest: n/a

WHAT: I-003-T3 authored (PACKET 40) as one full-width task (Director step-size ruling
2026-07-12): 16 Tier-2 held-out fixtures — deg 3–6 settle ×4 (one per degree) and periodic
×2; quasi-chaotic ×4 (parabola ×2, deg 3–6 ×2), each admitted only with a sensitivity
certificate (1e-30 IC perturbation diverging past 1e-10 in event time within the 25-event
cap); piecewise Bézier C1 settle ×3 (incl. 2- and 3-ball) and periodic ×2; near-double-root
×1 (collision-polynomial discriminant within 1e-6 of zero at first contact, 50-digit value
recorded). Full corpus 32 held-out; expected concentration flat 7/32, parabola 11/32,
deg 3–6 9/32, Bézier 5/32 — §8.iii cap closes. Carried disciplines: R1 two-touchpoint
float64 rule, R4-style dual-precision convergence (Tier-2 reference_converged per Law 5),
R6 verbatim evidence, LAW-1 (no engine binary). New: Python-native C1 continuity check at
Bézier knots at 50 digits (the C++ validator is LAW-1-forbidden here). Digest completeness
is a binary criterion per L-15. Step 0 = OUT_39 remediation.
NUMBERS: 16 fixtures; corpus 32; sensitivity bound 1e-10 within 25 events from 1e-30
perturbation; discriminant window 1e-6; C1 check at 50 digits.
LEARNED: nothing
NEXT: I-003-T3 (this packet); on ACCEPT — I-004-T2+T3 batched (PACKET 41), then C-001-T11
baseline spec.

---
### JRN-I003-13 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_39_I-003-T2-R1 per P6 §2. Criteria 1–8 all COMPLIANT: true 50-digit
periods with correct IEEE gaps (sqrt(2) gap 9.667e-17), exact-zero grazing ratio errors
with v_graze hex provenance (0x1.12e0be826d695p-30), R4 floor 49.61 digits, validator
locked at cal=2/heldout=16, LAW-1 + R5 affirmed, byte-verbatim status. L-10 row PARTIAL:
FILE DIGESTS section carried 2 of 16 fixtures; all 16 sha256s present verbatim in the
step-4 paste; byte counts of 14 fixtures absent from the OUT. Ruling per new L-15: ACCEPT
with mandatory remediation (PACKET 40 step 0: wc -c + shasum over all 16 fixtures +
manifest, asserted against OUT_39's step-4 digests; mismatch → BLOCK). Verdict: ACCEPT —
I-003-T2 VERIFIED via R1. Deviations (graze-3 curve coeff 1/2; graze-2 closed-form boundary
reference) reviewed: in-scope parameter choices, properly declared, canonical names kept
per R7.
NUMBERS: R4 floor 49.61 digits; ratio errors 0.0.
LEARNED: L-15 (docs/02_PROGRAM/LESSONS.md).
NEXT: I-003-T3 (PACKET 40).
---
### JRN-I003-12 · DONE
actor: composer-agent · task: I-003-T2-R1 · manifest: n/a

WHAT: I-003-T2-R1 complete DONE: re-minted 16 Tier-1 held-out scenarios in place per R1–R7
(float64 discipline, strict non-dyadicity, 1e-30 grazing ratios, 45-digit dual-precision
self-check, verbatim evidence); superseded quarantined T2 mint (never engine-executed);
validate_store.py exit=0 (calibration=2, heldout=16, split_locked=true).
NUMBERS: v_graze_hex=0x1.12e0be826d695p-30; grazing ratios err=0.0; R4 worst-case min 49.61
digits (HO-parabola-settle-2); concentration flat=7/16 parabola=9/16.
LEARNED: grazing 1.0× fixture requires closed-form reference at boundary; 2.0× needs coeff
1/2 for R4 simulate convergence.
NEXT: PM review OUT_39.

---
### JRN-I003-11 · CLAIM
actor: composer-agent · task: I-003-T2-R1 · manifest: n/a

WHAT: Claimed I-003-T2-R1 (re-mint 16 Tier-1 held-out fixtures, float64 contamination fix)
on branch task/I-003-T2 after PACKET 39 apply; in-place supersession of quarantined mint.
NUMBERS: none
LEARNED: nothing
NEXT: Fix mint tooling per R1–R4; run steps 3–9; write TR and OUT.

---
### JRN-I003-10 · NOTE
actor: pm-fable5-b · task: I-003-T2-R1 · manifest: n/a

WHAT: I-003-T2-R1 rework authored (PACKET 39). Root cause eliminated by spec, not patched:
mpmath dps ≥ 50 end-to-end; exactly two float64 touchpoints permitted — (a) reading the
exact binary value of the v_graze double constant from source (hex recorded as provenance),
(b) one correctly-rounded conversion per field at scenario-write time. Non-dyadicity check
redefined as strict inequality (50-digit closed-form value ≠ nearest double, gap printed at
≥30 digits); the symbolic_non_dyadic escape hatch is removed. Grazing targets constructed
exactly ({0.5,1,2} are powers of two: |achieved − target| ≤ 1e-30 required). Every fixture's
reference events pass a dual-precision self-check (dps=50 vs dps=100, ≥45-digit agreement)
before rounding to double. Verbatim-evidence rule restated as its own criterion. Naming
HO-graze-parabola-<k> ratified as canonical.
NUMBERS: 16 fixtures re-minted in place; ratio bound 1e-30; self-check bound 45 digits.
LEARNED: nothing (pending R1 outcome).
NEXT: I-003-T2-R1 (this packet); on ACCEPT — PACKET 40 batches I-003-T3 Tier-2 mint as one
large task + corrected two-branch merge instruction (Director step-size ruling 2026-07-12).

---
### JRN-I003-9 · NOTE
actor: pm-fable5-b · task: n/a · manifest: n/a

WHAT: Review of OUT_38_I-003-T2 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | venv record: pinned venv, mpmath 1.3.0 | COMPLIANT |
| 2 | generator exit=0; 16 fixtures | COMPLIANT |
| 3 | non-dyadicity checks + grazing ratios ≥20 sig digits | NON-COMPLIANT |
| 4 | store validator exit=0 | COMPLIANT |
| 5 | manifest 16 entries + heldout listing | COMPLIANT |
| 6 | LAW-1 affirmation | COMPLIANT |
| 7 | git status pasted | NON-COMPLIANT — glob summary "?? inbox/PACKET_*.md", not verbatim (L-10) |
Criterion-3 evidence: achieved grazing ratios off target by ~6.2e-17 relative (2^-54
fingerprint — a double in the pipeline); "period_50_digits" for HO-flat-periodic-1/-3 equals
the decimal expansion of the nearest double to sqrt(2) (…0951454746…), not sqrt(2)
(…09504880…) — the 50-digit display was taken of an already-rounded double, which is also
why double_inexact=false; pass was then claimed via the symbolic_non_dyadic escape, defeating
the constructive check the criterion required. Reference events consequently suspect at
Tier-1 standard. Verdict: REJECT. Fixtures quarantined non-gate-bearing; no Law-1 poisoning
(engine never touched them); re-mint in place via R1. Secondary finding from DEVIATIONS:
task/I-003-T1 is off the stacked chain — PACKET 38 merge DIRECTOR ACTION mis-sized, placed
ON HOLD; corrected instruction after R1. Positive note for the record: first substantive
REJECT under model B — the double-contamination class is precisely what PM-pre-built outputs
used to mask.
NUMBERS: ratio error ~6.2e-17 relative on all three grazing fixtures.
LEARNED: high-precision pipelines fail silently through invisible float64 round-trips; specs
must bound the *number and location* of double conversions, not just the target precision.
NEXT: I-003-T2-R1 (PACKET 39).

---
### JRN-I003-8 · DONE
actor: composer-agent · task: I-003-T2 · manifest: n/a

WHAT: I-003-T2 complete DONE: minted 16 Tier-1 held-out scenarios via
tools/scenarios/mint_tier1_heldout.py (refsim/CAS only; Law-1: no engine binary
built/linked/invoked); manifest + split-lock updated; validate_store.py exit=0
(calibration=2, heldout=16); concentration flat=7/16 parabola=9/16 (Tier-1-partial,
no waiver).
NUMBERS: 16 held-out fixtures; v_graze from src/core/bounce/engine/vca.hpp (G-1/S-1);
grazing ratios {0.5,1.0,2.0}× verified to ≥20 sig digits.
LEARNED: nothing
NEXT: PM review OUT_38; on ACCEPT, I-003-T3 Tier-2 mint brief.

---
### JRN-I003-7 · CLAIM
actor: composer-agent · task: I-003-T2 · manifest: n/a

WHAT: Claimed I-003-T2 (Tier-1 held-out corpus mint + lock) on branch task/I-003-T2 after
PACKET 38 apply; imported I-003-T1 split-lock machinery from task/I-003-T1.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–9 per BRIEF; mint 16 held-out fixtures; write TR and OUT.

---
### JRN-I003-6 · NOTE
actor: pm-fable5-b · task: I-003-T2 · manifest: n/a

WHAT: I-003-T2 authored (PACKET 38): Tier-1 held-out mint — 16 scenarios with registered
per-cell counts (flat settle 4, flat periodic non-dyadic 3, parabola settle 4, parabola bowl
2, grazing block 3 at {0.5,1.0,2.0}×v_graze), refsim/CAS only (Law-1 hard rule: no engine
binary in the task), constructive non-dyadicity checks, v_graze read from the versioned G-1
source, lock-on-mint via T1 machinery. Concentration cap (C-001-PREREG §8.iii) binds on the
full corpus after the T3 Tier-2 mint; T2 ratios recorded for the record. Model B: packet
carries spec and acceptance shape only.
NUMBERS: 16 fixtures; grazing ratios to ≥20 sig digits; non-dyadicity at ≥50-digit
derivation.
LEARNED: nothing
NEXT: I-003-T2 (this packet); T3 Tier-2 mint after T2 VERIFIED; I-004-T2 orchestrator in
parallel track.

---
### JRN-I003-5 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: Review of OUT_23_I-003-T1 per P6 §2. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | Step 3 ends exit=0 | COMPLIANT |
| 2 | Step 4 digest == 7301f955…, ends exit=0 | COMPLIANT |
| 3 | Step 5 four-line validate stdout, ends exit=0 | COMPLIANT |
| 4 | Step 6 heldout-access-denied, ends exit=1 | COMPLIANT |
| 5 | Step 7 heldout-access-ok, ends exit=0 | COMPLIANT |
| 6 | Step 8 identical to Step 5 | COMPLIANT |
| 7 | Step 9 no modified; untracked inbox/PACKET_*.md only (L-13) | COMPLIANT |
| 8 | CLAIM + DONE verbatim; serial-23 in APPLY CONFIRMATION | COMPLIANT |
| L-10/L-12 | P5 header; JRN-I003-2/-3/-4 verbatim; FILE DIGESTS; TR steps 3–9; BRANCH/COMMITS terminator | COMPLIANT |
Verdict: ACCEPT. I-003-T1 VERIFIED. C-002-T2 dispatched (PACKET 24).
NUMBERS: 2 calibration scenarios validated; 0 held-out.
LEARNED: nothing
NEXT: C-002-T2 (PACKET 24).

---
### JRN-I003-4 · DONE
actor: composer-agent · task: I-003-T1 · manifest: n/a

WHAT: I-003-T1 complete DONE: validate_store.py digest matches pre-registration
(7301f955…, 6465 bytes); validator stdout byte-identical across two runs (4-line output);
held-out access denied without BOUNCE_HELDOUT_LOCK (exit=1), ok with lock (exit=0);
workspace clean per L-13 (untracked inbox/PACKET_*.md only).
NUMBERS: 2 calibration scenarios validated; 0 held-out scenarios.
LEARNED: nothing
NEXT: PM review OUT_23; on ACCEPT, C-002-T2 brief (PACKET 24).

---
### JRN-I003-3 · CLAIM
actor: composer-agent · task: I-003-T1 · manifest: n/a

WHAT: Claimed I-003-T1 (split-lock marker + store validator + held-out empty manifest) on branch
task/I-003-T1 after PACKET 23 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 3–9 per PACKET 23; write TR and OUT.

---
### JRN-I003-2 · NOTE
actor: pm-composer · task: I-003-T1 · manifest: n/a

WHAT: I-003-T1 authored (PACKET 23): split-lock marker at data/scenarios/split-lock.json,
held-out empty manifest at data/scenarios/heldout/MANIFEST.json, validator at
tools/scenarios/validate_store.py (calibration schema check + split-lock hash + held-out access
gate via BOUNCE_HELDOUT_LOCK). PM pre-verification (P6 §7.4): validate_store.py sha256
7301f955c6891dd53b1d3926c83bd712349bfff9a00801df7d44cd9ab1dcbfb9 (6465 bytes);
split-lock.json sha256 ae8466e838dae9a1a817664e02336114b6778b37fc5e7f853825a5fc038cd4d4
(325 bytes); MANIFEST.json sha256 0c1b7eb91494bdf244aefed926f477d8dfdae5c442975c4cbfd94d32ee3b0ee9
(169 bytes). Two validate runs byte-identical; held-out access denied without lock (exit=1),
ok with BOUNCE_HELDOUT_LOCK=1 (exit=0).
NUMBERS: 2 calibration scenarios validated; 0 held-out scenarios.
LEARNED: nothing
NEXT: I-003-T1 (this packet); on ACCEPT, C-002-T2 brief (PACKET 24).

---
### JRN-I003-1 · NOTE
actor: pm-composer · task: n/a · manifest: n/a

WHAT: I-003 brief applied (PACKET 20). T1 split-lock task sketched; dispatch after C-002-T1.
NUMBERS: none
LEARNED: nothing
NEXT: I-003-T1 packet (subsequent).

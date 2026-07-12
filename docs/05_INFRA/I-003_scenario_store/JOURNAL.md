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

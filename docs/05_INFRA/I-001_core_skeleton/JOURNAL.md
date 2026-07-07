# JOURNAL — I-001 Engine library skeleton (append-only, newest at top)

```
doc_id:   I-001-JOURNAL
layer:    infra
audience: ALL
status:   ACTIVE
parent:   I-001-BRIEF
```

---
### JRN-I001-3 · DONE
actor: composer-agent · task: I-001-T1 · manifest: n/a

WHAT: I-001-T1 complete on task/I-001-T1: cmake --preset default (exit=0), build (exit=0),
ctest 100% passed (exit=0). TR_I-001-T1.md written with verbatim step outputs. Step 5 shows
untracked inbox packet files only; no modified tracked entries.
NUMBERS: none
LEARNED: nothing
NEXT: PM review of OUT_8_I-001-T1; on ACCEPT, register I-001 → VERIFIED.

---
### JRN-I001-2 · CLAIM
actor: composer-agent · task: I-001-T1 · manifest: n/a

WHAT: Claimed I-001-T1 (configure, build, test skeleton; paste evidence) on branch task/I-001-T1
after PACKET 8 apply.
NUMBERS: none
LEARNED: nothing
NEXT: Run steps 1–5 per brief; write TR and OUT.

---
### JRN-I001-1 · NOTE
actor: pm-fable5-a · task: I-001-T1 · manifest: n/a

WHAT: I-001 brief authored and skeleton transcribed (PACKET 8): root CMakeLists (C++20, MSVC
refused), CMakePresets (default), config/fp-determinism.cmake as the single FP-flag source
(-ffp-contract=off, -fno-fast-math; DELIVERABLE_B §4), bounce-core static lib exposing versioned
rule constants (engine 0.1.0, TB-1, G-1/S-1), doctest v2.4.11 via FetchContent (pinned tag;
test-only dependency, MIT — recorded here as the licensing note of adoption; bounce-core itself
stays zero-dependency), smoke test, FP-environment tests (FE_TONEAREST, subnormals alive both as
result and operand, contraction probe (1+2⁻²⁹)(1−2⁻²⁹)−1 == 0.0 two-step vs fma −2⁻⁵⁸,
FLT_EVAL_METHOD == 0). SPDX headers GPL-3.0-only per D2; "-only vs -or-later" is flagged for
Director confirmation at Phase-3 packaging, when the LICENSE file ships. std::fma appears in
tests only; the core's no-libm rule (DELIVERABLE_B §4) is untouched.
NUMBERS: none
LEARNED: nothing
NEXT: I-001-T1 (configure/build/test with pasted evidence); on ACCEPT, register I-001 → VERIFIED
and I-002 brief follows.

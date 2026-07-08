# PACKET 8 — Phase 1 opens: I-001 core skeleton (brief + sources + build task)
pm: pm-fable5-a · date: 2026-07-07 · task: I-001-T1

== VERDICT ==
OUT_7 reviewed per P6 §2: ACCEPT — pre-apply guard matched, module v0.2 post-apply digest matched
the pinned value exactly, all OUT-REQUIREMENTS met (table in JRN-C000-19, the closing entry of the
C-000 journal). Phase 1 opens with I-001: this packet transcribes the core skeleton — root CMake
project (C++20), CMakePresets, the single FP-determinism fragment, bounce-core with the versioned
rule constants (engine 0.1.0, TB-1, G-1/S-1), doctest via pinned FetchContent, a smoke test, and
the FP-environment assertion tests (round-to-nearest, subnormals alive, no FP contraction,
FLT_EVAL_METHOD 0) — and dispatches I-001-T1: configure, build, run tests, paste everything.
The infrastructure register row for I-001 advances only on acceptance (next packet), with STATE
carrying the transient status meanwhile.

== FILES ==

=====[ FILE OVERWRITE: docs/05_INFRA/I-001_core_skeleton/BRIEF.md ]=====
# I-001 BRIEF — Engine library skeleton

```
doc_id:   I-001-BRIEF
layer:    infra
audience: Agents (T-tasks), PM
status:   ACTIVE
parent:   INFRASTRUCTURE_REGISTER I-001 / DELIVERABLE_C §2–§3
```

## Context for agents
First code of Phase 1. The repository gains a buildable C++20 skeleton: a `bounce-core` static
library holding only versioned rule constants for now, a doctest test harness, and — the part
that matters — `config/fp-determinism.cmake`, the single source of truth for floating-point
flags (DELIVERABLE_B §4), plus tests that assert the FP environment at runtime. Your task builds
and tests exactly what the packet applied. A build or test failure is a RESULT to report
verbatim (status FAILED), never something to fix, patch, or retry with different flags.

## Files you may read
- `AGENTS.md` · `inbox/PACKET_8.md` · P0 §2–§6 · P3 · P4 · P1 §3 and §7
- This brief; the files this packet applied (listed in TASK I-001-T1 steps)
- `inbox/APPLIED.log`

## Files you will write
- `docs/05_INFRA/I-001_core_skeleton/JOURNAL.md` (append only)
- `docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1.md` (or BLK/FAILED per P4)
- `inbox/APPLIED.log` (append one line)
- `outbox/OUT_8_I-001-T1.md`
- Build artifacts under `build/` only (git-ignored)

## TASK I-001-T1: Configure, build, and test the skeleton; paste the evidence
depends_on: none
objective: Prove the committed skeleton configures, builds, and passes its tests on the
           environment of record, with all outputs pasted verbatim.
inputs:    The repository working tree after this packet's FILES section is applied. Network is
           used only by CMake FetchContent to fetch doctest at the pinned tag (v2.4.11) from
           github.com. No credentials. Manifest: n/a — manifest infrastructure is I-004
           (JRN-C000-2 ruling); all values are verbatim command output.
steps:
  1. Run: `cmake --version ; c++ --version ; sw_vers ; echo exit=$?` — copy the full output
     (environment record, P6 §4.5).
  2. Run: `cmake --preset default 2>&1 ; echo exit=$?` — copy the full output.
  3. Run: `cmake --build --preset default 2>&1 ; echo exit=$?` — copy the full output.
  4. Run: `ctest --preset default 2>&1 ; echo exit=$?` — copy the full output.
  5. Run: `git status --short --branch ; echo exit=$?` — copy the full output (expect: task
     branch, no modified or untracked entries; `build/` is git-ignored).
  6. Write `docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1.md` per P1 §7, header
     `manifest: n/a — pre-I-004; all values are verbatim command output (JRN-C000-2)`, one
     section per step, `Step 1` … `Step 5`, each containing only that step's verbatim output.
  7. Append the DONE (or FAILED) journal entry, commit, and write `outbox/OUT_8_I-001-T1.md`.
output:
  - docs/05_INFRA/I-001_core_skeleton/reports/TR_I-001-T1.md
  - journal CLAIM and DONE/FAILED entries
  - outbox/OUT_8_I-001-T1.md
courier:
  - Full text of TR_I-001-T1.md verbatim in the OUT REPORT section.
acceptance_criteria:
  1. TR contains `Step 1` with the verbatim toolchain/OS record.
  2. TR contains `Step 2` verbatim, ending `exit=0`.
  3. TR contains `Step 3` verbatim, ending `exit=0`.
  4. TR contains `Step 4` verbatim, showing 100% tests passed and ending `exit=0`.
  5. TR contains `Step 5` verbatim, showing no modified and no untracked entries.
  6. The OUT contains verbatim CLAIM and DONE/FAILED journal entries.
  7. The OUT's APPLY CONFIRMATION contains the pasted APPLIED.log line for serial 8.
  (If any of steps 2–4 ends with a non-zero exit: criteria 2–4 are replaced by "full output
  pasted verbatim including the failure"; task status is FAILED, honestly reported per P3 §7 —
  a FAILED report meeting that standard is reviewable and will not be treated as agent error.)
OUT-REQUIREMENTS (per L-10):
  - APPLY CONFIRMATION with the serial-8 ledger line pasted;
  - JOURNAL ENTRIES: verbatim copies of every journal entry this packet applied (JRN-I001-1,
    JRN-C000-19) AND the task's CLAIM and DONE/FAILED entries;
  - FILE DIGESTS: `wc -c` and `shasum -a 256` output for every file this packet's FILES section
    wrote (both briefs' docs and all source/build files listed in APPLY CONFIRMATION);
  - REPORT: TR_I-001-T1.md in full;
  - BRANCH/COMMITS: pasted output of `git log --format='%H %s' main..HEAD`.
failure_modes:
  - FetchContent cannot reach github.com or the tag is absent → the step-2 output records it;
    status FAILED (not BLOCKED); do not vendor, mirror, or substitute anything.
  - Step-5 shows unexpected modified/untracked entries → paste and report; note under
    OBSERVATIONS; PM judges at review.
  - Unresolved CLAIM for I-001-T1 in the infra journal → STOP, BLOCKED (collision guard).
DO_NOT:
  - Do not edit any file this packet applied — no CMake, source, or flag changes, even to make
    the build pass.
  - Do not install packages, toolchains, or CMake versions.
  - Do not run commands not listed in the steps.
  - Do not truncate outputs; long configure/build logs are pasted whole.
=====[ END FILE ]=====

=====[ FILE OVERWRITE: docs/05_INFRA/I-001_core_skeleton/JOURNAL.md ]=====
# JOURNAL — I-001 Engine library skeleton (append-only, newest at top)

```
doc_id:   I-001-JOURNAL
layer:    infra
audience: ALL
status:   ACTIVE
parent:   I-001-BRIEF
```

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

=====[ END FILE ]=====

=====[ FILE APPEND: docs/03_TRACKS/C-000_scoping/JOURNAL.md ]=====
---
### JRN-C000-19 · NOTE
actor: pm-fable5-a · task: n/a · manifest: n/a

WHAT: Review of OUT_7 per P6 §2 (closing entry; C-000 is CLOSED, this reviews the packet that
closed it). Verdict: ACCEPT. Criterion table:
| # | criterion | verdict |
|---|---|---|
| 1 | PRE-APPLY GUARD pasted, matched 889b3fae… | COMPLIANT |
| 2 | Serial-7 ledger line in APPLY CONFIRMATION | COMPLIANT |
| 3 | JRN-C000-18 / JRN-C000-17 verbatim | COMPLIANT |
| 4 | Post-apply digests pasted; 00_PROJECT.md == pinned db5cd59d… | COMPLIANT |
| 5 | BRANCH/COMMITS via git log --format='%H %s' | COMPLIANT |
Module v0.2 is the constitution of record; Phase 1 open. Further program review entries live in
the journals of the workstreams that produce them (first: I-001).
NUMBERS: none
LEARNED: nothing
NEXT: none — track closed.
=====[ END FILE ]=====

=====[ FILE APPEND: .gitignore ]=====
build/
=====[ END FILE ]=====

=====[ FILE OVERWRITE: CMakeLists.txt ]=====
cmake_minimum_required(VERSION 3.27)
project(bounce VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  message(FATAL_ERROR "MSVC is not a supported toolchain (targets: macOS arm64, Linux x86-64).")
endif()

include(config/fp-determinism.cmake)

add_library(bounce-core STATIC
  src/core/bounce/version.cpp
)
target_include_directories(bounce-core PUBLIC src/core)
bounce_apply_fp_determinism(bounce-core)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(bounce-tests
  tests/test_main.cpp
  tests/test_smoke.cpp
  tests/test_fp_environment.cpp
)
target_link_libraries(bounce-tests PRIVATE bounce-core doctest::doctest)
bounce_apply_fp_determinism(bounce-tests)

add_test(NAME bounce-tests COMMAND bounce-tests)
=====[ END FILE ]=====

=====[ FILE OVERWRITE: CMakePresets.json ]=====
{
  "version": 6,
  "configurePresets": [
    {
      "name": "default",
      "displayName": "Release (environment of record)",
      "binaryDir": "${sourceDir}/build/default",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    }
  ],
  "buildPresets": [
    { "name": "default", "configurePreset": "default" }
  ],
  "testPresets": [
    {
      "name": "default",
      "configurePreset": "default",
      "output": { "outputOnFailure": true }
    }
  ]
}
=====[ END FILE ]=====

=====[ FILE OVERWRITE: config/fp-determinism.cmake ]=====
# fp-determinism.cmake — the SINGLE source of truth for floating-point flags.
# Authority: DELIVERABLE_B §4 (numerics decision memo). Any change is an engine
# version bump and a PM-authored packet; nothing else may set FP-relevant flags.
#
#   -ffp-contract=off : no FMA contraction anywhere; results must not depend on
#                       FMA availability (cross-platform bit-identity).
#   -fno-fast-math    : forbid value-changing FP optimizations; keep IEEE-754
#                       semantics, NaN/Inf handling, and rounding intact.
#
# FTZ/DAZ are not touched here: they are runtime CPU-state settings; the test
# suite asserts at runtime that subnormals are alive (tests/test_fp_environment.cpp).

function(bounce_apply_fp_determinism target)
  target_compile_options(${target} PRIVATE
    -ffp-contract=off
    -fno-fast-math
  )
endfunction()
=====[ END FILE ]=====

=====[ FILE OVERWRITE: src/core/bounce/version.hpp ]=====
// SPDX-License-Identifier: GPL-3.0-only
// bounce-core — versioned identity of the engine and its ordering/contact rules.
// Authority: DELIVERABLE_B §3 (G-1/S-1), §5 (TB-1); PROJECT §9(c) (presets replay
// per engine version; rule changes are version bumps, never silent).
#pragma once

namespace bounce::core {

// Semantic version of bounce-core. Bumped by PM packet only.
const char* engine_version();

// Event-ordering tie-break rule version (DELIVERABLE_B §5).
const char* tie_break_version();

// Grazing / settle (Zeno-guard) contact rule versions (DELIVERABLE_B §3).
const char* contact_rule_version();

} // namespace bounce::core
=====[ END FILE ]=====

=====[ FILE OVERWRITE: src/core/bounce/version.cpp ]=====
// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/version.hpp"

namespace bounce::core {

const char* engine_version()       { return "0.1.0"; }
const char* tie_break_version()    { return "TB-1"; }
const char* contact_rule_version() { return "G-1/S-1"; }

} // namespace bounce::core
=====[ END FILE ]=====

=====[ FILE OVERWRITE: tests/test_main.cpp ]=====
// SPDX-License-Identifier: GPL-3.0-only
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
=====[ END FILE ]=====

=====[ FILE OVERWRITE: tests/test_smoke.cpp ]=====
// SPDX-License-Identifier: GPL-3.0-only
#include <doctest/doctest.h>
#include <cstring>
#include "bounce/version.hpp"

TEST_CASE("bounce-core exposes its versioned identity") {
  CHECK(std::strcmp(bounce::core::engine_version(), "0.1.0") == 0);
  CHECK(std::strcmp(bounce::core::tie_break_version(), "TB-1") == 0);
  CHECK(std::strcmp(bounce::core::contact_rule_version(), "G-1/S-1") == 0);
}
=====[ END FILE ]=====

=====[ FILE OVERWRITE: tests/test_fp_environment.cpp ]=====
// SPDX-License-Identifier: GPL-3.0-only
// Runtime assertions that the FP environment matches DELIVERABLE_B §4.
// These tests failing means the build or runtime environment violates the
// determinism surface — a gate-class failure, never something to work around.
// NOTE: std::fma is used HERE ONLY as a probe reference; bounce-core itself
// must remain libm-free (DELIVERABLE_B §4).
#include <doctest/doctest.h>
#include <cfenv>
#include <cfloat>
#include <cmath>

TEST_CASE("rounding mode is round-to-nearest-even") {
  CHECK(std::fegetround() == FE_TONEAREST);
}

TEST_CASE("no extended-precision expression evaluation") {
  CHECK(FLT_EVAL_METHOD == 0);
}

TEST_CASE("subnormals are alive (FTZ/DAZ off)") {
  volatile double t = DBL_MIN;      // smallest normal
  volatile double half = t / 2.0;   // subnormal result: flushed to 0 under FTZ
  CHECK(half > 0.0);
  volatile double quarter = half / 2.0; // subnormal operand and result (DAZ probe)
  CHECK(quarter > 0.0);
  CHECK(quarter * 4.0 == t);
}

TEST_CASE("no FP contraction: a*b + c is two IEEE roundings, not fma") {
  // (1 + 2^-29)(1 - 2^-29) = 1 - 2^-58, which rounds to exactly 1.0 in binary64.
  // Two-step:  round(a*b) + c = 1.0 - 1.0 = 0.0.
  // Contracted: fma(a,b,c)    = -2^-58 exactly.
  volatile double a = 1.0 + 0x1p-29;
  volatile double b = 1.0 - 0x1p-29;
  volatile double c = -1.0;
  double two_step = a * b + c;
  CHECK(two_step == 0.0);
  CHECK(std::fma(a, b, c) == -0x1p-58); // sanity: the probe distinguishes the cases
}
=====[ END FILE ]=====

== TASK ==
Precondition (Director, yes/no): last line of `inbox/APPLIED.log` is serial 7; `packet/7` merged;
repository on `main`, clean.

Reading list: `AGENTS.md` · this packet · P0 §2–§6 · P3 · P4 · P1 §3 and §7 ·
`docs/05_INFRA/I-001_core_skeleton/BRIEF.md`. No other files.

Assignment: apply the FILES section byte-exact (serial check: this is serial 8) on branch
`task/I-001-T1` from main, then execute TASK I-001-T1 exactly as written in the brief.

Non-negotiables: CLAIM entry (JRN-I001-2) committed before build work; a build/test failure is a
FAILED result with full pasted output, never a fix, retry, or flag change; evidence pasted per
criterion; OUT-REQUIREMENTS complete per L-10.

End state: one branch `task/I-001-T1`, one commit series, exactly one committed
`outbox/OUT_8_I-001-T1.md` marked DONE, FAILED, or BLOCKED. Then stop.

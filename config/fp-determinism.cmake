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

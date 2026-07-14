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
  src/core/bounce/curve/polynomial.cpp
  src/core/bounce/curve/bezier.cpp
  src/core/bounce/numerics/double_double.cpp
  src/core/bounce/engine/ballistic.cpp
  src/core/bounce/engine/vca.cpp
  src/core/bounce/engine/collision_sim.cpp
  src/core/bounce/scenario/rational.cpp
  src/core/bounce/scenario/calibration_loader.cpp
  src/core/bounce/io/sha256.cpp
  src/core/bounce/io/event_file.cpp
)
target_include_directories(bounce-core PUBLIC src/core)
bounce_apply_fp_determinism(bounce-core)

add_library(bounce-baseline STATIC
  src/baseline/polyline.cpp
  src/baseline/baseline_sim.cpp
)
target_link_libraries(bounce-baseline PUBLIC bounce-core)
target_include_directories(bounce-baseline PUBLIC src)
bounce_apply_fp_determinism(bounce-baseline)

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
  tests/test_polynomial_curve.cpp
  tests/test_bezier_curve.cpp
  tests/test_double_double.cpp
  tests/test_ballistic.cpp
  tests/test_vca.cpp
  tests/test_collision_sim.cpp
  tests/test_calibration_scenario.cpp
  tests/test_event_file.cpp
  tests/test_capacity.cpp
  tests/test_baseline_sim.cpp
  src/tools/run_scenario/run_scenario.cpp
  src/tools/run_baseline/run_baseline.cpp
)
target_link_libraries(bounce-tests PRIVATE bounce-core bounce-baseline doctest::doctest)
target_include_directories(bounce-tests PRIVATE src/tools/run_scenario src/tools/run_baseline)
target_compile_definitions(bounce-tests PRIVATE BOUNCE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
bounce_apply_fp_determinism(bounce-tests)

add_executable(bounce-run-scenario
  src/tools/run_scenario/main.cpp
  src/tools/run_scenario/run_scenario.cpp
)
target_link_libraries(bounce-run-scenario PRIVATE bounce-core)
target_include_directories(bounce-run-scenario PRIVATE src/tools/run_scenario)
bounce_apply_fp_determinism(bounce-run-scenario)

add_executable(bounce-baseline-run
  src/tools/run_baseline/main.cpp
  src/tools/run_baseline/run_baseline.cpp
)
target_link_libraries(bounce-baseline-run PRIVATE bounce-baseline)
target_include_directories(bounce-baseline-run PRIVATE src/tools/run_baseline)
bounce_apply_fp_determinism(bounce-baseline-run)

add_executable(bounce-survey-heldout-load
  src/tools/survey_load/survey_heldout_load.cpp
)
target_link_libraries(bounce-survey-heldout-load PRIVATE bounce-core)
target_compile_definitions(bounce-survey-heldout-load PRIVATE BOUNCE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
bounce_apply_fp_determinism(bounce-survey-heldout-load)

add_test(NAME bounce-tests COMMAND bounce-tests)

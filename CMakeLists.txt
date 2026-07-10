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
  tests/test_polynomial_curve.cpp
  tests/test_bezier_curve.cpp
  tests/test_double_double.cpp
  tests/test_ballistic.cpp
)
target_link_libraries(bounce-tests PRIVATE bounce-core doctest::doctest)
bounce_apply_fp_determinism(bounce-tests)

add_test(NAME bounce-tests COMMAND bounce-tests)

# SPDX-License-Identifier: GPL-3.0-only

find_program(SDL2_CONFIG sdl2-config)
if(NOT SDL2_CONFIG)
  message(STATUS "sdl2-config not found; skipping bounce-view target")
  return()
endif()

execute_process(
  COMMAND ${SDL2_CONFIG} --cflags
  OUTPUT_VARIABLE SDL2_CFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
  COMMAND ${SDL2_CONFIG} --libs
  OUTPUT_VARIABLE SDL2_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
separate_arguments(SDL2_CFLAGS_LIST UNIX_COMMAND "${SDL2_CFLAGS}")
separate_arguments(SDL2_LIBS_LIST UNIX_COMMAND "${SDL2_LIBS}")

add_executable(bounce-view
  main.cpp
  law1_guard.cpp
  av_mapping.cpp
  playback.cpp
  selftest.cpp
  interactive.cpp
  ppm_writer.cpp
)
target_link_libraries(bounce-view PRIVATE bounce-core ${SDL2_LIBS_LIST})
target_include_directories(bounce-view PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(bounce-view PRIVATE ${SDL2_CFLAGS_LIST})
bounce_apply_fp_determinism(bounce-view)

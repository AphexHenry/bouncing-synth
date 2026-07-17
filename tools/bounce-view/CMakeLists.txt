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

set(BOUNCE_VIEW_STAMP_HEADER "${CMAKE_CURRENT_BINARY_DIR}/build_stamp_generated.hpp")
add_custom_command(
  OUTPUT "${BOUNCE_VIEW_STAMP_HEADER}"
  COMMAND ${CMAKE_COMMAND}
          -DBOUNCE_VIEW_REPO_DIR=${CMAKE_SOURCE_DIR}
          -DBOUNCE_VIEW_STAMP_HEADER=${BOUNCE_VIEW_STAMP_HEADER}
          -P ${CMAKE_CURRENT_SOURCE_DIR}/gen_build_stamp.cmake
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/gen_build_stamp.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/build_stamp_generated.hpp.in
  COMMENT "Generating bounce-view S14 build stamp from git"
  VERBATIM
)
# Force regeneration each build so dirty/branch/commit stay current.
add_custom_target(bounce-view-stamp ALL
  DEPENDS "${BOUNCE_VIEW_STAMP_HEADER}"
  COMMAND ${CMAKE_COMMAND}
          -DBOUNCE_VIEW_REPO_DIR=${CMAKE_SOURCE_DIR}
          -DBOUNCE_VIEW_STAMP_HEADER=${BOUNCE_VIEW_STAMP_HEADER}
          -P ${CMAKE_CURRENT_SOURCE_DIR}/gen_build_stamp.cmake
  VERBATIM
)

add_executable(bounce-view
  main.cpp
  law1_guard.cpp
  av_mapping.cpp
  audio_voice.cpp
  playback.cpp
  selftest.cpp
  interactive.cpp
  perf.cpp
  scene.cpp
  bezier_display_geometry.cpp
  ppm_writer.cpp
  restitution_config.cpp
  build_stamp.cpp
  "${BOUNCE_VIEW_STAMP_HEADER}"
)
add_dependencies(bounce-view bounce-view-stamp)
target_link_libraries(bounce-view PRIVATE bounce-core ${SDL2_LIBS_LIST})
target_include_directories(bounce-view PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_options(bounce-view PRIVATE ${SDL2_CFLAGS_LIST})
bounce_apply_fp_determinism(bounce-view)

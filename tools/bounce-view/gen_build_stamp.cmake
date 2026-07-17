# SPDX-License-Identifier: GPL-3.0-only
# Generates build_stamp_generated.hpp from live git state at build time (S14).

if(NOT DEFINED BOUNCE_VIEW_REPO_DIR)
  message(FATAL_ERROR "BOUNCE_VIEW_REPO_DIR is required")
endif()
if(NOT DEFINED BOUNCE_VIEW_STAMP_HEADER)
  message(FATAL_ERROR "BOUNCE_VIEW_STAMP_HEADER is required")
endif()

execute_process(
  COMMAND git -C "${BOUNCE_VIEW_REPO_DIR}" rev-parse --short HEAD
  OUTPUT_VARIABLE BOUNCE_VIEW_GIT_SHORT
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
  RESULT_VARIABLE _short_rc
)
execute_process(
  COMMAND git -C "${BOUNCE_VIEW_REPO_DIR}" rev-parse --abbrev-ref HEAD
  OUTPUT_VARIABLE BOUNCE_VIEW_GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
  RESULT_VARIABLE _branch_rc
)
execute_process(
  COMMAND git -C "${BOUNCE_VIEW_REPO_DIR}" status --porcelain
  OUTPUT_VARIABLE _porcelain
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
  RESULT_VARIABLE _status_rc
)

if(NOT _short_rc EQUAL 0 OR BOUNCE_VIEW_GIT_SHORT STREQUAL "")
  set(BOUNCE_VIEW_GIT_SHORT "unknown")
endif()
if(NOT _branch_rc EQUAL 0 OR BOUNCE_VIEW_GIT_BRANCH STREQUAL "")
  set(BOUNCE_VIEW_GIT_BRANCH "unknown")
endif()

set(BOUNCE_VIEW_GIT_DIRTY "")
if(_status_rc EQUAL 0 AND NOT _porcelain STREQUAL "")
  set(BOUNCE_VIEW_GIT_DIRTY "+dirty")
endif()

set(_template "${CMAKE_CURRENT_LIST_DIR}/build_stamp_generated.hpp.in")
configure_file("${_template}" "${BOUNCE_VIEW_STAMP_HEADER}" @ONLY)

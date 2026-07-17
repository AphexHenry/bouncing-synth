# SPDX-License-Identifier: GPL-3.0-only
# Generates build_stamp_generated.hpp from live git state at build time (S14 / S14.1).

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

# S14.1: +dirty only for tracked modifications outside inbox/ and outbox/.
set(BOUNCE_VIEW_GIT_DIRTY "")
if(_status_rc EQUAL 0 AND NOT _porcelain STREQUAL "")
  set(_agent_dirty FALSE)
  string(REPLACE "\n" ";" _porcelain_lines "${_porcelain}")
  foreach(_line IN LISTS _porcelain_lines)
    if(_line STREQUAL "")
      continue()
    endif()
    # Porcelain: XY PATH  or  XY ORIG -> PATH. Skip untracked (??).
    string(SUBSTRING "${_line}" 0 2 _xy)
    if(_xy STREQUAL "??")
      continue()
    endif()
    string(SUBSTRING "${_line}" 3 -1 _pathpart)
    # Renames: take the right-hand path after " -> ".
    string(FIND "${_pathpart}" " -> " _arrow)
    if(NOT _arrow EQUAL -1)
      math(EXPR _after "${_arrow} + 4")
      string(SUBSTRING "${_pathpart}" ${_after} -1 _pathpart)
    endif()
    # Strip optional quotes.
    string(REPLACE "\"" "" _pathpart "${_pathpart}")
    if(_pathpart MATCHES "^inbox/" OR _pathpart MATCHES "^outbox/")
      continue()
    endif()
    set(_agent_dirty TRUE)
    break()
  endforeach()
  if(_agent_dirty)
    set(BOUNCE_VIEW_GIT_DIRTY "+dirty")
  endif()
endif()

set(_template "${CMAKE_CURRENT_LIST_DIR}/build_stamp_generated.hpp.in")
configure_file("${_template}" "${BOUNCE_VIEW_STAMP_HEADER}" @ONLY)

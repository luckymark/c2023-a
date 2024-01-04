# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\gobang_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\gobang_autogen.dir\\ParseCache.txt"
  "gobang_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OOP5_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OOP5_autogen.dir\\ParseCache.txt"
  "OOP5_autogen"
  )
endif()

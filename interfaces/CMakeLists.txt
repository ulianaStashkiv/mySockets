cmake_minimum_required(VERSION 3.9)
project(interfaces)

file(GLOB_RECURSE INTERF_SRC source/*.cpp)
set(INTERF_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create major target
add_library(interfaces 
  STATIC
    ${INTERF_SRC}
)

# Specify include directory
target_include_directories(interfaces
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
cmake_minimum_required(VERSION 2.8)

project(pushserver)

SET(CMAKE_C_COMPILER gcc)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

link_directories(
  ${PROJECT_BINARY_DIR}/lib
)

add_subdirectory(src)
add_subdirectory(tests)


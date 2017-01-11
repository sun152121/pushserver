cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE "Release")

message("Build Type:" ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/lib
)

aux_source_directory(./ SRC_LIST)
aux_source_directory(./core SRC_LIST)
aux_source_directory(./biz SRC_LIST)

add_executable(pushserver ${SRC_LIST})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)  

target_link_libraries(pushserver 
  -lpthread
  -ljson-c
)
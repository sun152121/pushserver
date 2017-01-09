cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE "Debug")


if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-unused-variable")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

message("Build Type:"${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})

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
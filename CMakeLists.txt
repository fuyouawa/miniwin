cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(fugui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)

include_directories(${THIRD_PARTY_DIR})
include_directories(${THIRD_PARTY_DIR}/imgui)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE COMMON_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(fugui STATIC ${COMMON_SOURCES})

find_package(glfw3 REQUIRED)
target_link_libraries(fugui glfw)
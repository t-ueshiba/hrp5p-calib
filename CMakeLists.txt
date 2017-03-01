cmake_minimum_required(VERSION 2.6)

project(hrp5p-calib)

include(FindPkgConfig)
include(CheckIncludeFiles)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_BUILD_TYPE Release)

add_definitions(-DNDEBUG)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

add_subdirectory(src)

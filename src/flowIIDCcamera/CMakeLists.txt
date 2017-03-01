#
#
#
cmake_minimum_required(VERSION 2.4)

#project(flowIIDCcamera)

find_package(X11 REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
    ../TUTools++
    ../TUv++
    ../TUIIDC++
    ../TUvIIDC++)

set(sources
    main.cc
    CaptureAndSave.cc)

set(headers
CaptureAndSave.h
MyCmdWindow.h
flowcamera.h
)

if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif ()

add_executable(flowIIDCcamera ${sources})
target_link_libraries(
    flowIIDCcamera
    TUvIIDC++
    TUIIDC++
    TUv++
    TUTools++)

install(TARGETS flowIIDCcamera RUNTIME DESTINATION bin)


#
#
#
cmake_minimum_required(VERSION 2.4)

#project(fv)				# プロジェクト名

find_package(X11 REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
    ../TUTools++
    ../TUv++)

set(sources
    main.cc
)

add_executable(fv ${sources})
target_link_libraries(
    fv
    TUv++)

install(TARGETS fv RUNTIME DESTINATION bin)


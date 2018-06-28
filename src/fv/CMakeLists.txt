cmake_minimum_required(VERSION 2.4)

#project(fv)

set(sources main.cc)

add_executable(fv ${sources})

target_link_libraries(
    fv
    ${TUVPP_LIB}
    ${TUTOOLSPP_LIB})

install(TARGETS fv RUNTIME DESTINATION bin)


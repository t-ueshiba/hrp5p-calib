cmake_minimum_required(VERSION 2.4)

#project(flowIIDCcamera)

set(sources main.cc CaptureAndSave.cc)

add_executable(flowIIDCcamera ${sources})

target_link_libraries(
    flowIIDCcamera
    ${TUVIIDCPP_LIB}
    ${TUIIDCPP_LIB}
    ${TUVPP_LIB} 
    ${TUTOOLSPP_LIB}) 

install(TARGETS flowIIDCcamera RUNTIME DESTINATION bin)



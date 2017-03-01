#
cmake_minimum_required(VERSION 2.4)

pkg_check_modules(LIBRAW1394 REQUIRED libraw1394)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)
include_directories(
    .
    ../TUTools++
    ${LIBRAW1394_INCLUDE_DIRS}
    ${LIBUSB_INCLUDE_DIRS})

set(sources
    FireWireNode.cc
    IIDCCamera.cc
    IIDCCameraArray.cc
    IIDCNode.cc
    USBNode.cc)

if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif ()

add_library(TUIIDC++ SHARED ${sources})

set(serial "1.0.0")
set(soserial "1")
set_target_properties(TUIIDC++	PROPERTIES
		      VERSION	${serial}
		      SOVERSION ${soserial})
target_link_libraries(
    TUIIDC++
    TUTools++
    ${LIBRAW1394_LIBRARIES}
    ${LIBUSB_LIBRARIES})

install(TARGETS TUIIDC++ LIBRARY DESTINATION lib)

add_subdirectory(TU)


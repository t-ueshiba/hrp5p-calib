# Install script for directory: /home/ueshiba/work/src/TUTools++/TU/simd/arm

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ueshiba/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/TU/simd/arm" TYPE FILE FILES
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/type_traits.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/dup.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/cvt.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/compare.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/arch.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/cast.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/bit_shift.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/arithmetic.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/logical.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/misc.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/shift.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/load_store.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/lookup.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/vec.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/zero.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/select.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arm/insert_extract.h"
    )
endif()


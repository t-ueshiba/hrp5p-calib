# Install script for directory: /home/ueshiba/work/src/TUTools++/TU/simd

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/TU/simd" TYPE FILE FILES
    "/home/ueshiba/work/src/TUTools++/TU/simd/type_traits.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/dup.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/allocator.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/load_store_iterator.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/cvt.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/cvtdown_iterator.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/compare.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/transform.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/cast.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/bit_shift.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/simd.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/arithmetic.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/Array++.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/map_iterator.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/iterator_wrapper.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/logical.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/misc.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/config.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/assignment_iterator.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/shift.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/load_store.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/lookup.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/vec.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/cvtup_iterator.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/zero.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/select.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/insert_extract.h"
    "/home/ueshiba/work/src/TUTools++/TU/simd/shift_iterator.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/TUTools++-prefix/src/TUTools++-build/TU/simd/x86/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/TUTools++-prefix/src/TUTools++-build/TU/simd/arm/cmake_install.cmake")

endif()


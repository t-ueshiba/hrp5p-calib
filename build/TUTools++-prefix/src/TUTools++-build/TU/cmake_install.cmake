# Install script for directory: /home/ueshiba/work/src/TUTools++/TU

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/TU" TYPE FILE FILES
    "/home/ueshiba/work/src/TUTools++/TU/Profiler.h"
    "/home/ueshiba/work/src/TUTools++/TU/type_traits.h"
    "/home/ueshiba/work/src/TUTools++/TU/Camera++.h"
    "/home/ueshiba/work/src/TUTools++/TU/NDTree++.h"
    "/home/ueshiba/work/src/TUTools++/TU/StereoBase.h"
    "/home/ueshiba/work/src/TUTools++/TU/BlockDiagonalMatrix++.h"
    "/home/ueshiba/work/src/TUTools++/TU/TreeFilter.h"
    "/home/ueshiba/work/src/TUTools++/TU/pair.h"
    "/home/ueshiba/work/src/TUTools++/TU/GuidedFilter.h"
    "/home/ueshiba/work/src/TUTools++/TU/EdgeDetector.h"
    "/home/ueshiba/work/src/TUTools++/TU/WeightedMedianFilter.h"
    "/home/ueshiba/work/src/TUTools++/TU/Geometry++.h"
    "/home/ueshiba/work/src/TUTools++/TU/Mesh++.h"
    "/home/ueshiba/work/src/TUTools++/TU/PM16C_04.h"
    "/home/ueshiba/work/src/TUTools++/TU/fdstream.h"
    "/home/ueshiba/work/src/TUTools++/TU/Bezier++.h"
    "/home/ueshiba/work/src/TUTools++/TU/FeatureMatch.h"
    "/home/ueshiba/work/src/TUTools++/TU/IntegralImage.h"
    "/home/ueshiba/work/src/TUTools++/TU/SURFCreator.h"
    "/home/ueshiba/work/src/TUTools++/TU/StereoUtility.h"
    "/home/ueshiba/work/src/TUTools++/TU/functional.h"
    "/home/ueshiba/work/src/TUTools++/TU/Filter2.h"
    "/home/ueshiba/work/src/TUTools++/TU/DericheConvolver.h"
    "/home/ueshiba/work/src/TUTools++/TU/GaussianConvolver.h"
    "/home/ueshiba/work/src/TUTools++/TU/Array++.h"
    "/home/ueshiba/work/src/TUTools++/TU/Minimize.h"
    "/home/ueshiba/work/src/TUTools++/TU/tuple.h"
    "/home/ueshiba/work/src/TUTools++/TU/SHOT602.h"
    "/home/ueshiba/work/src/TUTools++/TU/Rectify.h"
    "/home/ueshiba/work/src/TUTools++/TU/ICIA.h"
    "/home/ueshiba/work/src/TUTools++/TU/Image++.h"
    "/home/ueshiba/work/src/TUTools++/TU/BoxFilter.h"
    "/home/ueshiba/work/src/TUTools++/TU/iterator.h"
    "/home/ueshiba/work/src/TUTools++/TU/List.h"
    "/home/ueshiba/work/src/TUTools++/TU/BandMatrix++.h"
    "/home/ueshiba/work/src/TUTools++/TU/Nurbs++.h"
    "/home/ueshiba/work/src/TUTools++/TU/io.h"
    "/home/ueshiba/work/src/TUTools++/TU/Vector++.h"
    "/home/ueshiba/work/src/TUTools++/TU/FIRFilter.h"
    "/home/ueshiba/work/src/TUTools++/TU/Quantizer.h"
    "/home/ueshiba/work/src/TUTools++/TU/SADStereo.h"
    "/home/ueshiba/work/src/TUTools++/TU/TriggerGenerator.h"
    "/home/ueshiba/work/src/TUTools++/TU/Warp.h"
    "/home/ueshiba/work/src/TUTools++/TU/algorithm.h"
    "/home/ueshiba/work/src/TUTools++/TU/Movie.h"
    "/home/ueshiba/work/src/TUTools++/TU/GraphCuts.h"
    "/home/ueshiba/work/src/TUTools++/TU/SparseMatrix++.h"
    "/home/ueshiba/work/src/TUTools++/TU/GFStereo.h"
    "/home/ueshiba/work/src/TUTools++/TU/Ransac.h"
    "/home/ueshiba/work/src/TUTools++/TU/FIRGaussianConvolver.h"
    "/home/ueshiba/work/src/TUTools++/TU/IIRFilter.h"
    "/home/ueshiba/work/src/TUTools++/TU/Manip.h"
    "/home/ueshiba/work/src/TUTools++/TU/range.h"
    "/home/ueshiba/work/src/TUTools++/TU/SeparableFilter2.h"
    "/home/ueshiba/work/src/TUTools++/TU/DP.h"
    "/home/ueshiba/work/src/TUTools++/TU/Serial.h"
    "/home/ueshiba/work/src/TUTools++/TU/Feature.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/TUTools++-prefix/src/TUTools++-build/TU/simd/cmake_install.cmake")

endif()


# Install script for directory: /home/ueshiba/work/src/hrp5p-comps

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/IIDCCamera/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/IIDCMultiCamera/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/V4L2Camera/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/V4L2MultiCamera/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/VideoSynchronizer/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/ImageViewer/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/MultiImageViewer/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/TUControlPanelPlugin/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/TUImageViewerPlugin/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/TUMultiImageViewerPlugin/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/cnoid_project/cmake_install.cmake")
  include("/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/cmake_modules/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

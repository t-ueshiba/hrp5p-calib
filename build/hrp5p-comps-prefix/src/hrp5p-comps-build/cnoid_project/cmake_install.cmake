# Install script for directory: /home/ueshiba/work/src/hrp5p-comps/cnoid_project

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/ueshiba/cnoid_project/IIDCCamera.cnoid;/home/ueshiba/cnoid_project/IIDCCamera.py;/home/ueshiba/cnoid_project/IIDCMultiCamera.cnoid;/home/ueshiba/cnoid_project/IIDCMultiCamera.py;/home/ueshiba/cnoid_project/V4L2Camera.cnoid;/home/ueshiba/cnoid_project/V4L2Camera.py;/home/ueshiba/cnoid_project/V4L2MultiCamera.cnoid;/home/ueshiba/cnoid_project/V4L2MultiCamera.py;/home/ueshiba/cnoid_project/V4L2Camera-HRP2KAI.cnoid;/home/ueshiba/cnoid_project/V4L2Camera-HRP2KAI.py;/home/ueshiba/cnoid_project/SyncV4L2Camera-HRP2KAI.cnoid;/home/ueshiba/cnoid_project/SyncV4L2Camera-HRP2KAI.py;/home/ueshiba/cnoid_project/SyncLentiMarkV4L2Camera-HRP2KAI.cnoid;/home/ueshiba/cnoid_project/SyncLentiMarkV4L2Camera-HRP2KAI.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/ueshiba/cnoid_project" TYPE FILE FILES
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/IIDCCamera.cnoid"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/IIDCCamera.py"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/IIDCMultiCamera.cnoid"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/IIDCMultiCamera.py"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/V4L2Camera.cnoid"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/V4L2Camera.py"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/V4L2MultiCamera.cnoid"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/V4L2MultiCamera.py"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/V4L2Camera-HRP2KAI.cnoid"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/V4L2Camera-HRP2KAI.py"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/SyncV4L2Camera-HRP2KAI.cnoid"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/SyncV4L2Camera-HRP2KAI.py"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/SyncLentiMarkV4L2Camera-HRP2KAI.cnoid"
    "/home/ueshiba/work/src/hrp5p-comps/cnoid_project/SyncLentiMarkV4L2Camera-HRP2KAI.py"
    )
endif()


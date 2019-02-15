# Install script for directory: /home/ueshiba/work/src/TUv++/TU/v

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/TU/v" TYPE FILE FILES
    "/home/ueshiba/work/src/TUv++/TU/v/Confirm.h"
    "/home/ueshiba/work/src/TUv++/TU/v/ShmDC.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Timer.h"
    "/home/ueshiba/work/src/TUv++/TU/v/CanvasPaneDC.h"
    "/home/ueshiba/work/src/TUv++/TU/v/XDC.h"
    "/home/ueshiba/work/src/TUv++/TU/v/CmdWindow.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Menu.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Notify.h"
    "/home/ueshiba/work/src/TUv++/TU/v/DC.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Widget-Xaw.h"
    "/home/ueshiba/work/src/TUv++/TU/v/MemoryDC.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Colormap.h"
    "/home/ueshiba/work/src/TUv++/TU/v/TUv++.h"
    "/home/ueshiba/work/src/TUv++/TU/v/CmdPane.h"
    "/home/ueshiba/work/src/TUv++/TU/v/CanvasPaneDC3.h"
    "/home/ueshiba/work/src/TUv++/TU/v/ModalDialog.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Dialog.h"
    "/home/ueshiba/work/src/TUv++/TU/v/App.h"
    "/home/ueshiba/work/src/TUv++/TU/v/CanvasPane.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Bitmap.h"
    "/home/ueshiba/work/src/TUv++/TU/v/Icon.h"
    "/home/ueshiba/work/src/TUv++/TU/v/FileSelection.h"
    "/home/ueshiba/work/src/TUv++/TU/v/DC3.h"
    )
endif()


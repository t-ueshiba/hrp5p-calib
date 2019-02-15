# Install script for directory: /home/ueshiba/work/src/hrp5p-comps/V4L2MultiCamera

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/V4L2MultiCameraComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/V4L2MultiCameraComp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/V4L2MultiCameraComp"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/V4L2MultiCamera/V4L2MultiCameraComp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/V4L2MultiCameraComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/V4L2MultiCameraComp")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/V4L2MultiCameraComp"
         OLD_RPATH "/home/ueshiba/usr/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/V4L2MultiCameraComp")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Dd][Ee][Bb][Uu][Gg]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    if(EXISTS "$ENV{DESTDIR}/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so"
           RPATH "")
    endif()
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/usr/local/openrtp/lib/choreonoid-1.7/rtc" TYPE SHARED_LIBRARY FILES "/home/ueshiba/projects/HRP-5P/hrp5p-calib/build/hrp5p-comps-prefix/src/hrp5p-comps-build/V4L2MultiCamera/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so")
    if(EXISTS "$ENV{DESTDIR}/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so"
           OLD_RPATH "/home/ueshiba/usr/lib:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/openrtp/lib/choreonoid-1.7/rtc/V4L2MultiCameraRTC.so")
      endif()
    endif()
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Dd][Ee][Bb][Uu][Gg]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
endif()


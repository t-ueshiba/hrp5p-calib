cmake_minimum_required(VERSION 3.0)

project(hrp5p-vidsync)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
find_package(PkgConfig)

#########################################
#  Load external project		#
#########################################
set(EXTERNAL_PREFIX
    $ENV{HOME}/openrtp  CACHE STRING "External prefix")
set(EXTERNAL_SOURCE_ROOT
    $ENV{HOME}/work/src CACHE STRING "External source root")

include(ExternalProject)

#########################################
#  Load external project: TUTools++	#
#########################################
ExternalProject_Add(
    TUTools++
    SOURCE_DIR		${EXTERNAL_SOURCE_ROOT}/TUTools++
    GIT_REPOSITORY	https://github.com/t-ueshiba/TUToolsPP
    CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX=${EXTERNAL_PREFIX}
)

#########################################
#  Load external project: TUv++		#
#########################################
include(FindX11_Xaw3d)
find_package(X11_Xaw3d)

if(X11_Xaw3d_FOUND)
  ExternalProject_Add(
      TUv++
      SOURCE_DIR	${EXTERNAL_SOURCE_ROOT}/TUv++
      GIT_REPOSITORY	https://github.com/t-ueshiba/TUvPP
      CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX=${EXTERNAL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${EXTERNAL_PREFIX}/lib
  )
endif()

#########################################
#  Load external project: TUIIDC++	#
#########################################
pkg_check_modules(LIBRAW1394	libraw1394)
pkg_check_modules(LIBUSB	libusb-1.0)

if(LIBRAW1394_FOUND AND LIBUSB_FOUND)
  ExternalProject_Add(
      TUIIDC++
      SOURCE_DIR	${EXTERNAL_SOURCE_ROOT}/TUIIDC++
      GIT_REPOSITORY	https://github.com/t-ueshiba/TUIIDCPP
      CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX=${EXTERNAL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${EXTERNAL_PREFIX}/lib
  )
endif()

#########################################
#  Load external project: TUV4L2++	#
#########################################
if(EXISTS "/usr/include/linux/videodev2.h")
  ExternalProject_Add(
      TUV4L2++
      SOURCE_DIR	${EXTERNAL_SOURCE_ROOT}/TUV4L2++
      GIT_REPOSITORY	https://github.com/t-ueshiba/TUV4L2PP
      CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX=${EXTERNAL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${EXTERNAL_PREFIX}/lib
  )
endif()

#########################################
#  Load external project: htp5p-comps	#
#########################################
ExternalProject_Add(
    hrp5p-comps
    SOURCE_DIR		${EXTERNAL_SOURCE_ROOT}/hrp5p-comps
    GIT_REPOSITORY	https://github.com/t-ueshiba/hrp5p-comps
    CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX=${EXTERNAL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${EXTERNAL_PREFIX}/lib
)

#########################################
#  misc. programs			#
#########################################
add_subdirectory(src)

cmake_minimum_required(VERSION 3.0)

project(hrp5p-calib)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
find_package(PkgConfig)

if(DEFINED OPENRTM_DIR)
  set(OPENRTM_ARGS "-DOPENRTM_DIR=${OPENRTM_DIR}")
else()
  set(OPENRTM_ARGS "")
endif()

#########################################
#  Load external project		#
#########################################
set(EXTERNAL_SOURCE_ROOT
    $ENV{HOME}/src CACHE STRING "External source root")

include(ExternalProject)

#########################################
#  Load external project: TUTools++	#
#########################################
ExternalProject_Add(
    TUTools++
    SOURCE_DIR		${EXTERNAL_SOURCE_ROOT}/TUTools++
    GIT_REPOSITORY	https://github.com/t-ueshiba/TUToolsPP
    CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

#########################################
#  Load external project: htp5p-comps	#
#########################################
ExternalProject_Add(
    hrp5p-comps
    SOURCE_DIR		${EXTERNAL_SOURCE_ROOT}/hrp5p-comps
    GIT_REPOSITORY	https://github.com/t-ueshiba/hrp5p-comps
    CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib
			${OPENRTM_ARGS}
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
      CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib
  )
  add_dependencies(TUv++ TUTools++)
  add_dependencies(hrp5p-comps TUv++)
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
      CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib
  )
  add_dependencies(TUIIDC++ TUTools++)
  add_dependencies(hrp5p-comps TUIIDC++)
endif()

#########################################
#  Load external project: TUV4L2++	#
#########################################
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  ExternalProject_Add(
      TUV4L2++
      SOURCE_DIR	${EXTERNAL_SOURCE_ROOT}/TUV4L2++
      GIT_REPOSITORY	https://github.com/t-ueshiba/TUV4L2PP
      CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
			-DCMAKE_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib
  )
  add_dependencies(TUV4L2++ TUTools++)
  add_dependencies(hrp5p-comps TUV4L2++)
endif()

#########################################
#  misc. programs			#
#########################################
#add_subdirectory(src)

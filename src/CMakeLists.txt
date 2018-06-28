enable_language(CXX)
set(CMAKE_CXX_STANDARD		14)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)
set(CMAKE_CXX_EXTENSIONS	OFF)
set(CMAKE_CXX_FLAGS_RELEASE	"-Wall -O3")
set(CMAKE_CXX_FLAGS_DEBUG	"-g")
set(CMAKE_BUILD_TYPE		Release)
add_definitions(-DNDEBUG)

find_package(X11 REQUIRED)
find_package(Boost REQUIRED)
find_package(TULibs REQUIRED)

if(TUVPP_FOUND)
  include_directories(${Boost_INCLUDE_DIRS}
		      ${X11_INCLUDE_DIRS}
		      ${TULIBS_INCLUDE_DIR})

  add_subdirectory(fv)

  if(TUIIDCPP_FOUND)
    add_subdirectory(flowIIDCcamera)
  endif()
endif()

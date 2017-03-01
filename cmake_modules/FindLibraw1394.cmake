find_path(LIBRAW1394_INCLUDE_DIR
	  libraw1394
	  PATHS /opt/local/include /usr/include /usr/local/include
	  DOC "the top directory of libbraw1394 in libraw1394")

if (LIBRAW1394_INCLUDE_DIR)
  message(STATUS "Looking for libraw1394 - found")
else (LIBRAW1394_INCLUDE_DIR)
  message(FATAL_ERROR "Looking for libraw1394 - not found")
endif (LIBRAW1394_INCLUDE_DIR)

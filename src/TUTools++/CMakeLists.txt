#
#
#
cmake_minimum_required(VERSION 2.4)

include_directories(.)

set(sources
  ColorConverter.cc
  EdgeDetector.cc
  FIRGaussianCoefficients.cc
  FeatureMatch.cc
  GaussianCoefficients.cc
  GenericImage.cc
  ImageBase.cc
  Random.cc
  Rectify.cc
  SURFCreator.cc
  fdstream.cc
  io.cc
  manipulators.cc)

add_library(TUTools++ SHARED ${sources})

set(serial "1.0.0")
set(soserial "1")
set_target_properties(TUTools++ PROPERTIES
		      VERSION	${serial}
		      SOVERSION ${soserial})

install(TARGETS TUTools++ LIBRARY DESTINATION lib)

add_subdirectory(TU)


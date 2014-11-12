#===============================================================================
# CMake settings
#===============================================================================
cmake_minimum_required(VERSION 2.8.4)

#===============================================================================
# Project information
#===============================================================================
project(dart)

set(DART_MAJOR_VERSION "5")
set(DART_MINOR_VERSION "0")
set(DART_PATCH_VERSION "0")
set(DART_PKG_DESC "Dynamic Animation and Robotics Toolkit")
set(DART_VERSION "${DART_MAJOR_VERSION}.${DART_MINOR_VERSION}.${DART_PATCH_VERSION}")
set(DART_PKG_EXTERNAL_DEPS "")

#===============================================================================
# Print intro
#===============================================================================
message(STATUS "")
message(STATUS "======================")
message(STATUS "     DART ${DART_VERSION}")
message(STATUS "======================")

#===============================================================================
# Options
#===============================================================================
option(ENABLE_OPENMP "Build with OpenMP parallaization enabled" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TUTORIALS "Build tutorials" ON)

#===============================================================================
# Compiler flags
#===============================================================================
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(CMAKE_COMPILER_IS_GNUCXX)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(SEND_ERROR "Compiler not supported.")
endif()

#===============================================================================
# Find dependencies
#===============================================================================
message(STATUS "")
message(STATUS "[ Finding 3rd Party Packages ]")
#message(STATUS "")

#===============================================================================
# Print setting messages
#===============================================================================
message(STATUS "")
message(STATUS "[ Settings ]")
#message(STATUS "")
message(STATUS "Compiler ID      : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message(STATUS "ENABLE_OPENMP    : ${ENABLE_OPENMP}")
message(STATUS "BUILD_EXAMPLES   : ${BUILD_EXAMPLES}")
message(STATUS "BUILD_TUTORIALS  : ${BUILD_TUTORIALS}")
message(STATUS "Install path     : ${CMAKE_INSTALL_PREFIX}")
if(DEFINED CMAKE_CXX_FLAGS)
  message(STATUS "Custom CFlags    : ${CMAKE_CXX_FLAGS}")
else()
  message(STATUS "Custom CFlags    : Used default CFlags")
endif()
message(STATUS "CMAKE_SOURCE_DIR : ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")

#===============================================================================
# Configure files
#===============================================================================
message(STATUS "")
message(STATUS "[ Configuring files ]")
#message(STATUS "")

#===============================================================================
# Add sub-directories
#===============================================================================
add_subdirectory(dart)

#===============================================================================
# END
#===============================================================================
message(STATUS "")

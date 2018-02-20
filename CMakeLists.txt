#===============================================================================
# CMake settings
#===============================================================================
cmake_minimum_required(VERSION 3.5.1)

# Use MACOSX_RPATH by default on OS X. This was added in CMake 2.8.12 and
# became default in CMake 3.0. Explicitly setting this policy is necessary to
# suppress a warning in CMake 3.0 and above.
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

# Simplify variable reference and escape sequence evaluation. This was added in
# CMake 3.1. Explicitly setting this policy is necessary to suppress a warning
# in CMake 3.1 and above.
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(${CMAKE_MODULE_PATH}/Macros.cmake)

#===============================================================================
# Project information
#===============================================================================
project(cpptemplate VERSION 0.0.0 LANGUAGES CXX)
# The project() command stores the version number and its components in
# variables
# PROJECT_VERSION, <PROJECT-NAME>_VERSION
# PROJECT_VERSION_MAJOR, <PROJECT-NAME>_VERSION_MAJOR
# PROJECT_VERSION_MINOR, <PROJECT-NAME>_VERSION_MINOR
# PROJECT_VERSION_PATCH, <PROJECT-NAME>_VERSION_PATCH
# PROJECT_VERSION_TWEAK, <PROJECT-NAME>_VERSION_TWEAK

#===============================================================================
# Options
#===============================================================================
option(VERBOSE "" OFF)

#===============================================================================
# Find dependencies
#===============================================================================
# Eigen (required)
find_package(Eigen REQUIRED)

#===============================================================================
# Add sub-directories
#===============================================================================
include_directories(include)
include_directories(src)
add_subdirectory(include/${CMAKE_PROJECT_NAME})
add_subdirectory(src)

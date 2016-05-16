#===============================================================================
# CMake settings
#===============================================================================
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(${CMAKE_MODULE_PATH}/Macros.cmake)

#===============================================================================
# Project information
#===============================================================================
project(cpptemplate)

set(DART_MAJOR_VERSION "0")
set(DART_MINOR_VERSION "1")
set(DART_PATCH_VERSION "0")
set(DART_PKG_DESC "Dynamic Animation and Robotics Toolkit")
set(DART_VERSION "${DART_MAJOR_VERSION}.${DART_MINOR_VERSION}.${DART_PATCH_VERSION}")

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
option(DART_DOUBLE_PRECISION "Double precision" ON)
option(ENABLE_OPENMP "Build with OpenMP parallaization enabled" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TUTORIALS "Build tutorials" ON)
option(BUILD_DOCUMENTATION "Build API document" ON)

#===============================================================================
# Compiler flags
#===============================================================================
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
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

# Eigen (required)
find_package(Eigen REQUIRED)
if(EIGEN_FOUND)
  message(STATUS "Eigen: found")
else()
  message(SEND_ERROR "Eigen: not found")
endif()

#===============================================================================
# Print build summary
#===============================================================================
message(STATUS "")
message(STATUS "[ Build summary ]")
#message(STATUS "")
message(STATUS "CMAKE_GENERATOR  : ${CMAKE_GENERATOR}")
message(STATUS "Compiler ID      : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message(STATUS "DOUBLE_PRECISION : ${DART_DOUBLE_PRECISION}")
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

# Generate the dart config file (reference: http://www.vtk.org/Wiki/CMake:How_To_Write_Platform_Checks)
set(${CMAKE_PROJECT_NAME}_CONFIG_IN "${CMAKE_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/Config.hpp.in")
set(${CMAKE_PROJECT_NAME}_CONFIG_OUT ${CMAKE_BINARY_DIR}/include/${CMAKE_PROJECT_NAME}/Config.hpp)
configure_file(
    ${${CMAKE_PROJECT_NAME}_CONFIG_IN}
    ${${CMAKE_PROJECT_NAME}_CONFIG_OUT} @ONLY)
install(
    FILES ${${CMAKE_PROJECT_NAME}_CONFIG_OUT}
    DESTINATION include/${CMAKE_PROJECT_NAME})
message(STATUS "Config.h.in    -> ${${CMAKE_PROJECT_NAME}_CONFIG_OUT}")

#===============================================================================
# Include directories
#===============================================================================
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

include_directories(${Eigen_INCLUDE_DIRS})

#===============================================================================
# Add sub-directories
#===============================================================================
include_directories(include)
include_directories(src)
add_subdirectory(include/cpptemplate)
add_subdirectory(src)

# Add an "examples" target to build examples.
add_subdirectory(examples)

get_property(examples GLOBAL PROPERTY ${CMAKE_PROJECT_NAME}_EXAMPLES)
add_custom_target(examples DEPENDS ${examples})

message(STATUS "")
message(STATUS "[ Examples ]")

foreach(example ${examples})
  message(STATUS "Adding example: ${example}")
endforeach(example ${examples})

# Add a "tests" target to build unit tests.
enable_testing()
add_subdirectory(tests)

get_property(tests GLOBAL PROPERTY ${CMAKE_PROJECT_NAME}_TESTS)
add_custom_target(tests DEPENDS ${unittests})

message(STATUS "")
message(STATUS "[ Unit Tests ]")
foreach(unittest ${unittests})
  message(STATUS "Adding test: ${unittest}")
endforeach(unittest ${unittests})

#===============================================================================
# Code Formatting
#===============================================================================
message(STATUS "")
message(STATUS "[ Code Formatting ]")

find_program(CLANG_FORMAT_EXECUTABLE
             NAMES clang-format clang-format-3.9 clang-format-3.8)

if (CLANG_FORMAT_EXECUTABLE)

  message(STATUS "Looking for clang-format - found")

  file(GLOB_RECURSE FORMAT_FILES
       ${CMAKE_SOURCE_DIR}/include/*.hpp
       ${CMAKE_SOURCE_DIR}/src/*.cpp)

  add_custom_target(format
                    COMMAND ${CMAKE_COMMAND} -E echo "Formatting code... "
                    COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=file -i ${FORMAT_FILES}
                    COMMAND ${CMAKE_COMMAND} -E echo "Done."
                    DEPENDS ${CLANG_FORMAT_EXECUTABLE})

  add_custom_target(check-format
                    COMMAND ${CMAKE_COMMAND} -E echo "Checking code format... "
                    COMMAND ${CMAKE_SOURCE_DIR}/tools/check_format.sh ${CLANG_FORMAT_EXECUTABLE} ${FORMAT_FILES}
                    COMMAND ${CMAKE_COMMAND} -E echo "Done."
                    DEPENDS ${CLANG_FORMAT_EXECUTABLE})

else()

  message(STATUS "Looking for clang-format - NOT found, please install clang-format to enable automatic code formatting")

endif()

#===============================================================================
# API Document using Doxygen
#===============================================================================
# Reference:
# http://mementocodex.wordpress.com/2013/01/19/how-to-generate-code-documentation-with-doxygen-and-cmake-a-slightly-improved-approach/
# http://www.cmake.org/pipermail/cmake/2007-February/012796.html
if(BUILD_DOCUMENTATION)
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    set(DOXYGEN_DOXYFILE_IN  ${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in    )
    set(DOXYGEN_DOXYFILE     ${PROJECT_BINARY_DIR}/doxygen/Doxyfile       )
    set(DOXYGEN_HTML_INDEX   ${PROJECT_SOURCE_DIR}/doxygen/html/index.html)
    set(DOXYGEN_OUTPUT_ROOT  ${PROJECT_SOURCE_DIR}/doxygen/html           ) # Pasted into Doxyfile.in
    set(DOXYGEN_INPUT_ROOT   ${PROJECT_SOURCE_DIR}/dart                   ) # Pasted into Doxyfile.in
    set(DOXYGEN_EXTRA_INPUTS ${PROJECT_SOURCE_DIR}/doxygen/mainpage.dox   ) # Pasted into Doxyfile.in

    configure_file(${DOXYGEN_DOXYFILE_IN} ${DOXYGEN_DOXYFILE} @ONLY)

    add_custom_command(
      OUTPUT ${DOXYGEN_HTML_INDEX}
      COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
      COMMAND ${DOXYGEN_EXECUTABLE} -u ${DOXYGEN_DOXYFILE}
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_DOXYFILE}
      COMMAND ${CMAKE_COMMAND} -E echo "Done."
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doxygen
      DEPENDS ${DOXYGEN_DOXYFILE}
    )
    add_custom_target(docs DEPENDS ${DOXYGEN_HTML_INDEX})
    add_custom_target(
      docs_forced
      COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
      COMMAND ${DOXYGEN_EXECUTABLE} -u ${DOXYGEN_DOXYFILE}
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_DOXYFILE}
      COMMAND ${CMAKE_COMMAND} -E echo "Done."
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doxygen
    )

    install(DIRECTORY ${DOXYGEN_OUTPUT_ROOT} DESTINATION share/doc)

  else()
    message(WARNING "Doxygen is required to build the API documentation.")
  endif()
endif()

#===============================================================================
# END
#===============================================================================
message(STATUS "")

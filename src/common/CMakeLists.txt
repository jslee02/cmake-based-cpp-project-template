get_filename_component(DIRECTORY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(target_name ${PROJECT_NAME}-${DIRECTORY_NAME})

set(SOURCES
  Template.cpp
)

add_library(${target_name}
  ${${CMAKE_PROJECT_NAME}_HEADERS} ${SOURCES}
)

target_include_directories(${target_name}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}-${DIRECTORY_NAME}
  ${SOME_DEPENDENCY_LIBRARY}
)

target_compile_options(${target_name} PRIVATE -Werror)

target_compile_features(${target_name} PUBLIC cxx_std_11)

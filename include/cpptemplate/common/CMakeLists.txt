get_filename_component(DIRECTORY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

set(HEADERS
    Template.hpp)

add_library(${DIRECTORY_NAME}_HEADERS STATIC ${HEADERS})
set_target_properties(${DIRECTORY_NAME}_HEADERS PROPERTIES LINKER_LANGUAGE CXX)

generate_include_header_list(common_headers
                             "dart5/common/"
                             "common headers"
                             ${HEADERS})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/common.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/common.hpp)


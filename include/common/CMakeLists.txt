file(GLOB hdrs "*.hpp")

generate_include_header_list(common_headers
                             "dart5/common/"
                             "common headers"
                             ${hdrs})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/common.in
               ${CMAKE_CURRENT_BINARY_DIR}/common)


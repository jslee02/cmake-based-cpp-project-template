file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.h")
add_library(common ${srcs} ${hdrs})
target_link_libraries(common ${CMAKE_DL_LIBS})

generate_include_header_list(common_headers
                             "dart5/common/"
                             "common headers"
                             ${hdrs})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/common.in
               ${CMAKE_CURRENT_BINARY_DIR}/common)


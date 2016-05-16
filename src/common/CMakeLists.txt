file(GLOB srcs "*.cpp")
add_library(common ${srcs})
target_link_libraries(common ${CMAKE_DL_LIBS})

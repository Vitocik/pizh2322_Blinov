add_library(argparser STATIC ArgParser.cpp)
target_include_directories(argparser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

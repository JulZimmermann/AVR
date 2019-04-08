add_library(util STATIC)

target_sources(util PRIVATE UART.cpp)

target_include_directories(util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
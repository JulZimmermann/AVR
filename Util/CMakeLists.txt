add_library(util STATIC UART.h UART.cpp
                        Port.h
                        Pins.h
                        InterruptHandler.h)

target_include_directories(util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
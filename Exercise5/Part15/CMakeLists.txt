add_flashable_executable(e5p15HalloWelt sendHalloWelt.cpp UART.h UART.cpp)

target_link_libraries(e5p15HalloWelt util)
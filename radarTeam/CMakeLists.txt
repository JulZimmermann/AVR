cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "-mmcu=atmega32 -Os -save-temps")
add_definitions(-DF_CPU=1000000)

include(FlashableExecutable.cmake)

project(AVR)

add_subdirectory(Util)

add_subdirectory(Exercise11ButtonBlink)
add_subdirectory(Exercise13LedTimer)
add_subdirectory(Exercise14Song)
add_subdirectory(Exercise15UART)
add_subdirectory(Exercise16SdCard)
add_subdirectory(Other)
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "-mmcu=atmega32 -Os -save-temps")
add_definitions(-DF_CPU=1000000)

include(FlashableExecutable.cmake)

project(AVR)

add_subdirectory(Util)

add_subdirectory(Exercise3/Part1)
add_subdirectory(Exercise3/Part1C)
add_subdirectory(Exercise4/Part13)
add_subdirectory(Exercise4/Part14)
add_subdirectory(Exercise5/Part15)
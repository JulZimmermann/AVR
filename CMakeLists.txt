cmake_minimum_required(VERSION 3.7)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-mmcu=atmega32 -O3")
add_definitions(-DF_CPU=1000000)

project(AVR)

add_subdirectory(Util)

if(NOT PORT)
    set(PORT /dev/ttyUSB0)
endif()

add_subdirectory(Exercise3)


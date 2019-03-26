cmake_minimum_required(VERSION 3.7)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-mmcu=atmega32")

add_definitions(-DF_CPU=1000000)

project(AVR)

SET(PORT COM9)

add_subdirectory(Exercise3)


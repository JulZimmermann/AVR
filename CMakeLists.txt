cmake_minimum_required(VERSION 3.13)

set(AVR_MCU atmega32)

# TODO: Check why AVR_MCU doesn't set D__AVR_ATmega32__
add_definitions(-D__AVR_ATmega32__)
add_definitions(-DF_CPU=1000000)

project(AVR)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Exercise3)


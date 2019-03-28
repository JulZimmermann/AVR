if(NOT SERIAL_FLASH_PORT)
    set(SERIAL_FLASH_PORT /dev/ttyUSB0 CACHE STRING "Port for flashing the programm")
endif()

function(add_flashable_executable)
    add_executable(${ARGV})

    add_custom_command(TARGET ${ARGV0} POST_BUILD
            COMMAND avr-objcopy -O ihex ${ARGV0} ${ARGV0}.hex
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Creating hex file")

    add_custom_target(${ARGV0}_flash COMMAND avrdude -p m32 -c stk500 -U flash:w:${ARGV0}.hex -P ${SERIAL_FLASH_PORT}
            DEPENDS ${ARGV0})
endfunction()
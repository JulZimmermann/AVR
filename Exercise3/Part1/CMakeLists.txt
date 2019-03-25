SET(PART_NAME e3p1)

add_executable(${PART_NAME} main.cpp test.h)

add_custom_command(TARGET ${PART_NAME} POST_BUILD
        COMMAND avr-objcopy -O ihex ${PART_NAME} ${PART_NAME}.hex
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Creating HEX File")

add_custom_target(${PART_NAME}_flash COMMAND avrdude -p m32 -c stk500 -U flash:w:${PART_NAME}.hex -F -P /dev/ttyUSB0
                                     DEPENDS ${PART_NAME})
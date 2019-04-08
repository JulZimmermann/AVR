add_flashable_executable(e5p15HalloWelt sendHalloWelt.cpp)
target_link_libraries(e5p15HalloWelt util)

add_flashable_executable(e5p15Echo echo.cpp)
target_link_libraries(e5p15Echo util)

add_flashable_executable(e5p15Led led.cpp)
target_link_libraries(e5p15Led util)
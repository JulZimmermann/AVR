add_flashable_executable(keyboard keyboard.cpp)
add_flashable_executable(e4p14a a.cpp Note.h)

target_link_libraries(keyboard util)
target_link_libraries(e4p14a util)
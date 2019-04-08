add_flashable_executable(keyboard keyboard.cpp)
target_link_libraries(keyboard util)

add_flashable_executable(e4p14aEnten aEnten.cpp Note.h Song.h)
target_link_libraries(e4p14aEnten util)

add_flashable_executable(e4p14aEntenPlayer aEntenPlayer.cpp Note.h Player.h Song.h)
target_link_libraries(e4p14aEntenPlayer util)
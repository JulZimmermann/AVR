add_flashable_executable(keyboard keyboard.cpp)
target_link_libraries(keyboard util)

add_flashable_executable(e14Enten aEnten.cpp Note.h Song.h)
target_link_libraries(e14Enten util)

add_flashable_executable(e14EntenPlayer aEntenPlayer.cpp Note.h Player.h Song.h)
target_link_libraries(e14EntenPlayer util)
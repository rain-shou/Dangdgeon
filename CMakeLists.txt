cmake_minimum_required(VERSION 3.30)
project(Dangdgeon C)

set(CMAKE_C_STANDARD 11)

add_executable(Dangdgeon main.c
        curses_dealer.c
        curses_dealer.h
        map_generator.c
        map_generator.h
        map_data.h
        map_data.c
        player_control.h
        player_control.c
        game_init.h
        game_init.c
        rendering.h
        rendering.c
        player_generator.h
        player_generator.c
        environment_generator.h
        environment_generator.c
        interface.h
        interface.c
        general_script.c
        general_script.h
        dialogue.h
        dialogue.c
        equipment_data.h
        equipment_data.c
        player_data.h
        player_data.c
        entity_generator.h
        entity_generator.c
        enemy_data.h
        enemy_data.c
        enemy_generator.h
        enemy_generator.c
        combat_script.h
        combat_script.c
        enemy_script.h
        enemy_script.c
        saver_loader.h
        saver_loader.c
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(Dangdgeon ${CURSES_LIBRARIES})

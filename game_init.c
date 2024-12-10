#include "game_init.h"

void initializing(void) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            map_layer[i][j] = ' ';
            entity_layer[i][j] = ' ';
            walkable_layer[i][j] = 0;
            explored_layer[i][j] = false;
        }
    }
    for (int i = 0; i <= 8; ++i) {
        room_data[i].is_exist = true;
        for (int j = 0; j < 4; ++j) {
            room_data[i].map_info.gate[j].is_exist = true;
        }
    }
}

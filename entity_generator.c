#include <stdlib.h>
#include "entity_generator.h"
#include "shared.h"

void generate_entity() {
    for (int stair_pos_x, stair_pos_y;;) {
        stair_pos_x = (int)(random() % 99 + 1);
        stair_pos_y = (int)(random() % 35 + 1);
        if (walkable_layer[stair_pos_y][stair_pos_x] != 0 && map_layer[stair_pos_y][stair_pos_x] == ' '
                && entity_layer[stair_pos_y][stair_pos_x] == ' ') {
            entity_layer[stair_pos_y][stair_pos_x] = '%';
            break;
        }
    }
    for (;;) {
        player_pos_x = (int)(random() % 99 + 1);
        player_pos_y = (int)(random() % 35 + 1);
        if (walkable_layer[player_pos_y][player_pos_x] != 0 && map_layer[player_pos_y][player_pos_x] == ' '
                && entity_layer[player_pos_y][player_pos_x] == ' ') {
            entity_layer[player_pos_y][player_pos_x] = '@';
            break;
        }
    }
}

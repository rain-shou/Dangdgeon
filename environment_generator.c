#include <stdlib.h>
#include "environment_generator.h"
#include "shared.h"

void generate_stairs(void) {
    if (layer != 50) {
        for (int stair_pos_x, stair_pos_y;;) {
            stair_pos_x = (int)(random() % 99 + 1);
            stair_pos_y = (int)(random() % 35 + 1);
            if (walkable_layer[stair_pos_y][stair_pos_x] >= 0 && walkable_layer[stair_pos_y][stair_pos_x] < 9
                && entity_layer[stair_pos_y][stair_pos_x] == ' ') {
                walkable_layer[stair_pos_y][stair_pos_x] = 13;
                downstairs_pos[layer - 1][0] = stair_pos_x;
                downstairs_pos[layer - 1][1] = stair_pos_y;
                break;
            }
        }
    }
    if (layer != 1) {
        for (int stair_pos_x, stair_pos_y;;) {
            stair_pos_x = (int)(random() % 99 + 1);
            stair_pos_y = (int)(random() % 35 + 1);
            if (walkable_layer[stair_pos_y][stair_pos_x] >= 0 && walkable_layer[stair_pos_y][stair_pos_x] < 9
                && entity_layer[stair_pos_y][stair_pos_x] == ' ') {
                walkable_layer[stair_pos_y][stair_pos_x] = 14;
                upstairs_pos[layer - 1][0] = stair_pos_x;
                upstairs_pos[layer - 1][1] = stair_pos_y;
                break;
            }
        }
    }
}

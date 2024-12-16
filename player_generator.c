#include <stdlib.h>
#include "player_generator.h"
#include "map_data.h"
#include "player_data.h"

void generate_player(void) {
    if (layer == 1) {
        for (;;) {
            player.pos_x = (int)(random() % 99 + 1);
            player.pos_y = (int)(random() % 35 + 1);
            if (walkable_layer[player.pos_y][player.pos_x] >= 0 && walkable_layer[player.pos_y][player.pos_x] < 9
                && entity_layer[player.pos_y][player.pos_x] == ' ') {
                entity_layer[player.pos_y][player.pos_x] = '@';
                break;
            }
        }
    } else {
        player.pos_x = upstairs_pos[current_layer - 1][0];
        player.pos_y = upstairs_pos[current_layer - 1][1];
        entity_layer[player.pos_y][player.pos_x] = '@';
    }
}

void restore_player_to_upstairs(void) {
    player.pos_x = upstairs_pos[current_layer - 1][0];
    player.pos_y = upstairs_pos[current_layer - 1][1];
    entity_layer[player.pos_y][player.pos_x] = '@';
}

void restore_player_to_downstairs(void) {
    player.pos_x = downstairs_pos[current_layer - 1][0];
    player.pos_y = downstairs_pos[current_layer - 1][1];
    entity_layer[player.pos_y][player.pos_x] = '@';
}

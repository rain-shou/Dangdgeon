#include <stdlib.h>
#include "player_generator.h"
#include "shared.h"

void generate_player() {
    if (layer == 1) {
        for (;;) {
            player_pos_x = (int)(random() % 99 + 1);
            player_pos_y = (int)(random() % 35 + 1);
            if (walkable_layer[player_pos_y][player_pos_x] >= 0 && walkable_layer[player_pos_y][player_pos_x] < 9
                && entity_layer[player_pos_y][player_pos_x] == ' ') {
                entity_layer[player_pos_y][player_pos_x] = '@';
                break;
            }
        }
    } else {
        if ((walkable_layer[upstairs_pos[layer - 1][1] - 1][upstairs_pos[layer - 1][0]]) >= 0 &&
                (walkable_layer[upstairs_pos[layer - 1][1] - 1][upstairs_pos[layer - 1][0]]) < 9 &&
                entity_layer[upstairs_pos[layer - 1][1] - 1][upstairs_pos[layer - 1][0]] == ' ') {
            player_pos_x = upstairs_pos[layer - 1][0];
            player_pos_y = upstairs_pos[layer - 1][1] - 1;
            entity_layer[player_pos_y][player_pos_x] = '@';
        } else if ((walkable_layer[upstairs_pos[layer - 1][1] + 1][upstairs_pos[layer - 1][0]]) >= 0 &&
                   (walkable_layer[upstairs_pos[layer - 1][1] + 1][upstairs_pos[layer - 1][0]]) < 9 &&
                   entity_layer[upstairs_pos[layer - 1][1] + 1][upstairs_pos[layer - 1][0]] == ' ') {
            player_pos_x = upstairs_pos[layer - 1][0];
            player_pos_y = upstairs_pos[layer - 1][1] + 1;
            entity_layer[player_pos_y][player_pos_x] = '@';
        } else if ((walkable_layer[upstairs_pos[layer - 1][1]][upstairs_pos[layer - 1][0]] - 1) >= 0 &&
              (walkable_layer[upstairs_pos[layer - 1][1]][upstairs_pos[layer - 1][0]] - 1) < 9 &&
              entity_layer[upstairs_pos[layer - 1][1]][upstairs_pos[layer - 1][0]] == ' ') {
            player_pos_x = upstairs_pos[layer - 1][0] - 1;
            player_pos_y = upstairs_pos[layer - 1][1];
            entity_layer[player_pos_y][player_pos_x] = '@';
        } else if ((walkable_layer[upstairs_pos[layer - 1][1]][upstairs_pos[layer - 1][0]] + 1) >= 0 &&
                   (walkable_layer[upstairs_pos[layer - 1][1]][upstairs_pos[layer - 1][0]] + 1) < 9 &&
                   entity_layer[upstairs_pos[layer - 1][1]][upstairs_pos[layer - 1][0]] == ' ') {
            player_pos_x = upstairs_pos[layer - 1][0] + 1;
            player_pos_y = upstairs_pos[layer - 1][1];
            entity_layer[player_pos_y][player_pos_x] = '@';
        }
    }
}

void restore_player_to_upstairs() {
    if ((walkable_layer[upstairs_pos[current_layer - 1][1] - 1][upstairs_pos[current_layer - 1][0]]) >= 0 &&
        (walkable_layer[upstairs_pos[current_layer - 1][1] - 1][upstairs_pos[current_layer - 1][0]]) < 9 &&
        entity_layer[upstairs_pos[current_layer - 1][1] - 1][upstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = upstairs_pos[current_layer - 1][0];
        player_pos_y = upstairs_pos[current_layer - 1][1] - 1;
        entity_layer[player_pos_y][player_pos_x] = '@';
    } else if ((walkable_layer[upstairs_pos[current_layer - 1][1] + 1][upstairs_pos[current_layer - 1][0]]) >= 0 &&
               (walkable_layer[upstairs_pos[current_layer - 1][1] + 1][upstairs_pos[current_layer - 1][0]]) < 9 &&
               entity_layer[upstairs_pos[current_layer - 1][1] + 1][upstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = upstairs_pos[current_layer - 1][0];
        player_pos_y = upstairs_pos[current_layer - 1][1] + 1;
        entity_layer[player_pos_y][player_pos_x] = '@';
    } else if ((walkable_layer[upstairs_pos[current_layer - 1][1]][upstairs_pos[current_layer - 1][0]] - 1) >= 0 &&
               (walkable_layer[upstairs_pos[current_layer - 1][1]][upstairs_pos[current_layer - 1][0]] - 1) < 9 &&
               entity_layer[upstairs_pos[current_layer - 1][1]][upstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = upstairs_pos[current_layer - 1][0] - 1;
        player_pos_y = upstairs_pos[current_layer - 1][1];
        entity_layer[player_pos_y][player_pos_x] = '@';
    } else if ((walkable_layer[upstairs_pos[current_layer - 1][1]][upstairs_pos[current_layer - 1][0]] + 1) >= 0 &&
               (walkable_layer[upstairs_pos[current_layer - 1][1]][upstairs_pos[current_layer - 1][0]] + 1) < 9 &&
               entity_layer[upstairs_pos[current_layer - 1][1]][upstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = upstairs_pos[current_layer - 1][0] + 1;
        player_pos_y = upstairs_pos[current_layer - 1][1];
        entity_layer[player_pos_y][player_pos_x] = '@';
    }
}


void restore_player_to_downstairs() {
    if ((walkable_layer[downstairs_pos[current_layer - 1][1] - 1][downstairs_pos[current_layer - 1][0]]) >= 0 &&
        (walkable_layer[downstairs_pos[current_layer - 1][1] - 1][downstairs_pos[current_layer - 1][0]]) < 9 &&
        entity_layer[downstairs_pos[current_layer - 1][1] - 1][downstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = downstairs_pos[current_layer - 1][0];
        player_pos_y = downstairs_pos[current_layer - 1][1] - 1;
        entity_layer[player_pos_y][player_pos_x] = '@';
    } else if ((walkable_layer[downstairs_pos[current_layer - 1][1] + 1][downstairs_pos[current_layer - 1][0]]) >= 0 &&
               (walkable_layer[downstairs_pos[current_layer - 1][1] + 1][downstairs_pos[current_layer - 1][0]]) < 9 &&
               entity_layer[downstairs_pos[current_layer - 1][1] + 1][downstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = downstairs_pos[current_layer - 1][0];
        player_pos_y = downstairs_pos[current_layer - 1][1] + 1;
        entity_layer[player_pos_y][player_pos_x] = '@';
    } else if ((walkable_layer[downstairs_pos[current_layer - 1][1]][downstairs_pos[current_layer - 1][0]] - 1) >= 0 &&
               (walkable_layer[downstairs_pos[current_layer - 1][1]][downstairs_pos[current_layer - 1][0]] - 1) < 9 &&
               entity_layer[downstairs_pos[current_layer - 1][1]][downstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = downstairs_pos[current_layer - 1][0] - 1;
        player_pos_y = downstairs_pos[current_layer - 1][1];
        entity_layer[player_pos_y][player_pos_x] = '@';
    } else if ((walkable_layer[downstairs_pos[current_layer - 1][1]][downstairs_pos[current_layer - 1][0]] + 1) >= 0 &&
               (walkable_layer[downstairs_pos[current_layer - 1][1]][downstairs_pos[current_layer - 1][0]] + 1) < 9 &&
               entity_layer[downstairs_pos[current_layer - 1][1]][downstairs_pos[current_layer - 1][0]] == ' ') {
        player_pos_x = downstairs_pos[current_layer - 1][0] + 1;
        player_pos_y = downstairs_pos[current_layer - 1][1];
        entity_layer[player_pos_y][player_pos_x] = '@';
    }
}

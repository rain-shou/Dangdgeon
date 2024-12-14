#include <stdlib.h>
#include "entity_generator.h"
#include "equipment_data.h"
#include "map_data.h"

void refresh_entity_layer(void) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            entity_layer[i][j] = ' ';
        }
    }
}

void generate_entity_layer(void) {
    generate_equipment();
    generate_gold();
    generate_potion();
}

void generate_equipment(void) {
    int flag = false;
    for (int i = 0; i < 8; i++) {
        if (weapon_list[i].floor == current_layer && !weapon_list[i].be_taken) {
            layer_treasure[0] = 0;
            layer_treasure[1] = weapon_list[i].equipment_number;
            flag = true;
            break;
        } else if (armor_list[i].floor == current_layer && !armor_list[i].be_taken) {
            layer_treasure[0] = 1;
            layer_treasure[1] = armor_list[i].equipment_number;
            flag = true;
            break;
        }
    }
    if (flag) {
        for (;;) {
            int pos_x = (int)(random() % 99 + 1);
            int pos_y = (int)(random() % 35 + 1);
            if (walkable_layer[pos_y][pos_x] >= 0 && walkable_layer[pos_y][pos_x] < 9
                && entity_layer[pos_y][pos_x] == ' ') {
                if (layer_treasure[0] == 0) {
                    entity_layer[pos_y][pos_x] = ')';
                } else if (layer_treasure[0] == 1) {
                    entity_layer[pos_y][pos_x] = '[';
                }
                break;
            }
        }
    }
}

void generate_gold(void) {
    int total_gold = (int)(random() % ((current_layer + 3) / 3) + 1);
    for (int i = 0; i < total_gold; i++) {
        for (;;) {
            int pos_x = (int)(random() % 99 + 1);
            int pos_y = (int)(random() % 35 + 1);
            if (walkable_layer[pos_y][pos_x] >= 0 && walkable_layer[pos_y][pos_x] < 9
                && entity_layer[pos_y][pos_x] == ' ') {
                entity_layer[pos_y][pos_x] = '*';
                break;
            }
        }
    }
}

void generate_potion(void) {
    int total_potion = (int)(random() % current_layer + 1) % 5;
    for (int i = 0; i < total_potion; i++) {
        for (;;) {
            int pos_x = (int)(random() % 99 + 1);
            int pos_y = (int)(random() % 35 + 1);
            if (walkable_layer[pos_y][pos_x] >= 0 && walkable_layer[pos_y][pos_x] < 9
                && entity_layer[pos_y][pos_x] == ' ') {
                entity_layer[pos_y][pos_x] = '!';
                break;
            }
        }
    }
}

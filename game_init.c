#include <stdlib.h>
#include "game_init.h"
#include "dialogue.h"
#include "interface.h"
#include "player_data.h"
#include "map_data.h"
#include "equipment_data.h"

void initialize_game(void) {
    initialize_player(&player);
    get_player_name(player.name, MAX_NAME_LENGTH);
    layer = 0;
    current_layer = 1;
    for (int i = 0; i < LAYER; i++) {
        for (int j = 0; j < WIDTH; ++j) {
            for (int k = 0; k < LENGTH; ++k) {
                total_walkable_layer[i][j][k] = -1;
                total_explored_layer[i][j][k] = 0;
            }
        }
    }
    dialogue = create_dialogue();
    up_or_down = true;
    assign_equipments_to_unique_floors();
}

// void test_bag(void) {
// #include "string.h"
//     for (int i = 0; i < 8; i++) {
//         player.bag[i].number = weapon_list[i].equipment_number;
//         player.bag[i].has_equipped = false;
//         strncpy(player.bag[i].name, weapon_list[i].name, 20);
//         player.bag[i].category = 0;
//         player.bag_number++;
//     }
//     for (int i = 0; i < 8; i++) {
//         player.bag[i + 8].number = armor_list[i].equipment_number;
//         player.bag[i + 8].has_equipped = false;
//         strncpy(player.bag[i + 8].name, armor_list[i].name, 20);
//         player.bag[i + 8].category = 1;
//         player.bag_number++;
//     }
// }

void initialize_player(struct player_data *p) {
    p->health = 100;
    p->max_health = 100;
    p->attack = 10;
    p->total_attack = p->attack;
    p->defense = 5;
    p->total_defense = p->defense;
    p->level = 1;
    p->gold = 0;
    p->experience = 100;
    p->armor = 0;
    p->weapon = 0;
    p->portion = 0;
    // test_bag();
    p->bag_number = 0;
}

void initialize_layer(void) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            entity_layer[i][j] = ' ';
            walkable_layer[i][j] = -1;
            explored_layer[i][j] = 0;
        }
    }
    for (int i = 0; i <= 8; ++i) {
        room_data[i].is_exist = true;
        for (int j = 0; j < 4; ++j) {
            room_data[i].map_info.gate[j].is_exist = true;
        }
    }
    layer++;
}

void load_layer(int n) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            walkable_layer[i][j] = total_walkable_layer[n][i][j];
            explored_layer[i][j] = total_explored_layer[n][i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        regions[i] = total_regions[n][i];
    }
    for (int i = 0; i < 9; i++) {
        room_data[i] = total_room_data[n][i];
    }
}

void save_current_layer(int n) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            total_walkable_layer[n][i][j] = walkable_layer[i][j];
            total_explored_layer[n][i][j] = explored_layer[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        total_regions[n][i] = regions[i];
    }
    for (int i = 0; i < 9; i++) {
        total_room_data[n][i] = room_data[i];
    }
}

void assign_equipments_to_unique_floors(void) {
    for (int i = 0; i < 8; i++) {
        weapon_list[i].floor = (int)(random() % (weapon_list[i].max_floor - weapon_list[i].min_floor)) + weapon_list[i].min_floor;
        do {
            armor_list[i].floor = (int)(random() % (armor_list[i].max_floor - armor_list[i].min_floor)) + armor_list[i].min_floor;
        } while (armor_list[i].floor == weapon_list[i].floor);
    }
}

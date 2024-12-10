#include "game_init.h"
#include "shared.h"

void initialize_game(void) {
    initialize_player(&player);
    layer = 0;
}

void initialize_player(struct player_data *p) {
    p->health = 100;
    p->max_health = 100;
    p->attack = 10;
    p->defense = 5;
    p->level = 1;
    p->gold = 0;
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

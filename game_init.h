#ifndef DANGDGEON_GAME_INIT_H
#define DANGDGEON_GAME_INIT_H

#include "shared.h"

void initialize_game();
void initialize_layer();
void initialize_player(struct player_data *player);
void load_layer(int n);
void save_current_layer(int n);

#endif //DANGDGEON_GAME_INIT_H

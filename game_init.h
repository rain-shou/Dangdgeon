#ifndef DANGDGEON_GAME_INIT_H
#define DANGDGEON_GAME_INIT_H

#include "player_data.h"

void initialize_game(void);
void initialize_layer(void);
void initialize_player(struct player_data *player);
void load_layer(int n);
void save_current_layer(int n);
void assign_equipments_to_unique_floors(void);

#endif //DANGDGEON_GAME_INIT_H

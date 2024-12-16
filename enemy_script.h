#ifndef DANGDGEON_ENEMY_SCRIPT_H
#define DANGDGEON_ENEMY_SCRIPT_H

#include "enemy_data.h"

void all_enemies_move(void);
void enemy_move(struct enemy_data *);
bool check_player_besides(struct enemy_data *);
bool is_player_in_range(struct enemy_data *, int range);
void move_toward_player(struct enemy_data *);
void random_wander(struct enemy_data *);
bool enemy_can_move(int x, int y);

#endif //DANGDGEON_ENEMY_SCRIPT_H

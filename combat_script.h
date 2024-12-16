#ifndef DANGDGEON_COMBAT_SCRIPT_H
#define DANGDGEON_COMBAT_SCRIPT_H

#include "enemy_data.h"

bool trigger_combat(void);
void attack_closest_enemy(void);
bool check_combat(struct enemy_data *);
void enemy_engage_combat(struct enemy_data *);
void player_engage_combat(struct enemy_data *);
bool check_enemy_death(struct enemy_data *);
void add_experience(struct enemy_data *);
bool check_level_up(void);
void level_up(void);

#endif //DANGDGEON_COMBAT_SCRIPT_H

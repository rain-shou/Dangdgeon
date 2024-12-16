#ifndef DANGDGEON_ENEMY_GENERATOR_H
#define DANGDGEON_ENEMY_GENERATOR_H

#include "enemy_data.h"

void generate_current_layer_enemies(void);
void refresh_enemy(void);
void generate_enemy(struct enemy_data *);

#endif //DANGDGEON_ENEMY_GENERATOR_H

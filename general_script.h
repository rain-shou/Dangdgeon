#ifndef DANGDGEON_GENERAL_SCRIPT_H
#define DANGDGEON_GENERAL_SCRIPT_H

#include <stdbool.h>

void trigger_trap(void);
bool check_player_death(void);
void trigger_downstairs(void);
void trigger_upstairs(void);
void equip_equipment(int);
void pickup_weapon(void);
void pickup_armor(void);
void pickup_gold(void);
void pickup_potion(void);
void drink_potion(void);
void pickup_amulet(void);
bool check_win(void);

#endif //DANGDGEON_GENERAL_SCRIPT_H

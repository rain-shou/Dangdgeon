#ifndef DANGDGEON_SCRIPT_H
#define DANGDGEON_SCRIPT_H

#include <stdbool.h>

void trigger_trap(void);
bool check_death(void);
void trigger_downstairs(void);
void trigger_upstairs(void);
void equip_equipment(int);
void pickup_weapon(void);
void pickup_armor(void);
void pickup_gold(void);
void pickup_potion(void);
void drink_potion(void);

#endif //DANGDGEON_SCRIPT_H

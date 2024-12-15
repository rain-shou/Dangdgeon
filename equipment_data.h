#ifndef DANGDGEON_EQUIPMENT_DATA_H
#define DANGDGEON_EQUIPMENT_DATA_H

#include <stdbool.h>

#define WEAPON_AMOUNT 8
#define ARMOR_AMOUNT 8

struct equipment {
    const char *name;
    int equipment_number;
    int attack_change;
    int defense_change;
    int min_floor;
    int max_floor;
    int floor;
    bool be_taken;
};

extern struct equipment weapon_list[WEAPON_AMOUNT];
extern struct equipment armor_list[ARMOR_AMOUNT];

#endif //DANGDGEON_EQUIPMENT_DATA_H

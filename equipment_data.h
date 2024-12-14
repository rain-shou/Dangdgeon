#ifndef DANGDGEON_EQUIPMENT_DATA_H
#define DANGDGEON_EQUIPMENT_DATA_H

#include <stdbool.h>

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

extern struct equipment weapon_list[8];
extern struct equipment armor_list[8];

#endif //DANGDGEON_EQUIPMENT_DATA_H

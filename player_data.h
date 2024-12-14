#ifndef DANGDGEON_PLAYER_DATA_H
#define DANGDGEON_PLAYER_DATA_H

#define MAX_NAME_LENGTH 16
#define MAX_BAG_STORAGE 16

#include <stdbool.h>

struct bag_data {
    int category;   // 0 for weapon, 1 for armor
    int number;
    char name[20];
    bool has_equipped;
};

struct player_data {
    char name[MAX_NAME_LENGTH + 1];
    int health;
    int max_health;
    int attack;
    int total_attack;
    int defense;
    int total_defense;
    int experience;
    int level;
    int gold;
    int weapon;
    int armor;
    int portion;
    struct bag_data bag[16];
    int bag_number;
};

extern struct player_data player;
extern int player_pos_x, player_pos_y;

#endif //DANGDGEON_PLAYER_DATA_H

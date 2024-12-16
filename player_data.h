#ifndef DANGDGEON_PLAYER_DATA_H
#define DANGDGEON_PLAYER_DATA_H

#include <stdbool.h>

#define MAX_NAME_LENGTH 16
#define MAX_BAG_STORAGE 16

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
    int potion;
    struct bag_data bag[MAX_BAG_STORAGE];
    int bag_number;
    int pos_x;
    int pos_y;
};

extern struct player_data player;

#endif //DANGDGEON_PLAYER_DATA_H

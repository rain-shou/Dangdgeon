#ifndef DANGDGEON_ENEMY_DATA_H
#define DANGDGEON_ENEMY_DATA_H

#include <stdbool.h>

#define ENEMY_AMOUNT 6

struct enemy_data {
    char name;
    bool is_dead;
    int health;
    int attack;
    int defense;
    int level;
    int pos_x;
    int pos_y;
};

extern struct enemy_data enemy[6];
extern bool enemy_is_existed[26];
extern int enemies_amount;

#endif //DANGDGEON_ENEMY_DATA_H

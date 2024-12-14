#ifndef DANGDGEON_PLAYER_DATA_H
#define DANGDGEON_PLAYER_DATA_H

#define MAX_NAME_LENGTH 16

struct player_data {
    char name[MAX_NAME_LENGTH + 1];
    int health;
    int max_health;
    int attack;
    int defense;
    int experience;
    int level;
    int gold;
};

extern struct player_data player;
extern int player_pos_x, player_pos_y;

#endif //DANGDGEON_PLAYER_DATA_H

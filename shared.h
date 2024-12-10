#ifndef DANGDGEON_SHARED_H
#define DANGDGEON_SHARED_H

#include <stdbool.h>

#define LENGTH 99
#define WIDTH 35

/* Each map_layer is divided to one main-room_data and eight areas */
struct region_info {
    int north;
    int west;
    int south;
    int east;
};

/*Room size l1 = (rand() % (5 - 3 + 1) + 3) + 1;
            w1 = (rand() % (3 - 1 + 1) + 1) + 1; */
struct room_info {
    bool is_exist;
    struct room_map_info {
        int center_point[2]; /*0 for x, 1 for y*/
        int north;
        int south;
        int west;
        int east;
        struct connector {
            bool is_exist;
            int x;
            int y;
        } gate[4]; /*0 for north, 1 for west, 2 for south, 3 for east.*/

    }map_info;
    bool is_entered;
};

extern char map_layer[WIDTH][LENGTH];
extern char entity_layer[WIDTH][LENGTH];
extern int walkable_layer[WIDTH][LENGTH];
extern bool explored_layer[WIDTH][LENGTH];
extern struct region_info regions[8];
extern struct room_info room_data[9];
extern int player_pos_x, player_pos_y;

#endif //DANGDGEON_SHARED_H

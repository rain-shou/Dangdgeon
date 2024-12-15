#include "map_data.h"

char entity_layer[WIDTH][LENGTH];
int walkable_layer[WIDTH][LENGTH];
int explored_layer[WIDTH][LENGTH];
int total_walkable_layer[LAYER][WIDTH][LENGTH];
int total_explored_layer[LAYER][WIDTH][LENGTH];
struct region_info regions[8];
struct room_info room_data[9];
struct region_info total_regions[LAYER][8];
struct room_info total_room_data[LAYER][9];
int layer;
int current_layer;
int upstairs_pos[LAYER][2];
int downstairs_pos[LAYER][2];
int layer_treasure[2];
bool up_or_down;
bool amulet_not_taken;

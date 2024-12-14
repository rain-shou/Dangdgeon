#ifndef DANGDGEON_MAP_GENERATOR_H
#define DANGDGEON_MAP_GENERATOR_H

#include "map_data.h"

void generate_map_layer(void);
void generate_main_room(void);
void define_area_boundaries(void);
void clear_room_data(int n);
void generate_sub_room(int n);
void apply_room_to_layer(int n);
void generate_coordinates(int *x, int *y, int *l1, int *w1, int n);
void generate_gates(void);
void generate_paths(void);
void generate_vertical_path(int n1, int g1, int n2, int g2);
void generate_horizontal_path(int n1, int g1, int n2, int g2);
void generate_angled_path(int n1, int g1, int n2, int g2);

#endif //DANGDGEON_MAP_GENERATOR_H

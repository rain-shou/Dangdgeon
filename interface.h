#ifndef DANGDGEON_INTERFACE_H
#define DANGDGEON_INTERFACE_H

#include <stdbool.h>

void show_start_screen();
bool show_exit_screen();
bool show_game_over(void);
void get_player_name(char *name, int max_length);
void open_bag(void);

#endif //DANGDGEON_INTERFACE_H

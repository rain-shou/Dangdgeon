#ifndef DANGDGEON_INTERFACE_H
#define DANGDGEON_INTERFACE_H

#include <stdbool.h>

bool show_start_screen(void);
bool show_exit_screen(void);
bool show_game_over(void);
void get_player_name(char *name, int max_length);
void open_bag(void);
bool show_game_end(void);
void show_message(char *);

#endif //DANGDGEON_INTERFACE_H

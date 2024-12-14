#include <ncurses.h>
#include "rendering.h"
#include "map_data.h"
#include "dialogue.h"
#include "player_data.h"

void draw_layer(void) {
    clear();
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            if (entity_layer[i][j] == '@') {
                mvaddch(i, j, '@');
            } else if (explored_layer[i][j] == 2 && entity_layer[i][j] != ' ') {
                mvaddch(i, j, entity_layer[i][j]);
            } else {
                if (walkable_layer[i][j] < 0 || explored_layer[i][j] == 0 ||
                    (walkable_layer[i][j] <= 8 && explored_layer[i][j] == 1)) {
                    mvaddch(i, j, ' ');
                } else if (walkable_layer[i][j] <= 8 && explored_layer[i][j] == 2) {
                    mvaddch(i, j, '.');
                } else if (walkable_layer[i][j] == 9) {
                    mvaddch(i, j, '+');
                } else if (walkable_layer[i][j] == 10) {
                    mvaddch(i, j, '#');
                } else if (walkable_layer[i][j] == 11) {
                    mvaddch(i, j, '-');
                } else if (walkable_layer[i][j] == 12) {
                    mvaddch(i, j, '|');
                } else if (walkable_layer[i][j] == 13) {
                    mvaddch(i, j, '>');
                } else if (walkable_layer[i][j] == 14) {
                    mvaddch(i, j, '<');
                } else if (walkable_layer[i][j] == 15 && explored_layer[i][j] == 2) {
                    mvaddch(i, j, '^');
                }
            }
        }
    }
    mvprintw(WIDTH + 2, 0, "Layer: %3d  CL: %3d  Level:%3d  Gold: %6d  Hp: %4d(%4d)  Str: %4d  Arm: %4d  Exp: %6d/%6d",
             layer, current_layer, player.level, player.gold, player.health, player.max_health, player.attack, player.defense, player.experience, player.level * 100);

    for (int i = 0; i < dialogue->line_count; ++i) {
        mvprintw(WIDTH + 5 + i, 0, "%s", dialogue->lines[i]);
    }
    refresh();
}

void reveal_room(void) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            if (explored_layer[i][j] == 2) {
                explored_layer[i][j] = 1;
            }
        }
    }
    int n = walkable_layer[player_pos_y][player_pos_x];
    if (n >= 0 && n < 9) {
        for (int i = room_data[n].map_info.north; i <= room_data[n].map_info.south; ++i) {
            for (int j = room_data[n].map_info.west; j <= room_data[n].map_info.east; ++j) {
                explored_layer[i][j] = 2;
            }
        }
    }
    for (int i = player_pos_y - 1; i <= player_pos_y + 1; ++i) {
        for (int j = player_pos_x - 1; j <= player_pos_x + 1; ++j) {
            explored_layer[i][j] = 2;
        }
    }
}

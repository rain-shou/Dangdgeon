#include <ncurses.h>
#include "player_control.h"

int player_move(void) {
    int ch = getch();
    char x;

    entity_layer[player_pos_y][player_pos_x] = ' ';
    if (ch == 'w' || ch == 'W') {
        if (entity_layer[player_pos_y - 1][player_pos_x] == '%') {
            return 1;
        } else if (walkable_layer[player_pos_y - 1][player_pos_x] == 1) {
            player_pos_y--;
        }
    } else if (ch == 'a' || ch == 'A') {
        if (entity_layer[player_pos_y][player_pos_x - 1] == '%') {
            return 1;
        } else if (walkable_layer[player_pos_y][player_pos_x - 1] == 1) {
            player_pos_x--;
        }
    } else if (ch == 's' || ch == 'S') {
        if (entity_layer[player_pos_y + 1][player_pos_x] == '%') {
            return 1;
        } else if (walkable_layer[player_pos_y + 1][player_pos_x] == 1) {
            player_pos_y++;
        }
    } else if (ch == 'd' || ch == 'D') {
        if (entity_layer[player_pos_y][player_pos_x + 1] == '%') {
            return 1;
        } else if (walkable_layer[player_pos_y][player_pos_x + 1] == 1) {
            player_pos_x++;
        }
    } else if (ch == 'q' || ch == 'Q') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 2;
    }
    entity_layer[player_pos_y][player_pos_x] = '@';

    return 0;
}

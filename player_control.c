#include <ncurses.h>
#include "player_control.h"
#include "player_data.h"
#include "map_data.h"

int player_move(void) {
    int ch = getch();

    entity_layer[player_pos_y][player_pos_x] = ' ';
    if (ch == 'w' || ch == 'W') {
        if (walkable_layer[player_pos_y - 1][player_pos_x] == 13) {
            return 1;
        } else if (walkable_layer[player_pos_y - 1][player_pos_x] == 14) {
            return 2;
        } else if (walkable_layer[player_pos_y - 1][player_pos_x] >= 0
                && walkable_layer[player_pos_y - 1][player_pos_x] < 11) {
            player_pos_y--;
        } else if (walkable_layer[player_pos_y - 1][player_pos_x] == 15) {
            player_pos_y--;
            entity_layer[player_pos_y][player_pos_x] = '@';
            return 3;
        }
    } else if (ch == 'a' || ch == 'A') {
        if (walkable_layer[player_pos_y][player_pos_x - 1] == 13) {
            return 1;
        } else if (walkable_layer[player_pos_y][player_pos_x - 1] == 14) {
            return 2;
        } else if (walkable_layer[player_pos_y][player_pos_x - 1] >= 0
                && walkable_layer[player_pos_y][player_pos_x - 1] < 11) {
            player_pos_x--;
        } else if (walkable_layer[player_pos_y][player_pos_x - 1] == 15) {
            player_pos_x--;
            entity_layer[player_pos_y][player_pos_x] = '@';
            return 3;
        }
    } else if (ch == 's' || ch == 'S') {
        if (walkable_layer[player_pos_y + 1][player_pos_x] == 13) {
            return 1;
        } else if (walkable_layer[player_pos_y + 1][player_pos_x] == 14) {
            return 2;
        } else if (walkable_layer[player_pos_y + 1][player_pos_x] >= 0
                && walkable_layer[player_pos_y + 1][player_pos_x] < 11) {
            player_pos_y++;
        } else if (walkable_layer[player_pos_y + 1][player_pos_x] == 15) {
            player_pos_y++;
            entity_layer[player_pos_y][player_pos_x] = '@';
            return 3;
        }
    } else if (ch == 'd' || ch == 'D') {
        if (walkable_layer[player_pos_y][player_pos_x + 1] == 13) {
            return 1;
        } else if (walkable_layer[player_pos_y][player_pos_x + 1] == 14) {
            return 2;
        } else if (walkable_layer[player_pos_y][player_pos_x + 1] >= 0
                && walkable_layer[player_pos_y][player_pos_x + 1] < 11) {
            player_pos_x++;
        } else if (walkable_layer[player_pos_y][player_pos_x + 1] == 15) {
            player_pos_x++;
            entity_layer[player_pos_y][player_pos_x] = '@';
            return 3;
        }
    } else if (ch == 'q' || ch == 'Q') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 9;
    } else if (ch == 'b' || ch == 'B') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 8;
    } else if (ch == 'e' || ch == 'E') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 10;
    }
    if (entity_layer[player_pos_y][player_pos_x] == ')') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 4;
    } else if (entity_layer[player_pos_y][player_pos_x] == '[') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 5;
    } else if (entity_layer[player_pos_y][player_pos_x] == '*') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 6;
    } else if (entity_layer[player_pos_y][player_pos_x] == '!') {
        entity_layer[player_pos_y][player_pos_x] = '@';
        return 7;
    }
    entity_layer[player_pos_y][player_pos_x] = '@';

    return 0;
}

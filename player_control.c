#include <ncurses.h>
#include "player_control.h"
#include "player_data.h"
#include "map_data.h"

int player_move(void) {
    int ch = getch();

    if (ch == 'w' || ch == 'W') {
        return check_walkable(player.pos_x, player.pos_y - 1);
    } else if (ch == 'a' || ch == 'A') {
        return check_walkable(player.pos_x - 1, player.pos_y);
    } else if (ch == 's' || ch == 'S') {
        return check_walkable(player.pos_x, player.pos_y + 1);
    } else if (ch == 'd' || ch == 'D') {
        return check_walkable(player.pos_x + 1, player.pos_y);
    } else if (ch == 'q' || ch == 'Q') {
        return 9;
    } else if (ch == 'b' || ch == 'B') {
        entity_layer[player.pos_y][player.pos_x] = '@';
        return 8;
    } else if (ch == 'e' || ch == 'E') {
        return 10;
    }
    return 0;
}

int check_walkable(int x, int y) {
    if (entity_layer[y][x] >= 'a' && entity_layer[y][x] <= 'z') {
        return 0;
    } else if (walkable_layer[y][x] == 13) {
        return 1;
    } else if (walkable_layer[y][x] == 14) {
        return 2;
    } else if (walkable_layer[y][x] >= 0 && walkable_layer[y][x] < 11) {
        entity_layer[player.pos_y][player.pos_x] = ' ';
        player.pos_x = x;
        player.pos_y = y;
        if (entity_layer[player.pos_y][player.pos_x] == ')') {
            entity_layer[player.pos_y][player.pos_x] = '@';
            return 4;
        } else if (entity_layer[player.pos_y][player.pos_x] == '[') {
            entity_layer[player.pos_y][player.pos_x] = '@';
            return 5;
        } else if (entity_layer[player.pos_y][player.pos_x] == '*') {
            entity_layer[player.pos_y][player.pos_x] = '@';
            return 6;
        } else if (entity_layer[player.pos_y][player.pos_x] == '!') {
            entity_layer[player.pos_y][player.pos_x] = '@';
            return 7;
        } else if (entity_layer[player.pos_y][player.pos_x] == ',') {
            entity_layer[player.pos_y][player.pos_x] = '@';
            return 11;
        }
        entity_layer[player.pos_y][player.pos_x] = '@';
        return 0;
    } else if (walkable_layer[y][x] == 15) {
        entity_layer[player.pos_y][player.pos_x] = ' ';
        player.pos_x = x;
        player.pos_y = y;
        entity_layer[y][x] = '@';
        return 3;
    }
    return 0;
}

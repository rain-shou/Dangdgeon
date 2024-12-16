#include <stdlib.h>
#include "enemy_script.h"
#include "player_data.h"
#include "map_data.h"

void all_enemies_move(void) {
    for (int i = 0; i < enemies_amount; i++) {
        if (!enemy[i].is_dead) {
            enemy_move(&enemy[i]);
        }
    }
}

void enemy_move(struct enemy_data *e) {
    if (check_player_besides(e)) {
        return;
    }
    if (is_player_in_range(e, 7)) {
        move_toward_player(e);
    } else {
        random_wander(e);
    }
}

bool check_player_besides(struct enemy_data *e) {
    return abs(player.pos_x - e->pos_x) <= 1 && abs(player.pos_y - e->pos_y);
}

bool is_player_in_range(struct enemy_data *e, int range) {
    return abs(player.pos_x - e->pos_x) <= range && abs(player.pos_y - e->pos_y) <= range
        && walkable_layer[player.pos_y][player.pos_x] == walkable_layer[e->pos_y][e->pos_x];
}

void move_toward_player(struct enemy_data *e) {
    int dx = player.pos_x - e->pos_x;
    int dy = player.pos_y - e->pos_y;

    entity_layer[e->pos_y][e->pos_x] = ' ';
    if (abs(dx) > abs(dy)) {
        if (dx > 0 && enemy_can_move(e->pos_x + 1, e->pos_y)) {
            e->pos_x++;
        } else if (dx < 0 && enemy_can_move(e->pos_x - 1, e->pos_y)) {
            e->pos_x--;
        } else if (dy > 0 && enemy_can_move(e->pos_x, e->pos_y + 1)) {
            e->pos_y++;
        } else if (dy < 0 && enemy_can_move(e->pos_x, e->pos_y - 1)) {
            e->pos_y--;
        }
    } else {
        if (dy > 0 && enemy_can_move(e->pos_x, e->pos_y + 1)) {
            e->pos_y++;
        } else if (dy < 0 && enemy_can_move(e->pos_x, e->pos_y - 1)) {
            e->pos_y--;
        } else if (dx > 0 && enemy_can_move(e->pos_x + 1, e->pos_y)) {
            e->pos_x++;
        } else if (dx < 0 && enemy_can_move(e->pos_x - 1, e->pos_y)) {
            e->pos_x--;
        }
    }
    entity_layer[e->pos_y][e->pos_x] = e->name;
}

void random_wander(struct enemy_data *e) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int dir = (int)(random() % 4);
    int new_x = e->pos_x + directions[dir][0];
    int new_y = e->pos_y + directions[dir][1];

    entity_layer[e->pos_y][e->pos_x] = ' ';

    if (enemy_can_move(new_x, new_y)) {
        e->pos_x = new_x;
        e->pos_y = new_y;
    }
    entity_layer[e->pos_y][e->pos_x] = e->name;
}

bool enemy_can_move(int x, int y) {
    return walkable_layer[y][x] >= 0 && walkable_layer[y][x] < 9 && entity_layer[y][x] == ' ';
}

#include <stdlib.h>
#include "enemy_generator.h"
#include "map_data.h"

void generate_current_layer_enemies(void) {
    int current_layer_enemy = (int)(random() % (current_layer / 10 + 2));

    refresh_enemy();
    for (int i = 0; i < current_layer_enemy; i++) {
        generate_enemy(&enemy[i]);
    }
    enemies_amount = current_layer_enemy;
}

void refresh_enemy(void) {
    for (int i = 0; i < ENEMY_AMOUNT; i++) {
        enemy[i].is_dead = true;
    }
    for (int i = 0; i < 26; i++) {
        enemy_is_existed[i] = false;
    }
    enemies_amount = 0;
}

void generate_enemy(struct enemy_data *e) {
    char ch;

    do {
        ch = (char)('a' + (int)(random() % 26));
    } while (enemy_is_existed[ch - 'a']);

    e->name = ch;
    enemy_is_existed[ch - 'a'] = true;
    e->is_dead = false;
    e->attack = (int)(5 + current_layer * 0.5) + (int)(random() % (current_layer / 5 + 2));
    e->defense = (int)(2 + current_layer * 0.5) + (int)(random() % (current_layer / 10 + 2));
    e->health = (int)(20 + current_layer) + (int)(random() % (current_layer / 2 + 1));
    e->level = current_layer;
    for (;;) {
        int pos_x = (int)(random() % 99 + 1);
        int pos_y = (int)(random() % 35 + 1);
        if (walkable_layer[pos_y][pos_x] >= 0 && walkable_layer[pos_y][pos_x] < 9
            && entity_layer[pos_y][pos_x] == ' ') {
            entity_layer[pos_y][pos_x] = ch;
            e->pos_x = pos_x;
            e->pos_y = pos_y;
            break;
        }
    }
}

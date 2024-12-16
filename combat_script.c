#include <stdio.h>
#include "combat_script.h"
#include "player_data.h"
#include "general_script.h"
#include "dialogue.h"
#include "map_data.h"

bool trigger_combat(void) {
    attack_closest_enemy();
    for (int i = 0; i < enemies_amount; i++) {
        if (check_combat(&enemy[i])) {
            enemy_engage_combat(&enemy[i]);
            if (check_player_death()) {
                return false;
            }
        }
    }
    return true;
}

void attack_closest_enemy(void) {
    int dx[] = {0, -1, 0, 1, -1, -1, 1, 1};
    int dy[] = {-1, 0, 1, 0, -1, 1, -1, 1};

    for (int i = 0; i < 8; i++) {
        int nx = player.pos_x + dx[i];
        int ny = player.pos_y + dy[i];

        for (int j = 0; j < enemies_amount; j++) {
            if (!enemy[j].is_dead && enemy[j].pos_x == nx && enemy[j].pos_y == ny) {
                player_engage_combat(&enemy[j]);
                if (check_enemy_death(&enemy[j])) {
                    add_experience(&enemy[j]);
                    while (check_level_up()) {
                        level_up();
                    }
                }
                return;
            }
        }
    }
}

bool check_combat(struct enemy_data *e) {
    int dx[] = {0, -1, 0, 1, -1, -1, 1, 1};
    int dy[] = {-1, 0, 1, 0, -1, 1, -1, 1};

    if (e->is_dead) {
        return false;
    }
    for (int i = 0; i < 8; i++) {
        int nx = e->pos_x + dx[i];
        int ny = e->pos_y + dy[i];

        if (player.pos_x == nx && player.pos_y == ny) {
            return true;
        }
    }
    return false;
}

void enemy_engage_combat(struct enemy_data *e) {
    int raw_damage = e->attack;
    float defense_factor = (float)e->defense / (float)(e->defense + 50);
    int damage1 = (int)((float)raw_damage * (1 - defense_factor));
    int damage2 = player.total_attack - e->defense;
    int damage =  damage1 >= damage2 ? damage1 : damage2;
    char message[100];

    player.health -= damage;
    player.health = 0 > player.health ? 0 : player.health;

    snprintf(message, sizeof(message), "%c attacked you! You lost %d health!", e->name, damage);
    add_line_to_dialogue(dialogue, message);
}

void player_engage_combat(struct enemy_data *e) {
    int raw_damage = player.attack;
    float defense_factor = (float)e->defense / (float)(e->defense + 50);
    int damage1 = (int)((float)raw_damage * (1 - defense_factor));
    int damage2 = player.total_attack - e->defense;
    int damage =  damage1 >= damage2 ? damage1 : damage2;
    char message[100];

    e->health -= damage;
    e->health = 0 > e->health ? 0 : e->health;

    snprintf(message, sizeof(message), "You attacked %c! %c lost %d health!", e->name, e->name, damage);
    add_line_to_dialogue(dialogue, message);
}

bool check_enemy_death(struct enemy_data *e) {
    char message[100];

    if (e->health <= 0) {
        e->is_dead = true;
        entity_layer[e->pos_y][e->pos_x] = ' ';
        snprintf(message, sizeof(message), "%c is dead!", e->name);
        return true;
    }
    return false;
}

void add_experience(struct enemy_data *e) {
    char message[100];

    player.experience += e->level * 25;
    snprintf(message, sizeof(message), "You got %d experience!", e->level * 25);
    add_line_to_dialogue(dialogue, message);
}

bool check_level_up(void) {
    if (player.experience >= player.level * 100) {
        return true;
    }
    return false;
}

void level_up(void) {
    player.experience -= player.level * 100;
    player.level++;
    player.max_health += 10;
    player.attack += 2;
    player.defense += 1;
    player.health = player.max_health;
    player.total_attack += 2;
    player.total_defense += 1;
    add_line_to_dialogue(dialogue, "Congratulations! Level up!");
}

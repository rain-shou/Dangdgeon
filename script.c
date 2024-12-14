#include <stdlib.h>
#include <stdio.h>
#include "script.h"
#include "map_data.h"
#include "dialogue.h"
#include "game_init.h"
#include "player_data.h"
#include "equipment_data.h"

void trigger_trap(void) {
    int damage = (int)(random() % 10 + 1);
    char message[20];
    player.health -= damage;
    add_line_to_dialogue(dialogue, "You stepped on a trap!");
    snprintf(message, sizeof(message), "You lost %d health", damage);
    add_line_to_dialogue(dialogue, message);
}

bool check_death(void) {
    if (player.health <= 0) {
        return true;
    } else {
        return false;
    }
}

void trigger_downstairs(void) {
    save_current_layer(current_layer - 1);
    current_layer++;
    up_or_down = true;
    add_line_to_dialogue(dialogue, "You descend into the depths.");
}

void trigger_upstairs(void) {
    save_current_layer(current_layer - 1);
    current_layer--;
    up_or_down = false;
    add_line_to_dialogue(dialogue, "You ascend toward the light.");
}

void equip_equipment(int n) {
    int extra_attack = 0, extra_defense = 0;

    if (player.bag[n].has_equipped == false) {
        if (player.bag[n].category == 0) {
            if (player.weapon != 0) {
                player.bag[player.weapon].has_equipped = false;
            }
            player.weapon = n;
            player.bag[n].has_equipped = true;
        } else if (player.bag[n].category == 1) {
            if (player.armor != 0) {
                player.bag[player.armor].has_equipped = false;
            }
            player.armor = n;
            player.bag[n].has_equipped = true;
        }
        for (int i = 0; i < 8; i++) {
            if (weapon_list[i].equipment_number == player.bag[player.weapon].number) {
                extra_attack += weapon_list[i].attack_change;
                extra_defense += weapon_list[i].defense_change;
            }
            if (armor_list[i].equipment_number == player.bag[player.armor].number) {
                extra_attack += armor_list[i].attack_change;
                extra_defense += armor_list[i].defense_change;
            }
        }
        player.total_attack = player.attack + extra_attack;
        player.total_defense = player.defense + extra_defense;
        return;
    } else {
        if (player.bag[n].category == 0) {
            player.bag[n].has_equipped = false;
            player.weapon = -1;
        } else if (player.bag[n].category == 1) {
            player.bag[n].has_equipped = false;
            player.armor = -1;
        }
        for (int i = 0; i < 8; i++) {
            if (weapon_list[i].equipment_number == player.bag[player.weapon].number) {
                extra_attack += weapon_list[i].attack_change;
                extra_defense += weapon_list[i].defense_change;
            }
            if (armor_list[i].equipment_number == player.bag[player.armor].number) {
                extra_attack += armor_list[i].attack_change;
                extra_defense += armor_list[i].defense_change;
            }
        }
        return;
    }
}

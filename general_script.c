#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "general_script.h"
#include "map_data.h"
#include "dialogue.h"
#include "game_init.h"
#include "player_data.h"
#include "equipment_data.h"
#include "enemy_data.h"

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

    if (!player.bag[n].has_equipped) {
        if (player.bag[n].category == 0) {
            if (player.weapon != -1) {
                player.bag[player.weapon].has_equipped = false;
            }
            player.weapon = n;
            player.bag[n].has_equipped = true;
        } else if (player.bag[n].category == 1) {
            if (player.armor != -1) {
                player.bag[player.armor].has_equipped = false;
            }
            player.armor = n;
            player.bag[n].has_equipped = true;
        }
    } else {
        if (player.bag[n].category == 0) {
            player.weapon = -1;
        } else if (player.bag[n].category == 1) {
            player.armor = -1;
        }
        player.bag[n].has_equipped = false;
    }

    if (player.weapon != -1) {
        for (int i = 0; i < 8; i++) {
            if (weapon_list[i].equipment_number == player.bag[player.weapon].number) {
                extra_attack += weapon_list[i].attack_change;
                extra_defense += weapon_list[i].defense_change;
            }
        }
    }
    if (player.armor != -1) {
        for (int i = 0; i < 8; i++) {
            if (armor_list[i].equipment_number == player.bag[player.armor].number) {
                extra_attack += armor_list[i].attack_change;
                extra_defense += armor_list[i].defense_change;
            }
        }
    }

    player.total_attack = player.attack + extra_attack;
    player.total_defense = player.defense + extra_defense;
}

void pickup_weapon(void) {
    char message[100];

    if (player.bag_number <= MAX_BAG_STORAGE) {
        player.bag[player.bag_number].has_equipped = false;
        player.bag[player.bag_number].category = 0;
        player.bag[player.bag_number].number = layer_treasure[1];
        for (int i = 0; i < 8; i++) {
            if (player.bag[player.bag_number].number == weapon_list[i].equipment_number) {
                strncpy(player.bag[player.bag_number].name, weapon_list[i].name, 20);
                weapon_list[i].be_taken = true;
                break;
            }
        }
        snprintf(message, sizeof(message), "You picked up a weapon: %s\n", player.bag[player.bag_number].name);
        add_line_to_dialogue(dialogue, message);
        player.bag_number++;
    }
}

void pickup_armor(void) {
    char message[100];

    if (player.bag_number <= MAX_BAG_STORAGE) {
        player.bag[player.bag_number].has_equipped = false;
        player.bag[player.bag_number].category = 1;
        player.bag[player.bag_number].number = layer_treasure[1];
        for (int i = 0; i < 8; i++) {
            if (player.bag[player.bag_number].number == armor_list[i].equipment_number) {
                strncpy(player.bag[player.bag_number].name, armor_list[i].name, 20);
                armor_list[i].be_taken = true;
                break;
            }
        }
        snprintf(message, sizeof(message), "You picked up a armor: %s\n", player.bag[player.bag_number].name);
        add_line_to_dialogue(dialogue, message);
        player.bag_number++;
    }
}

void pickup_gold(void) {
    player.gold++;
    add_line_to_dialogue(dialogue, "You picked up gold!");
}

void pickup_potion(void) {
    player.potion++;
    add_line_to_dialogue(dialogue, "You picked up potion!");
}

void drink_potion(void) {
    char message[100];

    if (player.potion > 0) {
        int health = player.health + 20 >= player.max_health ? player.max_health : player.health + 20;
        int pre_health = player.health;
        player.health = health;
        add_line_to_dialogue(dialogue, "You drank a potion.");
        if (pre_health - health == 0) {
            add_line_to_dialogue(dialogue, "But it had no effect.");
        } else {
            snprintf(message, sizeof(message), "You feel refreshed. Recovered %d health.", health - pre_health);
            add_line_to_dialogue(dialogue, message);
        }
        player.potion--;
    } else {
        add_line_to_dialogue(dialogue, "Poor you. You don't have any potions.");
    }
}

void pickup_amulet(void) {
    amulet_not_taken = false;
    add_line_to_dialogue(dialogue, "At last, the Amulet of Yendor is yours! Now, escape to complete your quest!");
}

bool check_win(void) {
    if (!amulet_not_taken && current_layer == 1) {
        return true;
    } else {
        return false;
    }
}

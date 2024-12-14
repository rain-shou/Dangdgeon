#include <stdlib.h>
#include <stdio.h>
#include "script.h"
#include "map_data.h"
#include "dialogue.h"
#include "game_init.h"
#include "player_data.h"

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

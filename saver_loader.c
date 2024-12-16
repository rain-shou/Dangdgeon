#include <stdio.h>
#include <stdlib.h>
#include "saver_loader.h"
#include "map_data.h"
#include "player_data.h"
#include "game_init.h"
#include "equipment_data.h"

void save_game(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error: create_dialogue falls. Malloc Error.\n");
        exit(EXIT_FAILURE);
    }

    save_current_layer(current_layer - 1);
    fwrite(&player, sizeof(struct player_data), 1, file);
    fwrite(&current_layer, sizeof(int), 1, file);
    fwrite(&layer, sizeof(int), 1, file);
    fwrite(&amulet_not_taken, sizeof(bool), 1, file);

    for (int i = 0; i < layer; i++) {
        fwrite(total_walkable_layer[i], sizeof(walkable_layer), 1, file);
        fwrite(total_explored_layer[i], sizeof(explored_layer), 1, file);
        fwrite(total_regions[i], sizeof(regions), 1, file);
        fwrite(total_room_data[i], sizeof(room_data), 1, file);
        fwrite(upstairs_pos[i], sizeof(int) * 2, 1, file);
        fwrite(downstairs_pos[i], sizeof(int) * 2, 1, file);
    }

    for (int i = 0; i < WEAPON_AMOUNT; i++) {
        fwrite(weapon_list, sizeof(weapon_list), 1, file);
        fwrite(armor_list, sizeof(armor_list), 1, file);
    }

    fclose(file);
}

bool load_game(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return false;
    }

    fread(&player, sizeof(struct player_data), 1, file);
    fread(&current_layer, sizeof(int), 1, file);
    fread(&layer, sizeof(int), 1, file);
    fread(&amulet_not_taken, sizeof(bool), 1, file);

    for (int i = 0; i < layer; i++) {
        fread(total_walkable_layer[i], sizeof(walkable_layer), 1, file);
        fread(total_explored_layer[i], sizeof(explored_layer), 1, file);
        fread(total_regions[i], sizeof(regions), 1, file);
        fread(total_room_data[i], sizeof(room_data), 1, file);
        fread(upstairs_pos[i], sizeof(int) * 2, 1, file);
        fread(downstairs_pos[i], sizeof(int) * 2, 1, file);
    }

    for (int i = 0; i < WEAPON_AMOUNT; i++) {
        fread(weapon_list, sizeof(weapon_list), 1, file);
        fread(armor_list, sizeof(armor_list), 1, file);
    }

    fclose(file);

    return true;
}

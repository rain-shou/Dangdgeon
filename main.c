#include <stdlib.h>
#include <time.h>
#include "curses_dealer.h"
#include "player_control.h"
#include "map_generator.h"
#include "game_init.h"
#include "rendering.h"
#include "player_generator.h"
#include "interface.h"
#include "general_script.h"
#include "dialogue.h"
#include "map_data.h"
#include "entity_generator.h"
#include "enemy_generator.h"
#include "combat_script.h"
#include "enemy_script.h"
#include "saver_loader.h"

int main(void)
{
    bool loaded_game = false;
    start:
    srandom((unsigned)time(NULL));
    ncurses_init();
    set_terminal_size();

    if (show_start_screen()) {
        initialize_game();
        get_player_name(player.name, MAX_NAME_LENGTH);
    } else {
        initialize_game();
        if (load_game("./savegame.dat")) {
            show_message("Game loaded successfully. Enter any key to continue...");
            loaded_game = true;
        } else {
            show_message("No saved game found. Starting a new game.");
            initialize_game();
            get_player_name(player.name, MAX_NAME_LENGTH);
        }
    }

    while (1) {
        if (!loaded_game) {
            level_loop:
            if (current_layer > layer) {
                initialize_layer();
                generate_map();
                generate_player();
            } else if (current_layer <= layer) {
                refresh_entity_layer();
                load_layer(current_layer - 1);
                if (up_or_down) {
                    restore_player_to_upstairs();
                } else {
                    restore_player_to_downstairs();
                    if (check_win()) {
                        if (show_game_end()) {
                            goto start;
                        } else {
                            ncurses_cleanup();
                            exit(EXIT_SUCCESS);
                        }
                    }
                }
            }
        } else {
            refresh_entity_layer();
            load_layer(current_layer - 1);
            entity_layer[player.pos_y][player.pos_x] = '@';
        }
        generate_entity_layer();
        generate_current_layer_enemies();
        while (1) {
            action_loop:
            reveal_room();
            draw_layer();
            int signal = player_move();
            free_dialogue(dialogue);
            dialogue = create_dialogue();
            switch(signal) {
                case 0:
                    break;
                case 1:
                    trigger_downstairs();
                    goto level_loop;
                case 2:
                    trigger_upstairs();
                    goto level_loop;
                case 3:
                    trigger_trap();
                    if (check_player_death()) {
                        if (show_game_over()) {
                            goto start;
                        } else {
                            ncurses_cleanup();
                            exit(EXIT_SUCCESS);
                        }
                    }
                    break;
                case 4:
                    pickup_weapon();
                    break;
                case 5:
                    pickup_armor();
                    break;
                case 6:
                    pickup_gold();
                    break;
                case 7:
                    pickup_potion();
                    break;
                case 8:
                    open_bag();
                    goto action_loop;
                case 9:
                    if (!show_exit_screen()) {
                        ncurses_cleanup();
                        exit(EXIT_SUCCESS);
                    }
                    goto action_loop;
                case 10:
                    drink_potion();
                    break;
                case 11:
                    pickup_amulet();
                    break;
                default:
                    break;
            }
            all_enemies_move();
            if (!trigger_combat()) {
                if (show_game_over()) {
                    goto start;
                } else {
                    ncurses_cleanup();
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}

#include <stdlib.h>
#include <time.h>
#include "curses_dealer.h"
#include "player_control.h"
#include "map_generator.h"
#include "game_init.h"
#include "rendering.h"
#include "player_generator.h"
#include "interface.h"
#include "script.h"
#include "dialogue.h"
#include "map_data.h"

int main(void)
{
    start:
    srandom((unsigned)time(NULL));
    ncurses_init();
    set_terminal_size();

    show_start_screen();
    initialize_game();
    while (1) {
        loop:
        if (current_layer > layer) {
            initialize_layer();
            generate_map();
            generate_player();
        } else if (current_layer <= layer) {
            load_layer(current_layer - 1);
            if (up_or_down) {
                restore_player_to_upstairs();
            } else {
                restore_player_to_downstairs();
            }

        }
        while (1) {
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
                    goto loop;
                case 2:
                    trigger_upstairs();
                    goto loop;
                case 3:
                    trigger_trap();
                    if (check_death()) {
                        if (show_game_over()) {
                            goto start;
                        } else {
                            ncurses_cleanup();
                            exit(EXIT_SUCCESS);
                        }
                    }
                    break;
                case 8:
                    open_bag();
                    break;
                case 9:
                    if (!show_exit_screen()) {
                        ncurses_cleanup();
                        exit(EXIT_SUCCESS);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

#include <stdlib.h>
#include <time.h>
#include "curses_dealer.h"
#include "player_control.h"
#include "map_generator.h"
#include "game_init.h"
#include "rendering.h"
#include "player_generator.h"
#include "interface.h"

int main(void)
{
    bool flag = true;
    srandom((unsigned)time(NULL));
    ncurses_init();

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
            if (flag) {
                restore_player_to_upstairs();
            } else {
                restore_player_to_downstairs();
            }

        }
        while (1) {
            reveal_room();
            draw_layer();
            int signal = player_move();
            switch(signal) {
                case 0:
                    break;
                case 1:
                    save_current_layer(current_layer - 1);
                    current_layer++;
                    flag = true;
                    goto loop;
                case 2:
                    save_current_layer(current_layer - 1);
                    current_layer--;
                    flag = false;
                    goto loop;
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

#include <stdlib.h>
#include <time.h>
#include "curses_dealer.h"
#include "player_control.h"
#include "map_generator.h"
#include "game_init.h"
#include "display.h"
#include "entity_generator.h"

int main(void)
{
    srandom((unsigned)time(NULL));
    ncurses_init();

    show_start_screen();

    while (1) {
        loop:
        initializing();
        generate_map_layer();
        generate_entity();
        while (1) {
            reveal_room();
            draw_layer();
            int signal = player_move();
            switch(signal) {
                case 0:
                    break;
                case 1:
                    goto loop;
                case 2:
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

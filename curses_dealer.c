#include <ncurses.h>
#include <stdlib.h>
#include "curses_dealer.h"

void ncurses_init(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void ncurses_cleanup(void) {
    endwin();
}

void set_terminal_size(void) {
    system("printf '\\e[8;50;150t'");
}

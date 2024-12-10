#include <ncurses.h>
#include "curses_dealer.h"

void ncurses_init() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void ncurses_cleanup() {
    endwin();
}

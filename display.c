#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "display.h"

#define START_SCREEN_OPTION_COUNT 2
#define EXIT_SCREEN_OPTION_COUNT 2

void draw_layer() {
    clear();
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            if (explored_layer[i][j] == 2 && entity_layer[i][j] != ' ') {
                mvaddch(i, j, entity_layer[i][j]);
            } else {
                if (walkable_layer[i][j] < 0 || explored_layer[i][j] == 0 ||
                    (walkable_layer[i][j] <= 8 && explored_layer[i][j] == 1)) {
                    mvaddch(i, j, ' ');
                } else if (walkable_layer[i][j] <= 8 && explored_layer[i][j] == 2) {
                    mvaddch(i, j, '.');
                } else if (walkable_layer[i][j] == 9 ) {
                    mvaddch(i, j, '+');
                } else if (walkable_layer[i][j] == 10) {
                    mvaddch(i, j, '#');
                } else if (walkable_layer[i][j] == 11) {
                    mvaddch(i, j, '-');
                } else if (walkable_layer[i][j] == 12) {
                    mvaddch(i, j, '|');
                }
            }
        }
    }
    mvprintw(WIDTH + 2, 0, "Layer: %3d  Level:%3d  Gold: %6d  Hp: %4d(%4d)  Str: %4d  Arm: %4d  Exp: %6d/%6d",
             layer, player.level, player.gold, player.health, player.max_health, player.attack, player.defense, player.experience, player.level * 100);
    refresh();
}

void reveal_room() {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            if (explored_layer[i][j] == 2) {
                explored_layer[i][j] = 1;
            }
        }
    }
    int n = walkable_layer[player_pos_y][player_pos_x];
    if (n >= 0 && n < 9) {
        for (int i = room_data[n].map_info.north; i <= room_data[n].map_info.south; ++i) {
            for (int j = room_data[n].map_info.west; j <= room_data[n].map_info.east; ++j) {
                explored_layer[i][j] = 2;
            }
        }
    }
    for (int i = player_pos_y - 1; i <= player_pos_y + 1; ++i) {
        for (int j = player_pos_x - 1; j <= player_pos_x + 1; ++j) {
            explored_layer[i][j] = 2;
        }
    }
}

void show_start_screen() {
    int current_option = 0;
    const char *title[] = {
            " /$$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$           ",
            "| $$__  $$ /$$__  $$| $$$ | $$ /$$__  $$          ",
            "| $$  \\ $$| $$  \\ $$| $$$$| $$| $$  \\__/          ",
            "| $$  | $$| $$$$$$$$| $$ $$ $$| $$ /$$$$          ",
            "| $$  | $$| $$__  $$| $$  $$$$| $$|_  $$          ",
            "| $$  | $$| $$  | $$| $$\\  $$$| $$  \\ $$          ",
            "| $$$$$$$/| $$  | $$| $$ \\  $$|  $$$$$$/          ",
            "|_______/ |__/  |__/|__/  \\__/ \\______/           ",
            "                                                  ",
            " /$$$$$$$   /$$$$$$  /$$$$$$$$  /$$$$$$  /$$   /$$",
            "| $$__  $$ /$$__  $$| $$_____/ /$$__  $$| $$$ | $$",
            "| $$  \\ $$| $$  \\__/| $$      | $$  \\ $$| $$$$| $$",
            "| $$  | $$| $$ /$$$$| $$$$$   | $$  | $$| $$ $$ $$",
            "| $$  | $$| $$|_  $$| $$__/   | $$  | $$| $$  $$$$",
            "| $$  | $$| $$  \\ $$| $$      | $$  | $$| $$\\  $$$",
            "| $$$$$$$/|  $$$$$$/| $$$$$$$$|  $$$$$$/| $$ \\  $$",
            "|_______/  \\______/ |________/ \\______/ |__/  \\__/"
    };
    const int title_lines = sizeof(title) / sizeof(title[0]);
    const char *options[START_SCREEN_OPTION_COUNT] = {"START GAME", "EXIT GAME"};

    for (;;) {
        clear();
        for (int i = 0; i < title_lines; i++) {
            mvprintw(3 + i, (int)(COLS - strlen(title[i])) / 2, "%s", title[i]);
        }
        for (int i = 0; i < START_SCREEN_OPTION_COUNT; i++) {
            if (i == current_option) {
                mvprintw(6 + title_lines + i, (int)(COLS - strlen(options[i]) - 4) / 2, "< %s >", options[i]);
            } else {
                mvprintw(6 + title_lines + i, (int)(COLS - strlen(options[i])) / 2, "%s", options[i]);
            }
        }
        refresh();
        switch (getch()) {
            case KEY_UP:
                current_option = (current_option - 1 + START_SCREEN_OPTION_COUNT) % START_SCREEN_OPTION_COUNT;
                break;
            case KEY_DOWN:
                current_option = (current_option + 1) % START_SCREEN_OPTION_COUNT;
                break;
            case '\n':
                if (current_option == 0) {
                    return;
                } else if (current_option == 1) {
                    endwin();
                    exit(0);
                }
                break;
            default:
                break;
        }
    }
}

bool show_exit_screen() {
    int current_option = 0;
    const char *options[EXIT_SCREEN_OPTION_COUNT] = {"RESUME GAME", "EXIT GAME"};

    while (1) {
        clear();
        for (int i = 0; i < EXIT_SCREEN_OPTION_COUNT; i++) {
            if (i == current_option) {
                mvprintw(LINES / 2 + i, (int)(COLS - strlen(options[i]) - 4) / 2, "< %s >", options[i]);
            } else {
                mvprintw(LINES / 2 + i, (int)(COLS - strlen(options[i])) / 2, "%s", options[i]);
            }
        }
        refresh();
        switch (getch()) {
            case KEY_UP:
                current_option = (current_option - 1 + EXIT_SCREEN_OPTION_COUNT) % EXIT_SCREEN_OPTION_COUNT;
                break;
            case KEY_DOWN:
                current_option = (current_option + 1) % EXIT_SCREEN_OPTION_COUNT;
                break;
            case '\n':
                if (current_option == 0) {
                    return true;
                } else if (current_option == 1) {
                    return false;
                }
                break;
            default:
                break;
        }
    }
}

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
            if (entity_layer[i][j] != ' ') {
                mvaddch(i, j, entity_layer[i][j]);
            } else {
                mvaddch(i, j, map_layer[i][j]);
            }
        }
    }
    refresh();
}

void reveal_room() {
    for (int i = 0; i < 9; i++) {
        if (player_pos_x <= room_data[i].map_info.east && player_pos_x >= room_data[i].map_info.west
            && player_pos_y <= room_data[i].map_info.south && player_pos_y >= room_data[i].map_info.north) {
            for (int x = room_data[i].map_info.north + 1; x <= room_data[i].map_info.south - 1; ++x) {
                for (int y = room_data[i].map_info.west + 1; y <= room_data[i].map_info.east - 1; ++y) {
                    map_layer[x][y] = '.';
                }
            }
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

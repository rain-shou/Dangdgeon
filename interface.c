#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "interface.h"
#include "map_data.h"
#include "player_data.h"
#include "script.h"

#define START_SCREEN_OPTION_COUNT 2
#define EXIT_SCREEN_OPTION_COUNT 2

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

bool show_game_over(void) {
    int current_option = 0;
    const char *title[] = {
            "  ____                         ___                 \n",
            " / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ \n",
            "| |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|\n",
            "| |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |   \n",
            " \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ",
    };
    const int title_lines = sizeof(title) / sizeof(title[0]);
    const char *options[START_SCREEN_OPTION_COUNT] = {"RESTART", "EXIT GAME"};

    for (;;) {
        clear();
        for (int i = 0; i < title_lines; i++) {
            mvprintw(3 + i, (int)(COLS - strlen(title[i])) / 2, "%s", title[i]);
        }
        mvprintw(6 + title_lines, (int)(COLS - strlen(player.name)) / 2, "%s", player.name);
        mvprintw(7 + title_lines, (int)(COLS - 13) / 2, "Layer: %6d", layer);
        mvprintw(8 + title_lines, (int)(COLS - 12) / 2, "Gold: %6d", player.gold);
        for (int i = 0; i < START_SCREEN_OPTION_COUNT; i++) {
            if (i == current_option) {
                mvprintw(12 + title_lines + i, (int)(COLS - strlen(options[i]) - 4) / 2, "< %s >", options[i]);
            } else {
                mvprintw(12 + title_lines + i, (int)(COLS - strlen(options[i])) / 2, "%s", options[i]);
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

void get_player_name(char *name, int max_length) {
    char buffer[128];
    echo();
    curs_set(1);
    clear();
    mvprintw(LINES / 2 - 1, (COLS - 25) / 2, "Enter your name (max %d): ", max_length);
    refresh();
    mvgetnstr(LINES / 2, (COLS - max_length) / 2, buffer, max_length);
    strncpy(name, buffer, max_length);
    name[max_length] = '\0';
    noecho();
    curs_set(0);
}

void open_bag(void) {
    int current_selection = 0;

    while (1) {
        clear();
        mvprintw(0, 0, "Bag Contents (Use UP/DOWN to select, ENTER to equip, Q to quit):");
        for (int i = 0; i < player.bag_number; i++) {
            if (i == current_selection) {
                mvprintw(i + 2, 0, "> %s %s", player.bag[i].name, player.bag[i].has_equipped ? "[Equipped]" : " ");
            } else {
                mvprintw(i + 2, 0, "%s %s", player.bag[i].name, player.bag[i].has_equipped ? "[Equipped]" : " ");
            }
        }
        refresh();
        switch (getch()) {
            case KEY_UP:
                current_selection = (current_selection - 1 + player.bag_number) % player.bag_number;
                break;
            case KEY_DOWN:
                current_selection = (current_selection + 1) % player.bag_number;
                break;
            case '\n':
                equip_equipment(current_selection);
                break;
            case 'q':
                return;
            default:
                break;
        }
    }
}

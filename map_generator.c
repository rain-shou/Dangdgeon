#include <stdlib.h>
#include "map_generator.h"
#include "environment_generator.h"

void generate_map(void) {
    generate_main_room();
    define_area_boundaries();
    for (int i = 0; i < 8; i++) {
        generate_sub_room(i);
        apply_room_to_layer(i);
    }
    generate_paths();
    generate_stairs();
}

void generate_main_room(void) {
    int x = LENGTH / 2, y = WIDTH / 2;
    int len = (int)(random() % 5 + 4);    /* len for length x */
    int wid = (int)(random() % 3 + 4);    /* wid for width y */
    struct room_map_info *main_room = &room_data[8].map_info;   /* room_data 8 for the main room_data */

    main_room->north = y - wid;
    main_room->west = x - len;
    main_room->south = y + wid;
    main_room->east = x + len;
    apply_room_to_layer(8);
}

void define_area_boundaries(void) {
    struct room_map_info *main_room = &room_data[8].map_info;

    int area_data[8][4] = {
            {0, main_room->west, main_room->north - 1, main_room->east},            // area 0 for north-central
            {0, main_room->east + 1, main_room->north - 1, LENGTH - 1},             // area 1 for north-east
            {main_room->north, main_room->east + 1, main_room->south, LENGTH - 1},  // area 2 for middle-east
            {main_room->south + 1, main_room->east + 1, WIDTH - 1, LENGTH - 1},     // area 3 for south-east
            {main_room->south + 1, main_room->west, WIDTH - 1, main_room->east},    // area 4 for south-central
            {main_room->south + 1, 0, WIDTH - 1, main_room->west - 1},              // area 5 for south-west
            {main_room->north, 0, main_room->south, main_room->west - 1},           // area 6 for middle-west
            {0, 0, main_room->north - 1, main_room->west - 1}                       // area 7 for north-west
    };

    for (int i = 0; i < 8; i++) {
        regions[i].north = area_data[i][0];
        regions[i].west = area_data[i][1];
        regions[i].south = area_data[i][2];
        regions[i].east = area_data[i][3];
    }
}

void clear_room_data(int n) {
    room_data[n].map_info.north = 0;
    room_data[n].map_info.east = 0;
    room_data[n].map_info.south = 0;
    room_data[n].map_info.west = 0;
}

void generate_sub_room(int n) {
    int x, y, len, wid;

    if (!room_data[n].is_exist) {
        clear_room_data(n);
        return;
    }

    generate_coordinates(&x, &y, &len, &wid, n);
    switch (n) {
        case 0: /* north-central part */
            while ((x - len) <= regions[0].west || (x + len) >= regions[1].east ||
                   (y - wid) <= regions[0].north || (y + wid) >= regions[0].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            if ((x + len) >= regions[0].east) {
                room_data[1].is_exist = false;
            }
            /* north-central room_data(0) not have north gate */
            room_data[0].map_info.gate[0].is_exist = false;
            break;
        case 1: /* north-east part */
            while ((x - len) <= regions[1].west || (x + len) >= regions[1].east ||
                   (y - wid) <= regions[1].north || (y + wid) >= regions[2].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            if ((y + wid) >= regions[1].south) {
                room_data[2].is_exist = false;
            }
            /* north-east room_data(1) not have north gate & east gate */
            room_data[1].map_info.gate[0].is_exist = false;
            room_data[1].map_info.gate[3].is_exist = false;
            break;
        case 2: /* middle-east part */
            while ((x - len) <= regions[2].west || (x + len) >= regions[2].east ||
                   (y - wid) <= regions[2].north || (y + wid) >= regions[3].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            if ((y + wid) >= regions[2].south) {
                room_data[3].is_exist = false;
            }
            /* middle-east room_data(2) not have east gate */
            room_data[2].map_info.gate[3].is_exist = false;
            break;
        case 3: /* south-east part */
            while ((x - len) <= regions[4].west || (x + len) >= regions[3].east ||
                   (y - wid) <= regions[3].north || (y + wid) >= regions[3].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            if ((x - len) <= regions[3].west) {
                room_data[4].is_exist = false;
            }
            /* south-east room_data(3) not have south gate & east gate */
            room_data[3].map_info.gate[2].is_exist = false;
            room_data[3].map_info.gate[3].is_exist = false;
            break;
        case 4: /* south-central part */
            while ((x - len) <= regions[5].west || (x + len) >= regions[4].east ||
                   (y - wid) <= regions[4].north || (y + wid) >= regions[4].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            if ((x - len) <= regions[4].west) {
                room_data[5].is_exist = false;
            }
            /* south-central room_data(4) not have south gate */
            room_data[4].map_info.gate[2].is_exist = false;
            break;
        case 5: /* south-west part */
            while ((x - len) <= regions[5].west || (x + len) >= regions[5].east ||
                   (y - wid) <= regions[6].north || (y + wid) >= regions[5].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            if ((y - wid) <= regions[5].north) {
                room_data[6].is_exist = false;
            }
            /* south-west room_data(5) not have western-gate & south gate */
            room_data[5].map_info.gate[1].is_exist = false;
            room_data[5].map_info.gate[2].is_exist = false;
            break;
        case 6: /* middle-west part */
            while ((x - len) <= regions[6].west || (x + len) >= regions[6].east ||
                   (y - wid) <= regions[7].north || (y + wid) >= regions[6].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            if ((y - wid) <= regions[6].north) {
                room_data[7].is_exist = false;
            }
            /* middle-west room_data(6) not have west gate */
            room_data[6].map_info.gate[1].is_exist = false;
            break;
        case 7: /* north-west part */
            while ((x - len) <= regions[7].west || (x + len) >= regions[7].east ||
                   (y - wid) <= regions[7].north || (y + wid) >= regions[7].south) {
                generate_coordinates(&x, &y, &len, &wid, n);
            }
            /* north-west room_data(7) not have north gate & west gate */
            room_data[7].map_info.gate[0].is_exist = false;
            room_data[7].map_info.gate[1].is_exist = false;
            break;
        default:
            break;
    }

    room_data[n].map_info.north = y - wid;
    room_data[n].map_info.west = x - len;
    room_data[n].map_info.south = y + wid;
    room_data[n].map_info.east = x + len;
}

void apply_room_to_layer(int n) {
    if (room_data[n].is_exist) {
        for (int i = room_data[n].map_info.north + 1; i <= room_data[n].map_info.south - 1; ++i) {
            for (int j = room_data[n].map_info.west + 1; j <= room_data[n].map_info.east - 1; ++j) {
                walkable_layer[i][j] = n;
            }
        }
        for (int i = room_data[n].map_info.west; i <= room_data[n].map_info.east; ++i) {
            walkable_layer[room_data[n].map_info.north][i] = 11;
            walkable_layer[room_data[n].map_info.south][i] = 11;
        }
        for (int i = room_data[n].map_info.north + 1; i <= room_data[n].map_info.south - 1; ++i) {
            walkable_layer[i][room_data[n].map_info.west] = 12;
            walkable_layer[i][room_data[n].map_info.east] = 12;
        }
    }
}

void generate_coordinates(int *x, int *y, int *l1, int *w1, int n) {
    *x = (int)(random() % (regions[n].east - regions[n].west + 1) + regions[n].west);
    *y = (int)(random() % (regions[n].south - regions[n].north + 1) + regions[n].north);
    *l1 = (int)(random() % (5 - 3 + 1) + 3) + 1;
    *w1 = (int)(random() % (3 - 1 + 1) + 1) + 1;
}

void generate_gates(void) {
    for (int i = 0; i < 9; ++i) {
        if (room_data[i].map_info.gate[0].is_exist) {
            room_data[i].map_info.gate[0].x = (int)(random() % ((room_data[i].map_info.east - 1) -
                                                (room_data[i].map_info.west + 1) - 1) +
                                      (room_data[i].map_info.west + 1));
            room_data[i].map_info.gate[0].y = room_data[i].map_info.north;
        }
        if (room_data[i].map_info.gate[1].is_exist) {
            room_data[i].map_info.gate[1].x = room_data[i].map_info.west;
            room_data[i].map_info.gate[1].y = (int)(random() % ((room_data[i].map_info.south - 1) -
                                                (room_data[i].map_info.north + 1) - 1) +
                                      (room_data[i].map_info.north + 1));
        }
        if (room_data[i].map_info.gate[2].is_exist) {
            room_data[i].map_info.gate[2].x = (int)(random() % ((room_data[i].map_info.east - 1) -
                                                (room_data[i].map_info.west + 1) - 1) +
                                      (room_data[i].map_info.west + 1));
            room_data[i].map_info.gate[2].y = room_data[i].map_info.south;
        }
        if (room_data[i].map_info.gate[3].is_exist) {
            room_data[i].map_info.gate[3].x = room_data[i].map_info.east;
            room_data[i].map_info.gate[3].y = (int)(random() % ((room_data[i].map_info.south - 1) -
                                                (room_data[i].map_info.north + 1) - 1) +
                                      (room_data[i].map_info.north + 1));
        }
    }
}

void generate_paths(void) {
    generate_gates();

    if (room_data[0].is_exist) {
        /* link north-central room_data(0) and main room_data(8) */
        /* code 02-80 */
        generate_vertical_path(0, 2, 8, 0);

        /* link north-central room_data(0) and north-east room_data(1) */
        /* code 03-11 */
        if (room_data[1].is_exist) {
            generate_horizontal_path(0, 3, 1, 1);
        } else if (room_data[2].is_exist) {
            /* link north-central room_data(0) and middle-east room_data(2) */
            /* code 03-20 */
            generate_angled_path(0, 3, 2, 0);
        }
    }

    if (room_data[1].is_exist) {
        /* link north-east room_data(1) and middle-east room_data(2) */
        /* code 12-20 */
        if (room_data[2].is_exist) {
            generate_vertical_path(1, 2, 2, 0);
        } else if (room_data[3].is_exist) {
            /* link north-east room_data(1) and south-east room_data(3) */
            /* code 12-30 */
            generate_vertical_path(1, 2, 3, 0);
        }
    }

    if (room_data[2].is_exist) {
        /* link middle-east room_data(2) and main room_data(8) */
        /* code 83-21 */
        generate_horizontal_path(8, 3, 2, 1);

        /* link middle-east room_data(2) and south-east room_data(3) */
        /* code 22-30 */
        if (room_data[3].is_exist) {
            generate_vertical_path(2, 2, 3, 0);
        } else if (room_data[4].is_exist) {
            /* link middle-east room_data(2) and southern-central room_data(4) */
            /* code 43-22 */
            generate_angled_path(4, 3, 2, 2);
        }
    }

    if (room_data[3].is_exist) {
        /* link south-east room_data(3) and south-central room_data(4) */
        /* code 43-31 */
        if (room_data[4].is_exist) {
            generate_horizontal_path(4, 3, 3, 1);
        } else if (room_data[5].is_exist) {
            /* link south-east room_data(3) and south-west room_data(5) */
            /* code 53-31 */
            generate_horizontal_path(5, 3, 3, 1);
        }
    }

    if (room_data[4].is_exist) {
        /* link south-central room_data(4) and main room_data(8) */
        /* code 82-40 */
        generate_vertical_path(8, 2, 4, 0);

        /* link south-central room_data(4) and south-west room_data(5) */
        /* code 53-41 */
        if (room_data[5].is_exist) {
            generate_horizontal_path(5, 3, 4, 1);
        } else if (room_data[6].is_exist) {
            /* link south-central room_data(4) and middle-west room_data(6) */
            /* code 41-62 */
            generate_angled_path(4, 1, 6, 2);
        }
    }

    if (room_data[5].is_exist) {
        /* link south-west room_data(5) and middle-west room_data(6) */
        /* code 62-50 */
        if (room_data[6].is_exist) {
            generate_vertical_path(6, 2, 5, 0);
        } else if (room_data[7].is_exist) {
            /* link south-west room_data(5) and north-west room_data(7) */
            /* code 72-50 */
            generate_vertical_path(7, 2, 5, 0);
        }
    }

    if (room_data[6].is_exist) {
        /* link middle-west room_data(6) and main room_data(8) */
        /* code 63-81 */
        generate_horizontal_path(6, 3, 8, 1);

        /* link middle-west room_data(6) and north-west room_data(7) */
        /* code 73-81 */
        if (room_data[7].is_exist) {
            generate_vertical_path(7, 2, 6, 0);
        }
    }

    if (room_data[7].is_exist) {
        /* link north-west room_data(7) and north-central room_data(0) */
        /* code 73-81 */
        generate_horizontal_path(7, 3, 0, 1);
    }
}

/*n1.g1.y should be smaller than n2.g2.y*/
void generate_vertical_path(int n1, int g1, int n2, int g2) {
    int x1, x2;
    int center_point = (room_data[n1].map_info.gate[g1].y + room_data[n2].map_info.gate[g2].y) / 2;

    if (((n1 == 1 || n1 == 2) && n2 == 3 && !room_data[4].is_exist)) {
        if (center_point <= room_data[8].map_info.south) {
            center_point = room_data[8].map_info.south + 1;
        }
    }

    walkable_layer[room_data[n1].map_info.gate[g1].y][room_data[n1].map_info.gate[g1].x] = 9;
    walkable_layer[room_data[n2].map_info.gate[g2].y][room_data[n2].map_info.gate[g2].x] = 9;
    for (int i = room_data[n1].map_info.gate[g1].y + 1; i <= center_point; ++i) {
        walkable_layer[i][room_data[n1].map_info.gate[g1].x] = 10;
    }
    for (int i = center_point; i < (room_data[n2].map_info.gate[g2].y); ++i) {
        walkable_layer[i][room_data[n2].map_info.gate[g2].x] = 10;
    }
    x1 = (room_data[n1].map_info.gate[g1].x < room_data[n2].map_info.gate[g2].x ? room_data[n1].map_info.gate[g1].x :
          room_data[n2].map_info.gate[g2].x);
    x2 = (room_data[n1].map_info.gate[g1].x < room_data[n2].map_info.gate[g2].x ? room_data[n2].map_info.gate[g2].x :
          room_data[n1].map_info.gate[g1].x);
    for (; x1 <= x2; ++x1) {
        walkable_layer[center_point][x1] = 10;
    }
}

/*n1.g1.x should be smaller than n2.g2.x*/
void generate_horizontal_path(int n1, int g1, int n2, int g2) {
    int y1, y2;
    int center_point = (room_data[n1].map_info.gate[g1].x + room_data[n2].map_info.gate[g2].x) / 2;

    if (n1 == 0 && n2 == 1 && !room_data[2].is_exist) {
        if (center_point <= room_data[8].map_info.east) {
            center_point = room_data[8].map_info.east + 1;
        }
    }
    if ((n1 == 5 && (n2 == 3 || n2 == 4) && !room_data[6].is_exist)) {
        if (center_point >= room_data[8].map_info.west) {
            center_point = room_data[8].map_info.west - 1;
        }
    }

    walkable_layer[room_data[n1].map_info.gate[g1].y][room_data[n1].map_info.gate[g1].x] = 9;
    walkable_layer[room_data[n2].map_info.gate[g2].y][room_data[n2].map_info.gate[g2].x] = 9;
    for (int i = room_data[n1].map_info.gate[g1].x + 1; i <= center_point; ++i) {
        walkable_layer[room_data[n1].map_info.gate[g1].y][i] = 10;
    }
    for (int i = center_point; i < room_data[n2].map_info.gate[g2].x; ++i) {
        walkable_layer[room_data[n2].map_info.gate[g2].y][i] = 10;
    }
    y1 = (room_data[n1].map_info.gate[g1].y < room_data[n2].map_info.gate[g2].y ? room_data[n1].map_info.gate[g1].y :
          room_data[n2].map_info.gate[g2].y);
    y2 = (room_data[n1].map_info.gate[g1].y < room_data[n2].map_info.gate[g2].y ? room_data[n2].map_info.gate[g2].y :
          room_data[n1].map_info.gate[g1].y);
    for (; y1 <= y2; ++y1) {
        walkable_layer[y1][center_point] = 10;
    }
}

/*n1 should be the room_data in length, n2 should be the room_data in width*/
void generate_angled_path (int n1, int g1, int n2, int g2) {
    int x1, x2, y1, y2;

    if ((n1 == 0 && n2 == 2 && room_data[n1].map_info.gate[g1].x >= room_data[n2].map_info.gate[g2].x) ||
        (n1 == 4 && n2 == 2 && room_data[n2].map_info.gate[g2].y >= room_data[n1].map_info.gate[g1].y) ||
        (n1 == 4 && n2 == 6 && room_data[n1].map_info.gate[g1].x <= room_data[n2].map_info.gate[g2].x)) {
        return;
    }

    walkable_layer[room_data[n1].map_info.gate[g1].y][room_data[n1].map_info.gate[g1].x] = 9;
    walkable_layer[room_data[n2].map_info.gate[g2].y][room_data[n2].map_info.gate[g2].x] = 9;

    x1 = (room_data[n1].map_info.gate[g1].x < room_data[n2].map_info.gate[g2].x ? room_data[n1].map_info.gate[g1].x :
          room_data[n2].map_info.gate[g2].x);
    x2 = (room_data[n1].map_info.gate[g1].x < room_data[n2].map_info.gate[g2].x ? room_data[n2].map_info.gate[g2].x :
          room_data[n1].map_info.gate[g1].x);
    y1 = (room_data[n1].map_info.gate[g1].y < room_data[n2].map_info.gate[g2].y ? room_data[n1].map_info.gate[g1].y :
          room_data[n2].map_info.gate[g2].y);
    y2 = (room_data[n1].map_info.gate[g1].y < room_data[n2].map_info.gate[g2].y ? room_data[n2].map_info.gate[g2].y :
          room_data[n1].map_info.gate[g1].y);

    for (int i = x1 + 1; i < x2; ++i) {
        walkable_layer[room_data[n1].map_info.gate[g1].y][i] = 10;
    }
    for (int i = y1 + 1; i < y2; ++i) {
        walkable_layer[i][room_data[n2].map_info.gate[g2].x] = 10;
    }

    if (n1 == 0 && n2 == 2) {
        walkable_layer[y1][x2] = 10;
    } else if (n1 == 4 && n2 == 2) {
        walkable_layer[y2][x2] = 10;
    } else if (n1 == 4 && n2 == 6) {
        walkable_layer[y2][x1] = 10;
    }
}

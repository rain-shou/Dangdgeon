#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#define LENGTH 99
#define WIDTH 35

char layer[WIDTH][LENGTH];
char player[WIDTH][LENGTH];

int player_x, player_y;

/*Each layer be divided to one main-room and eight areas*/
struct area_info {
    int north;
    int west;
    int south;
    int east;
} area[8];

/*Room size l1 = (rand() % (5 - 3 + 1) + 3) + 1;
            w1 = (rand() % (3 - 1 + 1) + 1) + 1; */
struct room_info {
    bool is_exist;
    int centerpoint[2]; /*0 for x, 1 for y*/
    int north;
    int south;
    int west;
    int east;
    struct connector {
        bool is_exist;
        int x;
        int y;
    } gate[4]; /*0 for north, 1 for west, 2 for south, 3 for east.*/
} room[9];

void initializing(void);
void layer_generator(void); /*generate the whole layer*/
void main_room_generator(void); /*generate the main room*/
void area_coordinator_keeper(void); /*generate the other 8 areas*/
void sub_room_generator(int n); /*generate sub-rooms*/
void room_to_layer(int n); /*transfer room to layer*/
/*random coordinator generator*/
void coordinator_maker(int *x, int *y, int *l1, int *w1, int n);
void gate_generator(void);
void path_generator(void); /*generate path between each rooms*/
/*generate path which is vertical*/
void path_vertical_generator(int n1, int g1, int n2, int g2);
/*generate path which is horizontal*/
void path_horizontal_generator(int n1, int g1, int n2, int g2);
/*generate path with an angle*/
void path_angle_generator(int n1, int g1, int n2, int g2);
int player_move(void);

int main(void)
{
    srand((unsigned)time(NULL));

    while (1) {
        initializing();
        layer_generator();
        player_x = room[8].centerpoint[0];
        player_y = room[8].centerpoint[1];
        player[player_y][player_x] = '@';
        layer[player_y + 1][player_x + 1] = '%';
        while (1)
        {
            system("cls");
            for (int i = 0; i < WIDTH; ++i)
            {
                for (int j = 0; j < LENGTH; ++j)
                {
                    if (player[i][j] == '@') {
                        putchar(player[i][j]);
                    } else {
                        putchar(layer[i][j]);
                    }
                }
                putchar('\n');
            }
            if (player_move() == 1) {
                break;
            }
        }
    }

    system("pause");

    exit(EXIT_SUCCESS);
}

void initializing(void)
{
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            layer[i][j] = ' ';
            player[i][j] = ' ';
        }
    }
    for (int i = 0; i <= 8; ++i) {
        room[i].is_exist = true;
        for (int j = 0; j < 4; ++j) {
            room[i].gate[j].is_exist = true;
        }
    }
}

void layer_generator(void)
{
    main_room_generator();
    area_coordinator_keeper();
    for (int i = 0; i < 8; i++) {
        sub_room_generator(i);
        room_to_layer(i);
    }
    path_generator();
}

void main_room_generator(void)
{
    int x = LENGTH / 2, y = WIDTH / 2;
    int l1, w1;

    l1 = (rand() % (7 - 3 + 1) + 3) + 1; /*l1 for length x */
    w1 = (rand() % (5 - 3 + 1) + 3) + 1; /*w1 for width y*/
    /*room 8 for the main room*/
    room[8].centerpoint[0] = x;
    room[8].centerpoint[1] = y;
    room[8].north = y - w1;
    room[8].west = x - l1;
    room[8].south = y + w1;
    room[8].east = x + l1;
    room_to_layer(8);
}

void area_coordinator_keeper(void)
{
    /*area0 for the area in north-central*/
    area[0].north = 0;
    area[0].west = room[8].west;
    area[0].south = room[8].north - 1;
    area[0].east = room[8].east;
    /*area1 for the area in north-east*/
    area[1].north = 0;
    area[1].west = room[8].east + 1;
    area[1].south = room[8].north - 1;
    area[1].east = LENGTH - 1;
    /*place 2 for the area in middle-east*/
    area[2].north = room[8].north;
    area[2].west = room[8].east + 1;
    area[2].south = room[8].south;
    area[2].east = LENGTH - 1;
    /*place 3 for the area in south-east*/
    area[3].north = room[8].south + 1;
    area[3].west = room[8].east + 1;
    area[3].south = WIDTH - 1;
    area[3].east = LENGTH - 1;
    /*place 4 for the area in south-central*/
    area[4].north = room[8].south + 1;
    area[4].west = room[8].west;
    area[4].south = WIDTH - 1;
    area[4].east = room[8].east;
    /*place 5 for the area in south-west*/
    area[5].north = room[8].south + 1;
    area[5].west = 0;
    area[5].south = WIDTH - 1;
    area[5].east = room[8].west - 1;
    /*place 6 for the area in middle-west*/
    area[6].north = room[8].north;
    area[6].west = 0;
    area[6].south = room[8].south;
    area[6].east = room[8].west - 1;
    /*place 7 for the area in north-west*/
    area[7].north = 0;
    area[7].west = 0;
    area[7].south = room[8].north - 1;
    area[7].east = room[8].west - 1;
}

void sub_room_generator(int n)
{
    int x, y, l1, w1;

    if (!room[n].is_exist) {
        room[n].centerpoint[0] = room[n].centerpoint[1] = -1;
        room[n].north = room[n].east = room[n].south = room[n].west = 0;
        for (int i = 0; i < 4; ++i) {
            room[n].gate[i].is_exist = false;
            room[n].gate[i].x = room[n].gate[i].y= 0;
        }
        return;
    }

    coordinator_maker(&x, &y, &l1, &w1, n);
    switch (n) {
        case 0: /*north-central part*/
            while ((x - l1) <= area[0].west || (x + l1) >= area[1].east ||
                   (y - w1) <= area[0].north || (y + w1) >= area[0].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            if ((x + l1) >= area[0].east) {
                room[1].is_exist = false;
            }
            /*north-central room(0) not have northern-gate*/
            room[0].gate[0].is_exist = false;
            break;
        case 1: /*north-east part*/
            while ((x - l1) <= area[1].west || (x + l1) >= area[1].east ||
                   (y - w1) <= area[1].north || (y + w1) >= area[2].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            if ((y + w1) >= area[1].south) {
                room[2].is_exist = false;
            }
            /*north-east room(1) not have northern-gate & eastern-gate*/
            room[1].gate[0].is_exist = false;
            room[1].gate[3].is_exist = false;
            break;
        case 2: /*middle-east part*/
            while ((x - l1) <= area[2].west || (x + l1) >= area[2].east ||
                   (y - w1) <= area[2].north || (y + w1) >= area[3].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            if ((y + w1) >= area[2].south) {
                room[3].is_exist = false;
            }
            /*middle-east room(2) not have eastern-gate*/
            room[2].gate[3].is_exist = false;
            break;
        case 3: /*south-east part*/
            while ((x - l1) <= area[4].west || (x + l1) >= area[3].east ||
                   (y - w1) <= area[3].north || (y + w1) >= area[3].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            if ((x - l1) <= area[3].west) {
                room[4].is_exist = false;
            }
            /*south-east room(3) not have southern-gate & eastern-gate*/
            room[3].gate[2].is_exist = false;
            room[3].gate[3].is_exist = false;
            break;
        case 4: /*south-central part*/
            while ((x - l1) <= area[5].west || (x + l1) >= area[4].east ||
                   (y - w1) <= area[4].north || (y + w1) >= area[4].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            if ((x - l1) <= area[4].west) {
                room[5].is_exist = false;
            }
            /*south-central room(4) not have southern-gate*/
            room[4].gate[2].is_exist = false;
            break;
        case 5: /*south-west part*/
            while ((x - l1) <= area[5].west || (x + l1) >= area[5].east ||
                   (y - w1) <= area[6].north || (y + w1) >= area[5].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            if ((y - w1) <= area[5].north) {
                room[6].is_exist = false;
            }
            /*south-west room(5) not have western-gate & southern-gate*/
            room[5].gate[1].is_exist = false;
            room[5].gate[2].is_exist = false;
            break;
        case 6: /*middle-west part*/
            while ((x - l1) <= area[6].west || (x + l1) >= area[6].east ||
                   (y - w1) <= area[7].north || (y + w1) >= area[6].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            if ((y - w1) <= area[6].north) {
                room[7].is_exist = false;
            }
            /*middle-west room(6) not have western-gate*/
            room[6].gate[1].is_exist = false;
            break;
        case 7: /*north-west part*/
            while ((x - l1) <= area[7].west || (x + l1) >= area[7].east ||
                   (y - w1) <= area[7].north || (y + w1) >= area[7].south) {
                coordinator_maker(&x, &y, &l1, &w1, n);
            }
            /*north-west room(7) not have northern-gate & western-gate*/
            room[7].gate[0].is_exist = false;
            room[7].gate[1].is_exist = false;
            break;
    }

    room[n].north = y - w1;
    room[n].west = x - l1;
    room[n].south = y + w1;
    room[n].east = x + l1;
}

void room_to_layer(int n)
{
    if (room[n].is_exist) {
        for (int i = room[n].north + 1; i <= room[n].south - 1; ++i) {
            for (int j = room[n].west + 1; j <= room[n].east - 1; ++j) {
                layer[i][j] = '.';
                }
        }
        for (int i = room[n].west; i <= room[n].east; ++i) {
            layer[room[n].north][i] = layer[room[n].south][i] = '-';
        }
        for (int i = room[n].north + 1; i <= room[n].south - 1; ++i) {
            layer[i][room[n].west] = layer[i][room[n].east] = '|';
        }
    }
}

void coordinator_maker(int *x, int *y, int *l1, int *w1, int n)
{
    *x = (rand() % (area[n].east - area[n].west + 1) + area[n].west);
    *y = (rand() % (area[n].south - area[n].north + 1) + area[n].north);
    *l1 = (rand() % (5 - 3 + 1) + 3) + 1;
    *w1 = (rand() % (3 - 1 + 1) + 1) + 1;
}

void gate_generator(void)
{
    for (int i = 0; i < 9; ++i) {
        if (room[i].gate[0].is_exist) {
            room[i].gate[0].x = (rand() % ((room[i].east - 1) - 
                                           (room[i].west + 1) - 1) + 
                                           (room[i].west + 1));
            room[i].gate[0].y = room[i].north;
        }
        if (room[i].gate[1].is_exist) {
            room[i].gate[1].x = room[i].west;
            room[i].gate[1].y = (rand() % ((room[i].south - 1) -
                                           (room[i].north + 1) - 1) +
                                           (room[i].north + 1));
        }
        if (room[i].gate[2].is_exist) {
            room[i].gate[2].x = (rand() % ((room[i].east - 1) - 
                                           (room[i].west + 1) - 1) + 
                                           (room[i].west + 1));
            room[i].gate[2].y = room[i].south;
        }
        if (room[i].gate[3].is_exist) {
            room[i].gate[3].x = room[i].east;
            room[i].gate[3].y = (rand() % ((room[i].south - 1) - 
                                           (room[i].north + 1) - 1) + 
                                           (room[i].north + 1));
        }
    }
}

void path_generator(void)
{
    gate_generator();

    if (room[0].is_exist) {
        /*link north-central room(0) and main room(8)*/
        /*code number 02-80*/
        path_vertical_generator(0, 2, 8, 0);

        /*link north-central room(0) and north-east room(1)*/
        /*code number 03-11*/
        if (room[1].is_exist) {
            path_horizontal_generator(0, 3, 1, 1);
        } else if (room[2].is_exist) {
            /*link north-central room(0) and middle-east room(2)*/
            /*code number 03-20*/
            path_angle_generator(0, 3, 2, 0);
        }
    }

    if (room[1].is_exist) {
        /*link north-east room(1) and middle-east room(2)*/
        /*code number 12-20*/
        if (room[2].is_exist) {
            path_vertical_generator(1, 2, 2, 0);
        } else if (room[3].is_exist) {
            /*link north-east room(1) and south-east room(3)*/
            /*code number 12-30*/
            path_vertical_generator(1, 2, 3, 0);
        }
    }

    if (room[2].is_exist) {
        /*link middle-east room(2) and main room(8)*/
        /*code number 83-21*/
        path_horizontal_generator(8, 3, 2, 1);

        /*link middle-east room(2) and south-east room(3)*/
        /*code number 22-30*/
        if (room[3].is_exist) {
            path_vertical_generator(2, 2, 3, 0);
        } else if (room[4].is_exist) {
            /*link middle-east room(2) and southern-central room(4)*/
            /*code number 43-22*/
            path_angle_generator(4, 3, 2, 2);
        }
    }

    if (room[3].is_exist) {
        /*link south-east room(3) and south-central room(4)*/
        /*code number 43-31*/
        if (room[4].is_exist) {
            path_horizontal_generator(4, 3, 3, 1);
        } else if (room[5].is_exist) {
            /*link south-east room(3) and south-west room(5)*/
            /*code number 53-31*/
            path_horizontal_generator(5, 3, 3, 1);
        }
    }

    if (room[4].is_exist) {
        /*link south-central room(4) and main room(8)*/
        /*code number 82-40*/
        path_vertical_generator(8, 2, 4, 0);

        /*link south-central room(4) and south-west room(5)*/
        /*code number 53-41*/
        if (room[5].is_exist) {
            path_horizontal_generator(5, 3, 4, 1);
        } else if (room[6].is_exist) {
            /*link south-central room(4) and middle-west room(6)*/
            path_angle_generator(4, 1, 6, 2);
        }
    }

    if (room[5].is_exist) {
        /*link south-west room(5) and middle-west room(6)*/
        /*code number 62-50*/
        if (room[6].is_exist) {
            path_vertical_generator(6, 2, 5, 0);
        } else if (room[7].is_exist) {
            /*link south-west room(5) and north-west room(7)*/
            /*code number 72-50*/
            path_vertical_generator(7, 2, 5, 0);
        }
    }

    if (room[6].is_exist) {
        /*link middle-west room(6) and main room(8)*/
        /*code number 63-81*/
        path_horizontal_generator(6, 3, 8, 1);

        /*link middle-west room(6) and north-west room(7)*/
        /*code number 73-81*/
        if (room[7].is_exist) {
            path_vertical_generator(7, 2, 6, 0);
        }
    }

    if (room[7].is_exist) {
        /*link north-west room(7) and north-central room(0)*/
        /*code number 73-81*/
        path_horizontal_generator(7, 3, 0, 1);
    } 
}

/*n1.g1.y should be smaller than n2.g2.y*/
void path_vertical_generator(int n1, int g1, int n2, int g2)
{
    int x1, x2;
    int centerpoint = (room[n1].gate[g1].y + room[n2].gate[g2].y) / 2;

    if (((n1 == 1 || n1 == 2) && n2 == 3 && !room[4].is_exist)) {
        if (centerpoint <= room[8].south) {
            centerpoint = room[8].south + 1;
        }
    }

    layer[room[n1].gate[g1].y][room[n1].gate[g1].x] =
    layer[room[n2].gate[g2].y][room[n2].gate[g2].x] = '+';
    for (int i = room[n1].gate[g1].y + 1; i <= centerpoint; ++i) {
        layer[i][room[n1].gate[g1].x] = '#';
    }
    for (int i = centerpoint; i < (room[n2].gate[g2].y); ++i) {
        layer[i][room[n2].gate[g2].x] = '#';
    }
    x1 = (room[n1].gate[g1].x < room[n2].gate[g2].x ? room[n1].gate[g1].x : 
                                                      room[n2].gate[g2].x);
    x2 = (room[n1].gate[g1].x < room[n2].gate[g2].x ? room[n2].gate[g2].x : 
                                                      room[n1].gate[g1].x);
    for (; x1 <= x2; ++x1) {
        layer[centerpoint][x1] = '#';
    }
}

/*n1.g1.x shoule be smaller than n2.g2.x*/
void path_horizontal_generator(int n1, int g1, int n2, int g2)
{
    int y1, y2;
    int centerpoint = (room[n1].gate[g1].x + room[n2].gate[g2].x) / 2;

    if (n1 == 0 && n2 == 1 && !room[2].is_exist) {
        if (centerpoint <= room[8].east) {
            centerpoint = room[8].east + 1;
        }
    }
    if ((n1 == 5 && (n2 == 3 || n2 == 4) && !room[6].is_exist)) {
        if (centerpoint >= room[8].west) {
            centerpoint = room[8].west - 1;
        }
    }

    layer[room[n1].gate[g1].y][room[n1].gate[g1].x] = 
    layer[room[n2].gate[g2].y][room[n2].gate[g2].x] = '+';
    for (int i = room[n1].gate[g1].x + 1; i <= centerpoint; ++i) {
        layer[room[n1].gate[g1].y][i] = '#';
    }
    for (int i = centerpoint; i < room[n2].gate[g2].x; ++i) {
        layer[room[n2].gate[g2].y][i] = '#';
    }
    y1 = (room[n1].gate[g1].y < room[n2].gate[g2].y ? room[n1].gate[g1].y : 
                                                      room[n2].gate[g2].y);
    y2 = (room[n1].gate[g1].y < room[n2].gate[g2].y ? room[n2].gate[g2].y : 
                                                      room[n1].gate[g1].y);
    for (; y1 <= y2; ++y1) {
        layer[y1][centerpoint] = '#';
    }
}

/*n1 should be the room in length, n2 should be the room in width*/
void path_angle_generator (int n1, int g1, int n2, int g2) {
    int x1, x2, y1, y2;

    if ((n1 == 0 && n2 == 2 && room[n1].gate[g1].x >= room[n2].gate[g2].x) ||
        (n1 == 4 && n2 == 2 && room[n2].gate[g2].y >= room[n1].gate[g1].y) ||
        (n1 == 4 && n2 == 6 && room[n1].gate[g1].x <= room[n2].gate[g2].x)) {
        return;
    }

    layer[room[n1].gate[g1].y][room[n1].gate[g1].x] = 
    layer[room[n2].gate[g2].y][room[n2].gate[g2].x] = '+';

    x1 = (room[n1].gate[g1].x < room[n2].gate[g2].x ? room[n1].gate[g1].x : 
                                                      room[n2].gate[g2].x);
    x2 = (room[n1].gate[g1].x < room[n2].gate[g2].x ? room[n2].gate[g2].x : 
                                                      room[n1].gate[g1].x);
    y1 = (room[n1].gate[g1].y < room[n2].gate[g2].y ? room[n1].gate[g1].y : 
                                                      room[n2].gate[g2].y);
    y2 = (room[n1].gate[g1].y < room[n2].gate[g2].y ? room[n2].gate[g2].y : 
                                                      room[n1].gate[g1].y);

    for (int i = x1 + 1; i < x2; ++i) {
        layer[room[n1].gate[g1].y][i] = '#';
    }
    for (int i = y1 + 1; i < y2; ++i) {
        layer[i][room[n2].gate[g2].x] = '#';
    }

    if (n1 == 0 && n2 == 2) {
        layer[y1][x2] = '#';
    } else if (n1 == 4 && n2 == 2) {
        layer[y2][x2] = '#';
    } else if (n1 == 4 && n2 == 6) {
        layer[y2][x1] = '#';
    }
}

int player_move(void)
{
    char ch = getch(), x;

    player[player_y][player_x] = ' ';
    if (ch == 'w' || ch == 'W') {
        if ((x = layer[player_y - 1][player_x]) == '.' || 
             x == '#' || x == '+') {
            player_y--;
        } else if (x == '%') {
            return 1;
        }
    } else if (ch == 'a' || ch == 'A') {
        if ((x = layer[player_y][player_x - 1]) == '.' || 
             x == '#' || x == '+') {
            player_x--;
        } else if (x == '%') {
            return 1;
        }
    } else if (ch == 's' || ch == 'S') {
        if ((x = layer[player_y + 1][player_x]) == '.' || 
             x == '#' || x == '+') {
            player_y++;
        } else if (x == '%') {
            return 1;
        }
    } else if (ch == 'd' || ch == 'D') {
        if ((x = layer[player_y][player_x + 1]) == '.' || 
             x == '#' || x == '+') {
            player_x++;
        } else if (x == '%') {
            return 1;
        }
    }
    player[player_y][player_x] = '@';

    return 0;
}
#include "equipment_data.h"

struct equipment weapon_list[] = {
        {"Wooden Club", 1, 1, 0, 1, 5, 0, false},
        {"Rusty Sword", 2, 3, 0, 6, 10, 0, false},
        {"Steel Dagger", 3, 5, 0, 11, 15, 0, false},
        {"Long Sword", 4, 8, 0, 16, 20, 0, false},
        {"War Hammer", 5, 12, -4, 21, 25, 0, false},
        {"Great Sword", 6, 18, 0, 26, 30, 0, false},
        {"Dragon Fang", 7, 24, -6, 31, 40, 0, false},
        {"Demon Slayer", 8, 30, -12, 41, 49, 0, false}
};

struct equipment armor_list[] = {
        {"Leather Armor", 9, 0, 1, 1, 5, 0, false},
        {"Chainmail", 10, 0, 3, 6, 10, 0, false},
        {"Iron Plate Armor", 11, 0, 5, 11, 15, 0, false},
        {"Blessed Cloak", 12, 0, 8, 16, 20, 0, false},
        {"Dragon Scale Armor", 13, -4, 12, 21, 25, 0, false},
        {"Silver Plate Armor", 14, 0, 18, 26, 30, 0, false},
        {"Phantom Robe", 15, -6, 24, 31, 40, 0, false},
        {"Titan Plate Armor", 16, -12, 30, 41, 50, 0, false}
};

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <fstream>

#include "pos.hpp"

class Map
{
public:
    int w;
    int h;
    std::vector<int> tiles;
    std::vector<int> entities;
    std::vector<int> entity_count;
    int heroes_count;
    std::vector<Pos*> heroes_pos_on_map;
    std::vector<int> heroes_movement_points;

    Map();
    ~Map();

    int load_map_data(const std::string& filename);
    int get_tile(int x, int y) const;
    int get_tile(const Pos &pos) const;
    int get_entity(int x, int y) const;
    int get_entity(const Pos &pos) const;
};

#endif

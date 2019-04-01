#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <fstream>

class Map
{
public:
    int w;
    int h;
    std::vector<int> tiles;
    std::vector<int> entities;
    std::vector<int> entity_count;


    Map();
    ~Map();

    int load_map_data(const std::string& filename);
    int get_tile(int x, int y) const; /// nepatikrinta, assume it works
    int get_entity(int x, int y) const; /// nepatikrinta, assume it works
};

#endif

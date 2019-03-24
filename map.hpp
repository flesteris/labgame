#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <fstream>

class Map
{
private:

public:
    int w;
    int h;
    std::vector<int> tiles;

    Map();
    ~Map();
    int load_map_data(const std::string& filename);
};

#endif

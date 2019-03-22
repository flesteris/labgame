#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>

class Map
{
private:

public:
    //int w;
    //int h;

    int tiles[72][72];
    Map();
    ~Map();
    int load_map_data(const std::string& filename);
};

#endif

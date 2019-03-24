#include "map.hpp"
#include <fstream>

Map::Map() : w(0), h(0)
{

}

Map::~Map()
{

}

int Map::load_map_data(const std::string& filename)
{
    std::ifstream map_data(filename);

    if(map_data.is_open())
    {
        int x;
        map_data >> w;
        map_data >> h;
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                map_data >> x;
                tiles.push_back(x);
            }
        }
        map_data.close();
        return 1;
    }
    else
    {
        std::cout << "Failed to find the map data!" << std::endl;
        return 0;
    }
}

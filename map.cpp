#include "map.hpp"
#include <fstream>

Map::Map()
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
        /*map_data >> w;
        map_data >> h;*/
        for(int i = 0; i < 72; i++)
        {
            for(int j = 0; j < 72; j++)
            {
                map_data >> tiles[j][i];
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

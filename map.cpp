#include "map.hpp"

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
        int value;
        map_data >> w;
        map_data >> h;
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                map_data >> value;
                tiles.push_back(value);
            }
        }
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                map_data >> value;
                entities.push_back(value);
            }
        }
        while(!map_data.eof())
        {
            map_data >> value;
            entity_count.push_back(value);
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

int Map::get_tile(int x, int y) const
{
    if(x > w - 1|| y > h)
    {
        std::cout << "Incorrect coordinates!" << std::endl;
        return -1;
    }
    return tiles[y*w+x];
}

int Map::get_entity(int x, int y) const
{
    if(x > w - 1|| y > h)
    {
        std::cout << "Incorrect coordinates!" << std::endl;
        return -1;
    }
    return entities[y*w+x];
}

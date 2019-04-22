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
        int count, value, value_2;
        map_data >> w;
        map_data >> h;
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                map_data >> value;
                tiles.push_back(value);
            }
        }
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                map_data >> value;
                entities.push_back(value);
            }
        }
        map_data >> count;
        for(int i = 0; i < count; ++i)
        {
            map_data >> value;
            entity_count.push_back(value);
        }
        map_data >> heroes_count;
        for(int i = 0; i < heroes_count; ++i)
        {
            map_data >> value >> value_2;
            heroes_pos_on_map.push_back(new Pos(value, value_2));
            map_data >> value;
            heroes_movement_points.push_back(value);
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
    if(x >= w || y >= h || x < 0 || y < 0)
    {
        return -1;
    }
    return tiles[y * w + x];
}

int Map::get_tile(const Pos &pos) const
{
    if(pos.x >= w || pos.y >= h || pos.x < 0 || pos.y < 0)
    {
        return -1;
    }
    return tiles[pos.y * w + pos.x];
}

int Map::get_entity(int x, int y) const
{
    if(x >= w || y >= h || x < 0 || y < 0)
    {
        return -1;
    }
    return entities[y * w + x];
}

int Map::get_entity(const Pos &pos) const
{
    if(pos.x >= w || pos.y >= h || pos.x < 0 || pos.y < 0)
    {
        return -1;
    }
    return entities[pos.y * w + pos.x];
}

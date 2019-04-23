#include "tile_access_map.hpp"

TileAccessMap::TileAccessMap(Game* game, Hero* hero) :
    game(game),
    hero(hero)
{
    create_maps();
}

TileAccessMap::~TileAccessMap()
{

}

void TileAccessMap::create_maps()
{
    for(int i = 0; i < game->map.h * game->map.w; ++i)
    {
        access_map.push_back(-1);
        price_map.push_back(-1);
        vector_map.push_back(-1);
    }
}

void TileAccessMap::reset_maps()
{
    for(int i = 0; i < game->map.h * game->map.w; ++i)
    {
        access_map[i] = -1;
        price_map[i] = -1;
        vector_map[i] = -1;
    }
}

void TileAccessMap::update_maps()
{
    reset_maps();
    update_tile_access(hero->pos_on_map);
    update_tile_access_2();
    set_tile_price(hero->pos_on_map, 0);
    set_tile_vector(hero->pos_on_map, NO_DIRECTION);
    std::vector<int> min_values; // *searching for min values in there
    std::vector<Pos*> min_pos; // what pos is this min value at

    Pos pos = hero->pos_on_map;

    dijkstra(pos);

    std::ofstream map_data("mapped_prices.txt"); // <----- for testing
    std::ofstream map_data_2("mapped_vectors.txt");
    std::ofstream map_data_3("mapped_accessibility.txt");
    if(map_data.is_open() && map_data_2.is_open() && map_data_3.is_open())
    {
        for(int i = 0; i < game->map.h; i++)
        {
            for(int j = 0; j < game->map.w; j++)
            {
                int value = get_tile_price(Pos(j, i));
                map_data << std::setw(4) << std::right << value;
                value = get_tile_access(Pos(j, i));
                map_data_3 << std::setw(4) << std::right << value;

                int vektor = get_tile_vector(Pos(j, i));

                if(vektor == SOUTHWEST)
                {
                    map_data_2 << std::setw(4) << std::right << "v/ ";
                }
                else if(vektor == SOUTH)
                {
                    map_data_2 << std::setw(4) << std::right << "vv ";
                }
                else if(vektor == SOUTHEAST)
                {
                    map_data_2 << std::setw(4) << std::right << "\\v ";
                }
                else if(vektor == EAST)
                {
                    map_data_2 << std::setw(4) << std::right << "-> ";
                }
                else if(vektor == NORTHEAST)
                {
                    map_data_2 << std::setw(4) << std::right << "/^ ";
                }
                else if(vektor == NORTH)
                {
                    map_data_2 << std::setw(4) << std::right << "^^ ";
                }
                else if(vektor == NORTHWEST)
                {
                    map_data_2 << std::setw(4) << std::right << "^\\ ";
                }
                else if(vektor == WEST)
                {
                    map_data_2 << std::setw(4) << std::right << "<- ";
                }
                else
                {
                    map_data_2 << std::setw(4) << std::right << "oo ";
                }
            }
            map_data << std::endl;
            map_data_2 << std::endl;
            map_data_3 << std::endl;
        }
        map_data.close();
        map_data_2.close();
        map_data_3.close();
    }                                                   // ------
}

void TileAccessMap::update_tile_access(const Pos &pos)
{
    for(int i = 1; i < DIRECTION_COUNT; i += 2)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        if(game->map.get_entity(temp_pos) != -1)
        {
            if(game->map.get_entity(temp_pos) == 0)
            {
                if(get_tile_access(temp_pos) == -1)
                {
                    if(monster_nearby(temp_pos))
                    {
                        set_tile_access(temp_pos, 0);
                    }
                    else
                    {
                        set_tile_access(temp_pos, 10);
                        update_tile_access(temp_pos);
                    }
                }
            }
            //else if other entities
        }
    }
}

void TileAccessMap::update_tile_access_2()
{
    for(auto monster : game->monsters)
    {
        for(int i = 0; i < DIRECTION_COUNT; ++i)
        {
            Pos temp_pos = monster->pos_on_map + DIRECTIONS[i];
            for(int j = 0; j < DIRECTION_COUNT; j += 2)
            {
                Pos temp_2_pos = temp_pos + DIRECTIONS[j];
                if(get_tile_access(temp_2_pos) > 0)
                {
                    set_tile_access(temp_pos, 0);
                    break;
                }
            }
        }
    }
}

bool TileAccessMap::monster_nearby(const Pos &pos) const
{
    for(int i = 0; i < DIRECTION_COUNT; ++i)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        int entity = game->map.get_entity(temp_pos);
        if(is_monster(entity))
        {
            return true;
        }
    }
    return false;
}

bool TileAccessMap::is_monster(int entity) const
{
    if(entity <= 15 && entity > 0)
    {
        return true;
    }
    return false;
}

void TileAccessMap::set_tile_access(const Pos &pos, int value)
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return;
    }
    access_map[pos.y * game->map.w + pos.x] = value;
}

int TileAccessMap::get_tile_access(const Pos &pos) const
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return -1;
    }
    return access_map[pos.y * game->map.w + pos.x];
}

void TileAccessMap::set_tile_price(const Pos &pos, int value)
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return;
    }
    price_map[pos.y * game->map.w + pos.x] = value;
}

int TileAccessMap::get_tile_price(const Pos &pos) const
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return -1; // might be not ok idk
    }
    return price_map[pos.y * game->map.w + pos.x];
}

void TileAccessMap::set_tile_vector(const Pos &pos, int value)
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return;
    }
    vector_map[pos.y * game->map.w + pos.x] = value;
}

int TileAccessMap::get_tile_vector(const Pos &pos) const
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return -1;
    }
    return vector_map[pos.y * game->map.w + pos.x];
}

void TileAccessMap::dijkstra(const Pos &pos)
{
    for(int i = 0; i < DIRECTION_COUNT; ++i)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        int access;
        if(i % 2 == 0) // is the tile we're accessing diagonal from the current one
        {
            access = get_tile_access(temp_pos) * 1.41; // ... * square root of 2;
        }
        else
        {
            access = get_tile_access(temp_pos);
        }


        /*if(access == 0)
        {

        }
        else*/ if(access > 0)
        {
            int price = get_tile_price(pos) + access;
            int price_2 = get_tile_price(temp_pos);
            if(price_2 == -1)
            {
                dijkstra_values.push_back(price);
                dijkstra_pos.push_back(new Pos(temp_pos));
                set_tile_price(temp_pos, price);
                set_tile_vector(temp_pos, i);
                bring_min_to_front();
            }
            else if(price < price_2)
            {
                for(int j = 0; j < dijkstra_values.size(); ++j) /// maybe optimisible
                {
                    if(*dijkstra_pos[j] == temp_pos)
                    {
                        dijkstra_values[j] = price;
                        set_tile_price(temp_pos, price);
                        set_tile_vector(temp_pos, i);
                        break;
                    }
                }
                bring_min_to_front();
            }
        }
    }

    if(!dijkstra_values.empty())
    {
        Pos pos_2 = *dijkstra_pos[0];
        dijkstra_values.erase(dijkstra_values.begin());
        delete dijkstra_pos[0];
        dijkstra_pos.erase(dijkstra_pos.begin());
        dijkstra(pos_2);
    }
}

void TileAccessMap::bring_min_to_front()
{
    int temp_min = dijkstra_values[0], min_index = 0;
    for(int i = 1; i < dijkstra_values.size(); ++i)
    {
        if(temp_min > dijkstra_values[i])
        {
            temp_min = dijkstra_values[i];
            min_index = i;
        }
    }
    if(min_index != 0)
    {
        dijkstra_values[min_index] = dijkstra_values[0];
        dijkstra_values[0] = temp_min;
        Pos pos = *dijkstra_pos[min_index];
        *dijkstra_pos[min_index] = *dijkstra_pos[0];
        *dijkstra_pos[0] = pos;
    }
}

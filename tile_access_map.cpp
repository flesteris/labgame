#include "tile_access_map.hpp"

TileAccessMap::TileAccessMap(Game* game, Hero* hero) :
    game(game),
    hero(hero)
{
    create_accessible_tile_map();
}

TileAccessMap::~TileAccessMap()
{

}

void TileAccessMap::create_accessible_tile_map()
{
    for(int i = 0; i < game->map.h * game->map.w; ++i)
    {
        accessible_tile_map.push_back(-1);
        price_map.push_back(-1);
        vector_map.push_back(nullptr);
    }
}

void TileAccessMap::update_accessible_tile_map()
{
    update_tile_access(hero->pos_on_map);
    update_tile_access_3();
    set_tile_price(hero->pos_on_map, 0);
    set_tile_vector(hero->pos_on_map, DIRECTIONS[NO_DIRECTION]);
    std::vector<int> min_values; // *searching for min values in there
    std::vector<Pos*> min_pos; // what pos is this min value at

    Pos pos = hero->pos_on_map;

    dijkstra(pos);

    std::ofstream map_data("mapped.txt"); // <----- for testing
    if(map_data.is_open())
    {
        for(int i = 0; i < game->map.h; i++)
        {
            for(int j = 0; j < game->map.w; j++)
            {
                int value = get_tile_price(Pos(j, i));
                if(value >= 0)
                {
                    map_data << " " << value << " ";
                }
                else
                {
                    map_data << value << " ";
                }
            }
            map_data << std::endl;
        }
        map_data.close();
    }                                                  // ------
}

void TileAccessMap::update_tile_access(const Pos &pos)
{
    for(int i = 1; i < DIRECTION_COUNT; i += 2)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        update_tile_access_2(temp_pos);
    }
}

void TileAccessMap::update_tile_access_2(const Pos &pos)
{
    if(game->map.get_entity(pos) != -1)
    {
        if(game->map.get_entity(pos) == 0)
        {
            if(get_tile_accessibility(pos) == -1)
            {
                if(monster_nearby(pos))
                {
                    set_tile_accessibility(pos, 0);
                }
                else
                {
                    set_tile_accessibility(pos, 1);
                    update_tile_access(pos);
                }
            }
        }
        //else other entities
    }
}

void TileAccessMap::update_tile_access_3()
{
    for(auto monster : game->monsters)
    {
        for(int i = 0; i < DIRECTION_COUNT; ++i)
        {
            Pos temp_pos = monster->pos_on_map + DIRECTIONS[i];
            for(int j = 0; j < DIRECTION_COUNT; j += 2)
            {
                Pos temp_2_pos = temp_pos + DIRECTIONS[j];
                if(get_tile_accessibility(temp_2_pos) > 0)
                {
                    set_tile_accessibility(temp_pos, 0);
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

void TileAccessMap::set_tile_accessibility(const Pos &pos, int value)
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return;
    }
    accessible_tile_map[pos.y * game->map.w + pos.x] = value;
}

int TileAccessMap::get_tile_accessibility(const Pos &pos) const
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return -1;
    }
    return accessible_tile_map[pos.y * game->map.w + pos.x];
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

void TileAccessMap::set_tile_vector(const Pos &pos, const Pos &direction)
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return;
    }
    Pos temp_pos = direction;
    vector_map[pos.y * game->map.w + pos.x] = &temp_pos;
}

Pos TileAccessMap::get_tile_vector(const Pos &pos) const
{
    if(pos.x >= game->map.w || pos.y >= game->map.h || pos.x < 0 || pos.y < 0)
    {
        return Pos(); // might be not ok idk
    }
    return *vector_map[pos.y * game->map.w + pos.x];
}

void TileAccessMap::dijkstra(const Pos &pos)
{
    for(int i = 0; i < DIRECTION_COUNT; ++i)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        int access = get_tile_accessibility(temp_pos);

        /*if(access == 0)
        {

        }
        else*/ if(access > 0)
        {
            int price = get_tile_price(pos) + access;
            int price_2 = get_tile_price(temp_pos);
            if(price_2 == -1)
            {
                //std::cout << price << " ";
                //temp_pos.print_coordinates();
                min_values.push_back(price);
                min_pos.push_back(new Pos(temp_pos));
                set_tile_price(temp_pos, price);
                set_tile_vector(temp_pos, DIRECTIONS[i]);
                bring_min_to_front();
            }
            else if(price < price_2)
            {
                for(int j = 0; j < min_values.size(); ++j)
                {
                    if(*min_pos[j] == temp_pos)
                    {
                        min_values[j] = price;
                        set_tile_price(temp_pos, price);
                        set_tile_vector(temp_pos, DIRECTIONS[i]);
                        break;
                    }
                }
                bring_min_to_front();
            }
        }
    }

    if(!min_values.empty())
    {
        Pos pos_2 = *min_pos[0];
        min_values.erase(min_values.begin());
        min_pos.erase(min_pos.begin());
        dijkstra(pos_2);
    }
}

void TileAccessMap::bring_min_to_front()
{
    int temp_min = min_values[0], min_index = 0;
    for(int i = 1; i < min_values.size(); ++i)
    {
        if(temp_min > min_values[i])
        {
            temp_min = min_values[i];
            min_index = i;
        }
    }
    if(min_index != 0)
    {
        min_values[min_index] = min_values[0];
        min_values[0] = temp_min;
        Pos pos = *min_pos[min_index];
        *min_pos[min_index] = *min_pos[0];
        *min_pos[0] = pos;
    }
}


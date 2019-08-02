#include "tile_access_map.hpp"

void TileAccessMap::print_to_files() const // <----- for testing
{
    std::ofstream map_data("mapped_prices.txt");
    std::ofstream map_data_2("mapped_vectors.txt");
    std::ofstream map_data_3("mapped_accessibility.txt");
    if(map_data.is_open() && map_data_2.is_open() && map_data_3.is_open())
    {
        for(int i = 0; i < game->map->h; i++)
        {
            for(int j = 0; j < game->map->w; j++)
            {
                Pos pos(j, i);
                int value = price_map[pos];
                map_data << std::setw(4) << std::right << value;
                value = access_map[pos];
                map_data_3 << std::setw(4) << std::right << value;

                value = vector_map[pos];

                if(value == SOUTHWEST)
                {
                    map_data_2 << std::setw(4) << std::right << "v/ ";
                }
                else if(value == SOUTH)
                {
                    map_data_2 << std::setw(4) << std::right << "vv ";
                }
                else if(value == SOUTHEAST)
                {
                    map_data_2 << std::setw(4) << std::right << "\\v ";
                }
                else if(value == EAST)
                {
                    map_data_2 << std::setw(4) << std::right << "-> ";
                }
                else if(value == NORTHEAST)
                {
                    map_data_2 << std::setw(4) << std::right << "/^ ";
                }
                else if(value == NORTH)
                {
                    map_data_2 << std::setw(4) << std::right << "^^ ";
                }
                else if(value == NORTHWEST)
                {
                    map_data_2 << std::setw(4) << std::right << "^\\ ";
                }
                else if(value == WEST)
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
    }
}

TileAccessMap::TileAccessMap(Game* game, Hero* hero) :
    game(game),
    hero(hero),
    b_updated(true)
{
    create_maps();
}

TileAccessMap::~TileAccessMap()
{
    print_to_files();
}

void TileAccessMap::create_maps()
{
    access_map.resize(game->map->w, game->map->h, -1);
    price_map.resize(game->map->w, game->map->h, -1);
    vector_map.resize(game->map->w, game->map->h);
    setup_maps();
}

void TileAccessMap::reset_maps()
{
    for(int i = 0; i < game->map->h * game->map->w; ++i)
    {
        access_map[i] = -1;
        price_map[i] = -1;
        vector_map[i] = -1;
    }
}

void TileAccessMap::update_maps()
{
    b_updated = true;
    reset_maps();
    setup_maps();
}

void TileAccessMap::setup_maps()
{
    update_tile_access();
    update_tile_access_2(hero->pos_on_map);
    update_tile_access_3();

    price_map[hero->pos_on_map] = 0;
    vector_map[hero->pos_on_map] = NO_DIRECTION;
    dijkstra(hero->pos_on_map);
}

void TileAccessMap::update_tile_access()
{
    for(int i = 0; i < game->map->w * game->map->h; ++i)
    {
        Entity* entity = game->map->entities[i];
        Obstacle* obstacle = dynamic_cast<Obstacle*> (entity);
        Town* town = dynamic_cast<Town*> (entity);
        if(obstacle)
        {
            access_map[i] = INACCESSABLE;
            Forest1* forest1 = dynamic_cast<Forest1*> (obstacle);
            if(forest1)
            {
                Pos temp_pos = forest1->pos_on_map + DIRECTIONS[EAST];
                access_map[temp_pos] = INACCESSABLE;
            }
        }
        else if(town)
        {
            set_access_if_town(town->pos_on_map);
        }
    }
}

void TileAccessMap::set_access_if_town(const Pos &pos)
{
    Pos temp_pos = pos;
    temp_pos += DIRECTIONS[NORTH];
    access_map[temp_pos] = INACCESSABLE;
    for(int i = SOUTH; i < NORTH; ++i)
    {
        Pos temp_pos_2 = temp_pos + DIRECTIONS[i];
        access_map[temp_pos_2] = INACCESSABLE;
    }
    temp_pos += DIRECTIONS[EAST] + DIRECTIONS[EAST] + DIRECTIONS[EAST];
    access_map[temp_pos] = INACCESSABLE;
    for(int i = SOUTHWEST; i < NORTHEAST; ++i)
    {
        Pos temp_pos_2 = temp_pos + DIRECTIONS[i];
        access_map[temp_pos_2] = INACCESSABLE;
    }
    for(int i = NORTH; i < DIRECTION_COUNT; ++i)
    {
        Pos temp_pos_2 = temp_pos + DIRECTIONS[i];
        access_map[temp_pos_2] = INACCESSABLE;
    }
}

void TileAccessMap::update_tile_access_2(const Pos &pos)
{
    for(int i = SOUTHWEST; i < DIRECTION_COUNT; ++i)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        if(temp_pos.is_in_rect(game->map_size_rect))
        {
            int access = access_map[temp_pos];
            if(access == NOT_SET)
            {
                Entity* entity = game->map->entities[temp_pos];
                if(entity)
                {
                    Monster* monster = dynamic_cast<Monster*> (entity);
                    Hero* hero = dynamic_cast<Hero*> (entity);
                    Resource* resource = dynamic_cast<Resource*> (entity);
                    if(monster)
                    {
                        access_map[temp_pos] = MONSTER;
                    }
                    else if(hero)
                    {
                        access_map[temp_pos] = HERO;
                    }
                    else if(resource)
                    {
                        access_map[temp_pos] = RESOURCE;
                    }
                }
                else
                {
                    if(game->map->monster_nearby(temp_pos) != temp_pos) //If monster is nearby
                    {
                        access_map[temp_pos] = MONSTER_NEARBY;
                    }
                    else
                    {
                        access_map[temp_pos] = FREE;
                        update_tile_access_2(temp_pos);
                    }
                }
            }
        }
    }
}

void TileAccessMap::update_tile_access_3()
{
    for(int i = 0; i < game->map->w * game->map->h; ++i)
    {
        Entity* entity = game->map->entities[i];
        Monster* monster = dynamic_cast<Monster*> (entity);
        Town* town = dynamic_cast<Town*> (entity);
        if(monster)
        {
            for(int j = 0; j < DIRECTION_COUNT; ++j)
            {
                Pos temp_pos = monster->pos_on_map + DIRECTIONS[j];
                if(temp_pos.is_in_rect(game->map_size_rect))
                {
                    int access = access_map[temp_pos];
                    if(access != NOT_SET)
                    {
                        access_map[monster->pos_on_map] = MONSTER;
                        break;
                    }
                }
            }
        }
        else if(town)
        {
            Pos temp_pos = town->pos_on_map + DIRECTIONS[EAST] + DIRECTIONS[EAST];
            if(hero->pos_on_map != temp_pos)
            {
               for(int i = SOUTHWEST; i < EAST; ++i)
                {
                    Pos temp_pos_2 = temp_pos + DIRECTIONS[i];
                    if(access_map[temp_pos_2] == FREE || access_map[temp_pos_2] == HERO)
                    {
                        access_map[temp_pos] = ACCESSABLE_ONLY;
                        break;
                    }
                }
            }
            else
            {
                access_map[temp_pos] = HERO;
            }
        }
    }
}

void TileAccessMap::dijkstra(const Pos &pos)
{
    for(int i = 0; i < DIRECTION_COUNT; ++i)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        if(temp_pos.is_in_rect(game->map_size_rect))
        {
            int access = access_map[temp_pos];
            int access_2 = access_map[pos];
            bool b_is_diagonal = (i + 1) % 2;
            int price = price_map[pos];
            int price_2 = price_map[temp_pos];
            if(b_is_diagonal)
            {
                price += 10 * 1.41; // PRICE sometime will depend on the tile or smth
            }
            else
            {
                price += 10;
            }
            dijkstra_2(price, price_2, access, access_2, i, pos, temp_pos);
        }
    }
    next_min_value();
}

void TileAccessMap::dijkstra_2(int price, int price_2, int access, int access_2,
                               int i, const Pos &pos, const Pos &temp_pos)
{
    if(access_2 == MONSTER_NEARBY && pos != hero->pos_on_map)
    {
        if(game->map->is_monster(temp_pos))
        {
            if(price_2 == NOT_SET || price < price_2)
            {
                price_map[temp_pos] = price;
                vector_map[temp_pos] = i;
            }
        }
    }
    else if(access == RESOURCE)
    {
        if(price_2 == NOT_SET || price < price_2)
        {
            price_map[temp_pos] = price;
            vector_map[temp_pos] = i;
        }
    }
    else if(access >= 0) // else other access type
    {
        if(price_2 == NOT_SET)
        {
            dijkstra_min_values.push_back(new Pos(temp_pos));
            price_map[temp_pos] = price;
            vector_map[temp_pos] = i;
            sort_dijkstra_pos_from_end();
        }
        else if(price < price_2)
        {
            price_map[temp_pos] = price;
            vector_map[temp_pos] = i;
            sort_dijkstra_pos_from_begining();
        }
    }
}

void TileAccessMap::next_min_value()
{
    if(!dijkstra_min_values.empty())
    {
        Pos pos_2 = **(dijkstra_min_values.end() - 1);
        delete *(dijkstra_min_values.end() - 1);
        dijkstra_min_values.pop_back();
        dijkstra(pos_2);
    }
}

void TileAccessMap::sort_dijkstra_pos_from_end()
{
    std::vector<Pos*>::iterator it;
    for(it = dijkstra_min_values.end() - 1; it > dijkstra_min_values.begin(); --it)
    {
        int price = price_map[**it];
        int price_2 = price_map[**(it - 1)];
        if(price > price_2)
        {
            Pos* temp = *it;
            *it = *(it - 1);
            *(it - 1) = temp;
        }
        else
        {
            break;
        }
    }
}

void TileAccessMap::sort_dijkstra_pos_from_begining()
{
    std::vector<Pos*>::iterator it;
    for(it = dijkstra_min_values.begin(); it < dijkstra_min_values.end() - 1; ++it)
    {
        int price = price_map[**it];
        int price_2 = price_map[**(it + 1)];
        if(price < price_2)
        {
            Pos* temp = *it;
            *it = *(it + 1);
            *(it + 1) = temp;
        }
    }
}

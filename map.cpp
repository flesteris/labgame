#include "map.hpp"

Map::Map(Game* game) :
    w(0),
    h(0),
    game(game),
    b_zone_of_control_updated(false)
{

}

Map::~Map()
{
    for(size_t i = 0; i < entities.size(); ++i)
    {
        if(entities[i])
        {
            delete entities[i];
        }
    }
}

void Map::read_matrix(std::ifstream &map_data, Matrix<int> &matrix)
{
    int value;
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            map_data >> value;
            matrix[Pos(j, i)] = value;
        }
    }
}

void Map::create_entities(const Matrix<int> &entity_types,
                          std::list<int> &monster_count,
                          std::list<int> &heroes_movement_points)
{
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            int entity_type = entity_types[Pos(j, i)];
            Entity* entity = nullptr;
            if(entity_type == WOLF_ENTITY)
            {
                entity = new Wolf(game, Pos(j, i), *monster_count.begin());
                monster_count.erase(monster_count.begin());
            }
            else if(entity_type == GOBLIN_ENTITY)
            {
                entity = new Goblin(game, Pos(j, i), *monster_count.begin());
                monster_count.erase(monster_count.begin());
            }
            else if(entity_type == SNAKE_ENTITY)
            {
                entity = new Snake(game, Pos(j, i), *monster_count.begin());
                monster_count.erase(monster_count.begin());
            }
            else if(entity_type == HERO_ENTITY)
            {
                Hero* hero = new Hero(game, Pos(j, i), *heroes_movement_points.begin());
                entity = hero;
                game->player->heroes.push_back(hero);
                heroes_movement_points.erase(heroes_movement_points.begin());
            }
            else if(entity_type == FOREST_1_ENTITY)
            {
                entity = new Forest1(game, Pos(j, i));
            }
            else if(entity_type == HILLS_1_ENTITY)
            {
                entity = new Hills1(game, Pos(j, i));
            }
            else if(entity_type == HILLS_2_ENTITY)
            {
                entity = new Hills2(game, Pos(j, i));
            }
            else if(entity_type == GOLD_ENTITY)
            {
                entity = new Gold(game, Pos(j, i), 10);
            }
            else if(entity_type == MERCURY_CRYSTAL_ENTITY)
            {
                entity = new MercuryCrystal(game, Pos(j, i), 1);
            }
            else if(entity_type == SULPHUR_CRYSTAL_ENTITY)
            {
                entity = new SulphurCrystal(game, Pos(j, i), 1);
            }
            else if(entity_type == LIGHTNING_CRYSTAL_ENTITY)
            {
                entity = new LightningCrystal(game, Pos(j, i), 1);
            }
            else if(entity_type == TOWN_ENTITY)
            {
                entity = new Town(game, Pos(j, i));
            }
            entities[Pos(j, i)] = entity;
        }
    }
}

void Map::read_line(std::ifstream &map_data, std::list<int> &line)
{
    int value, count;
    map_data >> count;
    for(int i = 0; i < count; ++i)
    {
        map_data >> value;
        line.push_back(value);
    }
}

void Map::load_map_data(const std::string& filename)
{
    std::ifstream map_data(filename);

    if(map_data.is_open())
    {
        Matrix<int> entity_types;
        std::list<int> monster_count;
        std::list<int> heroes_movement_points;
        map_data >> w;
        map_data >> h;
        game->map_size_rect = Rect(0, 0, w - 1, h - 1);

        tiles.resize(w, h);
        entity_types.resize(w, h);
        entities.resize(w, h);
        zone_of_control.resize(w, h);

        read_matrix(map_data, tiles);
        read_matrix(map_data, entity_types);
        read_line(map_data, monster_count);
        read_line(map_data, heroes_movement_points);

        create_entities(entity_types, monster_count, heroes_movement_points);
        map_data.close();
    }
    else
    {
        throw map_file_missing(filename);
    }
}

void Map::move_entity(const Pos &pos, Entity* entity)
{
    entities[pos] = entity;
    entities.erase(entity->pos_on_map);
    entity->pos_on_map = pos;
}

bool Map::is_monster(const Pos &pos) const
{
    if(pos.is_in_rect(game->map_size_rect))
    {
        Entity* entity = entities[pos];
        Monster* monster = dynamic_cast<Monster*> (entity);
        if(monster)
        {
            return true;
        }
    }
    return false;
}

Pos Map::monster_nearby(const Pos &pos) const
{
    for(int i = 0; i < DIRECTION_COUNT; ++i)
    {
        Pos temp_pos = pos + DIRECTIONS[i];
        if(temp_pos.is_in_rect(game->map_size_rect))
        {
            if(is_monster(temp_pos))
            {
                return temp_pos;
            }
        }
    }
    return pos;
}

void Map::update_zone_of_control()
{
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            Pos pos(j, i);
            if(monster_nearby(pos) != pos || is_monster(pos))
            {
                zone_of_control[i * w + j] = true;
            }
            else
            {
                zone_of_control[i * w + j] = false;
            }
        }
    }
}

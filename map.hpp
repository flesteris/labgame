#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <fstream>

#include "entity.hpp"
#include "exceptions.hpp"
#include "hero.hpp"
#include "matrix.hpp"
#include "monster.hpp"
#include "obstacle.hpp"
#include "pos.hpp"
#include "resource.hpp"

enum EntityType
{
    NO_ENTITY = 0,
    WOLF_ENTITY = 1,
    GOBLIN_ENTITY = 2,
    SNAKE_ENTITY = 3,
    FOREST_1_ENTITY = 4,
    HILLS_1_ENTITY = 5,
    HILLS_2_ENTITY = 6,
    MERCURY_CRYSTAL_ENTITY = 7,
    SULPHUR_CRYSTAL_ENTITY = 8,
    LIGHTNING_CRYSTAL_ENTITY = 9,
    GOLD_ENTITY = 10,
    HERO_ENTITY = 11,
    TOWN_ENTITY = 12
};

class Hero;
class Monster;

class Map
{
private:
    Game* game;
    void read_matrix(std::ifstream &map_data, Matrix<int> &matrix);
    void read_line(std::ifstream &map_data, std::list<int> &line);
    void create_entities(const Matrix<int> &entity_types,
                         std::list<int> &monster_count,
                         std::list<int> &heroes_movement_points);

public:
    bool b_zone_of_control_updated;

    int w;
    int h;
    Matrix<int> tiles;
    Matrix<Entity*> entities;
    Matrix<bool> zone_of_control;

    Map(Game* game);
    ~Map();

    void load_map_data(const std::string& filename);
    void move_entity(const Pos &pos, Entity* entity);
    bool is_monster(const Pos &pos) const;
    Pos monster_nearby(const Pos &pos) const;
    void update_zone_of_control();
};

#endif

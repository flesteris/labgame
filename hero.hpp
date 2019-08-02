#ifndef HERO_HPP
#define HERO_HPP

#include "entity.hpp"
#include "game.hpp"
#include "monster.hpp"
#include "pos.hpp"
#include "resource.hpp"
#include "tile_access_map.hpp"

enum Direction
{
    SOUTHWEST = 0,
    SOUTH = 1,
    SOUTHEAST = 2,
    EAST = 3,
    NORTHEAST = 4,
    NORTH = 5,
    NORTHWEST = 6,
    WEST = 7,
    NO_DIRECTION = 8,
    DIRECTION_COUNT = 8,
    HERO_IMAGE_COUNT = 8
};

class Game;
class Monster;
class Resource;
class TileAccessMap;

class Hero : public Entity
{
private:
    int m_direction;
    int m_max_movement_points;
    int m_current_movement_points; // starts at max each turn

public:
////Flags///////////////////////////////////////////
    bool b_alive;
    bool b_hero_moving;
    bool b_destination_present;
    bool b_out_of_movement_points;
////Points relative to the map//////////////////////
    Pos destination_mark_pos_on_map;
    std::vector<Pos> destination_dot_pos_on_map;

    TileAccessMap* tile_access_map;
    std::vector<int> current_travel_path;
    std::array<Monster*, 5> hero_army; // max 5 units

    Hero(Game* game, const Pos &pos_on_map, int max_movement_points);
    ~Hero();

    bool move();
    bool initiate_combat(const Pos &monster_pos_on_map);
    void collect_resource(Resource* resource);
    void sort_hero_army();
    void stop();
    void reset_movement_points();
    void draw_entity(const Rect &drect) const;

////Seteriai ir geteriai////////////////////////////////////////////////////////
    void set_direction(int a) {m_direction = a;}
    int get_direction() {return m_direction;}

    void set_max_movement_points(int a) {m_max_movement_points = a;}
    int get_max_movement_points() {return m_max_movement_points;}

    void set_current_movement_points(int a) {m_current_movement_points = a;}
    int get_current_movement_points() {return m_current_movement_points;}
////////////////////////////////////////////////////////////////////////////////
};

#endif //HERO_HPP

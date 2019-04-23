#ifndef HERO_HPP
#define HERO_HPP

#include "game.hpp"
#include "monster.hpp"
#include "pos.hpp"
#include "tile_access_map.hpp"

enum HeroDirection
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
class TileAccessMap;

class Hero
{
private:
    int m_direction;
    int m_max_movement_points;
    int m_current_movement_points; // starts at max each turn
    Game* game;

public:
////Flags///////////////////////////////////////////
    bool b_hero_moving;
    bool b_destination_present;
    bool b_out_of_movement_points;

////Points relative to the map//////////////////////
    Pos pos_on_map;
    Pos destination_mark_pos_on_map;
    std::vector<Pos> destination_dot_pos_on_map;

    TileAccessMap* tile_access_map;
    std::vector<int> current_travel_path;
    std::vector<Monster*> hero_army; // max 5 units

    Hero(Game* game, Pos &pos, int max_movement_points);
    ~Hero();

    int move();
    void stop();

// Seteriai ir geteriai ////////////////////////////////////////////////////////
    void set_direction(int a) {m_direction = a;}
    int get_direction() {return m_direction;}

    void set_max_movement_points(int a) {m_max_movement_points = a;}
    int get_max_movement_points() {return m_max_movement_points;}

    void set_current_movement_points(int a) {m_current_movement_points = a;}
    int get_current_movement_points() {return m_current_movement_points;}
////////////////////////////////////////////////////////////////////////////////

    friend void draw_land(Game* game);
};

#endif //HERO_HPP

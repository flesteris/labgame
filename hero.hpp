#ifndef HERO_HPP
#define HERO_HPP

#include "game.hpp"
#include "pos.hpp"

extern const Pos DIRECTIONS[9];

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
    HERO_IMAGE_COUNT = 8
};

class Game;

class Hero
{
private:
    int m_direction;
    int m_max_movement_points;
    int m_current_movement_points; // starts at max each turn
    Game* game;

public:
    bool hero_moving = false;
    bool destination_present = false;
    bool out_of_movement_points = false;

    Pos m_pos;

    Hero(Game* game);
    Hero(Game* game, Pos &pos, int max_movement_points);
    ~Hero();

    int move();

// Seteriai ir geteriai ////////////////////////////////////////////////////////
    void set_direction(int a) {m_direction = a;}
    int get_direction() {return m_direction;}

    void set_pos(Pos a) {m_pos = a;}
    Pos get_pos() {return m_pos;}

    void set_pos_x(int a) {m_pos.x = a;}
    int get_pos_x() {return m_pos.x;}

    void set_pos_y(int a) {m_pos.y = a;}
    int get_pos_y() {return m_pos.y;}

    void set_max_movement_points(int a) {m_max_movement_points = a;}
    int get_max_movement_points() {return m_max_movement_points;}

    void set_current_movement_points(int a) {m_current_movement_points = a;}
    int get_current_movement_points() {return m_current_movement_points;}
////////////////////////////////////////////////////////////////////////////////

    friend void draw_land(Game* game);
};

#endif //HERO_HPP

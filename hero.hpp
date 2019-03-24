#ifndef HERO_HPP
#define HERO_HPP

#include "game.hpp"

class Game;

class Hero
{
private:
    int m_direction;
    Pos m_pos;
    int m_max_movement_points;
    int m_current_movement_points; // starts at max each turn

public:
    bool move_triggered = false;
    Game* game;
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
};

#endif //HERO_HPP

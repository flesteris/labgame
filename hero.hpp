#ifndef HERO_HPP
#define HERO_HPP
#include "image.hpp"
#include "images.hpp"
#include "map.hpp"
#include "game.hpp"

class Hero
{
private:
    int m_direction;
    int m_x;
    int m_y;
    int m_max_movement_points;
    int m_current_movement_points; // starts at max each turn

public:
    Hero();
    Hero(int x, int y, int max_movement_points);
    ~Hero();

    int move(Images &images, SDL_Renderer* ren, Rect &hero_drect, Map &map);

// Seteriai ir geteriai ////////////////////////////////////////////////////////
    void set_m_direction(int a) {m_direction = a;}
    int get_m_direction() {return m_direction;}

    void set_x(int a) {m_x = a;}
    int get_x() {return m_x;}

    void set_y(int a) {m_y = a;}
    int get_y() {return m_y;}

    void set_max_movement_points(int a) {m_max_movement_points = a;}
    int get_max_movement_points() {return m_max_movement_points;}

    void set_current_movement_points(int a) {m_current_movement_points = a;}
    int get_current_movement_points() {return m_current_movement_points;}
////////////////////////////////////////////////////////////////////////////////

    friend void draw_land(int x, int y, Map &map, Images &images, SDL_Renderer* ren);
};

void draw_land(int x, int y, Map &map, Images &images, SDL_Renderer* ren);

#endif //HERO_HPP

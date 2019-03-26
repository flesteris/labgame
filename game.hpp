#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include "game_time.hpp"
#include "hero.hpp"
#include "images.hpp"
#include "map.hpp"
#include "pos.hpp"
#include "window.hpp"

class Hero;
class Images;

class Game
{
private:

public:
    SDL_Event event;
    bool quit = false;
    bool hourglass_pressed = false;

    Rect hero_drect = {460, 320, 40, 40};
    Rect right_panel_drect = {960, 0, 320, 680};
    Rect bottom_bar_drect = {0, 680, 1280, 40};
    Rect hourglass_drect = {1070, 540, 100, 100};
    Rect out_of_movement_points_drect;
    std::vector<Rect> destination_dot_drect;
    Rect destination_drect;
    Rect map_screen_drect = {0, 0, 960, 680};
    bool destination_present = false;
    bool hero_moving = false;

    Pos center_pos_m;
    Pos destination_pos;
    Pos destination_pos_m;
    std::vector<Pos> destination_dot_pos_m;

    std::vector<int> travel;
    std::vector<Hero*> heroes;
    Map map;
    Window* window;
    Images* images;
    GameTime game_time;

    Game();
    ~Game();

    void get_input();
    void update();
    void draw();

    void set_options();
    void end_turn();
    void find_path();
    void lay_down_path();
};

void draw_land(Game* game);

#endif

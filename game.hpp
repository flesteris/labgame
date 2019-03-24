#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include "window.hpp"
#include "images.hpp"
#include "hero.hpp"
#include "map.hpp"
#include "game_time.hpp"
#include "pos.hpp"

class Hero;
class Images;

class Game
{
private:

public:
    bool quit = false;
    SDL_Event event;

    Rect hero_drect = {Pos(460, 320), 40, 40};
    Rect right_panel_drect = {Pos(960, 0), 320, 680};
    Rect bottom_bar_drect = {Pos(0, 680), 1280, 40};
    Rect hourglass_drect = {Pos(1070, 540), 100, 100};
    Rect out_of_movement_points_drect;
    bool destination_present = false;

    std::vector<Hero*> heroes;
    Map map;
    Window* window;
    Images* images;
    GameTime game_time;

    Game();
    ~Game();

    void set_options();
    void get_input();
    void update();
    void draw();
    friend void draw_land(Game* game);
};

void draw_land(Game* game);

#endif

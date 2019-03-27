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
#include "cursor.hpp"

class Cursor;
class Hero;
class Images;

class Game
{
private:

public:
    SDL_Event event;

////Flags///////////////////////////////////////////
    bool quit = false;
    bool hourglass_pressed = false;

////Rects///////////////////////////////////////////
    Rect map_screen_drect = Rect(0, 0, 960, 680);
    Rect hero_drect = Rect(460, 320, 40, 40);
    Rect right_panel_drect = Rect(960, 0, 320, 680);
    Rect bottom_bar_drect = Rect(0, 680, 1280, 40);
    Rect hourglass_drect = Rect(1070, 540, 100, 100);
    Rect destination_drect;
    std::vector<Rect> destination_dot_drect;

////Points relevant to the window///////////////////
    Pos selected_pos;
    Pos center_pos = Pos(460, 320);
    Pos destination_pos;
    std::vector<Pos> destination_dot_pos;

////Points relevant to the map//////////////////////
    Pos selected_pos_m;
    Pos center_pos_m;
    Pos destination_pos_m;
    std::vector<Pos> destination_dot_pos_m;

    Cursor cursor;
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
    void trigger_movement();
};

void draw_land(Game* game);

#endif

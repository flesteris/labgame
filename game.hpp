#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include "game_time.hpp"
#include "hero.hpp"
#include "images.hpp"
#include "map.hpp"
#include "pos.hpp"
#include "window.hpp"
#include "cursor.hpp"

enum HeroMoveSpeed
{
    SLOW_SPEED = 6,
    NORMAL_SPEED = 3,
    FAST_SPEED = 1
};

enum Dimensions
{
    TILE_WIDTH = 40,
    TILE_HEIGHT = 40,
    WINDOW_WIDTH_TILE_FIT = 24,
    WINDOW_HEIGTH_TILE_FIT = 17
};

class Cursor;
class Hero;
class Images;

class Game
{
private:

public:
    SDL_Event event;

////Flags///////////////////////////////////////////
    bool b_quit = false;
    bool b_hourglass_pressed = false;
    bool b_map_scroll[8] = {}; // '{}' Sets all as false
    bool b_end_turn = false;
    int hero_move_speed_counter = 0;

////Rects///////////////////////////////////////////
    Rect map_screen_drect = Rect(0, 0, 960, 680);
    Rect right_panel_drect = Rect(960, 0, 320, 680);
    Rect bottom_bar_drect = Rect(0, 680, 1280, 40);
    Rect hourglass_drect = Rect(1070, 540, 100, 100);
    Rect center_drect = Rect(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y, TILE_WIDTH, TILE_HEIGHT);
    Rect map_size_drect;

////Points relevant to the window///////////////////
    Pos selected_pos;
    Pos center_pos = Pos(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y);

////Points relevant to the map//////////////////////
    Pos selected_pos_m;
    Pos center_pos_m;

////Game 'options'//////////////////////////////////
    int hero_move_speed = NORMAL_SPEED; // Same for all heroes
    //int tiles_to_scroll = 0.5;

    Cursor cursor;
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
    void update_path();
    void draw_path();
    void draw_ui();
    void focus_hero();
    void trigger_movement();
    void update_movement();
    void detect_map_scrolling();
    void update_map_scrolling();
    void update_destination_mark_position();
    void update_destination_dot_position(int i);
};

void draw_land(Game* game);

#endif

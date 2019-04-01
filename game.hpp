#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include <algorithm>

#include "cursor.hpp"
#include "game_time.hpp"
#include "hero.hpp"
#include "images.hpp"
#include "map.hpp"
#include "monster.hpp"
#include "pos.hpp"
#include "window.hpp"

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
    WINDOW_HEIGTH_TILE_FIT = 17,
    WINDOW_CENTER_TILE_X = 460,
    WINDOW_CENTER_TILE_Y = 320
};

class Cursor;
class Hero;
class Images;

class Game
{
public:
    SDL_Event event;

////Flags///////////////////////////////////////////
    bool b_quit = false;
    bool b_hourglass_pressed = false;
    bool b_map_scroll[8] = {}; // '{}' - sets all as false
    bool b_end_turn = false;
    int hero_move_speed_counter = 0;

////Rects///////////////////////////////////////////
    const Rect map_screen_drect = Rect(0, 0, 960, 680);
    const Rect right_panel_drect = Rect(960, 0, 320, 680);
    const Rect bottom_bar_drect = Rect(0, 680, 1280, 40);
    const Rect hourglass_drect = Rect(1070, 540, 100, 100);
    const Rect center_drect = Rect(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y, TILE_WIDTH, TILE_HEIGHT);
    Rect map_size_rect;

////Points relative to the window///////////////////
    Pos motion_pos;
    Pos selected_pos;
    const Pos center_pos = Pos(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y);

////Points relative to the map//////////////////////
    Pos selected_pos_m;
    Pos center_pos_m;

////Game 'options'//////////////////////////////////
    int hero_move_speed = NORMAL_SPEED; // Same for all heroes
    //int tiles_to_scroll = 0.5;

    Cursor cursor;
    std::vector<Hero*> heroes;
    std::vector<Monster*> monsters;
    Map map;
    Window* window;
    Images* images;
    GameTime game_time;

    Game();
    ~Game();

    void get_input();
    void update();
    void draw();

    void set_monsters();
    void update_monsters_position();
    void draw_monsters();
    int fight(Hero* hero, Monster* monster);

    void set_options();
    void end_turn();
    void find_path();
    void lay_down_path();
    void update_path_position();
    void draw_path();
    void draw_ui();
    void focus_hero();
    void trigger_movement();
    void update_movement();
    bool detect_map_scrolling();
    bool cursor_on_destination_mark();
    bool cursor_on_monster();
    void update_cursor();
    void update_map_scrolling();
    void update_destination_mark_position();
    void update_destination_dot_position(int i);
};

void draw_land(Game* game);

#endif

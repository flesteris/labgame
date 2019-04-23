#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>

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
    SLOW_MOVE_SPEED = 6,
    NORMAL_MOVE_SPEED = 3,
    FAST_MOVE_SPEED = 1
};

enum MapScrollSpeed
{
    SLOW_SCROLL_SPEED = 8,
    NORMAL_SCROLL_SPEED = 20,
    FAST_SCROLL_SPEED = 40
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
class Monster;

class Game
{
public:
    SDL_Event event;

////Flags///////////////////////////////////////////
    bool b_quit;
    bool b_hourglass_pressed;
    bool b_end_turn;
    int map_scroll_direction;
    int hero_move_speed_counter;
    int selected_hero;

////Rects///////////////////////////////////////////
    const Rect map_screen_drect;
    const Rect right_panel_drect;
    const Rect bottom_bar_drect;
    const Rect hourglass_drect;
    const Rect center_drect;
    Rect map_size_rect;

////Points relative to the window///////////////////
    Pos cursor_pos;
    Pos selected_pos;
    Pos center_pos;

////Points relative to the map//////////////////////
    Pos selected_pos_on_map;
    Pos center_pos_on_map;

////Game 'options'//////////////////////////////////
    int hero_move_speed; // Same for all heroes
    int scroll_speed;

    Pos camera_offset;

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
    void draw_monsters();
    void set_options();
    void end_turn();
    void find_path();
    void lay_down_path();
    void draw_land();
    void draw_path();
    void draw_ui();
    void draw_hero();
    void focus_hero();
    void trigger_movement();
    void update_movement();
    bool detect_map_scrolling();
    bool cursor_on_destination_mark();
    int cursor_on_monster();
    void update_cursor();
    void update_map_scrolling();
    void adjust_center_tile(Pos &temp_center_pos_on_map);

    Pos pos_from_map_to_window(Pos &pos_on_map) const;
    Pos pos_from_window_to_map(Pos &pos_on_window) const;
};

bool fight(Hero* hero, Monster* monster);

#endif

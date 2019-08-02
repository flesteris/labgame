#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <list>
#include <iostream>

#include "cursor.hpp"
#include "entity.hpp"
#include "game_time.hpp"
#include "hero.hpp"
#include "images.hpp"
#include "map.hpp"
#include "matrix.hpp"
#include "monster.hpp"
#include "player.hpp"
#include "pos.hpp"
#include "resource.hpp"
#include "text_image.hpp"
#include "text_images.hpp"
#include "window.hpp"
#include "window_boxes.hpp"

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
class Map;
class Player;
class Resource;
class TextFont;
class TextImages;
class WindowBoxes;

class Game
{
public:
    SDL_Event event;
////Flags//////////////////////////////////////////
    bool b_quit;
    bool b_hourglass_pressed;
    bool b_terrain_tooltip_present;
    bool b_monster_tooltip_present;
    bool b_notification_present;
    bool b_end_turn;
////Other//////////////////////////////////////////
    int map_scroll_direction;
    int hero_move_speed_counter;
    int notification_uptime_counter;
    int selected_hero;
////Rects//////////////////////////////////////////
    Rect map_size_rect;
////Points relative to the window//////////////////
    Pos cursor_pos;
    Pos selected_pos;
////Points relative to the map/////////////////////
    Pos selected_pos_on_map;
    Pos center_pos_on_map;
////Game 'options'/////////////////////////////////
    int hero_move_speed;
    int scroll_speed;
////More members///////////////////////////////////
    Pos camera_offset;
    Player* player;
    Cursor cursor;
    Map* map;
    Window* window;
    Images* images;
    //std::vector<Entity*> entities;
    std::vector<std::unique_ptr<TextFont>> font_vector;
    TextImages* text_images;
    WindowBoxes* window_boxes;
    GameTime game_time;
////C D////////////////////////////////////////////
    Game();
    ~Game();
////Main loop//////////////////////////////////////
    void get_input();
    void update();
    void draw();
////get_input() helpers////////////////////////////
    void mouse_motion();
    void key_down();
    void key_up();
    void mouse_button_down();
    void mouse_button_up();
    void mouse_left_button_down();
    void mouse_right_button_down();
    void mouse_left_button_up();
    void mouse_right_button_up();
    bool r_button_down_monster(const Pos &pos_on_map) const;
    void tooltip_monster(const Pos &pos_on_map);
    bool r_button_down_resource(const Pos &pos_on_map) const;
    void tooltip_resource(const Pos &pos_on_map);
    bool r_button_down_obstacle(const Pos &pos_on_map) const;
    void tooltip_obstacle(const Pos &pos_on_map);
    void tooltip_out_of_boundaries();
    void tooltip_grassland();
    void find_path();
    void lay_down_path();
    void notification_uptime_counter_reset();
    void trigger_movement();
    bool interrupt_movement();
    void focus_hero();
    void end_turn();
////Cursor/////////////////////////////////////////
    void update_center_tile(const Pos &temp_center_pos_on_map);
    bool detect_map_scrolling();
    bool cursor_on_destination_mark() const;
    bool cursor_on_monster() const;
    bool cursor_on_accessable_tile() const;
    void update_cursor();
////update() helpers///////////////////////////////
    void update_map_scrolling();
    void update_zone_of_control();
    void update_tile_access_map();
    void update_movement_check();
    void update_map_scrolling_check();
    void check_winning_condition();
    void check_losing_condition();
    void update_notification();
    void update_movement();
////draw() helpers/////////////////////////////////
    void draw_notification() const;
    void draw_text() const;
    void draw_tooltip() const;
    void draw_zone_of_control() const;
    void draw_entities() const;
    void draw_land() const;
    void draw_path() const;
    void draw_ui() const;
    void draw_hero_army_ui() const;
    void notify(const std::string &text);
////Fight//////////////////////////////////////////
    friend bool fight(Game* game, Hero* hero, Monster* monster);
    void hero_army_unit_dead(Hero* hero, int &index);
    bool next_hero_army_unit(Hero* hero, int &index);
    bool any_hero_army_unit_alive(Hero* hero);
    void reset_retaliations(Hero* hero, Monster* monster);
    bool first_hero_army_unit_attack(Hero* hero, Monster* monster, int &index);
    bool monster_retaliation(Hero* hero, Monster* monster, int &index);
    bool first_monster_attack(Hero* hero, Monster* monster, int &index);
    bool hero_army_unit_retaliation(Hero* hero, Monster* monster, int &index);
    bool other_hero_army_attacks(Hero* hero, Monster* monster, int &index);
////Conversions////////////////////////////////////
    Pos pos_from_map_to_window(const Pos &pos_on_map) const;
    Pos pos_from_window_to_map(const Pos &pos_on_window) const;
};

bool fight(Game* game, Hero* hero, Monster* monster);

#endif

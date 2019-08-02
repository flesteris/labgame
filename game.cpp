#include "game.hpp"

const Pos gold_amount_pos(90, 686);
const Pos mercury_crystal_amount_pos(196, 686);
const Pos sulphur_crystal_amount_pos(302, 686);
const Pos lightning_crystal_amount_pos(408, 686);
const Pos day_pos(1018, 686);
const Pos week_pos(1122, 686);
const Pos month_pos(1245, 686);
const Pos day_name_pos(968, 686);
const Pos week_name_pos(1052, 686);
const Pos month_name_pos(1160, 686);
const Pos monsters_left_text_pos(965, 10);
const Pos monsters_left_number_pos(1240, 10);
const Pos notification_pos(1120, 160);
const Pos center_tile_pos(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y);
const Pos center_pos(WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
const Pos map_screen_center_pos(WINDOW_WIDTH / 2 - 160, WINDOW_HEIGTH / 2);
const Pos hero_army_unit_number_spot_pos[] = {Pos(1060, 332),
                                              Pos(1120, 332),
                                              Pos(1180, 332),
                                              Pos(1090, 392),
                                              Pos(1150, 392)};

const Rect visible_map_screen_drect(0, 0, 960, 680);
const Rect right_panel_drect(960, 0, 320, 680);
const Rect bottom_bar_drect(0, 680, 1280, 40);
const Rect hourglass_drect(1070, 540, 100, 100);
const Rect gold_icon_drect(5, 686, 30, 30);
const Rect mercury_crystal_icon_drect(111, 686, 30, 30);
const Rect sulphur_crystal_icon_drect(217, 686, 30, 30);
const Rect lightning_crystal_icon_drect(323, 686, 30, 30);
const Rect center_drect(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y, TILE_WIDTH, TILE_HEIGHT);
const Rect hero_army_unit_spot_drect[] = {Rect(1040, 290, 40, 40),
                                          Rect(1100, 290, 40, 40),
                                          Rect(1160, 290, 40, 40),
                                          Rect(1070, 350, 40, 40),
                                          Rect(1130, 350, 40, 40)};

Game::Game() :
    b_quit(false),
    b_hourglass_pressed(false),
    b_terrain_tooltip_present(false),
    b_monster_tooltip_present(false),
    b_notification_present(false),
    b_end_turn(false),
    map_scroll_direction(NO_DIRECTION),
    hero_move_speed_counter(0),
    notification_uptime_counter(0),
    selected_hero(0),
    hero_move_speed(FAST_MOVE_SPEED),
    scroll_speed(NORMAL_SCROLL_SPEED),
    camera_offset(Pos(0, 0))
{
    window = new Window();
    map = new Map(this);
    player = new Player(this);
    try
    {
        map->load_map_data("maps//map_1_data.txt");
        for(auto hero : player->heroes)
        {
            hero->tile_access_map = new TileAccessMap(this, hero);
        }
        images = new Images(this);
        text_images = new TextImages(this);
        window_boxes = new WindowBoxes(this);
    }
    catch(...)
    {
        delete images;
        delete player;
        delete map;
        delete window;
        delete text_images;
        throw;
    }
    focus_hero();
}

Game::~Game()
{
    delete player;
    delete map;
    delete images;
    delete text_images;
    delete window;
    delete window_boxes;
    std::cout << "Memory cleared! ...";
}

void Game::get_input()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            {
                b_quit = true;
                break;
            }
        case SDL_MOUSEMOTION:
            {
                mouse_motion();
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                mouse_button_down();
                break;
            }
        case SDL_MOUSEBUTTONUP:
            {
                mouse_button_up();
                break;
            }
        case SDL_KEYDOWN:
            {
                key_down();
                break;
            }
        case SDL_KEYUP:
            {
                key_up();
                break;
            }
        }
    }
}

void Game::mouse_motion()
{
    cursor_pos = Pos(event.button.x, event.button.y);
    detect_map_scrolling();
}

void Game::key_down()
{
    if(!interrupt_movement())
    {
        auto hero = player->heroes[selected_hero];
        switch(event.key.keysym.sym)
        {
        case SDLK_q:
            {
                b_quit = true;
                break;
            }
        case SDLK_e:
            {
                b_hourglass_pressed = true;
                break;
            }
        case SDLK_KP_1:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[SOUTHWEST];
                trigger_movement();
                break;
            }
        case SDLK_KP_2:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[SOUTH];
                trigger_movement();
                break;
            }
        case SDLK_DOWN:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[SOUTH];
                trigger_movement();
                break;
            }
        case SDLK_KP_3:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[SOUTHEAST];
                trigger_movement();
                break;
            }
        case SDLK_KP_4:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[WEST];
                trigger_movement();
                break;
            }
        case SDLK_LEFT:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[WEST];
                trigger_movement();
                break;
            }
        case SDLK_KP_6:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[EAST];
                trigger_movement();
                break;
            }
        case SDLK_RIGHT:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[EAST];
                trigger_movement();
                break;
            }
        case SDLK_KP_7:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[NORTHWEST];
                trigger_movement();
                break;
            }
        case SDLK_KP_8:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[NORTH];
                trigger_movement();
                break;
            }
        case SDLK_UP:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[NORTH];
                trigger_movement();
                break;
            }
        case SDLK_KP_9:
            {
                selected_pos_on_map = hero->pos_on_map + DIRECTIONS[NORTHEAST];
                trigger_movement();
                break;
            }
        case SDLK_SPACE:
            {
                focus_hero();
                break;
            }
        case SDLK_m:
            {
                if(hero->b_destination_present)
                {
                    trigger_movement();
                }
                break;
            }
        /*case SDLK_1:
            {
                if(player->heroes.size() >= 1)
                {
                    selected_hero = 0;
                    focus_hero();
                }
                break;
            }
        case SDLK_2:
            {
                if(player->heroes.size() >= 2)
                {
                    selected_hero = 1;
                    focus_hero();
                }
                break;
            }*/
        default:
            {
                break;
            }
        }
    }
}

void Game::key_up()
{
    if(event.key.keysym.sym == SDLK_e)
    {
        b_hourglass_pressed = false;
        end_turn();
    }
}

void Game::mouse_button_down()
{
    if(!interrupt_movement())
    {
        if(SDL_BUTTON_LEFT == event.button.button)
        {
            mouse_left_button_down();
        }
        else if(SDL_BUTTON_RIGHT == event.button.button)
        {
            mouse_right_button_down();
        }
    }
}

void Game::mouse_button_up()
{
    if(SDL_BUTTON_LEFT == event.button.button)
    {
        mouse_left_button_up();
    }
    else if(SDL_BUTTON_RIGHT == event.button.button)
    {
        mouse_right_button_up();
    }
}

void Game::mouse_left_button_down()
{
    selected_pos = Pos(event.button.x, event.button.y);
    if(selected_pos.is_in_rect(visible_map_screen_drect))
    {
        selected_pos_on_map = pos_from_window_to_map(selected_pos); // Which map tile was clicked
        trigger_movement();
    }
    else if(selected_pos.is_in_rect(hourglass_drect))
    {
        b_hourglass_pressed = true;
    }
}

void Game::mouse_right_button_down()
{
    if(cursor_pos.is_in_rect(visible_map_screen_drect))
    {
        Pos pos = pos_from_window_to_map(cursor_pos);
        if(!pos.is_in_rect(map_size_rect))
        {
            tooltip_out_of_boundaries();
        }
        else if(r_button_down_monster(pos))
        {
            tooltip_monster(pos);
        }
        else if(r_button_down_resource(pos))
        {
            tooltip_resource(pos);
        }
        else if(r_button_down_obstacle(pos))
        {
            tooltip_obstacle(pos);
        }
        else
        {
            tooltip_grassland();
        }
    }
}

void Game::mouse_left_button_up()
{
    Pos pos(event.button.x, event.button.y);
    if(b_hourglass_pressed)
    {
        if(pos.is_in_rect(hourglass_drect))
        {
            end_turn();
        }
        b_hourglass_pressed = false;
    }
}

void Game::mouse_right_button_up()
{
    if(b_terrain_tooltip_present)
    {
        b_terrain_tooltip_present = false;
    }
    else if(b_monster_tooltip_present)
    {
        b_monster_tooltip_present = false;
    }
}

bool Game::r_button_down_monster(const Pos &pos_on_map) const
{
    Entity* entity = map->entities[pos_on_map];
    Monster* monster = dynamic_cast<Monster*> (entity);
    if(monster)
    {
        return true;
    }
    return false;
}

void Game::tooltip_monster(const Pos &pos_on_map)
{
    Entity* entity = map->entities[pos_on_map];
    Monster* monster = dynamic_cast<Monster*> (entity);
    std::stringstream ss;
    ss << monster->get_count() << " " << monster->name();
    window_boxes->monster_tooltip->load_text(ss.str());
    b_monster_tooltip_present = true;
}

bool Game::r_button_down_resource(const Pos &pos_on_map) const
{
    Entity* entity = map->entities[pos_on_map];
    Resource* resource = dynamic_cast<Resource*> (entity);
    if(resource)
    {
        return true;
    }
    return false;
}

void Game::tooltip_resource(const Pos &pos_on_map)
{
    Entity* entity = map->entities[pos_on_map];
    Resource* resource = dynamic_cast<Resource*> (entity);
    Gold* gold = dynamic_cast<Gold*> (resource);
    MercuryCrystal* mercury_crystal = dynamic_cast<MercuryCrystal*> (resource);
    SulphurCrystal* sulphur_crystal = dynamic_cast<SulphurCrystal*> (resource);
    if(gold)
    {
        window_boxes->terrain_tooltip->load_text("Gold");
        b_terrain_tooltip_present = true;
    }
    else if(mercury_crystal)
    {
        window_boxes->terrain_tooltip->load_text("Mercury crystals");
        b_terrain_tooltip_present = true;
    }
    else if(sulphur_crystal)
    {
        window_boxes->terrain_tooltip->load_text("Sulphur crystals");
        b_terrain_tooltip_present = true;
    }
    else
    {
        window_boxes->terrain_tooltip->load_text("Lightning crystals");
        b_terrain_tooltip_present = true;
    }
}

bool Game::r_button_down_obstacle(const Pos &pos_on_map) const
{
    Entity* entity = map->entities[pos_on_map];
    Obstacle* obstacle = dynamic_cast<Obstacle*> (entity);
    Obstacle* obstacle_2 = nullptr;
    Pos temp_pos = pos_on_map + DIRECTIONS[WEST];
    if(temp_pos.is_in_rect(map_size_rect))
    {
        Entity* entity_2 = map->entities[temp_pos];
        obstacle_2 = dynamic_cast<Forest1*> (entity_2);
    }
    if(obstacle || obstacle_2)
    {
        return true;
    }
    return false;
}

void Game::tooltip_obstacle(const Pos &pos_on_map)
{
    Entity* entity = map->entities[pos_on_map];
    Forest1* forest1 = dynamic_cast<Forest1*> (entity);
    Forest1* forest1_2 = nullptr;
    Pos temp_pos = pos_on_map + DIRECTIONS[WEST];
    if(temp_pos.is_in_rect(map_size_rect))
    {
        Entity* entity_2 = map->entities[temp_pos];
        forest1_2 = dynamic_cast<Forest1*> (entity_2);
    }
    if(forest1 || forest1_2)
    {
        window_boxes->terrain_tooltip->load_text("Forest");
        b_terrain_tooltip_present = true;
    }
    else
    {
        window_boxes->terrain_tooltip->load_text("Hills");
        b_terrain_tooltip_present = true;
    }
}

void Game::tooltip_grassland()
{
    window_boxes->terrain_tooltip->load_text("Grassland");
    b_terrain_tooltip_present = true;
}

void Game::tooltip_out_of_boundaries()
{
    window_boxes->terrain_tooltip->load_text("Indispersible fog");
    b_terrain_tooltip_present = true;
}

void Game::notification_uptime_counter_reset()
{
    notification_uptime_counter = 90;
}

void Game::end_turn()
{
    game_time.next_day();
    for(auto hero : player->heroes)
    {
        hero->reset_movement_points();
    }
    focus_hero();
    notify("A new day!");
}

void Game::find_path()
{
    auto hero = player->heroes[selected_hero];
    auto t_a_map = hero->tile_access_map;
    hero->current_travel_path.clear();
    Pos selected_pos = selected_pos_on_map;
    if(selected_pos.is_in_rect(map_size_rect))
    {
        if(t_a_map->access_map[selected_pos] >= 0)
        {
            hero->destination_mark_pos_on_map = selected_pos;
            hero->b_destination_present = true;
            int vektor = t_a_map->vector_map[selected_pos];
            while(vektor != NO_DIRECTION)
            {
                hero->current_travel_path.push_back(vektor);
                selected_pos -= DIRECTIONS[vektor];
                vektor = t_a_map->vector_map[selected_pos];
            }
        }
    }
}

void Game::lay_down_path()
{
    auto hero = player->heroes[selected_hero];
    hero->destination_dot_pos_on_map.clear();
    if(hero->current_travel_path.size() > 1)
    {
        int direction = hero->current_travel_path[0];
        Pos pos(hero->destination_mark_pos_on_map - DIRECTIONS[direction]);
        hero->destination_dot_pos_on_map.push_back(pos);
        for(size_t i = 1; i < hero->current_travel_path.size() - 1; ++i)
        {
            direction = hero->current_travel_path[i];
            pos = hero->destination_dot_pos_on_map[i-1] - DIRECTIONS[direction];
            hero->destination_dot_pos_on_map.push_back(pos);
        }
    }
}

void Game::trigger_movement()
{
    auto hero = player->heroes[selected_hero];
    if(hero->b_destination_present)
    {
        if(hero->destination_mark_pos_on_map == selected_pos_on_map)
        {
            hero->b_hero_moving = true;
            return;
        }
    }
    if(selected_pos_on_map.is_in_rect(map_size_rect))
    {
        if(selected_pos_on_map != hero->pos_on_map)
        {
            if(hero->tile_access_map->price_map[selected_pos_on_map] != NOT_SET)
            {
                find_path();
                lay_down_path();
                return;
            }
        }
    }
    hero->b_destination_present = false;
}

bool Game::interrupt_movement()
{
    if(player->heroes[selected_hero]->b_hero_moving)
    {
        player->heroes[selected_hero]->stop();
        return true;
    }
    return false;
}

bool Game::detect_map_scrolling()
{
    if(cursor_pos == Pos(0, 0))
    {
        map_scroll_direction = NORTHWEST;
    }
    else if(cursor_pos == Pos(0, WINDOW_HEIGTH - 1))
    {
        map_scroll_direction = SOUTHWEST;
    }
    else if(cursor_pos == Pos(WINDOW_WIDTH - 1, WINDOW_HEIGTH - 1))
    {
        map_scroll_direction = SOUTHEAST;
    }
    else if(cursor_pos == Pos(WINDOW_WIDTH - 1, 0))
    {
        map_scroll_direction = NORTHEAST;
    }
    else if(cursor_pos.x == 0)
    {
        map_scroll_direction = WEST;
    }
    else if(cursor_pos.x == WINDOW_WIDTH - 1)
    {
        map_scroll_direction = EAST;
    }
    else if(cursor_pos.y == 0)
    {
        map_scroll_direction = NORTH;
    }
    else if(cursor_pos.y == WINDOW_HEIGTH - 1)
    {
        map_scroll_direction = SOUTH;
    }
    else
    {
        map_scroll_direction = NO_DIRECTION;
        return 0;
    }
    return 1;
}

void Game::focus_hero()
{
    center_pos_on_map = player->heroes[selected_hero]->pos_on_map;
    camera_offset = Pos(0, 0);
}

void Game::update_center_tile(const Pos &temp_center_pos_on_map)
{
    if(camera_offset.x > TILE_WIDTH/2)
    {
        camera_offset.x -= TILE_WIDTH;
        center_pos_on_map.x = temp_center_pos_on_map.x;
    }
    else if(camera_offset.x < -TILE_WIDTH/2)
    {
        camera_offset.x += TILE_WIDTH;
        center_pos_on_map.x = temp_center_pos_on_map.x;
    }
    if(camera_offset.y > TILE_HEIGHT/2)
    {
        camera_offset.y -= TILE_HEIGHT;
        center_pos_on_map.y = temp_center_pos_on_map.y;
    }
    else if(camera_offset.y < -TILE_HEIGHT/2)
    {
        camera_offset.y += TILE_HEIGHT;
        center_pos_on_map.y = temp_center_pos_on_map.y;
    }
}

bool Game::cursor_on_destination_mark() const
{
    auto hero = player->heroes[selected_hero];
    if(!(hero->b_destination_present))
    {
        return false;
    }
    Pos pos = pos_from_window_to_map(cursor_pos);
    if(hero->destination_mark_pos_on_map == pos)
    {
        return true;
    }
    return false;
}

bool Game::cursor_on_monster() const
{
    auto hero = player->heroes[selected_hero];
    Pos pos = pos_from_window_to_map(cursor_pos);
    if(pos.is_in_rect(map_size_rect))
    {
        int access = hero->tile_access_map->access_map[pos];
        if(access == MONSTER || access == MONSTER_NEARBY)
        {
            return true;
        }
    }
    return false;
}

bool Game::cursor_on_accessable_tile() const
{
    auto hero = player->heroes[selected_hero];
    Pos pos = pos_from_window_to_map(cursor_pos);
    if(pos.is_in_rect(map_size_rect))
    {
        int access = hero->tile_access_map->access_map[pos];
        if(access == FREE || access == RESOURCE)
        {
            return true;
        }
    }
    return false;
}

void Game::update()
{
    update_notification();
    text_images->load_inconstant_text_images();
    update_zone_of_control();
    update_cursor();
    update_tile_access_map();
    update_movement_check();
    update_map_scrolling_check();
    check_winning_condition();
    check_losing_condition();
}

void Game::update_movement()
{
    focus_hero();
    auto hero = player->heroes[selected_hero];
    if(!hero->current_travel_path.empty())
    {
        hero->set_direction(hero->current_travel_path.back());
        if(hero->move())
        {
            if(hero->current_travel_path.size() > 1)
            {
                hero->destination_dot_pos_on_map.pop_back();
            }
            hero->current_travel_path.pop_back();
        }
        else
        {
            hero->stop();
        }
    }
    if(hero->current_travel_path.empty())
    {
        hero->b_destination_present = false;
        hero->stop();
    }
}

void Game::update_cursor()
{
    if(map_scroll_direction != NO_DIRECTION)
    {
        cursor.set_cursor(map_scroll_direction);
    }
    else if(cursor_pos.is_in_rect(visible_map_screen_drect))
    {
        if(cursor_on_destination_mark())
        {
            cursor.set_cursor(GO_TO_DESTINATION);
        }
        else if(cursor_on_monster())
        {
            cursor.set_cursor(COMBAT_CURSOR);
        }
        else if(cursor_on_accessable_tile())
        {
            cursor.set_cursor(ACCESSIBLE_CURSOR);
        }
        else
        {
            cursor.set_cursor(NORMAL_CURSOR);
        }
    }
    else
    {
        cursor.set_cursor(NORMAL_CURSOR);
    }
}

void Game::update_map_scrolling()
{
    if(map_scroll_direction != NO_DIRECTION)
    {
        Pos temp_center_pos_on_map = center_pos_on_map + DIRECTIONS[map_scroll_direction];
        if(temp_center_pos_on_map.is_in_rect(map_size_rect))
        {
            camera_offset += DIRECTIONS[map_scroll_direction] * scroll_speed;
            update_center_tile(temp_center_pos_on_map);
        }
        else // How to scroll while near a border
        {
            Pos temp_camera_offset = camera_offset;
            Pos direction = DIRECTIONS[map_scroll_direction];
            temp_center_pos_on_map.fit_in_rect(map_size_rect);
            if(center_pos_on_map != temp_center_pos_on_map)
            {
                direction = temp_center_pos_on_map - center_pos_on_map;
                if(camera_offset.x != 0)
                {
                    direction.x = DIRECTIONS[map_scroll_direction].x;
                }
                if(camera_offset.y != 0)
                {
                    direction.y = DIRECTIONS[map_scroll_direction].y;
                }
            }
            else
            {
                if(camera_offset.x == 0)
                {
                    direction.x = 0;
                }
                if(camera_offset.y == 0)
                {
                    direction.y = 0;
                }
            }
            camera_offset += direction * scroll_speed;
            if(temp_camera_offset != camera_offset)
            {
                update_center_tile(temp_center_pos_on_map);
            }
        }
    }
}

void Game::update_notification()
{
    if(b_notification_present)
    {
        --notification_uptime_counter;
        if(!notification_uptime_counter)
        {
            b_notification_present = false;
        }
    }
}

void Game::update_zone_of_control()
{
    if(!map->b_zone_of_control_updated)
    {
        map->update_zone_of_control();
    }
}

void Game::check_winning_condition()
{
    if(Monster::get_object_count() == 0)
    {
        b_quit = true;
    }
}

void Game::update_tile_access_map()
{
    auto hero = player->heroes[selected_hero];
    if(!hero->tile_access_map->b_updated)
    {
        hero->tile_access_map->update_maps();
    }
}

void Game::update_movement_check()
{
    auto hero = player->heroes[selected_hero];
    if(hero->b_hero_moving)
    {
        if(hero_move_speed_counter == hero_move_speed)
        {
            hero_move_speed_counter = 0;
            update_movement();
            if(b_quit)
            {
                return;
            }
        }
        else
        {
            ++hero_move_speed_counter;
        }
    }
}

void Game::update_map_scrolling_check()
{
    auto hero = player->heroes[selected_hero];
    if(!hero->b_hero_moving)
    {
        update_map_scrolling();
    }
}

void Game::check_losing_condition()
{
    if(!player->heroes[selected_hero]->b_alive)
    {
        if(!notification_uptime_counter)
        {
            delete player->heroes[selected_hero];
            player->heroes.erase(player->heroes.begin() + selected_hero);
            b_quit = true;
        }
    }
}

void Game::draw()
{
    SDL_RenderClear(window->ren);
    draw_land();
    draw_entities();
    draw_zone_of_control();
    draw_path();
    draw_ui();
    draw_tooltip();
    draw_notification();
    SDL_RenderPresent(window->ren);
}

void Game::notify(const std::string &text)
{
    window_boxes->notification->load_text(text);
    notification_uptime_counter_reset();
    b_notification_present = true;
}

void Game::draw_notification() const
{
    if(b_notification_present)
    {
        window_boxes->notification->draw_window_box_centered(notification_pos);
    }
}

void Game::draw_tooltip() const
{
    if(b_terrain_tooltip_present)
    {
        window_boxes->terrain_tooltip->draw_window_box_centered(map_screen_center_pos);
    }
    else if(b_monster_tooltip_present)
    {
        window_boxes->monster_tooltip->draw_window_box_low_centered(map_screen_center_pos);
    }
}

void Game::draw_text() const
{
    text_images->resources[GOLD_TEXT]->draw_right_aligned(gold_amount_pos);
    text_images->resources[MERCURY_CRYSTAL_TEXT]->draw_right_aligned(mercury_crystal_amount_pos);
    text_images->resources[SULPHUR_CRYSTAL_TEXT]->draw_right_aligned(sulphur_crystal_amount_pos);
    text_images->resources[LIGHTNING_CRYSTAL_TEXT]->draw_right_aligned(lightning_crystal_amount_pos);
    text_images->time_names[DAY_TEXT]->draw(day_name_pos);
    text_images->time_names[WEEK_TEXT]->draw(week_name_pos);
    text_images->time_names[MONTH_TEXT]->draw(month_name_pos);
    text_images->date[DAY_TEXT]->draw(day_pos);
    text_images->date[WEEK_TEXT]->draw(week_pos);
    text_images->date[MONTH_TEXT]->draw(month_pos);
    text_images->monsters_left_text->draw(monsters_left_text_pos);
    text_images->monsters_left_number->draw(monsters_left_number_pos);
}

void Game::draw_zone_of_control() const
{
    for(int i = 0; i < map->h; ++i)
    {
        for(int j = 0; j < map->w; ++j)
        {
            Pos pos(j, i);
            Pos pos_2 = pos_from_map_to_window(pos);
            Rect drect = visible_map_screen_drect;
            if(pos_2.is_in_rect(drect.expand(TILE_WIDTH, TILE_HEIGHT)))
            {
                if(map->zone_of_control[pos])
                {
                    drect = Rect(pos_2, TILE_WIDTH, TILE_HEIGHT);
                    images->transparent_tile->draw(Rect(), drect);
                }
            }
        }
    }
}

void Game::draw_entities() const
{
    for(size_t i = 0; i < map->entities.size(); ++i)
    {
        if(map->entities[i])
        {
            Pos pos = pos_from_map_to_window(map->entities[i]->pos_on_map);
            Rect drect = visible_map_screen_drect;
            if(pos.is_in_rect(drect.expand(TILE_WIDTH, TILE_HEIGHT)))
            {
                drect = Rect(pos, TILE_WIDTH, TILE_HEIGHT);
                map->entities[i]->draw_entity(drect);
            }
        }
    }
}

void Game::draw_land() const
{
    int i_from = center_pos_on_map.x - WINDOW_WIDTH_TILE_FIT/2 - 1;
    int j_from = center_pos_on_map.y - WINDOW_HEIGTH_TILE_FIT/2 - 1;
    int i_until = center_pos_on_map.x + WINDOW_WIDTH_TILE_FIT/2 + 2;
    int j_until = center_pos_on_map.y + WINDOW_HEIGTH_TILE_FIT/2 + 2;

    for(int i = i_from, k = -2; i < i_until; ++i, ++k)
    {
        if(i < 0 || map->h - 1 < i)
        {
            for(int j = j_from, l = -1; j < j_until; ++j, ++l)
            {
                Pos pos(Pos(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT) - camera_offset);
                Rect tile_drect(pos, TILE_WIDTH, TILE_HEIGHT);
                images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = j_from, l = -1; j < j_until; ++j, ++l)
            {
                Pos pos(Pos(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT) - camera_offset);
                Rect tile_drect(pos, TILE_WIDTH, TILE_HEIGHT);
                if(j < 0 || map->w - 1 < j)
                {
                    images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
                }
                else
                {
                    Pos tile_index(i, j);
                    int image_id = map->tiles[tile_index];
                    images->tiles[image_id]->draw(Rect(), tile_drect);
                }
            }
        }
    }
}

void Game::draw_path() const
{
    auto hero = player->heroes[selected_hero];
    if(hero->b_destination_present)
    {
        if(!hero->get_current_movement_points())
        {
            hero->b_out_of_movement_points = true;
        }
        int i = hero->destination_dot_pos_on_map.size() - 1;
        int j = hero->get_current_movement_points();
        for(; i > -1; --i, --j)
        {
            Pos pos = pos_from_map_to_window(hero->destination_dot_pos_on_map[i]);
            if(pos.is_in_rect(visible_map_screen_drect))
            {
                Rect drect(pos, TILE_WIDTH, TILE_HEIGHT);
                int image_id = DESTINATION_DOT + hero->b_out_of_movement_points;
                images->ui[image_id]->draw(Rect(), drect);
            }
            if(!(j-1))
            {
                hero->b_out_of_movement_points = true;
            }
        }
        Pos pos = pos_from_map_to_window(hero->destination_mark_pos_on_map);
        if(pos.is_in_rect(visible_map_screen_drect))
        {
            Rect drect(pos, TILE_WIDTH, TILE_HEIGHT);
            int image_id = DESTINATION_MARK + hero->b_out_of_movement_points;
            images->ui[image_id]->draw(Rect(), drect);
        }
        hero->b_out_of_movement_points = false;
    }
}

void Game::draw_ui() const
{
    images->ui[RIGHT_PANEL]->draw(Rect(), right_panel_drect);
    images->ui[HOURGLASS + b_hourglass_pressed]->draw(Rect(), hourglass_drect);
    images->ui[BOTTOM_BAR]->draw(Rect(), bottom_bar_drect);
    images->resource_images[GOLD]->draw(Rect(), gold_icon_drect);
    images->resource_images[MERCURY_CRYSTAL]->draw(Rect(), mercury_crystal_icon_drect);
    images->resource_images[SULPHUR_CRYSTAL]->draw(Rect(), sulphur_crystal_icon_drect);
    images->resource_images[LIGHTNING_CRYSTAL]->draw(Rect(), lightning_crystal_icon_drect);
    draw_text();
    draw_hero_army_ui();
}

void Game::draw_hero_army_ui() const
{
    auto hero = player->heroes[selected_hero];
    for(int i = 0; i < HERO_ARMY_SLOT_COUNT; ++i)
    {
        if(hero->hero_army[i])
        {
            hero->hero_army[i]->draw_entity(hero_army_unit_spot_drect[i]);
            text_images->hero_army_numbers[i]->draw_centered(hero_army_unit_number_spot_pos[i]);
        }
    }
}

bool fight(Game* game, Hero* hero, Monster* monster)
{
    while(true)
    {
        int index;
        for(size_t i = 0; i < HERO_ARMY_SLOT_COUNT; ++i)
        {
            if(hero->hero_army[i])
            {
                index = i;
                break;
            }
        }

        if(game->first_hero_army_unit_attack(hero, monster, index))
        {
            return true;
        }
        else if(game->monster_retaliation(hero, monster, index))
        {
            if(!game->next_hero_army_unit(hero, index))
            {
                return false;
            }
        }

        if(game->first_monster_attack(hero, monster, index))
        {
            if(!game->next_hero_army_unit(hero, index))
            {
                return false;
            }
        }
        else if(game->hero_army_unit_retaliation(hero, monster, index))
        {
            return true;
        }

        for(size_t i = index; i < HERO_ARMY_SLOT_COUNT; ++i)
        {
            if(game->other_hero_army_attacks(hero, monster, index))
            {
                return true;
            }
        }
        game->reset_retaliations(hero, monster);
    }
}

bool Game::first_hero_army_unit_attack(Hero* hero, Monster* monster, int &index)
{
    if(!(monster->defend(hero->hero_army[index]->attack())))
    {
        return true;
    }
    return false;
}

bool Game::monster_retaliation(Hero* hero, Monster* monster, int &index)
{
    if(!(hero->hero_army[index]->defend(monster->retaliate())))
    {
        hero_army_unit_dead(hero, index);
        return true;
    }
    return false;
}

bool Game::first_monster_attack(Hero* hero, Monster* monster, int &index)
{
    if(!(hero->hero_army[index]->defend(monster->attack())))
    {
        hero_army_unit_dead(hero, index);
        return true;
    }
    return false;
}

bool Game::hero_army_unit_retaliation(Hero* hero, Monster* monster, int &index)
{
    if(!(monster->defend(hero->hero_army[index]->retaliate())))
    {
        return true;
    }
    return false;
}

bool Game::other_hero_army_attacks(Hero* hero, Monster* monster, int &index)
{
    if(next_hero_army_unit(hero, index))
    {
        if(!(monster->defend(hero->hero_army[index]->attack())))
        {
            return true;
        }
    }
    return false;
}

void Game::reset_retaliations(Hero* hero, Monster* monster)
{
    for(auto hero_army_unit : hero->hero_army)
    {
        if(hero_army_unit)
        {
            hero_army_unit->b_retaliated = false;
        }
    }
    monster->b_retaliated = false;
}

void Game::hero_army_unit_dead(Hero* hero, int &index)
{
    delete hero->hero_army[index];
    ++Monster::object_count;
    hero->hero_army[index] = nullptr;
}

bool Game::next_hero_army_unit(Hero* hero, int &index)
{
    for(int i = index + 1; i < HERO_ARMY_SLOT_COUNT; ++i)
    {
        if(hero->hero_army[i])
        {
            index = i;
            return true;
        }
    }
    return false;
}

bool Game::any_hero_army_unit_alive(Hero* hero)
{
    for(size_t i = 0; i < HERO_ARMY_SLOT_COUNT; ++i)
    {
        if(hero->hero_army[i])
        {
            return true;
        }
    }
    return false;
}

Pos Game::pos_from_map_to_window(const Pos &pos_on_map) const
{
    Pos pos = pos_on_map - center_pos_on_map;
    pos.x = (pos.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH - TILE_WIDTH/2;
    pos.y = (pos.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT;
    pos -= camera_offset;
    return pos;
}

Pos Game::pos_from_window_to_map(const Pos &pos_on_window) const
{
    Pos pos = center_pos_on_map;
    Pos pos_2 = pos_on_window + camera_offset;
    pos.x = pos.x - WINDOW_WIDTH_TILE_FIT/2 + (pos_2.x + TILE_WIDTH/2) / TILE_WIDTH;
    pos.y = pos.y - WINDOW_HEIGTH_TILE_FIT/2 + pos_2.y / TILE_HEIGHT;
    return pos;
}

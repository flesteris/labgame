#include "game.hpp"

Game::Game() :
    b_quit(false),
    b_hourglass_pressed(false),
    b_end_turn(false),
    map_scroll_direction(8),
    hero_move_speed_counter(0),
    map_screen_drect(Rect(0, 0, 960, 680)),
    right_panel_drect(Rect(960, 0, 320, 680)),
    bottom_bar_drect(Rect(0, 680, 1280, 40)),
    hourglass_drect(Rect(1070, 540, 100, 100)),
    center_drect(Rect(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y, TILE_WIDTH, TILE_HEIGHT)),
    center_pos(Pos(WINDOW_CENTER_TILE_X, WINDOW_CENTER_TILE_Y)),
    hero_move_speed(NORMAL_MOVE_SPEED),
    scroll_speed(NORMAL_SCROLL_SPEED),
    camera_offset(Pos())
{
    map.load_map_data("maps//map_1_data.txt");
    map_size_rect = Rect(0, 0, map.w - 1, map.h - 1);
    set_options();
    window = new Window();
    images = new Images(this);
    set_monsters();
    end_turn();
    heroes[0]->tile_access_map->update_accessible_tile_map();
}

Game::~Game()
{
    delete images;
    delete window;
    std::cout << "Memory cleared! ...";
}

void Game::set_options()
{
    for(int i = 0; i < map.heroes_count; ++i)
    {
        Pos pos = *map.heroes_pos_on_map[i];
        int movement_points = map.heroes_movement_points[i];
        heroes.push_back(new Hero(this, pos, movement_points));
    }
    if(map.heroes_count)
    {
        center_pos_on_map = *map.heroes_pos_on_map[0];
    }
    else
    {
        center_pos_on_map = Pos(0, 0);
    }
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
                cursor_pos = Pos(event.button.x, event.button.y);
                detect_map_scrolling();
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                if(SDL_BUTTON_LEFT == event.button.button && event.button.clicks)
                {
                    heroes[0]->b_hero_moving = false;
                    selected_pos = Pos(event.button.x, event.button.y) + camera_offset;
                    if(selected_pos.is_in_rect(map_screen_drect))
                    {
                        selected_pos_on_map = pos_from_window_to_map(selected_pos); // Which map tile was clicked
                        trigger_movement();
                    }
                    else if(selected_pos.is_in_rect(hourglass_drect))
                    {
                        b_hourglass_pressed = true;
                    }
                }
                if(SDL_BUTTON_RIGHT == event.button.button)
                {
                    int i = cursor_on_monster();
                    if(i >= 0)
                    {
                        std::cout << monsters[i]->get_count() << " " << monsters[i]->name() << "(s)" << std::endl;
                    }
                }
                break;
            }
        case SDL_MOUSEBUTTONUP:
            {
                if(event.button.button == SDL_BUTTON_LEFT)
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
                break;
            }
        case SDL_KEYDOWN:
            {
                heroes[0]->b_hero_moving = false;
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
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[SOUTHWEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_2:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[SOUTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_DOWN:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[SOUTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_3:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[SOUTHEAST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_4:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[WEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_LEFT:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[WEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_6:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[EAST];
                        trigger_movement();
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[EAST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_7:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[NORTHWEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_8:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[NORTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_UP:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[NORTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_9:
                    {
                        selected_pos_on_map = heroes[0]->pos_on_map + DIRECTIONS[NORTHEAST];
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
                        if(heroes[0]->b_destination_present)
                        {
                            trigger_movement();
                        }
                        break;
                    }
                default:
                    {
                        break;
                    }
                }
                break;
            }
        case SDL_KEYUP:
            {
                if(event.key.keysym.sym == SDLK_e)
                {
                    b_hourglass_pressed = false;
                    end_turn();
                }
                break;
            }
        }
    }
}

void Game::update()
{
    update_cursor();
    if(heroes[0]->b_hero_moving)
    {
        if(hero_move_speed_counter == hero_move_speed)
        {
            hero_move_speed_counter = 0;
            update_movement();
        }
        else
        {
            ++hero_move_speed_counter;
        }
    }
    else // So that you couldn't scroll while moving
    {
        update_map_scrolling();
    }
}

void Game::draw()
{
    //SDL_RenderClear(window->ren);
    draw_land();
    draw_monsters();
    draw_hero();
    draw_path();
    draw_ui();
    SDL_RenderPresent(window->ren);
}

void Game::draw_hero()
{
    Pos pos = pos_from_map_to_window(heroes[0]->pos_on_map);
    Rect drect = map_screen_drect;
    if(pos.is_in_rect(drect.expand(TILE_WIDTH, TILE_HEIGHT)))
    {
        pos.x -= TILE_WIDTH/2;
        drect = Rect(pos - camera_offset, TILE_WIDTH, TILE_HEIGHT);
        int image_id = heroes[0]->get_direction();
        images->hero_images[image_id]->draw(Rect(), drect);
    }
}

void Game::draw_land()
{
    int i_from = center_pos_on_map.x - WINDOW_WIDTH_TILE_FIT/2 - 1;
    int j_from = center_pos_on_map.y - WINDOW_HEIGTH_TILE_FIT/2 - 1;
    int i_until = center_pos_on_map.x + WINDOW_WIDTH_TILE_FIT/2 + 2;
    int j_until = center_pos_on_map.y + WINDOW_HEIGTH_TILE_FIT/2 + 2;

    for(int i = i_from, k = -2; i < i_until; ++i, ++k)
    {
        if(i < 0 || i > map.h - 1)
        {
            for(int j = j_from, l = -1; j < j_until; ++j, ++l)
            {
                Rect tile_drect(Pos(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT) - camera_offset, TILE_WIDTH, TILE_HEIGHT);
                images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = j_from, l = -1; j < j_until; ++j, ++l)
            {
                Rect tile_drect(Pos(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT) - camera_offset, TILE_WIDTH, TILE_HEIGHT);
                if(j < 0 || j > map.w - 1)
                {
                    images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
                }
                else
                {
                    int tile_id = i + j * map.w;
                    int image_id = map.tiles[tile_id] - 1;
                    images->tiles[image_id]->draw(Rect(), tile_drect);
                }
            }
        }
    }
}

void Game::end_turn()
{
    heroes[0]->set_current_movement_points(heroes[0]->get_max_movement_points());
    focus_hero();
    std::cout << std::endl << "**********************************************" << std::endl;
    game_time.next_day();
    std::cout << "Your current army:" << std::endl;
    for(auto hero_army_unit : heroes[0]->hero_army)
    {
        std::cout << hero_army_unit->get_count() << " " << hero_army_unit->name() << "(s)" << std::endl;
    }
    /*for(int i = 0; i < (int)heroes[0]->hero_army.size(); ++i)
    {
        std::cout << heroes[0]->hero_army[i]->get_count() << " " << heroes[0]->hero_army[i]->name() << "(s)" << std::endl;
    }*/
    std::cout << "**********************************************" << std::endl << std::endl;

}

void Game::find_path()
{
    heroes[0]->current_travel_path.clear();
    Pos pos_on_map = heroes[0]->destination_mark_pos_on_map;
    bool west_f = false, east_f = false;

    while(heroes[0]->pos_on_map != pos_on_map)
    {
        if(heroes[0]->pos_on_map.x < pos_on_map.x)
        {
            heroes[0]->current_travel_path.push_back(EAST);
            --pos_on_map.x;
            east_f = true;
        }
        else if(heroes[0]->pos_on_map.x > pos_on_map.x)
        {
            heroes[0]->current_travel_path.push_back(WEST);
            ++pos_on_map.x;
            west_f = true;
        }
        if(heroes[0]->pos_on_map.y < pos_on_map.y)
        {
            int size = heroes[0]->current_travel_path.size() - 1;
            if(east_f)
            {
                heroes[0]->current_travel_path[size] = SOUTHEAST;
                --pos_on_map.y;
                east_f = false;
            }
            else if(west_f)
            {
                heroes[0]->current_travel_path[size] = SOUTHWEST;
                --pos_on_map.y;
                west_f = false;
            }
            else
            {
                heroes[0]->current_travel_path.push_back(SOUTH);
                --pos_on_map.y;
            }
        }
        else if(heroes[0]->pos_on_map.y > pos_on_map.y)
        {
            int size = heroes[0]->current_travel_path.size() - 1;
            if(east_f)
            {
                heroes[0]->current_travel_path[size] = NORTHEAST;
                ++pos_on_map.y;
                east_f = false;
            }
            else if(west_f)
            {
                heroes[0]->current_travel_path[size] = NORTHWEST;
                ++pos_on_map.y;
                west_f = false;
            }
            else
            {
                heroes[0]->current_travel_path.push_back(NORTH);
                ++pos_on_map.y;
            }
        }
    }
}

void Game::lay_down_path()
{
    heroes[0]->destination_dot_pos_on_map.clear();
    if(heroes[0]->current_travel_path.size() > 1)
    {
        Pos pos(heroes[0]->destination_mark_pos_on_map - DIRECTIONS[heroes[0]->current_travel_path[0]]);
        heroes[0]->destination_dot_pos_on_map.push_back(pos);
        for(int i = 1; i < (int)heroes[0]->current_travel_path.size() - 1; ++i)
        {
            pos = heroes[0]->destination_dot_pos_on_map[i-1] - DIRECTIONS[heroes[0]->current_travel_path[i]];
            heroes[0]->destination_dot_pos_on_map.push_back(pos);
        }
    }
}

void Game::draw_path()
{
    if(heroes[0]->b_destination_present)
    {
        if(!heroes[0]->get_current_movement_points())
        {
            heroes[0]->b_out_of_movement_points = true;
        }
        for(int i = heroes[0]->destination_dot_pos_on_map.size() - 1, j = heroes[0]->get_current_movement_points(); i > -1; --i, --j)
        {
            Pos pos = pos_from_map_to_window(heroes[0]->destination_dot_pos_on_map[i]);
            if(pos.is_in_rect(map_screen_drect))
            {
                pos.x -= TILE_WIDTH/2;
                Rect drect(pos - camera_offset, TILE_WIDTH, TILE_HEIGHT);
                int image_id = DESTINATION_DOT + heroes[0]->b_out_of_movement_points;
                images->ui[image_id]->draw(Rect(), drect);
            }
            if(!(j-1))
            {
                heroes[0]->b_out_of_movement_points = true;
            }
        }
        Pos pos = pos_from_map_to_window(heroes[0]->destination_mark_pos_on_map);
        if(pos.is_in_rect(map_screen_drect))
        {
            pos.x -= TILE_WIDTH/2;
            Rect drect(pos - camera_offset, TILE_WIDTH, TILE_HEIGHT);
            int image_id = DESTINATION_MARK + heroes[0]->b_out_of_movement_points;
            images->ui[image_id]->draw(Rect(), drect);
        }
        heroes[0]->b_out_of_movement_points = false;
    }
}

void Game::draw_ui()
{
    images->ui[RIGHT_PANEL]->draw(Rect(), right_panel_drect);
    images->ui[BOTTOM_BAR]->draw(Rect(), bottom_bar_drect);
    images->ui[HOURGLASS + b_hourglass_pressed]->draw(Rect(), hourglass_drect);
}

void Game::trigger_movement()
{
    if(heroes[0]->destination_mark_pos_on_map == selected_pos_on_map && heroes[0]->b_destination_present)
    {
        heroes[0]->b_hero_moving = true;
    }
    else
    {
        if(selected_pos_on_map.is_in_rect(0, 0, map.w - 1, map.h - 1) && selected_pos_on_map != heroes[0]->pos_on_map)
        {
            heroes[0]->b_destination_present = true;
            heroes[0]->destination_mark_pos_on_map = selected_pos_on_map;
            find_path();
            lay_down_path();
            //heroes[0]->destination_mark_pos_on_map.print_coordinates();
        }
        else
        {
            heroes[0]->b_destination_present = false;
        }
    }
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
    center_pos_on_map = heroes[0]->pos_on_map;
    camera_offset = Pos();
}

void Game::update_movement()
{
    focus_hero();
    if(heroes[0]->current_travel_path.empty())
    {
        heroes[0]->b_hero_moving = false;
        heroes[0]->b_destination_present = false;
    }
    else
    {
        heroes[0]->set_direction(heroes[0]->current_travel_path.back());
        if(heroes[0]->move())
        {
            if(heroes[0]->current_travel_path.size() > 1)
            {
                heroes[0]->destination_dot_pos_on_map.pop_back();
            }
            heroes[0]->current_travel_path.pop_back();
            if(heroes[0]->current_travel_path.empty())
            {
                for(int i = 0; i < (int)monsters.size(); ++i)
                {
                    Rect drect(monsters[i]->pos_on_map - 1, monsters[i]->pos_on_map + 1);
                    if(heroes[0]->pos_on_map.is_in_rect(drect))
                    {
                        if(fight(heroes[0], monsters[i]))
                        {
                            delete monsters[i];
                            monsters.erase(monsters.begin() + i);
                        }
                        else
                        {
                            std::cout << "Your hero has died! You have lost!" << std::endl;
                            b_quit = true;
                            return;
                        }
                        break;
                    }
                }
                heroes[0]->b_hero_moving = false;
                heroes[0]->b_destination_present = false;
            }
        }
        else
        {
            heroes[0]->b_hero_moving = false;
        }
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
            adjust_center_tile(temp_center_pos_on_map);
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
                adjust_center_tile(temp_center_pos_on_map);
            }
        }
    }
}

void Game::adjust_center_tile(Pos &temp_center_pos_on_map)
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

bool Game::cursor_on_destination_mark()
{
    if(!(heroes[0]->b_destination_present))
    {
        return 0;
    }
    Pos pos = pos_from_map_to_window(heroes[0]->destination_mark_pos_on_map);
    pos.x -= TILE_WIDTH/2;
    Rect drect(pos - camera_offset, TILE_WIDTH, TILE_HEIGHT);
    if(cursor_pos.is_in_rect(drect))
    {
        return 1;
    }
    return 0;
}

int Game::cursor_on_monster()
{
    for(int i = 0; i < (int)monsters.size(); ++i)
    {
        Pos pos = pos_from_map_to_window(monsters[i]->pos_on_map);
        if(pos.is_in_rect(map_screen_drect))
        {
            pos.x -= TILE_WIDTH/2;
            Rect drect(pos - camera_offset, TILE_WIDTH, TILE_HEIGHT);
            if(cursor_pos.is_in_rect(drect.expand(TILE_WIDTH, TILE_HEIGHT)))
            {
                return i;
            }
        }
    }
    return -1;
}

void Game::update_cursor()
{
    if(map_scroll_direction != NO_DIRECTION)
    {
        cursor.set_cursor(map_scroll_direction);
    }
    else if(cursor_on_monster() >= 0)
    {
        cursor.set_cursor(COMBAT_CURSOR);
    }
    else if(cursor_on_destination_mark())
    {
        cursor.set_cursor(GO_TO_DESTINATION);
    }
    else
    {
        cursor.set_cursor(NORMAL_CURSOR);
    }
}

void Game::set_monsters()
{
    for(int y = 0; y < map.h; ++y)
    {
        for(int x = 0; x < map.w; ++x)
        {
            if(map.get_entity(x, y))
            {
                int size = map.entity_count.size() - 1;
                if(map.get_entity(x, y) == 1)
                {
                    monsters.push_back(new Wolf(x, y, map.entity_count[size]));
                }
                else if(map.get_entity(x, y) == 2)
                {
                    monsters.push_back(new Goblin(x, y, map.entity_count[size]));
                }
                else
                {
                    monsters.push_back(new Snake(x, y, map.entity_count[size]));
                }
                map.entity_count.pop_back();
            }
        }
    }
}

void Game::draw_monsters()
{
    for(auto monster : monsters)
    {
        Pos pos = pos_from_map_to_window(monster->pos_on_map);
        Rect drect = map_screen_drect;
        if(pos.is_in_rect(drect.expand(TILE_WIDTH, TILE_HEIGHT)))
        {
            pos.x -= TILE_WIDTH/2;
            drect = Rect(pos - camera_offset, TILE_WIDTH, TILE_HEIGHT);
            int image_id = map.get_entity(monster->pos_on_map.x, monster->pos_on_map.y) - 1;
            images->monster_images[image_id]->draw(Rect(), drect);
        }
    }
}

bool fight(Hero* hero, Monster* monster) // temporary
{
    std::cout << "You just attacked " << monster->count << " " << monster->name() << "(s)!" << std::endl;
    while(true)
    {
        std::cout << "Your " << hero->hero_army[0]->name() << " attacked." << std::endl << "Enemy ";
        if(!monster->defend(hero->hero_army[0]->attack()))
        {
            std::cout << "You have won!" << std::endl;
            return true;
        }
        else
        {
            std::cout << "The enemy " << monster->name() << " retaliated." << std::endl << "Your ";
            if(!(hero->hero_army[0]->defend(monster->retaliate())))
            {
                delete hero->hero_army[0];
                hero->hero_army.erase(hero->hero_army.begin());
                if(hero->hero_army.empty())
                {
                    return false;
                }
            }
        }
        std::cout << "The enemy " << monster->name() << " attacked." << std::endl << "Your ";
        if(!hero->hero_army[0]->defend(monster->attack()))
        {
            delete hero->hero_army[0];
            hero->hero_army.erase(hero->hero_army.begin());
            if(hero->hero_army.empty())
            {
                return false;
            }
        }
        else
        {
            std::cout << "Your " << hero->hero_army[0]->name() << " retaliated." << std::endl << "Enemy ";
            if(!(monster->defend(hero->hero_army[0]->retaliate())))
            {
                std::cout << "You have won!" << std::endl;
                return true;
            }
        }
        if(hero->hero_army.size() > 1)
        {
            for(int i = 1; i < (int)hero->hero_army.size(); ++i)
            {
                std::cout << "Your " << hero->hero_army[i]->name() << " attacked." << std::endl << "Enemy ";
                if(!monster->defend(hero->hero_army[i]->attack()))
                {
                    std::cout << "You have won!" << std::endl;
                    return true;
                }
                else
                {
                    if(!monster->retaliate())
                    {
                        std::cout << "The enemy " << monster->name() << " retaliated." << std::endl << "Your ";
                        if(!(hero->hero_army[i]->defend(monster->retaliate())))
                        {
                            delete hero->hero_army[i];
                            hero->hero_army.erase(hero->hero_army.begin() + i);
                        }
                    }
                }
            }
        }
        for(auto hero_army_unit : hero->hero_army)
        {
            hero_army_unit->b_retaliated = false;
        }
        monster->b_retaliated = false;
    }
}

Pos Game::pos_from_map_to_window(Pos &pos_on_map) const
{
    int x = (pos_on_map.x - center_pos_on_map.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH;
    int y = (pos_on_map.y - center_pos_on_map.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT;
    return Pos(x, y);
}

Pos Game::pos_from_window_to_map(Pos &pos_on_window) const
{
    int x = center_pos_on_map.x - WINDOW_WIDTH_TILE_FIT/2 + (pos_on_window.x + 20) / TILE_WIDTH;
    int y = center_pos_on_map.y - WINDOW_HEIGTH_TILE_FIT/2 + pos_on_window.y / TILE_HEIGHT;
    return Pos(x, y);
}

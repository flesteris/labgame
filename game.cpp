#include "game.hpp"

Game::Game()
{
    map.load_map_data("maps//map_1_data.txt");
    map_size_rect = Rect(0, 0, map.w - 1, map.h - 1);
    set_options();
    window = new Window();
    images = new Images(this);
    set_monsters();
    update_monsters_position();
    end_turn();
    SDL_RaiseWindow(window->win);
    SDL_SetWindowGrab(window->win, SDL_TRUE);
}

Game::~Game()
{
    delete images;
    delete window;
    std::cout << "Memory cleared! ...";
}

void Game::set_options()
{
    std::cout << "Enter starting coordinates(0-" << map.w - 1 << " 0-" << map.h - 1 << "): ";
    std::cin >> center_pos_m.x >> center_pos_m.y;
    if(!center_pos_m.is_in_rect(map_size_rect))
    {
        center_pos_m = Pos(0, 0);
        std::cout << "Incorrect coordinates. Loading default coordinates." << std::endl;
        heroes.push_back(new Hero(this));
    }
    else
    {
        int max_movement_points;
        std::cout << "Enter hero's max movement points(1-50): ";
        std::cin >> max_movement_points;
        if(max_movement_points < 1 || max_movement_points > 50)
        {
            std::cout << "Incorrect hero's max movement points. Loading default movement points(10)." << std::endl;
            heroes.push_back(new Hero(this, center_pos_m, 10));
        }
        heroes.push_back(new Hero(this, center_pos_m, max_movement_points));
    }
}

void Game::get_input()
{
    if(SDL_PollEvent(&event))
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
                motion_pos = Pos(event.button.x, event.button.y);
                if(!detect_map_scrolling())
                {
                    update_cursor();
                }
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                if(SDL_BUTTON_LEFT == event.button.button && event.button.clicks)
                {
                    heroes[0]->b_hero_moving = false;
                    selected_pos = Pos(event.button.x, event.button.y);

                    if(selected_pos.is_in_rect(map_screen_drect))
                    {
                        selected_pos_m = Pos(center_pos_m.x - WINDOW_WIDTH_TILE_FIT/2 + (event.button.x + 20) / TILE_WIDTH, center_pos_m.y - WINDOW_HEIGTH_TILE_FIT/2 + event.button.y / TILE_HEIGHT); // Which map tile is clicked
                        trigger_movement();
                    }
                    else if(selected_pos.is_in_rect(hourglass_drect))
                    {
                        b_hourglass_pressed = true;
                    }
                }
                /*if(SDL_BUTTON_RIGHT == event.button.button)
                {

                }*/
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
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[SOUTHWEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_2:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[SOUTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_DOWN:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[SOUTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_3:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[SOUTHEAST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_4:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[WEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_LEFT:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[WEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_6:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[EAST];
                        trigger_movement();
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[EAST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_7:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[NORTHWEST];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_8:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[NORTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_UP:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[NORTH];
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_9:
                    {
                        selected_pos_m = heroes[0]->pos_m + DIRECTIONS[NORTHEAST];
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
    if(heroes[0]->b_hero_moving)
    {
        if(hero_move_speed_counter == hero_move_speed)
        {
            hero_move_speed_counter = 0;
            update_movement();
            update_monsters_position();
            update_cursor();
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
    draw_land(this);
    draw_monsters();
    draw_path();
    images->hero_images[heroes[0]->get_direction()]->draw(Rect(), heroes[0]->hero_drect);
    draw_ui();
    SDL_RenderPresent(window->ren);
}

void draw_land(Game* game)
{
    for(int i = game->center_pos_m.x - WINDOW_WIDTH_TILE_FIT/2, k = -1/*(int)game->center_pos_m.x - game->center_pos_m.x - 1*/; i < game->center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2 + 1; ++i, ++k)
    {
        if(i < 0 || i > game->map.h - 1)
        {
            for(int j = game->center_pos_m.y - WINDOW_HEIGTH_TILE_FIT/2, l = 0/*(int)game->center_pos_m.y - game->center_pos_m.y*/; j < game->center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2 + 2; ++j, ++l)
            {
                Rect tile_drect(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
                game->images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = game->center_pos_m.y - WINDOW_HEIGTH_TILE_FIT/2, l = 0/*(int)game->center_pos_m.y - game->center_pos_m.y*/; j < game->center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2 + 2; ++j, ++l)
            {
                if(j < 0 || j > game->map.w - 1)
                {
                    Rect tile_drect(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
                    game->images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
                }
                else
                {
                    Rect tile_drect(Pos(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
                    game->images->tiles[game->map.tiles[i+j*game->map.w] - 1]->draw(Rect(), tile_drect);
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
    for(int i = 0; i < heroes[0]->hero_army.size(); ++i)
    {
        std::cout << heroes[0]->hero_army[i]->get_count() << " " << heroes[0]->hero_army[i]->name() << "(s)" << std::endl;
    }
    std::cout << "**********************************************" << std::endl << std::endl;

}

void Game::find_path()
{
    heroes[0]->travel.clear();
    Pos pos_m = heroes[0]->destination_mark_pos_m;
    bool west_f = false, east_f = false;

    while(heroes[0]->pos_m != pos_m)
    {
        if(heroes[0]->pos_m.x < pos_m.x)
        {
            heroes[0]->travel.push_back(EAST);
            --pos_m.x;
            east_f = true;
        }
        else if(heroes[0]->pos_m.x > pos_m.x)
        {
            heroes[0]->travel.push_back(WEST);
            ++pos_m.x;
            west_f = true;
        }
        if(heroes[0]->pos_m.y < pos_m.y)
        {
            if(east_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = SOUTHEAST;
                --pos_m.y;
                east_f = false;
            }
            else if(west_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = SOUTHWEST;
                --pos_m.y;
                west_f = false;
            }
            else
            {
                heroes[0]->travel.push_back(SOUTH);
                --pos_m.y;
            }
        }
        else if(heroes[0]->pos_m.y > pos_m.y)
        {
            if(east_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = NORTHEAST;
                ++pos_m.y;
                east_f = false;
            }
            else if(west_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = NORTHWEST;
                ++pos_m.y;
                west_f = false;
            }
            else
            {
                heroes[0]->travel.push_back(NORTH);
                ++pos_m.y;
            }
        }
    }
}

void Game::lay_down_path()
{
    update_destination_mark_position();

    heroes[0]->destination_dot_pos_m.clear();
    heroes[0]->destination_dot_pos.clear();
    heroes[0]->destination_dot_drect.clear();

    if(heroes[0]->travel.size() > 1)
    {
        heroes[0]->destination_dot_pos_m.push_back(Pos(heroes[0]->destination_mark_pos_m - DIRECTIONS[heroes[0]->travel[0]]));
        heroes[0]->destination_dot_pos.push_back(Pos((heroes[0]->destination_dot_pos_m[0].x - center_pos_m.x + 12) * TILE_WIDTH, (heroes[0]->destination_dot_pos_m[0].y - center_pos_m.y + 8) * TILE_HEIGHT));
        heroes[0]->destination_dot_drect.push_back(Rect(heroes[0]->destination_dot_pos[0].x - TILE_WIDTH/2, heroes[0]->destination_dot_pos[0].y, TILE_WIDTH, TILE_HEIGHT));
        for(int i = 1; i < (int)heroes[0]->travel.size() - 1; ++i)
        {
            heroes[0]->destination_dot_pos_m.push_back(Pos(heroes[0]->destination_dot_pos_m[i-1] - DIRECTIONS[heroes[0]->travel[i]]));
            heroes[0]->destination_dot_pos.push_back(Pos((heroes[0]->destination_dot_pos_m[i].x - center_pos_m.x + 12) * TILE_WIDTH, (heroes[0]->destination_dot_pos_m[i].y - center_pos_m.y + 8) * TILE_HEIGHT));
            heroes[0]->destination_dot_drect.push_back(Rect(heroes[0]->destination_dot_pos[i].x - TILE_WIDTH/2, heroes[0]->destination_dot_pos[i].y, TILE_WIDTH, TILE_HEIGHT));
        }
    }
}

void Game::update_path_position()
{
    update_destination_mark_position();
    for(int i = 0; i < (int)heroes[0]->travel.size() - 1; ++i)
    {
        update_destination_dot_position(i);
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
        for(int i = heroes[0]->destination_dot_drect.size() - 1, j = heroes[0]->get_current_movement_points(); i > -1; --i, --j)
        {
            images->ui[DESTINATION_DOT + heroes[0]->b_out_of_movement_points]->draw(Rect(), heroes[0]->destination_dot_drect[i]);
            if(!(j-1))
            {
                heroes[0]->b_out_of_movement_points = true;
            }
        }
        images->ui[DESTINATION_MARK + heroes[0]->b_out_of_movement_points]->draw(Rect(), heroes[0]->destination_mark_drect);
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
    if(heroes[0]->destination_mark_pos_m == selected_pos_m && heroes[0]->b_destination_present)
    {
        heroes[0]->b_hero_moving = true;
    }
    else
    {
        if(selected_pos_m.is_in_rect(0, 0, map.w - 1, map.h - 1) && selected_pos_m != heroes[0]->pos_m)
        {
            heroes[0]->b_destination_present = true;
            heroes[0]->destination_mark_pos_m = selected_pos_m;
            find_path();
            lay_down_path();
            update_cursor();
            //destination_mark_pos_m.print_coordinates();
        }
        else
        {
            heroes[0]->b_destination_present = false;
            heroes[0]->destination_mark_drect = Rect();
        }
    }
}

bool Game::detect_map_scrolling()
{
    std::fill_n(b_map_scroll, 8, false);
    if(motion_pos == Pos(0, 0))
    {
        b_map_scroll[NORTHWEST] = true;
        cursor.set_cursor(NW_ARROW);
        return 1;
    }
    else if(motion_pos == Pos(0, WINDOW_HEIGTH - 1))
    {
        b_map_scroll[SOUTHWEST] = true;
        cursor.set_cursor(SW_ARROW);
        return 1;
    }
    else if(motion_pos == Pos(WINDOW_WIDTH - 1, WINDOW_HEIGTH - 1))
    {
        b_map_scroll[SOUTHEAST] = true;
        cursor.set_cursor(SE_ARROW);
        return 1;
    }
    else if(motion_pos == Pos(WINDOW_WIDTH - 1, 0))
    {
        b_map_scroll[NORTHEAST] = true;
        cursor.set_cursor(NE_ARROW);
        return 1;
    }
    else
    {
        std::fill_n(b_map_scroll, 8, false); // Without this the scrolling speed sometimes would be double
        if(motion_pos.x == 0)
        {
            b_map_scroll[WEST] = true;
            cursor.set_cursor(W_ARROW);
            return 1;
        }
        else if(motion_pos.x == WINDOW_WIDTH - 1)
        {
            b_map_scroll[EAST] = true;
            cursor.set_cursor(E_ARROW);
            return 1;
        }
        else if(motion_pos.y == 0)
        {
            b_map_scroll[NORTH] = true;
            cursor.set_cursor(N_ARROW);
            return 1;
        }
        else if(motion_pos.y == WINDOW_HEIGTH - 1)
        {
            b_map_scroll[SOUTH] = true;
            cursor.set_cursor(S_ARROW);
            return 1;
        }
        return 0;
    }
}

void Game::focus_hero()
{
    center_pos_m = heroes[0]->pos_m;
    heroes[0]->pos = center_pos;
    heroes[0]->hero_drect = center_drect;
    update_path_position();
    update_monsters_position();
    update_cursor();
}

void Game::update_movement()
{
    focus_hero();
    update_cursor();
    if(heroes[0]->travel.empty())
    {
        heroes[0]->b_hero_moving = false;
        heroes[0]->b_destination_present = false;
    }
    else
    {
        heroes[0]->set_direction(heroes[0]->travel.back());
        if(heroes[0]->move())
        {
            if(heroes[0]->travel.size() > 1)
            {
                heroes[0]->destination_dot_pos_m.pop_back();
                heroes[0]->destination_dot_pos.pop_back();
                heroes[0]->destination_dot_drect.pop_back();
                for(int i = 0; i < (int)heroes[0]->travel.size() - 1; ++i)
                {
                    update_destination_dot_position(i);
                }
            }
            heroes[0]->travel.pop_back();
            if(heroes[0]->travel.empty())
            {
                for(int i = 0; i < (int)monsters.size(); ++i)
                {
                    if(heroes[0]->pos_m == monsters[i]->pos_m)
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
            update_destination_mark_position();
        }
        else
        {
            heroes[0]->b_hero_moving = false;
        }
    }
}

void Game::update_map_scrolling()
{
    for(int i = 0; i < DIRECTION_COUNT; ++i)
    {
        if(b_map_scroll[i])
        {
            Pos pos_m = center_pos_m + DIRECTIONS[i];
            if(pos_m.is_in_rect(map_size_rect))
            {
                center_pos_m = pos_m;
                heroes[0]->pos = Pos((heroes[0]->pos_m.x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->pos_m.y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT);
                heroes[0]->hero_drect = Rect(heroes[0]->pos.x - TILE_WIDTH/2, heroes[0]->pos.y, TILE_WIDTH, TILE_HEIGHT);
                update_path_position();
                update_monsters_position();
            }
            else // Doesn't stick to the border while scrolling diagonally
            {
                pos_m.fit_in_rect(map_size_rect);
                if(center_pos_m != pos_m)
                {
                    center_pos_m = pos_m;
                    heroes[0]->pos = Pos((heroes[0]->pos_m.x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->pos_m.y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT);
                    heroes[0]->hero_drect = Rect(heroes[0]->pos.x - TILE_WIDTH/2, heroes[0]->pos.y, TILE_WIDTH, TILE_HEIGHT);
                    update_path_position();
                    update_monsters_position();
                }
            }
            break;
        }
    }
}

void Game::update_destination_mark_position()
{
    if(!heroes[0]->travel.empty())
    {
        heroes[0]->destination_mark_pos = Pos((heroes[0]->destination_mark_pos_m.x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->destination_mark_pos_m.y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT);
        heroes[0]->destination_mark_drect = Rect(heroes[0]->destination_mark_pos.x - TILE_WIDTH/2, heroes[0]->destination_mark_pos.y, TILE_WIDTH, TILE_HEIGHT);
    }
    else
    {
        heroes[0]->destination_mark_drect = Rect();
    }
}

void Game::update_destination_dot_position(int i)
{
    heroes[0]->destination_dot_pos[i] = (Pos((heroes[0]->destination_dot_pos_m[i].x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->destination_dot_pos_m[i].y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT));
    heroes[0]->destination_dot_drect[i] = (Rect(heroes[0]->destination_dot_pos[i].x - TILE_WIDTH/2, heroes[0]->destination_dot_pos[i].y, TILE_WIDTH, TILE_HEIGHT));
}

bool Game::cursor_on_destination_mark()
{
    if(motion_pos.is_in_rect(heroes[0]->destination_mark_drect))
    {
        return 1;
    }
    return 0;
}

bool Game::cursor_on_monster()
{
    for(int i = 0; i < (int)monsters.size(); ++i)
    {
        if(motion_pos.is_in_rect(monsters[i]->drect))
        {
            return 1;
        }
    }
    return 0;
}

void Game::update_cursor()
{
    if(cursor_on_monster())
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
                if(map.get_entity(x, y) == 1)
                {
                    monsters.push_back(new Wolf(x, y, map.entity_count[map.entity_count.size() - 1]));
                }
                else if(map.get_entity(x, y) == 2)
                {
                    monsters.push_back(new Goblin(x, y, map.entity_count[map.entity_count.size() - 1]));
                }
                else
                {
                    monsters.push_back(new Snake(x, y, map.entity_count[map.entity_count.size() - 1]));
                }
                map.entity_count.pop_back();
            }
        }
    }
}

void Game::update_monsters_position()
{
    for(int i = 0; i < (int)monsters.size(); ++i)
    {
        monsters[i]->pos = Pos((monsters[i]->pos_m.x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (monsters[i]->pos_m.y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT);
        monsters[i]->drect = Rect(monsters[i]->pos.x - TILE_WIDTH/2, monsters[i]->pos.y, TILE_WIDTH, TILE_HEIGHT);
    }
}

void Game::draw_monsters()
{
    for(int i = 0; i < (int)monsters.size(); ++i)
    {
        images->monster_images[map.get_entity(monsters[i]->pos_m.x, monsters[i]->pos_m.y) - 1]->draw(Rect(), monsters[i]->drect);
    }
}

int Game::fight(Hero* hero, Monster* monster) // temporary
{
    std::cout << "You just attacked " << monster->get_count() << " " << monster->name() << "(s)!" << std::endl;
    while(true)
    {
        std::cout << "Your " << hero->hero_army[0]->name() << " attacked." << std::endl << "Enemy ";
        if(!monster->defend(hero->hero_army[0]->attack()))
        {
            std::cout << "You have won!" << std::endl;
            return 1;
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
                    return 0;
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
                return 0;
            }
        }
        else
        {
            std::cout << "Your " << hero->hero_army[0]->name() << " retaliated." << std::endl << "Enemy ";
            if(!(monster->defend(hero->hero_army[0]->retaliate())))
            {
                std::cout << "You have won!" << std::endl;
                return 1;
            }
        }

        if(hero->hero_army.size() > 1)
        {
            for(int i = 1; i < hero->hero_army.size(); ++i)
            {
                std::cout << "Your " << hero->hero_army[i]->name() << " attacked." << std::endl << "Enemy ";
                if(!monster->defend(hero->hero_army[i]->attack()))
                {
                    std::cout << "You have won!" << std::endl;
                    return 1;
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
        for(int i = 0; i < hero->hero_army.size(); ++i)
        {
            hero->hero_army[i]->retaliate_reset();
        }
        monster->retaliate_reset();
    }
}


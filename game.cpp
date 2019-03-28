#include "game.hpp"

Game::Game()
{
    map.load_map_data("maps//map_1_data.txt");
    map_size_drect = Rect(0, 0, map.w - 1, map.h - 1);
    set_options();
    window = new Window();
    images = new Images(this);
    SDL_RaiseWindow(window->win);
    SDL_SetWindowGrab(window->win, SDL_TRUE);
}

Game::~Game()
{
    delete window;
    delete images;
    std::cout << "Memory cleared! ...";
}

void Game::set_options()
{
    std::cout << "Enter starting coordinates(0-" << map.w - 1 << " 0-" << map.h - 1 << "): ";
    std::cin >> center_pos_m.x >> center_pos_m.y;
    if(!center_pos_m.is_in_rect(map_size_drect))
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
                detect_map_scrolling();
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
                    for(int i = 0; i < (int)travel.size(); ++i)
                    {
                        std::cout << travel[i] << " " ;
                    }
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
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[SOUTHWEST]);
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_2:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[SOUTH]);
                        trigger_movement();
                        break;
                    }
                case SDLK_DOWN:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[SOUTH]);
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_3:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[SOUTHEAST]);
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_4:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[WEST]);
                        trigger_movement();
                        break;
                    }
                case SDLK_LEFT:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[WEST]);
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_6:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[EAST]);
                        trigger_movement();
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[EAST]);
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_7:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[NORTHWEST]);
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_8:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[NORTH]);
                        trigger_movement();
                        break;
                    }
                case SDLK_UP:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[NORTH]);
                        trigger_movement();
                        break;
                    }
                case SDLK_KP_9:
                    {
                        selected_pos_m = Pos(heroes[0]->pos_m + DIRECTIONS[NORTHEAST]);
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
                Rect tile_drect = Rect(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
                game->images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = game->center_pos_m.y - WINDOW_HEIGTH_TILE_FIT/2, l = 0/*(int)game->center_pos_m.y - game->center_pos_m.y*/; j < game->center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2 + 2; ++j, ++l)
            {
                if(j < 0 || j > game->map.w - 1)
                {
                    Rect tile_drect = Rect(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
                    game->images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
                }
                else
                {
                    Rect tile_drect = Rect(Pos(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
                    game->images->tiles[game->map.tiles[i+j*game->map.w] - 1]->draw(Rect(), tile_drect);
                }
            }
        }
    }
}

void Game::end_turn()
{
    heroes[0]->set_current_movement_points(heroes[0]->get_max_movement_points());
    game_time.next_day();
    focus_hero();
}

void Game::find_path()
{
    heroes[0]->travel.clear();
    Pos pos = heroes[0]->destination_mark_pos_m;
    bool west_f = false, east_f = false;

    while(heroes[0]->pos_m != pos)
    {
        if(heroes[0]->pos_m.x < pos.x)
        {
            heroes[0]->travel.push_back(EAST);
            --pos.x;
            east_f = true;
        }
        else if(heroes[0]->pos_m.x > pos.x)
        {
            heroes[0]->travel.push_back(WEST);
            ++pos.x;
            west_f = true;
        }
        if(heroes[0]->pos_m.y < pos.y)
        {
            if(east_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = SOUTHEAST;
                --pos.y;
                east_f = false;
            }
            else if(west_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = SOUTHWEST;
                --pos.y;
                west_f = false;
            }
            else
            {
                heroes[0]->travel.push_back(SOUTH);
                --pos.y;
            }
        }
        else if(heroes[0]->pos_m.y > pos.y)
        {
            if(east_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = NORTHEAST;
                ++pos.y;
                east_f = false;
            }
            else if(west_f)
            {
                heroes[0]->travel[heroes[0]->travel.size() - 1] = NORTHWEST;
                ++pos.y;
                west_f = false;
            }
            else
            {
                heroes[0]->travel.push_back(NORTH);
                ++pos.y;
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

void Game::update_path()
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
            heroes[0]->destination_mark_pos_m = selected_pos_m;
            find_path();
            lay_down_path();
            heroes[0]->b_destination_present = true;
            //destination_mark_pos_m.print_coordinates();
        }
        else
        {
            heroes[0]->b_destination_present = false;
        }
    }
}

void Game::detect_map_scrolling()
{
    Pos pos = Pos(event.button.x, event.button.y);

    std::fill_n(b_map_scroll, 8, false);
    if(pos == Pos(0, 0))
    {
        b_map_scroll[NORTHWEST] = true;
        cursor.set_cursor(NW_ARROW);
    }
    else if(pos == Pos(0, WINDOW_HEIGTH - 1))
    {
        b_map_scroll[SOUTHWEST] = true;
        cursor.set_cursor(SW_ARROW);
    }
    else if(pos == Pos(WINDOW_WIDTH - 1, WINDOW_HEIGTH - 1))
    {
        b_map_scroll[SOUTHEAST] = true;
        cursor.set_cursor(SE_ARROW);
    }
    else if(pos == Pos(WINDOW_WIDTH - 1, 0))
    {
        b_map_scroll[NORTHEAST] = true;
        cursor.set_cursor(NE_ARROW);
    }
    else
    {
        std::fill_n(b_map_scroll, 8, false); // Without this the scrolling speed sometimes would be double
        if(pos.x == 0)
        {
            b_map_scroll[WEST] = true;
            cursor.set_cursor(W_ARROW);
        }
        else if(pos.x == WINDOW_WIDTH - 1)
        {
            b_map_scroll[EAST] = true;
            cursor.set_cursor(E_ARROW);
        }
        else if(pos.y == 0)
        {
            b_map_scroll[NORTH] = true;
            cursor.set_cursor(N_ARROW);
        }
        else if(pos.y == WINDOW_HEIGTH - 1)
        {
            b_map_scroll[SOUTH] = true;
            cursor.set_cursor(S_ARROW);
        }
        else
        {
            cursor.set_cursor();
        }
    }
}

void Game::focus_hero()
{
    center_pos_m = heroes[0]->pos_m;
    heroes[0]->pos = center_pos;
    heroes[0]->hero_drect = center_drect;
    update_path();
}

void Game::update_movement()
{
    focus_hero();
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
            Pos pos_m = Pos(center_pos_m + DIRECTIONS[i]);
            if(pos_m.is_in_rect(map_size_drect))
            {
                center_pos_m = pos_m;
                heroes[0]->pos = Pos((heroes[0]->pos_m.x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->pos_m.y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT);
                heroes[0]->hero_drect = Rect(heroes[0]->pos.x - TILE_WIDTH/2, heroes[0]->pos.y, TILE_WIDTH, TILE_HEIGHT);
                update_path();
            }
            else // Doesn't stick to the border while scrolling diagonally
            {
                pos_m.fit_in_rect(map_size_drect);
                if(center_pos_m != pos_m)
                {
                    center_pos_m = pos_m;
                    heroes[0]->pos = Pos((heroes[0]->pos_m.x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->pos_m.y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT);
                    heroes[0]->hero_drect = Rect(heroes[0]->pos.x - TILE_WIDTH/2, heroes[0]->pos.y, TILE_WIDTH, TILE_HEIGHT);
                    update_path();
                }
            }
            break;
        }
    }
}

void Game::update_destination_mark_position()
{
    heroes[0]->destination_mark_pos = Pos((heroes[0]->destination_mark_pos_m.x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->destination_mark_pos_m.y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT);
    heroes[0]->destination_mark_drect = Rect(heroes[0]->destination_mark_pos.x - TILE_WIDTH/2, heroes[0]->destination_mark_pos.y, TILE_WIDTH, TILE_HEIGHT);
}

void Game::update_destination_dot_position(int i)
{
    heroes[0]->destination_dot_pos[i] = (Pos((heroes[0]->destination_dot_pos_m[i].x - center_pos_m.x + WINDOW_WIDTH_TILE_FIT/2) * TILE_WIDTH, (heroes[0]->destination_dot_pos_m[i].y - center_pos_m.y + WINDOW_HEIGTH_TILE_FIT/2) * TILE_HEIGHT));
    heroes[0]->destination_dot_drect[i] = (Rect(heroes[0]->destination_dot_pos[i].x - TILE_WIDTH/2, heroes[0]->destination_dot_pos[i].y, TILE_WIDTH, TILE_HEIGHT));
}



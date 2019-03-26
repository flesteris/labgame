#include "game.hpp"

Game::Game()
{
    map.load_map_data("maps//map_1_data.txt");
    set_options();
    window = new Window();
    images = new Images(this);
    SDL_RaiseWindow(window->win);
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
    if(center_pos_m.x < 0 || center_pos_m.x > map.w - 1 || center_pos_m.y < 0 || center_pos_m.y > map.h - 1)
    {
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
                quit = true;
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    Pos pos(event.button.x, event.button.y);
                    if(pos.is_in_rect(map_screen_drect))
                    {
                        Pos pos_m(center_pos_m.x - 12 + (event.button.x + 20) / TILE_WIDTH, center_pos_m.y - 8 + event.button.y / TILE_HEIGHT); // Which map tile is clicked
                        if(destination_pos_m == pos_m && destination_present)
                        {
                            hero_moving = true;
                        }
                        else
                        {
                            destination_pos_m = pos_m;
                            if(destination_pos_m.is_in_rect(0, 0, map.w - 1, map.h - 1))
                            {
                                find_path();
                                //lay_down_path();
                                std::cout << "COORDS: x = " << destination_pos_m.x << ", y = " << destination_pos_m.y << std::endl;
                                destination_present = true;
                            }
                            else
                            {
                                destination_present = false;
                            }
                        }
                    }
                    else if(pos.is_in_rect(hourglass_drect))
                    {
                        hourglass_pressed = true;
                    }
                }
                /*if(event.button.button == SDL_BUTTON_RIGHT)
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
                    if(hourglass_pressed)
                    {
                        if(pos.is_in_rect(hourglass_drect))
                        {
                            end_turn();
                        }
                        hourglass_pressed = false;
                    }
                }
                break;
            }
        case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_q:
                    {
                        quit = true;
                        break;
                    }
                case SDLK_e:
                    {
                        hourglass_pressed = true;
                        break;
                    }
                case SDLK_KP_1:
                    {
                        heroes[0]->set_direction(SOUTHWEST);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_KP_2:
                    {
                        heroes[0]->set_direction(SOUTH);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_DOWN:
                    {
                        heroes[0]->set_direction(SOUTH);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_KP_3:
                    {
                        heroes[0]->set_direction(SOUTHEAST);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_KP_4:
                    {
                        heroes[0]->set_direction(WEST);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_LEFT:
                    {
                        heroes[0]->set_direction(WEST);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_KP_6:
                    {
                        heroes[0]->set_direction(EAST);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        heroes[0]->set_direction(EAST);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_KP_7:
                    {
                        heroes[0]->set_direction(NORTHWEST);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_KP_8:
                    {
                        heroes[0]->set_direction(NORTH);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_UP:
                    {
                        heroes[0]->set_direction(NORTH);
                        heroes[0]->move_triggered = true;
                        break;
                    }
                case SDLK_KP_9:
                    {
                        heroes[0]->set_direction(NORTHEAST);
                        heroes[0]->move_triggered = true;
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
                    end_turn();
                    hourglass_pressed = false;
                }
                break;
            }
        }
    }
}

void Game::update()
{
    destination_pos = {(destination_pos_m.x - center_pos_m.x + 12) * TILE_WIDTH, (destination_pos_m.y - center_pos_m.y + 8) * TILE_HEIGHT};
    destination_drect = {destination_pos.x - 20, destination_pos.y, TILE_WIDTH, TILE_HEIGHT};
    if(hero_moving)
    {
        if(travel.empty())
        {
            hero_moving = false;
        }
        else
        {
            heroes[0]->set_direction(travel[travel.size() - 1]);
            if(heroes[0]->move())
            {
                travel.pop_back();
            }
            else
            {
                hero_moving = false;
            }
        }
    }
    if(heroes[0]->move_triggered)
    {
        heroes[0]->move();
        heroes[0]->move_triggered = false;
    }
}

void Game::draw()
{
    draw_land(this);
    if(destination_present)
    {
        /*for(int i = 0; i < (int)destination_dot_drect.size() - 1; i++)
        {
            images->ui[DESTINATION_DOT]->draw(Rect(), destination_dot_drect[i]);
        }*/
        images->ui[DESTINATION]->draw(Rect(), destination_drect);
    }
    images->ui[RIGHT_PANEL]->draw(Rect(), right_panel_drect);
    images->ui[BOTTOM_BAR]->draw(Rect(), bottom_bar_drect);
    images->ui[HOURGLASS + hourglass_pressed]->draw(Rect(), hourglass_drect);
    images->hero_images[heroes[0]->get_direction()]->draw(Rect(), hero_drect);




    SDL_RenderPresent(window->ren);
}

void draw_land(Game* game)
{
    Rect tile_drect;
    for(int i = game->heroes[0]->m_pos.x - 12, k = -1; i < game->heroes[0]->m_pos.x + 13; i++, k++)
    {
        if(i < 0 || i > game->map.h - 1)
        {
            for(int j = game->heroes[0]->m_pos.y - 8, l = 0; j < game->heroes[0]->m_pos.y + 9; j++, l++)
            {
                tile_drect = {k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
                game->images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = game->heroes[0]->m_pos.y - 8, l = 0; j < game->heroes[0]->m_pos.y + 9; j++, l++)
            {
                if(j < 0 || j > game->map.w - 1)
                {
                    tile_drect = {k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
                    game->images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
                }
                else
                {
                    tile_drect = {Pos(k*TILE_WIDTH + TILE_WIDTH/2, l*TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT};
                    game->images->tiles[game->map.tiles[i+j*game->map.w] - 1]->draw(Rect(), tile_drect);
                }
            }
        }
    }
}

void Game::end_turn()
{
    heroes[0]->set_current_movement_points(heroes[0]->get_max_movement_points());

    /*if(destination_present)
    {
        images->ui[DESTINATION]->draw(Rect(), out_of_movement_points_drect);
        destination_present = false;
    }*/
    game_time.next_day();
}

void Game::find_path()
{
    travel.clear();
    Pos pos = destination_pos_m;
    bool west_f = false, east_f = false;

    while(center_pos_m != pos)
    {
        if(center_pos_m.x < pos.x)
        {
            travel.push_back(EAST);
            --pos.x;
            east_f = true;
        }
        else if(center_pos_m.x > pos.x)
        {
            travel.push_back(WEST);
            ++pos.x;
            west_f = true;
        }
        if(center_pos_m.y < pos.y)
        {
            if(east_f)
            {
                travel[travel.size() - 1] = SOUTHEAST;
                --pos.y;
                east_f = false;
            }
            else if(west_f)
            {
                travel[travel.size() - 1] = SOUTHWEST;
                --pos.y;
                west_f = false;
            }
            else
            {
                travel.push_back(SOUTH);
                --pos.y;
            }
        }
        else if(center_pos_m.y > pos.y)
        {
            if(east_f)
            {
                travel[travel.size() - 1] = NORTHEAST;
                ++pos.y;
                east_f = false;
            }
            else if(west_f)
            {
                travel[travel.size() - 1] = NORTHWEST;
                ++pos.y;
                west_f = false;
            }
            else
            {
                travel.push_back(NORTH);
                ++pos.y;
            }
        }
    }
}

void Game::lay_down_path()
{
    //destination_dot_drect.clear();

    /*destination_dot_drect.push_back(Rect((Pos(460, 320) + DIRECTIONS[travel[travel.size() - 1]] * 40), TILE_WIDTH, TILE_HEIGHT));
    for(int i = travel.size() - 2; i > 2; --i)
    {
        destination_dot_drect.push_back(Rect((destination_dot_drect[i+1].pos->x + DIRECTIONS[travel[i]].x * 40), (destination_dot_drect[i+1].pos->y + DIRECTIONS[travel[i]].y * 40), TILE_WIDTH, TILE_HEIGHT));
    }*/
}

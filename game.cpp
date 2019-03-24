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
    Pos pos;

    std::cout << "Enter starting coordinates(0-" << map.w - 1 << " 0-" << map.h - 1 << "): ";
    std::cin >> pos.x >> pos.y;
    if(pos.x < 0 || pos.x > map.w - 1 || pos.y < 0 || pos.y > map.h - 1)
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
            heroes.push_back(new Hero(this, pos, 10));
        }
        heroes.push_back(new Hero(this, pos, max_movement_points));
    }
}

void Game::get_input()
{
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            quit = true;
        }
        else if(event.type == SDL_KEYDOWN)
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
                    heroes[0]->set_current_movement_points(heroes[0]->get_max_movement_points());

                    if(destination_present)
                    {
                        images->ui[DESTINATION]->draw(Rect(), out_of_movement_points_drect);
                        SDL_RenderPresent(window->ren);
                        destination_present = false;
                    }
                    game_time.next_day();
                    //std::string day_s = IntToString(day);
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
        }
    }
}

void Game::update()
{

}

void Game::draw()
{
    draw_land(this);
    images->ui[RIGHT_PANEL]->draw(Rect(), right_panel_drect);
    images->ui[BOTTOM_BAR]->draw(Rect(), bottom_bar_drect);
    images->ui[HOURGLASS]->draw(Rect(), hourglass_drect);
    images->hero_images[heroes[0]->get_direction()]->draw(Rect(), hero_drect);
    if(heroes[0]->move_triggered)
    {
        heroes[0]->move();
        heroes[0]->move_triggered = false;
        /*if(heroes[0]->move())
        {
            destination_present = false;
        }
        else
        {
            out_of_movement_points_drect = {Pos(470, 330), 20, 20};
            images->ui[NO_MOVEMENT_POINTS]->draw(Rect(), out_of_movement_points_drect);
            destination_present = true;
        }*/
    }

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

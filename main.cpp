// Kad sukompiliuoti per terminalą:
// g++ sdl.cpp -lSDL2
// SDL2 turi būti instaliuota, kad šitas veiktų

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "hero.hpp"
#include "image.hpp"
#include "images.hpp"
#include "map.hpp"
#include "rect.hpp"
#include "game.hpp"
#include "window.hpp"
#include "game_time.hpp"
#include "pos.hpp"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    Game game;

    draw_land(game);
    game.images->hero_images[EAST]->draw(Rect(), game.hero_drect);
    game.images->ui[RIGHT_PANEL]->draw(Rect(), game.right_panel_drect);
    game.images->ui[BOTTOM_BAR]->draw(Rect(), game.bottom_bar_drect);
    game.images->ui[HOURGLASS]->draw(Rect(), game.hourglass_drect);
    SDL_RenderPresent(game.window->ren);

    SDL_RaiseWindow(game.window->win);

    SDL_Event event;
    bool quit = false;

    while(!quit)
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
                        game.heroes[0]->set_current_movement_points(game.heroes[0]->get_max_movement_points());

                        if(game.destination_present)
                        {
                            game.images->ui[DESTINATION]->draw(Rect(), game.out_of_movement_points_drect);
                            SDL_RenderPresent(game.window->ren);
                            game.destination_present = false;
                        }
                        game.game_time.next_day();
                        //std::string day_s = IntToString(day);
                        break;
                    }
                    case SDLK_KP_1:
                    {
                        game.heroes[0]->set_direction(SOUTHWEST);
                        break;
                    }
                    case SDLK_KP_2:
                    {
                        game.heroes[0]->set_direction(SOUTH);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        game.heroes[0]->set_direction(SOUTH);
                        break;
                    }
                    case SDLK_KP_3:
                    {
                        game.heroes[0]->set_direction(SOUTHEAST);
                        break;
                    }
                    case SDLK_KP_4:
                    {
                        game.heroes[0]->set_direction(WEST);
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        game.heroes[0]->set_direction(WEST);
                        break;
                    }
                    case SDLK_KP_6:
                    {
                        game.heroes[0]->set_direction(EAST);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        game.heroes[0]->set_direction(EAST);
                        break;
                    }
                    case SDLK_KP_7:
                    {
                        game.heroes[0]->set_direction(NORTHWEST);
                        break;
                    }
                    case SDLK_KP_8:
                    {
                        game.heroes[0]->set_direction(NORTH);
                        break;
                    }
                    case SDLK_UP:
                    {
                        game.heroes[0]->set_direction(NORTH);
                        break;
                    }
                    case SDLK_KP_9:
                    {
                        game.heroes[0]->set_direction(NORTHEAST);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }

        if(game.heroes[0]->get_direction() != NO_DIRECTION)
        {
            if(game.heroes[0]->move())
            {
                draw_land(game);
                game.images->hero_images[game.heroes[0]->get_direction()]->draw(Rect(), game.hero_drect);
                game.destination_present = false;
                game.heroes[0]->set_direction(NO_DIRECTION);
            }
            else
            {
                draw_land(game);
                game.images->hero_images[game.heroes[0]->get_direction()]->draw(Rect(), game.hero_drect);
                game.out_of_movement_points_drect = {Pos(470, 330), 20, 20};
                game.images->ui[NO_MOVEMENT_POINTS]->draw(Rect(), game.out_of_movement_points_drect);
                game.destination_present = true;
                game.heroes[0]->set_direction(NO_DIRECTION);
            }
        }

        SDL_RenderPresent(game.window->ren);

        // Miegam nurodytą skaičių milisekundžių; 60 fps
        SDL_Delay(1000 / 60);
    }
    SDL_Quit();
    return 0;
}

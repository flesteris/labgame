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
#include "instance.hpp"
#include "date.hpp"

int main(int argc, char** argv)
{
    Game game;

    draw_land(game);
    game.images->hero_images[EAST].draw(game.ren, Rect(), game.hero_drect);
    game.images->ui[RIGHT_PANEL].draw(game.ren, Rect(), game.right_panel_drect);
    game.images->ui[BOTTOM_BAR].draw(game.ren, Rect(), game.bottom_bar_drect);
    game.images->ui[HOURGLASS].draw(game.ren, Rect(), game.hourglass_drect);
    SDL_RenderPresent(game.ren);


    // Gaunam klavietūros būseną (t.y. kurie klavišai paspausti)
    const auto state = SDL_GetKeyboardState(NULL);

    SDL_RaiseWindow(game.win);

    while(true)
    {
        // Atnaujinam state masyvą
        SDL_PumpEvents();

        if(state[SDL_SCANCODE_Q])
        {
            break;
        }

        if(state[SDL_SCANCODE_E])
        {
            game.heroes[0]->set_current_movement_points(game.heroes[0]->get_max_movement_points());

            if(game.destination_present)
            {
                game.images->ui[DESTINATION].draw(game.ren, Rect(), game.out_of_movement_points_drect);
                SDL_RenderPresent(game.ren);
                game.destination_present = false;
            }
            game.date.next();

            SDL_Delay(100);
            //std::string day_s = IntToString(day);
        }

        if(state[SDL_SCANCODE_KP_1])
        {
            game.heroes[0]->set_m_direction(SOUTHWEST);
        }

        if(state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_KP_2])
        {
            game.heroes[0]->set_m_direction(SOUTH);
        }

        if(state[SDL_SCANCODE_KP_3])
        {
            game.heroes[0]->set_m_direction(SOUTHEAST);
        }

        if(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_KP_4])
        {
            game.heroes[0]->set_m_direction(WEST);
        }

        if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_KP_6])
        {
            game.heroes[0]->set_m_direction(EAST);
        }

        if(state[SDL_SCANCODE_KP_7])
        {
            game.heroes[0]->set_m_direction(NORTHWEST);
        }

        if(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_KP_8])
        {
            game.heroes[0]->set_m_direction(NORTH);
        }

        if(state[SDL_SCANCODE_KP_9])
        {
            game.heroes[0]->set_m_direction(NORTHEAST);
        }

        if(game.heroes[0]->get_m_direction() != NO_DIRECTION)
        {
            if(game.heroes[0]->move(game))
            {
                game.destination_present = false;
                SDL_Delay(100);
            }
            else
            {
                draw_land(game);
                game.images->hero_images[game.heroes[0]->get_m_direction()].draw(game.ren, Rect(), game.hero_drect);
                game.out_of_movement_points_drect = {470, 330, 20, 20};
                game.images->ui[NO_MOVEMENT_POINTS].draw(game.ren, Rect(), game.out_of_movement_points_drect);
                game.destination_present = true;
                game.heroes[0]->set_m_direction(NO_DIRECTION);
            }
        }

        SDL_RenderPresent(game.ren);

        // Miegam nurodytą skaičių milisekundžių; 60 fps
        SDL_Delay(1000 / 60);
    }
    return 0;
}

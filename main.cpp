// Kad sukompiliuoti per terminalą:
// g++ sdl.cpp -lSDL2
// SDL2 turi būti instaliuota, kad šitas veiktų

#include <SDL.h>
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
    //Game game;

    std::vector<Hero*> heroes;
    int x, y;

    std::cout << "Enter starting coordinates(0-71 0-71): ";
    std::cin >> x >> y;
    if(x < 0 || x > 71 || y < 0 || y > 71)
    {
        std::cout << "Incorrect coordinates. Loading default coordinates." << std::endl;
        heroes.push_back(new Hero());
    }
    else
    {
        int max_movement_points;
        std::cout << "Enter hero's max movement points(1-50): ";
        std::cin >> max_movement_points;
        if(max_movement_points < 1 || max_movement_points > 50)
        {
            std::cout << "Incorrect hero's max movement points. Loading default movement points(10)." << std::endl;
            heroes.push_back(new Hero(x, y, 10));
        }
        heroes.push_back(new Hero(x, y, max_movement_points));
    }

    // Inicijuojamas video rėžimas
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        for (int i = 0; i < (int)heroes.size(); i++)
        {
            delete heroes[i];
        }
        heroes.clear();
        return 1;
    }

    // Sukuriamas tuščias langas
    SDL_Window* win = SDL_CreateWindow("Spicy boi", 320, 180, 1280, 720, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        for (int i = 0; i < (int)heroes.size(); i++)
        {
            delete heroes[i];
        }
        heroes.clear();
        return 1;
    }

    // Sukuriamas "piešėjas", kuris susietas su prieš tai sukurtu langu
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        for (int i = 0; i < (int)heroes.size(); i++)
        {
            delete heroes[i];
        }
        heroes.clear();
        return 1;
    }

    Map map;
    if (!map.load_map_data("maps//map_1_data.txt"))
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        for (int i = 0; i < (int)heroes.size(); i++)
        {
            delete heroes[i];
        }
        heroes.clear();
        return 1;
    }

    int destination_present = 0;

    Images images(ren);
    images.load_images();

    Rect hero_drect = {460, 320, 40, 40};
    Rect right_panel_drect = {960, 0, 320, 680};
    Rect bottom_bar_drect = {0, 680, 1280, 40};
    Rect hourglass_drect = {1070, 540, 100, 100};
    Rect out_of_movement_points_drect;

    draw_land(heroes[0]->get_x(), heroes[0]->get_y(), map, images, ren);
    images.hero_images[EAST].draw(ren, Rect(), hero_drect);
    images.ui[RIGHT_PANEL].draw(ren, Rect(), right_panel_drect);
    images.ui[BOTTOM_BAR].draw(ren, Rect(), bottom_bar_drect);
    images.ui[HOURGLASS].draw(ren, Rect(), hourglass_drect);
    SDL_RenderPresent(ren);

    Date date;

    // Gaunam klavietūros būseną (t.y. kurie klavišai paspausti)
    const auto state = SDL_GetKeyboardState(NULL);

    SDL_RaiseWindow(win);

    while(true)
    {
        // Atnaujinam state masyvą
        SDL_PumpEvents();

        /*if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_Log("Mouse Button 1 (left) is pressed.");
        }*/

        if(state[SDL_SCANCODE_Q])
        {
            break;
        }

        if(state[SDL_SCANCODE_E])
        {
            heroes[0]->set_current_movement_points(heroes[0]->get_max_movement_points());

            if(destination_present == 1)
            {
                images.ui[DESTINATION].draw(ren, Rect(), out_of_movement_points_drect);
                SDL_RenderPresent(ren);
                destination_present = 0;
            }
            date.next();

            SDL_Delay(100);
            //std::string day_s = IntToString(day);
        }

        if(state[SDL_SCANCODE_KP_1])
        {
            heroes[0]->set_m_direction(SOUTHWEST);
        }

        if(state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_KP_2])
        {
            heroes[0]->set_m_direction(SOUTH);
        }

        if(state[SDL_SCANCODE_KP_3])
        {
            heroes[0]->set_m_direction(SOUTHEAST);
        }

        if(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_KP_4])
        {
            heroes[0]->set_m_direction(WEST);
        }

        if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_KP_6])
        {
            heroes[0]->set_m_direction(EAST);
        }

        if(state[SDL_SCANCODE_KP_7])
        {
            heroes[0]->set_m_direction(NORTHWEST);
        }

        if(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_KP_8])
        {
            heroes[0]->set_m_direction(NORTH);
        }

        if(state[SDL_SCANCODE_KP_9])
        {
            heroes[0]->set_m_direction(NORTHEAST);
        }

        if(heroes[0]->get_m_direction() != NO_DIRECTION)
        {
            if(heroes[0]->move(images, ren, hero_drect, map))
            {
                destination_present = 0;
                SDL_Delay(100);
            }
            else
            {
                draw_land(heroes[0]->get_x(), heroes[0]->get_y(), map, images, ren);
                images.hero_images[heroes[0]->get_m_direction()].draw(ren, Rect(), hero_drect);
                out_of_movement_points_drect = {470, 330, 20, 20};
                images.ui[NO_MOVEMENT_POINTS].draw(ren, Rect(), out_of_movement_points_drect);
                destination_present = 1;
                heroes[0]->set_m_direction(NO_DIRECTION);
            }
        }

        SDL_RenderPresent(ren);

        // Miegam nurodytą skaičių milisekundžių; 60 fps
        SDL_Delay(1000 / 60);
    }

    // Sunaikinam viską, ką sukūrėm
    for (int i = 0; i < (int)heroes.size(); i++)
	{
		delete heroes[i];
	}
	heroes.clear();

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

#include "instance.hpp"
#include <iostream>
#include <SDL2/SDL.h>

Instance::Instance()
{

}

Instance::~Instance()
{

}

int Instance::instantiate(std::vector<Hero*> &heroes, SDL_Window* &win, SDL_Renderer* &ren, Map &map)
{
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
    win = SDL_CreateWindow("Spicy boi", 320, 180, 1280, 720, SDL_WINDOW_SHOWN);
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
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    if (!map.load_map_data("maps//map_1_data.txt"))
    {
        std::cout << "Failed to load map data!  ."<< std::endl;
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
    return 0;
}

void Instance::clear(std::vector<Hero*> &heroes, SDL_Window* &win, SDL_Renderer* &ren, Map &map)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    for (int i = 0; i < (int)heroes.size(); i++)
    {
        delete heroes[i];
    }
    heroes.clear();
}

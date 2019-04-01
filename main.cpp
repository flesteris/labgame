#include <iostream>
#include <SDL2/SDL.h>

#include "game.hpp"

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    Game game;

    while(!game.b_quit)
    {
        game.get_input();
        game.update();
        game.draw();
        SDL_Delay(1000 / 60);
    }

    SDL_Quit();
    return 0;
}

/// medium - norisi scrollinimo greiti reguliuoti arba tiesiog suletinti
/// 'minor' - Piesiama ryskiai uz ribu (manrods) - veliau tvarkyt
/// medium - SDL_PollEvent gali baisiai uzsibufferint

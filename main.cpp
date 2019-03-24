// Kad sukompiliuoti per terminalą:
// g++ sdl.cpp -lSDL2
// SDL2 turi būti instaliuota, kad šitas veiktų

#include <SDL2/SDL.h>
#include <iostream>
#include "game.hpp"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    Game game;

    while(!game.quit)
    {
        game.get_input();
        game.update();
        game.draw();
        SDL_Delay(1000 / 60);
    }

    SDL_Quit();
    return 0;
}

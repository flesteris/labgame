#include <iostream>
#include <SDL2/SDL.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>

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

/// klausimas del auto iteratoriaus (kai reikalingas index i, ar kai pradedama iteruoti nuo 1, o ne nuo 0)
/// klausimas should I SDL_RenderClear(window->ren);
/// klausimas ar return damage(int + int...);?,
/// klausimas ar det const prie Game* game?
/// klausimas ar svarbu padarius koki pakeitima butina istrint overloadintus operatorius

/// future note: make some blur maybe
/// maybe clear some of map memory
/// bug(kinda) galimai stovint istrizai nuo monsterio, kuris taip pat yra uz terraino, bus combat

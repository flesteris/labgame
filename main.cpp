#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

//#include <SDL_image.h>

#include "game.hpp"

void run_game_loop()
{
    Game game;

    while(!game.b_quit)
    {
        game.get_input();
        game.update();
        game.draw();
        SDL_Delay(1000 / 60);
    }
}

int main(int argc, char** argv)
{
    try
    {
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw SDL_Init_error();
        }
        if(TTF_Init() == -1)
        {
            SDL_Quit();
            throw TTF_Init_error();
        }

        run_game_loop();

        TTF_Quit();
        SDL_Quit();
        return 0;
    }
    catch(const std::exception &e)
    {
        TTF_Quit();
        SDL_Quit();
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}


/// HERO ARMY MANAGEMENT
/// TOOOOOWN
/// BATTLE RESULTS
/// animacijos
/// mapo remai
/// fog of war
/// music
/// entity colision

/// cursor kai ant pilies
/// ar abu draw boxes naudojami?
/// draw_path() is garbage
/// praplesti path piesimo area
/// nudazyt destination mark raudonai kai fight() bus
/// I should calculate price differently
/// direction type
/// padaryt kad veiktu su dviem heroes
/// smooth vaiksciojimas

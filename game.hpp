#ifndef GAME_HPP
#define GAME_HPP

#include "instance.hpp"
#include "images.hpp"
#include "hero.hpp"
#include "map.hpp"
#include <vector>

class Game
{
private:

public:
    //std::vector<Hero*> heroes;
    SDL_Window* win;
    SDL_Renderer* ren;
    Map map;

    //Instance instance(std::vector<Hero*> &heroes, SDL_Window* win, SDL_Renderer* ren, Map &map);

    Game();
    ~Game();
};

#endif

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <vector>
#include "hero.hpp"
#include "map.hpp"

class Game;
class Hero;
class Instance
{
private:

public:
    //Game* game;


    Instance();
    ~Instance();

    int instantiate(std::vector<Hero*> &heroes, SDL_Window* &win, SDL_Renderer* &ren, Map &map);
    void clear(std::vector<Hero*> &heroes, SDL_Window* &win, SDL_Renderer* &ren, Map &map);
};

#endif

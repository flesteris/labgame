#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "instance.hpp"
#include "images.hpp"
#include "hero.hpp"
#include "map.hpp"
#include "date.hpp"

class Hero;
class Instance;
class Images;

class Game
{
private:

public:
    Rect hero_drect = {460, 320, 40, 40};
    Rect right_panel_drect = {960, 0, 320, 680};
    Rect bottom_bar_drect = {0, 680, 1280, 40};
    Rect hourglass_drect = {1070, 540, 100, 100};
    Rect out_of_movement_points_drect;
    bool destination_present = false;

    std::vector<Hero*> heroes;
    SDL_Window* win;
    SDL_Renderer* ren;
    Map map;
    Instance* instance;
    Images* images;
    Date date;

    Game();
    ~Game();
};

#endif

#include "game.hpp"

Game::Game()
{
    instance->instantiate(heroes, win, ren, map);
    images = new Images(ren);
    images->load_images();
}

Game::~Game()
{
    instance->clear(heroes, win, ren, map);
    delete images;
    std::cout << "Memory cleared";
}

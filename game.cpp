#include "game.hpp"

Game::Game()
{
    set_options();
    window = new Window();
    images = new Images(this);
    load_map();
}

Game::~Game()
{
    delete window;
    delete images;
    std::cout << "Memory cleared! ...";
}

void Game::set_options()
{
    int x, y;

    std::cout << "Enter starting coordinates(0-71 0-71): ";
    std::cin >> x >> y;
    if(x < 0 || x > 71 || y < 0 || y > 71)
    {
        std::cout << "Incorrect coordinates. Loading default coordinates." << std::endl;
        heroes.push_back(new Hero(this));
    }
    else
    {
        int max_movement_points;
        std::cout << "Enter hero's max movement points(1-50): ";
        std::cin >> max_movement_points;
        if(max_movement_points < 1 || max_movement_points > 50)
        {
            std::cout << "Incorrect hero's max movement points. Loading default movement points(10)." << std::endl;
            heroes.push_back(new Hero(this, x, y, 10));
        }
        heroes.push_back(new Hero(this, x, y, max_movement_points));
    }
}

void Game::load_map()
{
    if (!map.load_map_data("maps//map_1_data.txt"))
    {
        std::cout << "Failed to load map data!  ..."<< std::endl;
        for (int i = 0; i < (int)heroes.size(); i++)
        {
            delete heroes[i];
        }
        heroes.clear();
    }
}

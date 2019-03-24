#include "game.hpp"

Game::Game()
{
    map.load_map_data("maps//map_1_data.txt");
    set_options();
    window = new Window();
    images = new Images(this);
}

Game::~Game()
{
    delete window;
    delete images;
    std::cout << "Memory cleared! ...";
}

void Game::set_options()
{
    Pos pos;

    std::cout << "Enter starting coordinates(0-" << map.w - 1 << " 0-" << map.h - 1 << "): ";
    std::cin >> pos.x >> pos.y;
    if(pos.x < 0 || pos.x > map.w - 1 || pos.y < 0 || pos.y > map.h - 1)
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
            heroes.push_back(new Hero(this, pos, 10));
        }
        heroes.push_back(new Hero(this, pos, max_movement_points));
    }
}


void draw_land(Game &game)
{
    Rect tile_drect, tile_srect;
    for(int i = game.heroes[0]->get_pos_x() - 11, k = 0; i < game.heroes[0]->get_pos_x() + 12; i++, k++)
    {
        if(i < 0 || i > game.map.h)
        {
            for(int j = game.heroes[0]->get_pos_y() - 8, l = 0; j < game.heroes[0]->get_pos_y() + 9; j++, l++)
            {
                tile_drect = {Pos(k*40 + 20, l*40), 40, 40};
                game.images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = game.heroes[0]->get_pos_y() - 8, l = 0; j < game.heroes[0]->get_pos_y() + 9; j++, l++)
            {
                if(j < 0 || j > game.map.w)
                {
                    tile_drect = {Pos(k*40 + 20, l*40), 40, 40};
                    game.images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
                }
                else
                {
                    tile_drect = {Pos(k*40 + 20, l*40), 40, 40};
                    game.images->tiles[game.map.tiles[i+j*game.map.w] - 1]->draw(Rect(), tile_drect);
                }
            }
        }
    }

    for(int i = game.heroes[0]->get_pos_x() - 12, k = 0; k < 1; i++, k++)
    {
        if(i < 0)
        {
            for(int j = game.heroes[0]->get_pos_y() - 8, l = 0; j < game.heroes[0]->get_pos_y() + 9; j++, l++)
            {
                tile_srect = {Pos(20, 0), 20, 40};
                tile_drect = {Pos(0*40, l*40), 20, 40};
                game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
            }
        }
        else
        {
            for(int j = game.heroes[0]->get_pos_y() - 8, l = 0; j < game.heroes[0]->get_pos_y() + 9; j++, l++)
            {
                if(j < 0 || j > game.map.w)
                {
                    tile_srect = {Pos(20, 0), 20, 40};
                    tile_drect = {Pos(0*40, l*40), 20, 40};
                    game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
                }
                else
                {
                    tile_srect = {Pos(20, 0), 20, 40};
                    tile_drect = {Pos(0*40, l*40), 20, 40};
                    game.images->tiles[game.map.tiles[i+j*game.map.w] - 1]->draw(tile_srect, tile_drect);
                }
            }
        }
    }

    for(int i = game.heroes[0]->get_pos_x() + 12, k = 0; k < 1; i++, k++)
    {
        if(i > game.map.h)
        {
            for(int j = game.heroes[0]->get_pos_y() - 8, l = 0; j < game.heroes[0]->get_pos_y() + 9; j++, l++)
            {
                tile_srect = {Pos(0, 0), 20, 40};
                tile_drect = {Pos(24*40 - 20, l*40), 20, 40};
                game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
            }
        }
        else
        {
            for(int j = game.heroes[0]->get_pos_y() - 8, l = 0; j < game.heroes[0]->get_pos_y() + 9; j++, l++)
            {
                if(j < 0 || j > game.map.w)
                {
                    tile_srect = {Pos(0, 0), 20, 40};
                    tile_drect = {Pos(24*40 - 20, l*40), 20, 40};
                    game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
                }
                else
                {
                    tile_srect = {Pos(0, 0), 20, 40};
                    tile_drect = {Pos(24*40 - 20, l*40), 20, 40};
                    game.images->tiles[game.map.tiles[i+j*game.map.w] - 1]->draw(tile_srect, tile_drect);
                }
            }
        }
    }
}

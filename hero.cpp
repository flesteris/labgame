#include "hero.hpp"

Hero::Hero(Game* game) : m_x(0), m_y(0), m_max_movement_points(10), m_current_movement_points(10), m_direction(NO_DIRECTION)
{

}

Hero::Hero(Game* game, int x, int y, int max_movement_points) : m_x(x), m_y(y), m_max_movement_points(max_movement_points), m_current_movement_points(max_movement_points), m_direction(NO_DIRECTION)
{

}

Hero::~Hero()
{

}

int Hero::move()
{
    if(m_current_movement_points == 0)
    {
        return 0;
    }

    switch(m_direction)
    {
    case SOUTHWEST:
        {
            if(m_x == 0 || m_y == 71)
            {
                return -1;
            }
            m_x -= 1;
            m_y += 1;
            break;
        }
    case SOUTH:
        {
            if(m_y == 71)
            {
                return -1;
            }
            m_y += 1;
            break;
        }
    case SOUTHEAST:
        {
            if(m_x == 71 || m_y == 71)
            {
                return -1;
            }
            m_x += 1;
            m_y += 1;
            break;
        }
    case EAST:
        {
            if(m_x == 71)
            {
                return -1;
            }
            m_x += 1;
            break;
        }
    case NORTHEAST:
        {
            if(m_x == 71 || m_y == 0)
            {
                return -1;
            }
            m_x += 1;
            m_y -= 1;
            break;
        }
    case NORTH:
        {
            if(m_y == 0)
            {
                return -1;
            }
            m_y -= 1;
            break;
        }
    case NORTHWEST:
        {
            if(m_y == 0 || m_x == 0)
            {
                return -1;
            }
            m_x -= 1;
            m_y -= 1;
            break;
        }
    case WEST:
        {
            if(m_x == 0)
            {
                return -1;
            }
            m_x -= 1;
            break;
        }
    default:
        {
            break;
        }
    }

    m_current_movement_points--;
    //draw_land(game);
    //game->images->hero_images[m_direction]->draw(game->ren, Rect(), game->hero_drect);
    m_direction = NO_DIRECTION;
    return 1;
}

void draw_land(Game &game)
{
    Rect tile_drect, tile_srect;
    for(int i = game.heroes[0]->get_x() - 11, k = 0; i < game.heroes[0]->get_x() + 12; i++, k++)
    {
        if(i < 0 || i > 71)
        {
            for(int j = game.heroes[0]->get_y() - 8, l = 0; j < game.heroes[0]->get_y() + 9; j++, l++)
            {
                tile_drect = {k*40 + 20, l*40, 40, 40};
                game.images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = game.heroes[0]->get_y() - 8, l = 0; j < game.heroes[0]->get_y() + 9; j++, l++)
            {
                if(j < 0 || j > 71)
                {
                    tile_drect = {k*40 + 20, l*40, 40, 40};
                    game.images->tiles[OFF_MAP_TILE]->draw(Rect(), tile_drect);
                }
                else
                {
                    tile_drect = {k*40 + 20, l*40, 40, 40};
                    game.images->tiles[game.map.tiles[i][j] - 1]->draw(Rect(), tile_drect);
                }
            }
        }
    }

    for(int i = game.heroes[0]->get_x() - 12, k = 0; k < 1; i++, k++)
    {
        if(i < 0)
        {
            for(int j = game.heroes[0]->get_y() - 8, l = 0; j < game.heroes[0]->get_y() + 9; j++, l++)
            {
                tile_srect = {20, 0, 20, 40};
                tile_drect = {0*40, l*40, 20, 40};
                game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
            }
        }
        else
        {
            for(int j = game.heroes[0]->get_y() - 8, l = 0; j < game.heroes[0]->get_y() + 9; j++, l++)
            {
                if(j < 0 || j > 71)
                {
                    tile_srect = {20, 0, 20, 40};
                    tile_drect = {0*40, l*40, 20, 40};
                    game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
                }
                else
                {
                    tile_srect = {20, 0, 20, 40};
                    tile_drect = {0*40, l*40, 20, 40};
                    game.images->tiles[game.map.tiles[i][j] - 1]->draw(tile_srect, tile_drect);
                }
            }
        }
    }

    for(int i = game.heroes[0]->get_x() + 12, k = 0; k < 1; i++, k++)
    {
        if(i > 71)
        {
            for(int j = game.heroes[0]->get_y() - 8, l = 0; j < game.heroes[0]->get_y() + 9; j++, l++)
            {
                tile_srect = {0, 0, 20, 40};
                tile_drect = {24*40 - 20, l*40, 20, 40};
                game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
            }
        }
        else
        {
            for(int j = game.heroes[0]->get_y() - 8, l = 0; j < game.heroes[0]->get_y() + 9; j++, l++)
            {
                if(j < 0 || j > 71)
                {
                    tile_srect = {0, 0, 20, 40};
                    tile_drect = {24*40 - 20, l*40, 20, 40};
                    game.images->tiles[OFF_MAP_TILE]->draw(tile_srect, tile_drect);
                }
                else
                {
                    tile_srect = {0, 0, 20, 40};
                    tile_drect = {24*40 - 20, l*40, 20, 40};
                    game.images->tiles[game.map.tiles[i][j] - 1]->draw(tile_srect, tile_drect);
                }
            }
        }
    }
}

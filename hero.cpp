#include "hero.hpp"
#include "rect.hpp"

Hero::Hero() : m_x(9), m_y(9), m_max_movement_points(10), m_current_movement_points(10), m_direction(NO_DIRECTION)
{

}

Hero::Hero(int x, int y, int max_movement_points) : m_x(x), m_y(y), m_max_movement_points(max_movement_points), m_current_movement_points(max_movement_points), m_direction(NO_DIRECTION)
{

}

Hero::~Hero()
{

}

int Hero::move(Images &images, SDL_Renderer* ren, Rect &hero_drect, Map &map)
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
    draw_land(m_x, m_y, map, images, ren);
    images.hero_images[m_direction].draw(ren, Rect(), hero_drect);
    m_direction = NO_DIRECTION;
    return 1;
}

void draw_land(int x, int y, Map &map, Images &images, SDL_Renderer* ren)
{
    Rect tile_drect, tile_srect;
    for(int i = x - 11, k = 0; i < x + 12; i++, k++)
    {
        if(i < 0 || i > 71)
        {
            for(int j = y - 8, l = 0; j < y + 9; j++, l++)
            {
                tile_drect = {k*40 + 20, l*40, 40, 40};
                images.tiles[OFF_MAP_TILE].draw(ren, Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = y - 8, l = 0; j < y + 9; j++, l++)
            {
                if(j < 0 || j > 71)
                {
                    tile_drect = {k*40 + 20, l*40, 40, 40};
                    images.tiles[OFF_MAP_TILE].draw(ren, Rect(), tile_drect);
                }
                else
                {
                    tile_drect = {k*40 + 20, l*40, 40, 40};
                    images.tiles[map.tiles[i][j] - 1].draw(ren, Rect(), tile_drect);
                }
            }
        }
    }

    for(int i = x - 12, k = 0; k < 1; i++, k++)
    {
        if(i < 0)
        {
            for(int j = y - 8, l = 0; j < y + 9; j++, l++)
            {
                tile_srect = {20, 0, 20, 40};
                tile_drect = {0*40, l*40, 20, 40};
                images.tiles[OFF_MAP_TILE].draw(ren, Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = y - 8, l = 0; j < y + 9; j++, l++)
            {
                if(j < 0 || j > 71)
                {
                    tile_srect = {20, 0, 20, 40};
                    tile_drect = {0*40, l*40, 20, 40};
                    images.tiles[OFF_MAP_TILE].draw(ren, Rect(), tile_drect);
                }
                else
                {
                    tile_srect = {20, 0, 20, 40};
                    tile_drect = {0*40, l*40, 20, 40};
                    images.tiles[map.tiles[i][j] - 1].draw(ren, Rect(), tile_drect);
                }
            }
        }
    }

    for(int i = x + 12, k = 0; k < 1; i++, k++)
    {
        if(i > 71)
        {
            for(int j = y - 8, l = 0; j < y + 9; j++, l++)
            {
                tile_srect = {0, 0, 20, 40};
                tile_drect = {24*40 - 20, l*40, 20, 40};
                images.tiles[OFF_MAP_TILE].draw(ren, Rect(), tile_drect);
            }
        }
        else
        {
            for(int j = y - 8, l = 0; j < y + 9; j++, l++)
            {
                if(j < 0 || j > 71)
                {
                    tile_srect = {0, 0, 20, 40};
                    tile_drect = {24*40 - 20, l*40, 20, 40};
                    images.tiles[OFF_MAP_TILE].draw(ren, Rect(), tile_drect);
                }
                else
                {
                    tile_srect = {0, 0, 20, 40};
                    tile_drect = {24*40 - 20, l*40, 20, 40};
                    images.tiles[map.tiles[i][j] - 1].draw(ren, Rect(), tile_drect);
                }
            }
        }
    }
}


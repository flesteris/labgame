#include "hero.hpp"

Hero::Hero(Game* game) : game(game), m_pos(0, 0), m_max_movement_points(10), m_current_movement_points(10), m_direction(EAST)
{

}

Hero::Hero(Game* game, Pos &pos, int max_movement_points) : game(game), m_pos(pos), m_max_movement_points(max_movement_points), m_current_movement_points(max_movement_points), m_direction(EAST)
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
            if(m_pos.x == 0 || m_pos.y == game->map.h - 1)
            {
                return -1;
            }
            m_pos.x -= 1;
            m_pos.y += 1;
            break;
        }
    case SOUTH:
        {
            if(m_pos.y == game->map.h - 1)
            {
                return -1;
            }
            m_pos.y += 1;
            break;
        }
    case SOUTHEAST:
        {
            if(m_pos.x == game->map.w - 1 || m_pos.y == game->map.h - 1)
            {
                return -1;
            }
            m_pos.x += 1;
            m_pos.y += 1;
            break;
        }
    case EAST:
        {
            if(m_pos.x == game->map.w - 1)
            {
                return -1;
            }
            m_pos.x += 1;
            break;
        }
    case NORTHEAST:
        {
            if(m_pos.x == game->map.w - 1 || m_pos.y == 0)
            {
                return -1;
            }
            m_pos.x += 1;
            m_pos.y -= 1;
            break;
        }
    case NORTH:
        {
            if(m_pos.y == 0)
            {
                return -1;
            }
            m_pos.y -= 1;
            break;
        }
    case NORTHWEST:
        {
            if(m_pos.y == 0 || m_pos.x == 0)
            {
                return -1;
            }
            m_pos.x -= 1;
            m_pos.y -= 1;
            break;
        }
    case WEST:
        {
            if(m_pos.x == 0)
            {
                return -1;
            }
            m_pos.x -= 1;
            break;
        }
    default:
        {
            break;
        }
    }
    m_current_movement_points--;
    return 1;
}

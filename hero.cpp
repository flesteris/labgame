#include "hero.hpp"

const Pos DIRECTIONS[] = {Pos(-1, 1), Pos(0, 1), Pos(1, 1), Pos(1, 0), Pos(1, -1), Pos(0, -1), Pos(-1, -1), Pos(-1, 0), Pos(0, 0)};

Hero::Hero(Game* game) : game(game), pos_m(0, 0), m_max_movement_points(10), m_current_movement_points(10), m_direction(EAST)
{

}

Hero::Hero(Game* game, Pos &pos, int max_movement_points) : game(game), pos_m(pos), m_max_movement_points(max_movement_points), m_current_movement_points(max_movement_points), m_direction(EAST)
{

}

Hero::~Hero()
{

}

int Hero::move()
{
    if(m_current_movement_points <= 0)
    {
        return 0;
    }
    Pos pos = Pos(pos_m + DIRECTIONS[m_direction]);

    if(pos.is_in_rect(0, 0, game->map.w - 1, game->map.h - 1))
    {
        pos_m = pos;
        game->center_pos_m = pos;
        m_current_movement_points--;
        return 1;
    }
    return 0;
}

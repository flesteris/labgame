#include "hero.hpp"

#include <fstream>

Hero::Hero(Game* game, Pos &pos, int max_movement_points) :
    game(game),
    pos_on_map(pos),
    m_max_movement_points(max_movement_points),
    m_current_movement_points(max_movement_points),
    m_direction(EAST),
    b_hero_moving(false),
    b_destination_present(false),
    b_out_of_movement_points(false)
{
    hero_army.push_back(new Wolf(15));
    hero_army.push_back(new Goblin(15));
    hero_army.push_back(new Snake(20));
    tile_access_map = new TileAccessMap(game, this);
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
    Pos pos = pos_on_map + DIRECTIONS[m_direction];

    if(pos.is_in_rect(0, 0, game->map.w - 1, game->map.h - 1))
    {
        pos_on_map = pos;
        game->center_pos_on_map = pos;
        m_current_movement_points--;
        return 1;
    }
    return 0;
}

void Hero::stop()
{
    b_hero_moving = false;
    tile_access_map->update_maps();
}

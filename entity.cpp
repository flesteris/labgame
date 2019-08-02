#include "entity.hpp"

Entity::Entity(Game* game) :
    game(game),
    pos_on_map(Pos())
{

}

Entity::Entity(Game* game, const Pos &pos_on_map) :
    game(game),
    pos_on_map(pos_on_map)
{

}

Entity::~Entity()
{

}

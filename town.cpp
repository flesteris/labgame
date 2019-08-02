#include "town.hpp"

Town::Town(Game* game, const Pos &pos_on_map) :
    Entity::Entity(game, pos_on_map)
{

}

Town::~Town()
{

}

void Town::draw_entity(const Rect &drect) const
{
    Rect drect_2 = drect.expand(0, 120, 160, 20);
    game->images->town_image->draw(Rect(), drect_2);
}

#include "obstacle.hpp"

Obstacle::Obstacle(Game* game, const Pos &pos_on_map) :
    Entity::Entity(game, pos_on_map)
{

}

Obstacle::~Obstacle()
{

}



Forest1::Forest1(Game* game, const Pos &pos_on_map) :
    Obstacle::Obstacle(game, pos_on_map)
{

}

Forest1::~Forest1()
{

}

void Forest1::draw_entity(const Rect &drect) const
{
    Rect drect_2 = drect.expand(0, 20, 40, 0);
    game->images->obstacle_images[FOREST_1]->draw(Rect(), drect_2);
}



Hills1::Hills1(Game* game, const Pos &pos_on_map) :
    Obstacle::Obstacle(game, pos_on_map)
{

}

Hills1::~Hills1()
{

}

void Hills1::draw_entity(const Rect &drect) const
{
    Rect drect_2 = drect.expand(10, 20, 10, 10);
    game->images->obstacle_images[HILLS_1]->draw(Rect(), drect_2);
}



Hills2::Hills2(Game* game, const Pos &pos_on_map) :
    Obstacle::Obstacle(game, pos_on_map)
{

}

Hills2::~Hills2()
{

}

void Hills2::draw_entity(const Rect &drect) const
{
    Rect drect_2 = drect.expand(10, 20, 10, 10);
    game->images->obstacle_images[HILLS_2]->draw(Rect(), drect_2);
}

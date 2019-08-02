#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "pos.hpp"

class Game;

class Entity
{
protected:
    Game* game;

public:
    Pos pos_on_map;

    Entity(Game* game);
    Entity(Game* game, const Pos &pos_on_map);
    virtual ~Entity();

    virtual void draw_entity(const Rect &drect) const = 0;
};

#endif // ENTITY_HPP

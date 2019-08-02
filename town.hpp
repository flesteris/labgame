#ifndef TOWN_HPP
#define TOWN_HPP

#include "entity.hpp"
#include "game.hpp"
#include "pos.hpp"

class Town : public Entity
{
public:

    Town(Game* game, const Pos &pos_on_map);
    ~Town();

    void draw_entity(const Rect &drect) const;
};

#endif // TOWN_HPP

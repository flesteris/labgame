#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "entity.hpp"
#include "game.hpp"

class Game;

class Obstacle : public Entity
{
public:
    Obstacle(Game* game, const Pos &pos_on_map);
    ~Obstacle();
};

class Forest1 : public Obstacle
{
public:
    Forest1(Game* game, const Pos &pos_on_map);
    ~Forest1();

    void draw_entity(const Rect &drect) const;
};

class Hills1 : public Obstacle
{
public:
    Hills1(Game* game, const Pos &pos_on_map);
    ~Hills1();

    void draw_entity(const Rect &drect) const;
};

class Hills2 : public Obstacle
{
public:
    Hills2(Game* game, const Pos &pos_on_map);
    ~Hills2();

    void draw_entity(const Rect &drect) const;
};

#endif // OBSTACLE_HPP

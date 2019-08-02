#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "entity.hpp"
#include "game.hpp"

class Game;

class Resource : public Entity
{
protected:
    int amount;

public:
    Resource(Game* game, const Pos &pos_on_map, int amount);
    ~Resource();

    void set_amount(int amount_) {amount = amount_;}
    int get_amount() {return amount;}
};

class Gold : public Resource
{
public:
    Gold(Game* game, const Pos &pos_on_map, int amount);
    ~Gold();

    void draw_entity(const Rect &drect) const;
};

class MercuryCrystal : public Resource
{
public:
    MercuryCrystal(Game* game, const Pos &pos_on_map, int amount);
    ~MercuryCrystal();

    void draw_entity(const Rect &drect) const;
};

class SulphurCrystal : public Resource
{
public:
    SulphurCrystal(Game* game, const Pos &pos_on_map, int amount);
    ~SulphurCrystal();

    void draw_entity(const Rect &drect) const;
};

class LightningCrystal : public Resource
{
public:
    LightningCrystal(Game* game, const Pos &pos_on_map, int amount);
    ~LightningCrystal();

    void draw_entity(const Rect &drect) const;
};

#endif // RESOURCE_HPP

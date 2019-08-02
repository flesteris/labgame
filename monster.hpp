#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <time.h>

#include "entity.hpp"
#include "game.hpp"
#include "hero.hpp"
#include "pos.hpp"
#include "rect.hpp"

typedef int damage;

class Entity;
class Hero;
class Game;

class Monster : public Entity
{
protected:
    int count;
    int attack_value;
    int defense_value;
    int current_hp;
    int max_hp;
    int health_pool;

public:
    bool b_retaliated;
    static int object_count;

    Monster(Game* game, int count, int attack_value, int defense_value, int max_hp);
    Monster(Game* game, const Pos &pos_on_map, int count, int attack_value, int defense_value, int max_hp);
    Monster(const Monster &other);
    virtual ~Monster();

    virtual int get_defense_value() const;
    virtual int get_count() const;

    virtual damage attack() const = 0;
    virtual bool defend(damage incoming_damage) = 0;
    virtual int retaliate() = 0;
    virtual void retaliate_reset() = 0;
    virtual std::string name() const = 0;

    static int get_object_count() {return object_count;}

    friend bool fight(Hero* hero, Monster* monster);
};

class Wolf : public Monster
{
public:
    Wolf(Game* game, int count_);
    Wolf(Game* game, const Pos &pos_on_map, int count_);
    ~Wolf();

    damage attack() const;
    bool defend(damage incoming_damage);
    int retaliate();
    void retaliate_reset();
    std::string name() const;
    void draw_entity(const Rect &drect) const;
};

class Goblin : public Monster
{
public:
    Goblin(Game* game, int count_);
    Goblin(Game* game, const Pos &pos_on_map, int count_);
    ~Goblin();

    damage attack() const;
    bool defend(damage incoming_damage);
    int retaliate();
    void retaliate_reset();
    std::string name() const;
    void draw_entity(const Rect &drect) const;
};

class Snake : public Monster
{
public:
    Snake(Game* game, int count_);
    Snake(Game* game, const Pos &pos_on_map, int count_);
    ~Snake();

    damage attack() const;
    bool defend(damage incoming_damage);
    int retaliate();
    void retaliate_reset();
    std::string name() const;
    void draw_entity(const Rect &drect) const;
};

#endif // MONSTER_HPP

#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <time.h>

#include "pos.hpp"
#include "rect.hpp"

class Monster
{
protected:
    int count;
    int attack_value;
    int defense_value;
    int current_hp;
    int max_hp;
    int health_pool;
    bool b_retaliated = false;

public:
    Pos pos_m;
    Pos pos;
    Rect drect;

    Monster(int count, int attack_value, int defense_value, int max_hp);
    Monster(int x, int y, int count, int attack_value, int defense_value, int max_hp);
    virtual ~Monster();

    virtual int get_defense_value();
    virtual int get_count();

    virtual void talk() = 0;
    virtual int attack() = 0;
    virtual bool defend(int damage) = 0;
    virtual int retaliate() = 0;
    virtual void retaliate_reset() = 0;
    virtual std::string name() = 0;
};

class Wolf : public Monster
{
public:
    Wolf(int count_);
    Wolf(int x, int y, int count_);
    ~Wolf();

    void talk();
    int attack();
    bool defend(int damage);
    int retaliate();
    void retaliate_reset();
    std::string name();
};

class Goblin : public Monster
{
public:
    Goblin(int count_);
    Goblin(int x, int y, int count_);
    ~Goblin();

    void talk();
    int attack();
    bool defend(int damage);
    int retaliate();
    void retaliate_reset();
    std::string name();
};

class Snake : public Monster
{
public:
    Snake(int count_);
    Snake(int x, int y, int count_);
    ~Snake();

    void talk();
    int attack();
    bool defend(int damage);
    int retaliate();
    void retaliate_reset();
    std::string name();
};

#endif // MONSTER_HPP

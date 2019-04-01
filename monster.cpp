#include "monster.hpp"

Monster::Monster(int count, int attack_value, int defense_value, int max_hp) : count(count), attack_value(attack_value), defense_value(defense_value), current_hp(max_hp), max_hp(max_hp), health_pool(max_hp * count)
{

}

Monster::Monster(int x, int y, int count, int attack_value, int defense_value, int max_hp) : count(count), attack_value(attack_value), defense_value(defense_value), current_hp(max_hp), max_hp(max_hp), pos_m(Pos(x, y)), health_pool(max_hp * count)
{

}

Monster::~Monster()
{

}

int Monster::get_defense_value()
{
    return defense_value;
}

int Monster::get_count()
{
    return count;
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////

Wolf::Wolf(int count_) : Monster::Monster(count_, 4, 1, 7)
{

}

Wolf::Wolf(int x, int y, int count_) : Monster::Monster(x, y, count_, 4, 1, 7)
{

}

Wolf::~Wolf()
{
    talk();
}

void Wolf::talk()
{
    std::cout << "Woof" << std::endl;
}

int Wolf::attack()
{
    srand(time(NULL));
    int num = (rand() % 3); // 33% chance to deal 150% damage
    if(!num)
    {
        std::cout << "wolf dealt 50% more damage!" << std::endl;
        return attack_value * count * 3 / 2;
    }
    return attack_value * count;
}

bool Wolf::defend(int damage)
{
    int incoming_damage;
    if(defense_value)
    {
        incoming_damage = damage / defense_value;
    }
    else
    {
        incoming_damage = damage;
    }

    std::cout << "wolf got hit by " << incoming_damage << " damage!" << std::endl;
    health_pool -= incoming_damage;
    if(health_pool <= 0)
    {
        std::cout << "Wolf has perished!" << std::endl;
        return false;
    }
    else
    {
        if(!(health_pool % max_hp))
        {
            count = health_pool / max_hp;
            current_hp = max_hp;
        }
        else
        {
            count = health_pool / max_hp + 1;
            current_hp = health_pool % max_hp;
        }
        std::cout << "Wolf count left: " << count << std::endl;
        return true;
    }
}

int Wolf::retaliate()
{
    if(!b_retaliated)
    {
        b_retaliated = true;
        return attack();
    }
    else
    {
        return 0;
    }
}

void Wolf::retaliate_reset()
{
    b_retaliated = false;
}

std::string Wolf::name()
{
    return "wolf";
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////

Goblin::Goblin(int count_) : Monster::Monster(count_, 2, 2, 10)
{

}

Goblin::Goblin(int x, int y, int count_) : Monster::Monster(x, y, count_, 2, 2, 10)
{

}

Goblin::~Goblin()
{
    talk();
}

void Goblin::talk()
{
    std::cout << "Meow" << std::endl;
}

int Goblin::attack()
{
    return attack_value * count;
}

bool Goblin::defend(int damage)
{
    int incoming_damage;
    if(defense_value)
    {
        incoming_damage = damage / defense_value;
    }
    else
    {
        incoming_damage = damage;
    }
    std::cout << "goblin got hit by " << incoming_damage << " damage!" << std::endl;
    health_pool -= incoming_damage;
    if(health_pool <= 0)
    {
        std::cout << "Goblin has perished!" << std::endl;
        return false;
    }
    else
    {
        if(!(health_pool % max_hp))
        {
            count = health_pool / max_hp;
            current_hp = max_hp;
        }
        else
        {
            count = health_pool / max_hp + 1;
            current_hp = health_pool % max_hp;
        }
        std::cout << "Goblin count left: " << count << std::endl;
        return true;
    }
}

int Goblin::retaliate()
{
    return attack(); // Goblin has unlimited retaliations
}

void Goblin::retaliate_reset()
{
    b_retaliated = false;
}

std::string Goblin::name()
{
    return "goblin";
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////

Snake::Snake(int count_) : Monster::Monster(count_, 5, 1, 3)
{

}

Snake::Snake(int x, int y, int count_) : Monster::Monster(x, y, count_, 5, 1, 3)
{

}

Snake::~Snake()
{
    talk();
}

void Snake::talk()
{
    std::cout << "Ssss" << std::endl;
}

int Snake::attack()
{
    return attack_value * count;
}

bool Snake::defend(int damage)
{
    int incoming_damage;

    srand(time(NULL));
    int num = (rand() % 4); // 25% chance to block/evade 50% of the incoming damage
    if(!num)
    {
        if(defense_value)
        {
            incoming_damage = (damage / defense_value) / 2;
        }
        else
        {
            incoming_damage = damage / 2;
        }
        std::cout << "snake evaded 50% of the incoming damage!" << std::endl;
    }
    else
    {
        if(defense_value)
        {
            incoming_damage = damage / defense_value;
        }
        else
        {
            incoming_damage = damage;
        }
    }
    std::cout << "snake got hit by " << incoming_damage << " damage!" << std::endl;
    health_pool -= incoming_damage;

    if(health_pool <= 0)
    {
        std::cout << "Snake has perished!" << std::endl;
        return false;
    }
    else
    {
        if(!(health_pool % max_hp))
        {
            count = health_pool / max_hp;
            current_hp = max_hp;
        }
        else
        {
            count = health_pool / max_hp + 1;
            current_hp = health_pool % max_hp;
        }
        std::cout << "Snake count left: " << count << std::endl;
        return true;
    }
}

int Snake::retaliate()
{
    if(!b_retaliated)
    {
        b_retaliated = true;
        return attack();
    }
    else
    {
        return 0;
    }
}

void Snake::retaliate_reset()
{
    b_retaliated = false;
}

std::string Snake::name()
{
    return "snake";
}

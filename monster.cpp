#include "monster.hpp"

int Monster::object_count = 0;

Monster::Monster(Game* game, int count, int attack_value, int defense_value, int max_hp) :
    Entity::Entity(game),
    count(count),
    attack_value(attack_value),
    defense_value(defense_value),
    current_hp(max_hp),
    max_hp(max_hp),
    health_pool(max_hp * count),
    b_retaliated(false)
{

}

Monster::Monster(Game* game, const Pos &pos_on_map, int count, int attack_value, int defense_value, int max_hp) :
    Entity::Entity(game, pos_on_map),
    count(count),
    attack_value(attack_value),
    defense_value(defense_value),
    current_hp(max_hp),
    max_hp(max_hp),
    health_pool(max_hp * count),
    b_retaliated(false)
{
    object_count++;
}


Monster::Monster(const Monster &other) :
    Entity::Entity(other.game, other.pos_on_map),
    count(other.count),
    attack_value(other.attack_value),
    defense_value(other.defense_value),
    current_hp(other.max_hp),
    max_hp(other.max_hp),
    health_pool(other.max_hp * count),
    b_retaliated(false)
{
    object_count++;
}

Monster::~Monster()
{
    object_count--;
}

int Monster::get_defense_value() const
{
    return defense_value;
}

int Monster::get_count() const
{
    return count;
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////

Wolf::Wolf(Game* game, int count_) :
    Monster::Monster::Monster(game, count_, 4, 1, 7)
{

}

Wolf::Wolf(Game* game, const Pos &pos_on_map, int count_) :
    Monster(game, pos_on_map, count_, 4, 1, 7)
{

}

Wolf::~Wolf()
{

}

damage Wolf::attack() const
{
    srand(time(NULL));
    int num = (rand() % 3); // 33% chance to deal 150% damage
    if(!num)
    {
        //std::cout << "wolf dealt 50% more damage!" << std::endl;
        return attack_value * count * 3 / 2;
    }
    return attack_value * count;
}

bool Wolf::defend(damage incoming_damage)
{
    int received_damage;
    if(defense_value)
    {
        received_damage = incoming_damage / defense_value;
    }
    else
    {
        received_damage = incoming_damage;
    }

    //std::cout << "wolf got hit by " << received_damage << " damage!" << std::endl;
    health_pool -= received_damage;
    if(health_pool <= 0)
    {
        //std::cout << "Wolf has perished!" << std::endl;
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
        //std::cout << "Wolf count left: " << count << std::endl;
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

std::string Wolf::name() const
{
    if(get_count() > 1)
    {
        return "wolves";
    }
    return "wolf";
}

void Wolf::draw_entity(const Rect &drect) const
{
    game->images->monster_images[WOLF]->draw(Rect(), drect);
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////

Goblin::Goblin(Game* game, int count_) :
    Monster::Monster(game, count_, 2, 2, 10)
{

}

Goblin::Goblin(Game* game, const Pos &pos_on_map, int count_) :
    Monster::Monster(game, pos_on_map, count_, 2, 2, 10)
{

}

Goblin::~Goblin()
{

}

damage Goblin::attack() const
{
    return attack_value * count;
}

bool Goblin::defend(damage incoming_damage)
{
    int received_damage;
    if(defense_value)
    {
        received_damage = incoming_damage / defense_value;
    }
    else
    {
        received_damage = incoming_damage;
    }
    //std::cout << "goblin got hit by " << received_damage << " damage!" << std::endl;
    health_pool -= received_damage;
    if(health_pool <= 0)
    {
        //std::cout << "Goblin has perished!" << std::endl;
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
        //std::cout << "Goblin count left: " << count << std::endl;
        return true;
    }
}

int Goblin::retaliate()
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

void Goblin::retaliate_reset()
{
    b_retaliated = false;
}

std::string Goblin::name() const
{
    if(get_count() > 1)
    {
        return "goblins";
    }
    return "goblin";
}

void Goblin::draw_entity(const Rect &drect) const
{
    game->images->monster_images[GOBLIN]->draw(Rect(), drect);
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////

Snake::Snake(Game* game, int count_) :
    Monster::Monster(game, count_, 5, 1, 3)
{

}

Snake::Snake(Game* game, const Pos &pos_on_map, int count_) :
    Monster::Monster(game, pos_on_map, count_, 5, 1, 3)
{

}

Snake::~Snake()
{

}

damage Snake::attack() const
{
    return attack_value * count;
}

bool Snake::defend(damage incoming_damage)
{
    int received_damage;

    srand(time(NULL));
    int num = (rand() % 4); // 25% chance to block/evade 50% of the incoming damage
    if(!num)
    {
        if(defense_value)
        {
            received_damage = (incoming_damage / defense_value) / 2;
        }
        else
        {
            received_damage = incoming_damage / 2;
        }
        //std::cout << "snake evaded 50% of the incoming damage!" << std::endl;
    }
    else
    {
        if(defense_value)
        {
            received_damage = incoming_damage / defense_value;
        }
        else
        {
            received_damage = incoming_damage;
        }
    }
    //std::cout << "snake got hit by " << received_damage << " damage!" << std::endl;
    health_pool -= received_damage;

    if(health_pool <= 0)
    {
        //std::cout << "Snake has perished!" << std::endl;
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
        //std::cout << "Snake count left: " << count << std::endl;
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

std::string Snake::name() const
{
    if(get_count() > 1)
    {
        return "snakes";
    }
    return "snake";
}

void Snake::draw_entity(const Rect &drect) const
{
    game->images->monster_images[SNAKE]->draw(Rect(), drect);
}

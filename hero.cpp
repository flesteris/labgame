#include "hero.hpp"

#include <fstream>

Hero::Hero(Game* game, const Pos &pos_on_map, int max_movement_points) :
    Entity::Entity(game, pos_on_map),
    m_max_movement_points(max_movement_points),
    m_current_movement_points(max_movement_points),
    m_direction(EAST),
    b_alive(true),
    b_hero_moving(false),
    b_destination_present(false),
    b_out_of_movement_points(false)
{
    hero_army = {new Wolf(game, 10),
                 nullptr,
                 new Goblin(game, 2),
                 new Snake(game, 2),
                 nullptr};
}

Hero::~Hero()
{
    game->map->entities[pos_on_map] = nullptr;
    for(auto hero_army_unit : hero_army)
    {
        delete hero_army_unit;
    }
    delete tile_access_map;
}

bool Hero::move()
{
    if(m_current_movement_points <= 0)
    {
        game->notify("Out of movement points");
        return false;
    }
    Pos temp_pos = pos_on_map + DIRECTIONS[m_direction];

    if(temp_pos.is_in_rect(game->map_size_rect))
    {
        Entity* entity = game->map->entities[temp_pos];
        Resource* resource = dynamic_cast<Resource*> (entity);
        if(resource)
        {
            collect_resource(resource);
        }
        else
        {
            Pos monster_pos_on_map = game->map->monster_nearby(temp_pos);
            if(game->map->is_monster(temp_pos))
            {
                if(!initiate_combat(temp_pos))
                {
                    b_alive = false;
                    return false;
                }
                sort_hero_army();
            }
            else if(monster_pos_on_map != temp_pos)
            {
                if(!initiate_combat(monster_pos_on_map))
                {
                    b_alive = false;
                    return false;
                }
                sort_hero_army();
                game->map->move_entity(temp_pos, this);
            }
            else
            {
                game->map->move_entity(temp_pos, this);
            }
        }
        game->focus_hero();
        --m_current_movement_points; /// Fix pricing ///////////////////
        return true;
    }
    return false;
}

bool Hero::initiate_combat(const Pos &monster_pos_on_map)
{
    Entity* entity = game->map->entities[monster_pos_on_map];
    Monster* monster = dynamic_cast<Monster*> (entity);
    if(fight(game, this, monster))
    {
        game->notify("You have won the battle!");
        game->map->entities.erase(monster->pos_on_map);
        delete monster;
        stop();
        game->map->b_zone_of_control_updated = false;
        return true;
    }
    else
    {
        std::stringstream ss;
        ss << "Your hero has died!";
        game->notify(ss.str());
        if(game->player->heroes.size() > 1)
        {
            game->selected_hero = 0;
        }
        else
        {
            ss << " You have lost!";
            game->notify(ss.str());
        }
        return false;
    }
}

void Hero::collect_resource(Resource* resource)
{
    int amount = resource->get_amount();
    Gold* gold = dynamic_cast<Gold*> (resource);
    if(gold)
    {
        game->player->add_gold(amount);
        std::stringstream ss;
        ss << "Obtained " << amount << " gold";
        game->notify(ss.str());
    }
    else
    {
        MercuryCrystal* mercury_crystal = dynamic_cast<MercuryCrystal*> (resource);
        if(mercury_crystal)
        {
            game->player->add_mercury_crystals(amount);
            std::stringstream ss;
            ss << "Obtained " << amount << " mercury crystal";
            game->notify(ss.str());
        }
        else
        {
            SulphurCrystal* sulphur_crystal = dynamic_cast<SulphurCrystal*> (resource);
            if(sulphur_crystal)
            {
                game->player->add_sulphur_crystals(amount);
                std::stringstream ss;
                ss << "Obtained " << amount << " sulphur crystal";
                game->notify(ss.str());
            }
            else
            {
                game->player->add_lightning_crystals(amount);
                std::stringstream ss;
                ss << "Obtained " << amount << " lightning crystal";
                game->notify(ss.str());
            }
        }
    }
    game->map->entities.erase(resource->pos_on_map);
    delete resource;
}

void Hero::sort_hero_army()
{
    /*std::vector<int> myvector (myints, myints+8);
    std::sort(hero_army.begin(), hero_army.end());*/
}

void Hero::stop()
{
    b_hero_moving = false;
    for(auto hero : game->player->heroes)
    {
        hero->tile_access_map->b_updated = false;
    }
}

void Hero::reset_movement_points()
{
    m_current_movement_points = m_max_movement_points;
}

void Hero::draw_entity(const Rect &drect) const
{
    game->images->hero_images[m_direction]->draw(Rect(), drect);
}

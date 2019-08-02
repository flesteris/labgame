#include "resource.hpp"

Resource::Resource(Game* game, const Pos &pos_on_map, int amount) :
    Entity::Entity(game, pos_on_map),
    amount(amount)
{

}

Resource::~Resource()
{

}



Gold::Gold(Game* game, const Pos &pos_on_map, int amount) :
    Resource::Resource(game, pos_on_map, amount)
{

}

Gold::~Gold()
{

}

void Gold::draw_entity(const Rect &drect) const
{
    game->images->resource_images[GOLD]->draw(Rect(), drect);
}



MercuryCrystal::MercuryCrystal(Game* game, const Pos &pos_on_map, int amount) :
    Resource::Resource(game, pos_on_map, amount)
{

}

MercuryCrystal::~MercuryCrystal()
{

}

void MercuryCrystal::draw_entity(const Rect &drect) const
{
    game->images->resource_images[MERCURY_CRYSTAL]->draw(Rect(), drect);
}



SulphurCrystal::SulphurCrystal(Game* game, const Pos &pos_on_map, int amount) :
    Resource::Resource(game, pos_on_map, amount)
{

}

SulphurCrystal::~SulphurCrystal()
{

}

void SulphurCrystal::draw_entity(const Rect &drect) const
{
    game->images->resource_images[SULPHUR_CRYSTAL]->draw(Rect(), drect);
}



LightningCrystal::LightningCrystal(Game* game, const Pos &pos_on_map, int amount) :
    Resource::Resource(game, pos_on_map, amount)
{

}

LightningCrystal::~LightningCrystal()
{

}

void LightningCrystal::draw_entity(const Rect &drect) const
{
    game->images->resource_images[LIGHTNING_CRYSTAL]->draw(Rect(), drect);
}

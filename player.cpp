#include "player.hpp"

Player::Player(Game* game) :
    game(game),
    m_gold(0),
    m_mercury_crystals(0),
    m_sulphur_crystals(0),
    m_lightning_crystals(0)
{

}

Player::~Player()
{
    for(auto hero : heroes)
    {
        delete hero;
    }
}

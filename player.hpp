#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game.hpp"
#include "hero.hpp"

class Player
{
private:
    Game* game;
    int m_gold;
    int m_mercury_crystals;
    int m_sulphur_crystals;
    int m_lightning_crystals;

public:
    std::vector<Hero*> heroes;

    Player(Game* game);
    ~Player();

    void set_gold(int amount) {m_gold = amount;}
    void add_gold(int amount) {m_gold += amount;}
    int get_gold() {return m_gold;}

    void set_mercury_crystals(int amount) {m_mercury_crystals = amount;}
    void add_mercury_crystals(int amount) {m_mercury_crystals += amount;}
    int get_mercury_crystals() {return m_mercury_crystals;}

    void set_sulphur_crystals(int amount) {m_sulphur_crystals = amount;}
    void add_sulphur_crystals(int amount) {m_sulphur_crystals += amount;}
    int get_sulphur_crystals() {return m_sulphur_crystals;}

    void set_lightning_crystals(int amount) {m_lightning_crystals = amount;}
    void add_lightning_crystals(int amount) {m_lightning_crystals += amount;}
    int get_lightning_crystals() {return m_lightning_crystals;}
};

#endif // PLAYER_HPP

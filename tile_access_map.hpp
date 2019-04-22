#ifndef TILE_ACCESS_MAP_HPP
#define TILE_ACCESS_MAP_HPP

#include <vector>

#include "game.hpp"
#include "hero.hpp"
#include "pos.hpp"

class Game;

class TileAccessMap
{
private:
    Game* game;
    Hero* hero;

public:
    std::vector<int> accessible_tile_map;
    std::vector<int> price_map;
    std::vector<Pos*> vector_map;

    std::vector<int> min_values; // used in dijkstra
    std::vector<Pos*> min_pos; // used in dijkstra

    TileAccessMap(Game* game, Hero* hero);
    ~TileAccessMap();

    void create_accessible_tile_map();
    void update_accessible_tile_map();
    void update_tile_access(const Pos &pos);
    void update_tile_access_2(const Pos &pos);
    void update_tile_access_3();
    bool monster_nearby(const Pos &pos) const;
    bool is_monster(int entity) const;

    void set_tile_accessibility(const Pos &pos, int value);
    int get_tile_accessibility(const Pos &pos) const;
    void set_tile_price(const Pos &pos, int value);
    int get_tile_price(const Pos &pos) const;
    void set_tile_vector(const Pos &pos, const Pos &direction);
    Pos get_tile_vector(const Pos &pos) const;

    void dijkstra(const Pos &pos);
    void bring_min_to_front();
};

#endif // TILE_ACCESS_MAP_HPP

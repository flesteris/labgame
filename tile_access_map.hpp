#ifndef TILE_ACCESS_MAP_HPP
#define TILE_ACCESS_MAP_HPP

#include <vector>

#include "game.hpp"
#include "hero.hpp"
#include "pos.hpp"
#include <iomanip>

class Game;

class TileAccessMap
{
private:
    Game* game;
    Hero* hero;

public:
    std::vector<int> access_map;
    std::vector<int> price_map;
    std::vector<int> vector_map;

    std::vector<int> dijkstra_values;
    std::vector<Pos*> dijkstra_pos;

    TileAccessMap(Game* game, Hero* hero);
    ~TileAccessMap();

    void create_maps();
    void reset_maps();
    void update_maps();
    void update_tile_access(const Pos &pos);
    void update_tile_access_2();
    bool monster_nearby(const Pos &pos) const;
    bool is_monster(int entity) const;

    void set_tile_access(const Pos &pos, int value);
    int get_tile_access(const Pos &pos) const;
    void set_tile_price(const Pos &pos, int value);
    int get_tile_price(const Pos &pos) const;
    void set_tile_vector(const Pos &pos, int value);
    int get_tile_vector(const Pos &pos) const;

    void dijkstra(const Pos &pos);
    void bring_min_to_front();
};

#endif // TILE_ACCESS_MAP_HPP

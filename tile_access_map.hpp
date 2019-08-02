#ifndef TILE_ACCESS_MAP_HPP
#define TILE_ACCESS_MAP_HPP

#include <algorithm>
#include <vector>
#include <iomanip>
#include <unordered_map>

#include "game.hpp"
#include "hero.hpp"
#include "matrix.hpp"
#include "pos.hpp"
#include "town.hpp"

enum AccessType
{
    INACCESSABLE = -2,
    NOT_SET = -1,
    MONSTER_NEARBY = 0,
    FREE = 1,
    MONSTER = 2,
    RESOURCE = 3,
    ACCESSABLE_ONLY = 8,
    HERO = 9
};

class Game;
class Hero;

class TileAccessMap
{
private:
    Game* game;
    Hero* hero;

    void update_tile_access();
    void update_tile_access_2(const Pos &pos);
    void update_tile_access_3();
    void set_access_if_town(const Pos &pos);

    void dijkstra(const Pos &pos);
    void dijkstra_2(int price, int price_2, int access, int access_2,
                    int i, const Pos &pos, const Pos &temp_pos);
    void next_min_value();

    void sort_dijkstra_pos_from_end(); // sort almost sorted container (insertion sort last element)
    void sort_dijkstra_pos_from_begining(); // sort almost sorted container (bubble sort one middle element)

    std::vector<Pos*> dijkstra_min_values; // sorted in a decreasing order

public:
    bool b_updated;

    Matrix<int> access_map;
    Matrix<int> price_map;
    Matrix<int> vector_map;

    void print_to_files() const;
    TileAccessMap(Game* game, Hero* hero);
    ~TileAccessMap();

    void create_maps();
    void setup_maps();
    void update_maps();
    void reset_maps();
};

#endif // TILE_ACCESS_MAP_HPP

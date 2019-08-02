#ifndef GAME_TIME_HPP
#define GAME_TIME_HPP

#include <iostream>

class GameTime
{
public:
    int day;
    int week;
    int month;

    GameTime();
    ~GameTime();

    void next_day();
};

#endif

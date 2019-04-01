#ifndef GAME_TIME_HPP
#define GAME_TIME_HPP

#include <iostream>

class GameTime
{
private:
    int day;
    int week;
    int month;

public:
    GameTime();
    ~GameTime();
    void print_date();
    void next_day();
};

#endif

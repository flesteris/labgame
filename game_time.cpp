#include "game_time.hpp"
#include <iostream>

GameTime::GameTime() : day(1), week(1), month(1)
{

}

GameTime::~GameTime()
{

}


void GameTime::next_day()
{
    if(day == 7)
    {
        day = 1;
        if(week == 4)
        {
            week = 1;
            month++;
        }
        else
        {
            week++;
        }
    }
    else
    {
        day++;
    }

    std::cout << "Day " << day << ", Week " << week << ", Month " << month << std::endl;
}

#include "game_time.hpp"

GameTime::GameTime() : day(0), week(1), month(1)
{

}

GameTime::~GameTime()
{

}

void GameTime::print_date()
{
    std::cout << "Day " << day << ", Week " << week << ", Month " << month << std::endl;
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
    print_date();
}

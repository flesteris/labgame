#include "date.hpp"
#include <iostream>

Date::Date() : day(1), week(1), month(1)
{

}

Date::~Date()
{

}


void Date::next()
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

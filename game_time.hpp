#ifndef GAME_TIME_HPP
#define GAME_TIME_HPP

class GameTime
{
private:
    int day;
    int week;
    int month;

public:
    GameTime();
    ~GameTime();
    void next_day();
};

#endif

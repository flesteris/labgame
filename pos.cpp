#include "pos.hpp"

Pos::Pos() : x(0), y(0)
{

}

Pos::Pos(int x, int y) : x(x), y(y)
{

}

Pos Pos:: operator +(const Pos& other) const
{
    return Pos(x + other.x, y + other.y);
}

Pos Pos:: operator -(const Pos& other) const
{
    return Pos(x - other.x, y - other.y);
}

Pos Pos:: operator *(const int &other) const
{
    return Pos(x * other, y * other);
}

bool Pos:: operator ==(const Pos& other) const
{
    return x == other.x && y == other.y;
}

bool Pos:: operator !=(const Pos& other) const
{
    return x != other.x || y != other.y;
}

bool Pos::is_in_rect(Rect &rect)
{
    if(x < rect.pos->x || y < rect.pos->y || x > rect.pos->x + rect.w || y > rect.pos->y + rect.h)
    {
        return false;
    }
    return true;
}

bool Pos::is_in_rect(int uper_left_x, int uper_left_y, int w, int h)
{
    if(x < uper_left_x || y < uper_left_y || x > uper_left_x + w || y > uper_left_y + h)
    {
        return false;
    }
    return true;
}



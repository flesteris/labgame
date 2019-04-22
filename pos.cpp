#include "pos.hpp"

const Pos DIRECTIONS[] = {Pos(-1, 1), Pos(0, 1), Pos(1, 1), Pos(1, 0), Pos(1, -1), Pos(0, -1), Pos(-1, -1), Pos(-1, 0), Pos(0, 0)};

Pos::Pos() : x(0), y(0)
{

}

Pos::Pos(int x, int y) : x(x), y(y)
{

}

Pos Pos::operator +(const Pos &other) const
{
    return Pos(x + other.x, y + other.y);
}

Pos Pos::operator +(int other) const
{
    return Pos(x + other, y + other);
}

Pos &Pos::operator++() // Called for ++Pos
{
    ++x;
    ++y;
    return *this;
}

Pos &Pos::operator +=(const Pos &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Pos Pos::operator -(const Pos &other) const
{
    return Pos(x - other.x, y - other.y);
}

Pos Pos::operator -(int other) const
{
    return Pos(x - other, y - other);
}

Pos &Pos::operator -=(const Pos &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Pos Pos::operator *(const Pos &other) const
{
    return Pos(x * other.x, y * other.y);
}

Pos Pos::operator *(int other) const
{
    return Pos(x * other, y * other);
}

bool Pos::operator ==(const Pos &other) const
{
    return x == other.x && y == other.y;
}

bool Pos::operator !=(const Pos &other) const
{
    return x != other.x || y != other.y;
}

bool Pos::is_in_rect(const Rect &rect) const
{
    if(x < rect.pos->x || y < rect.pos->y || x > rect.w + rect.pos->x || y > rect.h + rect.pos->y)
    {
        return false;
    }
    return true;
}

bool Pos::is_in_rect(const Pos &pos, int w, int h) const
{
    if(x < pos.x || y < pos.y || x > w + pos.x || y > h + pos.y)
    {
        return false;
    }
    return true;
}

bool Pos::is_in_rect(int uper_left_x, int uper_left_y, int w, int h) const
{
    if(x < uper_left_x || y < uper_left_y || x > w + uper_left_x || y > h + uper_left_y)
    {
        return false;
    }
    return true;
}

void Pos::fit_in_rect(const Rect &rect)
{
    if(x < rect.pos->x)
    {
        x = rect.pos->x;
    }
    else if(x > rect.w + rect.pos->x)
    {
        x = rect.w + rect.pos->x;
    }
    if(y < rect.pos->y)
    {
        y = rect.pos->y;
    }
    else if(y > rect.h + rect.pos->y)
    {
        y = rect.h + rect.pos->y;
    }
}

void Pos::print_coordinates() const /// Just a test helper
{
    std::cout << "x: " << x << ", y: " << y << "." << std::endl;
}

//static Pos Pos::from_direction(Direction dir);

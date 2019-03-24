#include "pos.hpp"

Pos::Pos() : x(0), y(0)
{

}

Pos::Pos(int x, int y) : x(x), y(y)
{

}

bool Pos::is_in_rect(int uper_left_x, int uper_left_y, int w, int h)
{
    if(x < uper_left_x || y < uper_left_y || x > uper_left_x + w || y > uper_left_y + h)
    {
        return false;
    }
    return true;
}

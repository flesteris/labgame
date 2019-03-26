#ifndef POS_HPP
#define POS_HPP

#include "rect.hpp"

class Rect;

class Pos
{
private:

public:
    int x;
    int y;

    Pos();
    Pos(int x, int y);
    Pos operator +(const Pos &other) const;
    Pos operator -(const Pos &other) const;
    Pos operator *(const int &other) const;
    bool operator ==(const Pos &other) const;
    bool operator !=(const Pos &other) const;
    bool is_in_rect(Rect &rect);
    bool is_in_rect(int uper_left_x, int uper_left_y, int w, int h);
};

#endif // POS_HPP

#ifndef POS_HPP
#define POS_HPP

#include <iostream>

#include "rect.hpp"

class Rect;

class Pos
{
public:
    int x;
    int y;

    Pos();
    Pos(int x, int y);

    Pos operator +(const Pos &other) const;
    Pos operator +(int other) const;
    Pos& operator +=(const Pos &other);
    Pos operator -(const Pos &other) const;
    Pos operator -(int other) const;
    Pos& operator -=(const Pos &other);
    Pos operator *(const Pos &other) const;
    Pos operator *(int other) const;
    bool operator ==(const Pos &other) const;
    bool operator !=(const Pos &other) const;

    bool is_in_rect(const Rect &rect) const;
    bool is_in_rect(const Pos &pos, int w, int h) const;
    bool is_in_rect(int uper_left_x, int uper_left_y, int w, int h) const;
    void fit_in_rect(const Rect &rect);
};

std::ostream& operator<<(std::ostream &os, const Pos &pos);

extern const Pos DIRECTIONS[9];

#endif // POS_HPP

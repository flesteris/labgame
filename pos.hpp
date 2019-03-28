#ifndef POS_HPP
#define POS_HPP

#include <iostream> /// Just a test helper
#include "rect.hpp"

class Rect;

class Pos
{
private:

public:
    /*float x;
    float y;*/

    int x;
    int y;

    Pos();
    Pos(const Pos &pos);
    Pos(int x, int y);
    //Pos(float x, float y);

    Pos operator +(const Pos &other) const;
    Pos operator +=(const Pos &other) const;
    Pos operator -(const Pos &other) const;
    Pos operator -=(const Pos &other) const;
    Pos operator *(const int &other) const;
    //Pos operator *(const float &other) const;
    bool operator ==(const Pos &other) const;
    bool operator !=(const Pos &other) const;

    bool is_in_rect(Rect &rect);
    bool is_in_rect(int uper_left_x, int uper_left_y, int w, int h);
    void fit_in_rect(Rect &rect);
    void print_coordinates(); /// Just a test helper
};

#endif // POS_HPP

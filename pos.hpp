#ifndef POS_HPP
#define POS_HPP

class Pos
{
private:

public:
    int x;
    int y;

    Pos();
    Pos(int x, int y);
    Pos operator +(const Pos& other) const
    {
        Pos pos;
        pos.x = this->x + other.x;
        pos.y = this->y + other.y;
        return pos;
    }
    bool is_in_rect(int uper_left_x, int uper_left_y, int w, int h);
};

#endif // POS_HPP

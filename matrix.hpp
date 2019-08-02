#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <vector>

#include "pos.hpp"

template <typename T>
class Matrix
{
public:
    typedef typename std::vector<T>::reference reference;
    typedef typename std::vector<T>::const_reference const_reference;

    int w;
    int h;
    std::vector<T> data;

    Matrix() : w(0), h(0){}
    size_t size(){return data.size();}
    void resize(int w, int h)
    {
        this->w = w;
        this->h = w;
        data.resize(w * h);
    }
    void resize(int w, int h, const T &value_to_fill_with)
    {
        this->w = w;
        this->h = h;
        data.resize(w * h, value_to_fill_with);
    }
    void erase(int i)
    {
        assert(i >= 0 && i < w * h);
        data[i] = T{};
    }
    void erase(const Pos &pos)
    {
        assert(pos.x >= 0 && pos.x < w && pos.y >= 0 && pos.y < h);
        data[pos.y * w + pos.x] = T{};
    }
    const_reference operator [](int i) const
    {
        assert(i >= 0 && i < w * h);
        return data[i];
    }
    reference operator [](int i)
    {
        assert(i >= 0 && i < w * h);
        return data[i];
    }
    const_reference operator [](const Pos &pos) const
    {
        assert(pos.x >= 0 && pos.x < w && pos.y >= 0 && pos.y < h);
        return data[pos.y * w + pos.x];
    }
    reference operator [](const Pos &pos)
    {
        assert(pos.x >= 0 && pos.x < w && pos.y >= 0 && pos.y < h);
        return data[pos.y * w + pos.x];
    }
};

#endif // MATRIX_HPP

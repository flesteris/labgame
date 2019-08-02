#ifndef TEXT_FONT_HPP
#define TEXT_FONT_HPP

#include <SDL_ttf.h>
#include <string>

#include "exceptions.hpp"

class TextFont
{
public:
    TTF_Font* font;
    size_t font_size;

    TextFont(size_t font_size);
    ~TextFont();
};

#endif // TEXT_FONT_HPP

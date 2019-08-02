#include "text_font.hpp"

TextFont::TextFont(size_t font_size) : font_size(font_size)
{
    std::string filename = "font//Country Western Black Regular.ttf";
    font = TTF_OpenFont(filename.c_str(), font_size);
    if(!font)
    {
        throw font_load_error(filename);
    }
}

TextFont::~TextFont()
{
    TTF_CloseFont(font);
}

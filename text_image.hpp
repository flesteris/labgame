#ifndef TEXT_IMAGE_HPP
#define TEXT_IMAGE_HPP

#include <memory>
#include <sstream>
#include <SDL_ttf.h>

#include "game.hpp"
#include "pos.hpp"
#include "rect.hpp"
#include "text_font.hpp"


class TextImage
{
private:
    int font_vector_index;
    Game* game;
    SDL_Color font_color;
    int font_size;
    std::string text;
    SDL_Texture* texture;

    void create_image();
    void load_font();
    bool compare_colors(const SDL_Color &font_color_);

public:
    int w;
    int h;

    TextImage(Game* game, size_t font_size);
    TextImage(Game* game);
    ~TextImage();

    bool font_exists();
    void set_font_size(size_t font_size_);
    void set_font_color(Uint8 red, Uint8 green, Uint8 blue);
    void set_font_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    void load_from_text(const std::string &text_);
    void load_from_text(int number);
    void draw(const Pos &pos) const;
    void draw_centered(const Pos &pos) const;
    void draw_right_aligned(const Pos &pos) const;
};

#endif // TEXT_IMAGE_HPP

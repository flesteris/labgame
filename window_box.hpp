#ifndef WINDOW_BOX_HPP
#define WINDOW_BOX_HPP

#include "image.hpp"
#include "pos.hpp"
#include "rect.hpp"
#include "text_image.hpp"

class WindowBox
{
private:
    Game* game;
    Image* image;

public:
    TextImage* text_image;
    int w;
    int h;

    WindowBox(Game* game);
    ~WindowBox();

    void loadBMP(const std::string &filename);
    void load_text(const std::string &text, size_t font_size);
    void load_text(const std::string &text);
    void draw_window_box_centered(const Pos &pos) const;
    void draw_window_box_low_centered(const Pos &pos) const;
};

#endif // WINDOW_BOX_HPP

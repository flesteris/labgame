#include "window_box.hpp"

WindowBox::WindowBox(Game* game) : game(game)
{
    image = new Image(game);
    text_image = new TextImage(game);
}

WindowBox::~WindowBox()
{
    delete text_image;
    delete image;
}

void WindowBox::loadBMP(const std::string &filename)
{
    image->loadBMP(filename);
    SDL_QueryTexture(image->texture, NULL, NULL, &w, &h);
}

void WindowBox::load_text(const std::string &text, size_t font_size)
{
    text_image->set_font_size(font_size);
    text_image->load_from_text(text);
}

void WindowBox::load_text(const std::string &text)
{
    text_image->load_from_text(text);
}

void WindowBox::draw_window_box_centered(const Pos &pos) const
{
    Pos temp_pos = pos;
    temp_pos.x -= w / 2;
    temp_pos.y -= h / 2;
    image->draw(Rect(), Rect(temp_pos, w, h));
    Pos temp_pos_2 = pos;
    temp_pos_2.y -= text_image->h / 2;
    text_image->draw_centered(temp_pos_2);
}

void WindowBox::draw_window_box_low_centered(const Pos &pos) const
{
    Pos temp_pos = pos;
    temp_pos.x -= w / 2;
    temp_pos.y -= h / 2;
    image->draw(Rect(), Rect(temp_pos, w, h));
    Pos temp_pos_2 = pos;
    temp_pos_2.y -= text_image->h * 2 - w / 2;
    text_image->draw_centered(temp_pos_2);
}

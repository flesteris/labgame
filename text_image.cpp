#include "text_image.hpp"

TextImage::TextImage(Game* game, size_t font_size) :
    game(game),
    texture(nullptr),
    font_color({255, 255, 255}),
    font_size(font_size),
    font_vector_index(0)
{
    load_font();
}

TextImage::TextImage(Game* game) :
    game(game),
    texture(nullptr),
    font_color({255, 255, 255}),
    font_size(20),
    font_vector_index(0)
{
    load_font();
}

TextImage::~TextImage()
{
    SDL_DestroyTexture(texture);
}

void TextImage::create_image()
{
    if(!text.empty())
    {
        SDL_DestroyTexture(texture);
        SDL_Surface* surface = TTF_RenderText_Solid(game->font_vector[font_vector_index]->font, text.c_str(), font_color);
        if(!surface)
        {
            throw TTF_render_error();
        }
        else
        {
            texture = SDL_CreateTextureFromSurface(game->window->ren, surface);
            SDL_FreeSurface(surface);
            if(!texture)
            {
                throw SDL_texture_error();
            }
            SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        }
    }
}

bool TextImage::font_exists()
{
    for(size_t i = 0; i < game->font_vector.size(); ++i)
    {
        if(game->font_vector[i]->font_size == font_size)
        {
            font_vector_index = i;
            return true;
        }
    }
    return false;
}

void TextImage::load_font()
{
    if(!font_exists())
    {
        game->font_vector.push_back(std::unique_ptr<TextFont>(new TextFont(font_size)));
        font_vector_index = game->font_vector.size() - 1;
    }
}

bool TextImage::compare_colors(const SDL_Color &font_color_)
{
    if(font_color_.r != font_color.r ||
       font_color_.g != font_color.g ||
       font_color_.b != font_color.b ||
       font_color_.a != font_color.a)
    {
        return false;
    }
    return true;
}

void TextImage::set_font_size(size_t font_size_)
{
    if(font_size != font_size_)
    {
        font_size = font_size_;
        load_font();
        create_image();
    }
}

void TextImage::set_font_color(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_Color font_color_ = {red, green, blue};
    if(!compare_colors(font_color_))
    {
        font_color = font_color_;
        create_image();
    }
}

void TextImage::set_font_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    SDL_Color font_color_ = {red, green, blue, alpha};
    if(!compare_colors(font_color_))
    {
        font_color = font_color_;
        create_image();
    }
}

void TextImage::load_from_text(const std::string &text_)
{
    if(text != text_)
    {
        text = text_;
        create_image();
    }
}

void TextImage::load_from_text(int number)
{
    std::stringstream ss;
    ss << number;
    std::string text_ = ss.str();
    if(text != text_)
    {
        text = text_;
        create_image();
    }
}

void TextImage::draw(const Pos &pos) const
{
    Rect drect(pos, w, h);
    SDL_Rect sdl_drect = drect.to_sdl_rect();
    SDL_Rect* sdl_srect_ptr = nullptr;
    SDL_Rect* sdl_drect_ptr = drect.is_empty() ? nullptr : &sdl_drect;
    SDL_RenderCopy(game->window->ren, texture, sdl_srect_ptr, sdl_drect_ptr);
}

void TextImage::draw_centered(const Pos &pos) const
{
    Rect drect(pos, w, h);
    drect.pos->x -= w / 2;
    SDL_Rect sdl_drect = drect.to_sdl_rect();
    SDL_Rect* sdl_srect_ptr = nullptr;
    SDL_Rect* sdl_drect_ptr = drect.is_empty() ? nullptr : &sdl_drect;
    SDL_RenderCopy(game->window->ren, texture, sdl_srect_ptr, sdl_drect_ptr);
}

void TextImage::draw_right_aligned(const Pos &pos) const
{
    Rect drect(pos, w, h);
    drect.pos->x -= w;
    SDL_Rect sdl_drect = drect.to_sdl_rect();
    SDL_Rect* sdl_srect_ptr = nullptr;
    SDL_Rect* sdl_drect_ptr = drect.is_empty() ? nullptr : &sdl_drect;
    SDL_RenderCopy(game->window->ren, texture, sdl_srect_ptr, sdl_drect_ptr);
}

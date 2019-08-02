#include "image.hpp"

Image::Image(Game* game) : game(game), texture(nullptr)
{

}

Image::~Image()
{
    SDL_DestroyTexture(texture);
}

void Image::draw(const Rect& srect, const Rect& drect)
{
    SDL_Rect sdl_srect = srect.to_sdl_rect();
    SDL_Rect sdl_drect = drect.to_sdl_rect();
    SDL_Rect* sdl_srect_ptr = srect.is_empty() ? nullptr : &sdl_srect;
    SDL_Rect* sdl_drect_ptr = drect.is_empty() ? nullptr : &sdl_drect;
    SDL_RenderCopy(game->window->ren, texture, sdl_srect_ptr, sdl_drect_ptr);
}

void Image::loadBMP(const std::string &filename)
{
    SDL_Surface* surface = SDL_LoadBMP(filename.c_str()); // Uzkraunam BMP i atminti
    if(!surface)
    {
        throw SDL_bmp_load_error(filename);
    }
    texture = SDL_CreateTextureFromSurface(game->window->ren, surface); // Is paveiksliuko padarom tekstura, kuria galima piesti i ekrana
    SDL_FreeSurface(surface);
    if(!texture)
    {
        throw SDL_texture_error();
    }
}



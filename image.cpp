#include "image.hpp"
#include "rect.hpp"

Image::Image() : texture(nullptr)
{

}

Image::~Image()
{
    SDL_DestroyTexture(texture);
}

void Image::draw(SDL_Renderer* ren, const Rect& srect, const Rect& drect)
{
    SDL_Rect sdl_srect = srect.to_sdl_rect();
    SDL_Rect sdl_drect = drect.to_sdl_rect();
    SDL_Rect* sdl_srect_ptr = srect.is_empty() ? nullptr : &sdl_srect;
    SDL_Rect* sdl_drect_ptr = drect.is_empty() ? nullptr : &sdl_drect;
    SDL_RenderCopy(ren, texture, sdl_srect_ptr, sdl_drect_ptr);
}

void Image::loadBMP(SDL_Renderer* ren, const std::string filename)
{
    SDL_Surface* surface = SDL_LoadBMP(filename.c_str()); // Uzkraunam BMP i atminti
    if(surface)
    {
        texture = SDL_CreateTextureFromSurface(ren, surface); // Is paveiksliuko padarom tekstura, kuria galima piesti i ekrana
        SDL_FreeSurface(surface); // Paveiksliuko daugiau nebereikia, nes turim tekstura
    }
}

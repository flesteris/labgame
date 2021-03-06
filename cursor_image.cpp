#include "cursor_image.hpp"

CursorImage::CursorImage() : surface(nullptr)
{

}

CursorImage::~CursorImage()
{
    SDL_FreeSurface(surface);
}

void CursorImage::loadBMP(const std::string &filename)
{
    surface = SDL_LoadBMP(filename.c_str());
    if(!surface)
    {
        throw SDL_bmp_load_error(filename);
    }
}

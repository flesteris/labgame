#include "cursor.hpp"

Cursor::Cursor()
{
    load_surfaces();
    set_cursor();
}

void Cursor::load_surfaces()
{
    for(int i = 0; i < 2; ++i)
    {
        surfaces.push_back(new SDL_Surface());
    }

    surfaces[SW_ARROW] = SDL_LoadBMP("images//destination.bmp");
    surfaces[S_ARROW] = SDL_LoadBMP("images//destination_empty.bmp");
}

void Cursor::set_cursor()
{
    cursor = SDL_CreateColorCursor(surfaces[0], 20, 20);
    SDL_SetCursor(cursor);
}

void Cursor::set_cursor(int a)
{
    cursor = SDL_CreateColorCursor(surfaces[a], 20, 20);
    SDL_SetCursor(cursor);
}


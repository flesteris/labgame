#include "cursor.hpp"

Cursor::Cursor()
{
    load_surfaces();
    set_cursor();
}

Cursor::~Cursor()
{
    for(int i = 0; i < CURSOR_IMAGE_COUNT; ++i)
    {
        SDL_FreeSurface(surfaces[i]);
    }
    surfaces.clear();
}

void Cursor::load_surfaces()
{
    for(int i = 0; i < CURSOR_IMAGE_COUNT; ++i)
    {
        surfaces.push_back(new SDL_Surface());
    }

    surfaces[SW_ARROW] = SDL_LoadBMP("images//cursors//SW_arrow.bmp");
    surfaces[S_ARROW] = SDL_LoadBMP("images//cursors//S_arrow.bmp");
    surfaces[SE_ARROW] = SDL_LoadBMP("images//cursors//SE_arrow.bmp");
    surfaces[E_ARROW] = SDL_LoadBMP("images//cursors//E_arrow.bmp");
    surfaces[NE_ARROW] = SDL_LoadBMP("images//cursors//NE_arrow.bmp");
    surfaces[N_ARROW] = SDL_LoadBMP("images//cursors//N_arrow.bmp");
    surfaces[NW_ARROW] = SDL_LoadBMP("images//cursors//NW_arrow.bmp");
    surfaces[W_ARROW] = SDL_LoadBMP("images//cursors//W_arrow.bmp");
    surfaces[NORMAL_CURSOR] = SDL_LoadBMP("images//cursors//normal_cursor.bmp");
    surfaces[GO_TO_DESTINATION] = SDL_LoadBMP("images//cursors//go_to_destination.bmp");
}

void Cursor::set_cursor() ///gal ir nereik
{
    cursor = SDL_CreateColorCursor(surfaces[NORMAL_CURSOR], 0, 0);
    SDL_SetCursor(cursor);
}

void Cursor::set_cursor(int a)
{
    switch(a)
    {
    case SW_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[SW_ARROW], 0, 19);
            break;
        }
    case S_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[S_ARROW], 10, 19);
            break;
        }
    case SE_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[SE_ARROW], 19, 19);
            break;
        }
    case E_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[E_ARROW], 19, 10);
            break;
        }
    case NE_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[NE_ARROW], 19, 0);
            break;
        }
    case N_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[N_ARROW], 10, 0);
            break;
        }
    case NW_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[NW_ARROW], 0, 0);
            break;
        }
    case W_ARROW:
        {
            cursor = SDL_CreateColorCursor(surfaces[W_ARROW], 0, 10);
            break;
        }
    case NORMAL_CURSOR:
        {
            cursor = SDL_CreateColorCursor(surfaces[NORMAL_CURSOR], 0, 0);
            break;
        }
    case GO_TO_DESTINATION:
        {
            cursor = SDL_CreateColorCursor(surfaces[GO_TO_DESTINATION], 10, 10);
            break;
        }
    default:
        {
            cursor = SDL_CreateColorCursor(surfaces[NORMAL_CURSOR], 0, 0);
        }
    }
    SDL_SetCursor(cursor);
}


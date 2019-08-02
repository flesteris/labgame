#include "cursor.hpp"

Cursor::Cursor()
{
    load_surfaces();
    set_cursor(NORMAL_CURSOR);
    current_cursor = NORMAL_CURSOR;
}

Cursor::~Cursor()
{
    for(auto cursor : cursors)
    {
        SDL_FreeCursor(cursor);
    }
}

void Cursor::load_surfaces()
{
    CursorImage* cursor_image = new CursorImage();

    cursor_image->loadBMP("images//cursors//SW_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 0, 19));
    cursor_image->loadBMP("images//cursors//S_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 10, 19));
    cursor_image->loadBMP("images//cursors//SE_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 19, 19));
    cursor_image->loadBMP("images//cursors//E_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 19, 10));
    cursor_image->loadBMP("images//cursors//NE_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 19, 0));
    cursor_image->loadBMP("images//cursors//N_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 10, 0));
    cursor_image->loadBMP("images//cursors//NW_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 0, 0));
    cursor_image->loadBMP("images//cursors//W_arrow.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 0, 10));
    cursor_image->loadBMP("images//cursors//normal_cursor.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 0, 0));
    cursor_image->loadBMP("images//cursors//accessible_cursor.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 0, 0));
    cursor_image->loadBMP("images//cursors//go_to_destination.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 10, 10));
    cursor_image->loadBMP("images//cursors//combat_cursor.bmp");
    cursors.push_back(SDL_CreateColorCursor(cursor_image->surface, 0, 0));

    delete cursor_image;
}

void Cursor::set_cursor(int i)
{
    if(i != current_cursor)
    {
        SDL_SetCursor(cursors[i]);
        current_cursor = i;
    }
}

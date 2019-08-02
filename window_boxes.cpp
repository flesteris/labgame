#include "window_boxes.hpp"

WindowBoxes::WindowBoxes(Game* game) : game(game)
{
    create_window_boxes();
    load_window_boxes();
}

WindowBoxes::~WindowBoxes()
{
    delete terrain_tooltip;
    delete monster_tooltip;
    delete notification;
}

void WindowBoxes::create_window_boxes()
{
    terrain_tooltip = new WindowBox(game);
    monster_tooltip = new WindowBox(game);
    notification = new WindowBox(game);
}

void WindowBoxes::load_window_boxes()
{
    terrain_tooltip->loadBMP("images//window_boxes//terrain_tooltip.bmp");
    terrain_tooltip->text_image->set_font_color(153, 255, 153); //Light green
    terrain_tooltip->text_image->set_font_size(25);

    monster_tooltip->loadBMP("images//window_boxes//monster_tooltip.bmp");
    monster_tooltip->text_image->set_font_color(255, 153, 153); //Light red
    monster_tooltip->text_image->set_font_size(25);

    notification->loadBMP("images//window_boxes//notification.bmp");
    notification->text_image->set_font_color(255, 255, 255); //White
    notification->text_image->set_font_size(20);
}

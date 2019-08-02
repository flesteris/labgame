#ifndef WINDOW_BOXES_HPP
#define WINDOW_BOXES_HPP

#include "window_box.hpp"

class WindowBox;

class WindowBoxes
{
private:
    Game* game;

public:
    WindowBox* terrain_tooltip;
    WindowBox* monster_tooltip;
    WindowBox* notification;

    WindowBoxes(Game* game);
    ~WindowBoxes();

    void create_window_boxes();
    void load_window_boxes();
};

#endif // WINDOW_BOXES_HPP

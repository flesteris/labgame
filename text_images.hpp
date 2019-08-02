#ifndef TEXT_IMAGES_HPP
#define TEXT_IMAGES_HPP

#include <SDL2/SDL.h>
#include <vector>

#include "game.hpp"
#include "text_image.hpp"

enum ResourceText
{
    GOLD_TEXT = 0,
    MERCURY_CRYSTAL_TEXT = 1,
    SULPHUR_CRYSTAL_TEXT = 2,
    LIGHTNING_CRYSTAL_TEXT = 3,
    RESOURCE_TEXT_COUNT = 4
};

enum Date
{
    DAY_TEXT = 0,
    WEEK_TEXT = 1,
    MONTH_TEXT = 2,
    DATE_TEXT_COUNT = 3
};

enum HeroArmySlots
{
    FIRST_SLOT = 0,
    SECOND_SLOT = 1,
    THIRD_SLOT = 2,
    FOURTH_SLOT = 3,
    FIFTH_SLOT = 4,
    HERO_ARMY_SLOT_COUNT = 5
};

class Game;
class TextImage;

class TextImages
{
private:
    Game* game;

public:
    std::vector<TextImage*> resources;
    std::vector<TextImage*> time_names; // DAY, WEEK, MONTH
    std::vector<TextImage*> date;
    std::vector<TextImage*> hero_army_numbers;
    TextImage* monsters_left_text;
    TextImage* monsters_left_number;

    TextImages(Game* game);
    ~TextImages();

    void create_text_images();
    void load_inconstant_text_images();
    void load_constant_text_images();
};

#endif // TEXT_IMAGES_HPP

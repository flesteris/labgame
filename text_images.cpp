#include "text_images.hpp"

TextImages::TextImages(Game* game) : game(game)
{
    create_text_images();
    load_inconstant_text_images();
    load_constant_text_images();
}

TextImages::~TextImages()
{
    for(int i = 0; i < RESOURCE_TEXT_COUNT; ++i)
    {
        delete resources[i];
    }
    for(int i = 0; i < DATE_TEXT_COUNT; ++i)
    {
        delete time_names[i];
        delete date[i];
    }
    for(int i = 0; i < HERO_ARMY_SLOT_COUNT; ++i)
    {
        delete hero_army_numbers[i];
    }
    delete monsters_left_text;
    delete monsters_left_number;
}

void TextImages::create_text_images()
{
    for(int i = 0; i < RESOURCE_TEXT_COUNT; ++i)
    {
        resources.push_back(new TextImage(game, 24));
    }
    for(int i = 0; i < DATE_TEXT_COUNT; ++i)
    {
        time_names.push_back(new TextImage(game, 24));
        date.push_back(new TextImage(game, 24));
    }
    for(int i = 0; i < HERO_ARMY_SLOT_COUNT; ++i)
    {
        hero_army_numbers.push_back(new TextImage(game, 16));
    }

    monsters_left_text = new TextImage(game, 21);
    monsters_left_text->set_font_color(255, 0, 0); //Red

    monsters_left_number = new TextImage(game, 21);
    monsters_left_number->set_font_color(255, 0, 0); //Red
}

void TextImages::load_inconstant_text_images()
{
    resources[GOLD_TEXT]->load_from_text(game->player->get_gold());
    resources[MERCURY_CRYSTAL_TEXT]->load_from_text(game->player->get_mercury_crystals());
    resources[SULPHUR_CRYSTAL_TEXT]->load_from_text(game->player->get_sulphur_crystals());
    resources[LIGHTNING_CRYSTAL_TEXT]->load_from_text(game->player->get_lightning_crystals());

    date[DAY_TEXT]->load_from_text(game->game_time.day);
    date[WEEK_TEXT]->load_from_text(game->game_time.week);
    date[MONTH_TEXT]->load_from_text(game->game_time.month);

    auto hero = game->player->heroes[game->selected_hero];
    for(int i = 0; i < HERO_ARMY_SLOT_COUNT; ++i)
    {
        if(hero->hero_army[i])
        {
            hero_army_numbers[i]->load_from_text(hero->hero_army[i]->get_count());
        }
    }

    monsters_left_number->load_from_text(Monster::get_object_count());
}

void TextImages::load_constant_text_images()
{
    time_names[DAY_TEXT]->load_from_text("DAY: ");
    time_names[WEEK_TEXT]->load_from_text("WEEK: ");
    time_names[MONTH_TEXT]->load_from_text("MONTH: ");
    monsters_left_text->load_from_text("Monsters on map remaining: ");
}

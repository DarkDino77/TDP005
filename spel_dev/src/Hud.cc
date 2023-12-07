#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Hud.h"
#include "World.h"

Hud::Hud(sf::Vector2f const& position, sf::Texture const& sprite, World & world)
: Updatable(position, sprite)
{
    shape.setOrigin(0,0);
    shape.setScale(1,1);
    load_hud(world);
}

void Hud::update(sf::Time const&, World & world, std::shared_ptr<Game_Object> const&)
{
    health_percent = world.get_health_percent();
    hud_elements.at(0)->setScale(4.0f * health_percent, 4.0f);

    level_percent = world.get_level_percent();
    hud_elements.at(1)->setScale(4.0f * level_percent, 4.0f);

    player_level = world.get_level();
    hud_texts.at(0)->setString(std::to_string(player_level));

    if(world.get_weapon_stats()->get_ammo_capacity() == -1)
    {
        hud_texts.at(1)->setString("o");
        hud_texts.at(1)->setPosition(1906-5*4 - hud_texts.at(1)->getLocalBounds().width, 10+23*4);
    }
    else
    {
        hud_texts.at(1)->setString(std::to_string(world.get_weapon_stats()->get_ammo_amount()));
        hud_texts.at(1)->setPosition(1906-5*4 - hud_texts.at(1)->getLocalBounds().width, 10+23*4);
    }

    hud_elements.at(2)->setTexture(&world.get_sprite(world.get_weapon_stats()->get_name() + "_hud"));

}

void Hud::load_hud(World & world)
{
    std::shared_ptr<sf::Text> level_text{std::make_shared<sf::Text>()};
    level_text->setFont(world.get_font());
    level_text->setCharacterSize(12);
    level_text->setOutlineColor(sf::Color (0x373737ff));
    level_text->setOutlineThickness(4);
    level_text->setOrigin(12,0);
    level_text->setString("0");
    level_text->setPosition(10+30*4, 10+13*4);
    hud_texts.push_back(level_text);

    std::shared_ptr<sf::Text> ammo_text{std::make_shared<sf::Text>()};
    ammo_text->setFont(world.get_font());
    ammo_text->setCharacterSize(12);
    ammo_text->setOutlineColor(sf::Color (0x373737ff));
    ammo_text->setOutlineThickness(4);
    ammo_text->setOrigin(12,0);
    ammo_text->setString("o");
    ammo_text->setPosition(1906-5*4 - ammo_text->getLocalBounds().width, 10+23*4);
    hud_texts.push_back(ammo_text);

    std::shared_ptr<sf::RectangleShape> hud_current_health = std::make_shared<sf::RectangleShape>();
    hud_current_health->setTexture(&world.get_sprite("hud_health_fill"));
    hud_current_health->setSize(sf::Vector2f(hud_current_health->getTexture()->getSize()));
    hud_current_health->setOrigin({hud_current_health->getSize().x,hud_current_health->getSize().y/2.0f});
    hud_current_health->setPosition( 1906-17*4,26);
    hud_current_health->setScale(4.0f * health_percent, 4.0f);
    hud_elements.push_back(hud_current_health);

    std::shared_ptr<sf::RectangleShape> hud_current_level = std::make_shared<sf::RectangleShape>();
    hud_current_level->setTexture(&world.get_sprite("hud_level_fill"));
    hud_current_level->setSize(sf::Vector2f(hud_current_level->getTexture()->getSize()));
    hud_current_level->setOrigin({0,hud_current_level->getSize().y/2.0f});
    hud_current_level->setPosition(14,26);
    hud_current_level->setScale(4.0f * level_percent * 4.0f, 4.0f);
    hud_elements.push_back(hud_current_level);

    std::shared_ptr<sf::RectangleShape> hud_weapon = std::make_shared<sf::RectangleShape>();
    hud_weapon->setTexture(&world.get_sprite("glock_hud"));
    hud_weapon->setSize(sf::Vector2f(hud_weapon->getTexture()->getSize()));
    hud_weapon->setOrigin({hud_weapon->getSize().x, 0});
    hud_weapon->setPosition(1910, 10);
    hud_weapon->setScale(4.0f, 4.0f);
    hud_elements.push_back(hud_weapon);
}

void Hud::render(sf::RenderWindow &window)
{

    window.draw(*hud_elements.at(0));
    window.draw(*hud_elements.at(1));
    window.draw(shape);
    window.draw(*hud_elements.at(2));
    for(std::shared_ptr<sf::Text> const& text : hud_texts)
    {
        window.draw(*text);
    }

}

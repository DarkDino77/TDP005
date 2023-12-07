#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Hud.h"
#include "World.h"

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
    ammo_text->setString("-");
    ammo_text->setPosition(1906-5*4 - ammo_text->getLocalBounds().width, 10+23*4);
    hud_texts.push_back(ammo_text);

    std::shared_ptr<sf::RectangleShape> hud_current_health = std::make_shared<sf::RectangleShape>();
    hud_current_health->setTexture(&world.get_sprite("hud_health_fill"));
    hud_current_health->setSize(sf::Vector2f(hud_current_health->getTexture()->getSize()));
    hud_current_health->setOrigin({hud_current_health->getSize().x,hud_current_health->getSize().y/2.0f});
    hud_current_health->setPosition( 1906-18*4,26);
    hud_current_health->setScale(4.0f * health_percent, 4.0f);
    hud_elements.push_back(hud_current_health);

    std::shared_ptr<sf::RectangleShape> hud_health = std::make_shared<sf::RectangleShape>();
    hud_health->setTexture(&world.get_sprite("hud_health"));
    hud_health->setSize(sf::Vector2f(hud_health->getTexture()->getSize()));
    hud_health->setOrigin({hud_health->getSize().x,0});
    hud_health->setPosition(1910-18*4,10);
    hud_health->setScale(4.0f, 4.0f);
    hud_elements.push_back(hud_health);

    std::shared_ptr<sf::RectangleShape> hud_current_level = std::make_shared<sf::RectangleShape>();
    hud_current_level->setTexture(&world.get_sprite("hud_level_fill"));
    hud_current_level->setSize(sf::Vector2f(hud_current_level->getTexture()->getSize()));
    hud_current_level->setOrigin({0,hud_current_level->getSize().y/2.0f});
    hud_current_level->setPosition(14,26);
    hud_current_level->setScale(4.0f * level_percent * 4.0f, 4.0f);
    hud_elements.push_back(hud_current_level);

    std::shared_ptr<sf::RectangleShape> hud_level = std::make_shared<sf::RectangleShape>();
    hud_level->setTexture(&world.get_sprite("hud_level"));
    hud_level->setSize(sf::Vector2f(hud_level->getTexture()->getSize()));
    hud_level->setOrigin({0,0});
    hud_level->setPosition(10,10);
    hud_level->setScale(4.0f, 4.0f);
    hud_elements.push_back(hud_level);

    std::shared_ptr<sf::RectangleShape> hud_weapon_background = std::make_shared<sf::RectangleShape>();
    hud_weapon_background->setTexture(&world.get_sprite("hud_weapon_background"));
    hud_weapon_background->setSize(sf::Vector2f(hud_weapon_background->getTexture()->getSize()));
    hud_weapon_background->setOrigin({hud_weapon_background->getSize().x, 0});
    hud_weapon_background->setPosition(1910, 10);
    hud_weapon_background->setScale(4.0f, 4.0f);
    hud_elements.push_back(hud_weapon_background);
}

void Hud::draw_hud(sf::RenderWindow & window)
{
    for(std::shared_ptr<sf::RectangleShape> const& hud_element : hud_elements)
    {
        window.draw(*hud_element);
    }
    for(std::shared_ptr<sf::Text> const& text : hud_texts)
    {
        window.draw(*text);
    }
}

void Hud::set_level_percent(float percent)
{
    level_percent = percent;
    hud_elements.at(2)->setScale(4.0f * level_percent, 4.0f);
}

void Hud::set_health_percent(float percent)
{
    health_percent = percent;
    hud_elements.at(0)->setScale(4.0f * health_percent, 4.0f);
}

void Hud::set_player_level(int level)
{
    player_level = level;
    hud_texts.at(0)->setString(std::to_string(level));
}

void Hud::set_weapon_stats(std::shared_ptr<Weapon> const& weapon)
{
    if(weapon->get_ammo_capacity() == -1)
    {
        hud_texts.at(1)->setString("-");
        hud_texts.at(1)->setPosition(1906-5*4 - hud_texts.at(1)->getLocalBounds().width, 10+23*4);
    }
    else
    {
        hud_texts.at(1)->setString(std::to_string(weapon->get_ammo_amount()));
        hud_texts.at(1)->setPosition(1906-5*4 - hud_texts.at(1)->getLocalBounds().width, 10+23*4);
    }

}
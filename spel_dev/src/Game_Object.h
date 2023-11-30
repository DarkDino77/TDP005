#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

class World;

class Game_Object
{
public:
    Game_Object(sf::Vector2f position, sf::Texture const& sprite, bool detect_collision);
    virtual void update(sf::Clock delta_time, World world);
    virtual void render(sf::RenderWindow &window);
    sf::RectangleShape shape;
private:
    sf::Vector2f position;
    sf::Texture sprite;
    bool detect_collision;
};

#endif
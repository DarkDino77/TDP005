#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <memory>

class World;

class Game_Object
{
public:
    Game_Object(sf::Vector2f const& position, sf::Texture const& sprite);
    virtual ~Game_Object() = default;
    Game_Object(Game_Object const& other_obj) = delete;
    Game_Object(Game_Object && other_obj) = delete;
    Game_Object& operator=(Game_Object const& other_obj) = delete;
    Game_Object& operator=(Game_Object && other_obj) = delete;

    virtual void render(sf::RenderWindow & window);
    sf::RectangleShape& get_shape();
    sf::Vector2f& get_position();

protected:
    sf::RectangleShape shape{};
    sf::Vector2f position{};

private:
    sf::Texture sprite;
};

#endif
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <memory>

class World;

class Game_Object
{
public:
    sf::RectangleShape shape{};
    sf::Vector2f position{};

    Game_Object(sf::Vector2f position, sf::Texture const& sprite);
    virtual ~Game_Object() = default;
    virtual void update(sf::Time const&, World &, std::shared_ptr<Game_Object>);
    virtual void render(sf::RenderWindow &window);

private:
    sf::Texture sprite;
};

#endif
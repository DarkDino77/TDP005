#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <memory>

class World;

class Game_Object
{
public:
    Game_Object(sf::Vector2f position, sf::Texture const& sprite);
    virtual ~Game_Object() = default;
    virtual void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&);
    virtual void handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const&);
    virtual void render(sf::RenderWindow &window);
    sf::RectangleShape get_shape();
    sf::Vector2f get_position();

protected:
    sf::RectangleShape shape{};
    sf::Vector2f position{};

private:
    sf::Texture sprite;
};

#endif
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
    virtual void update(sf::Time const& delta_time, World & world, sf::Window & window, std::shared_ptr<Game_Object> obj);
    virtual void render(sf::RenderWindow &window);

    sf::RectangleShape shape;
    virtual sf::Shape& get_collision_shape();


    sf::Vector2f position;
private:
    sf::Texture sprite;
    bool detect_collision;
};

#endif
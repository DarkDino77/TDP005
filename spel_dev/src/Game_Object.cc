#include "Game_Object.h"
#include "World.h"

Game_Object::Game_Object(sf::Vector2f position, sf::Texture const& sprite)
: position{position}, sprite{sprite}
{
    float sprite_scale{2.0f};
    sf::Vector2f temp_size{sprite.getSize()};
    shape.setSize(temp_size);
    shape.setTexture(&sprite);
    shape.setOrigin(temp_size/2.0f);
    shape.setScale(sprite_scale, sprite_scale);
    shape.setPosition(position);
}

void Game_Object::update(sf::Time const& delta_time, World &world, sf::Window &window, std::shared_ptr<Game_Object> obj){}

void Game_Object::render(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::Shape& Game_Object::get_collision_shape()
{
    return shape;
}
#include <iostream>
#include "Game_Object.h"
#include "World.h"

Game_Object::Game_Object(sf::Vector2f position, sf::Texture const& sprite, bool detect_collision)
: position{position}, sprite{sprite}, detect_collision{detect_collision}
{
    float sprite_scale{2.0f};
    sf::Vector2f temp_size{sprite.getSize()};
    shape.setSize(temp_size);
    shape.setTexture(&sprite);
    shape.setOrigin(temp_size/2.0f);
    shape.setScale(sprite_scale, sprite_scale);
    shape.setPosition(position);
} 

void Game_Object::update(sf::Clock delta_time, World world)
{
    std::cout << "do something" << std::endl;
}

void Game_Object::render(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::Shape& Game_Object::get_collision_shape()
{
    return shape;
}
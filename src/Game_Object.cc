#include "Game_Object.h"

Game_Object::Game_Object(sf::Vector2f const& position, sf::Texture const& sprite)
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

void Game_Object::render(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::RectangleShape& Game_Object::get_shape()
{
    return shape;
}

sf::Vector2f& Game_Object::get_position()
{
    return position;
}
#include "Movable.h"

Movable::Movable(sf::Vector2f position, sf::Texture const& sprite, bool detect_collision)
: Game_Object(position, sprite, detect_collision)
{
    collision_shape.setRadius(shape.getSize().x);
    collision_shape.setOrigin(shape.getSize());
    collision_shape.setPosition(position);
};

sf::Shape& Movable::get_collision_shape()
{
    return collision_shape;
};
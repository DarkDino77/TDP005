#include "Movable.h"

Movable::Movable(sf::Vector2f position, sf::Texture const& sprite)
: Game_Object(position, sprite)
{
    collision_shape.setRadius(shape.getSize().x*0.95f);
    collision_shape.setOrigin(shape.getSize());
    collision_shape.setPosition(position);
};

sf::Shape& Movable::get_collision_shape()
{
    return collision_shape;
};
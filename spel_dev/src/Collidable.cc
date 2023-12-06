#include "Collidable.h"

Collidable::Collidable(sf::Vector2f position, sf::Texture const& sprite)
: Updatable(position, sprite)
{
    collision_shape.setRadius(shape.getSize().x*0.9f);
    collision_shape.setOrigin({collision_shape.getRadius(),collision_shape.getRadius()});
    collision_shape.setPosition(shape.getPosition());
    collision_shape.setFillColor(sf::Color::Red);
}

sf::CircleShape Collidable::get_collision_shape()
{
    return collision_shape;
}
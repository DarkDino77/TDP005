#include "Movable.h"
#include <cmath>

Movable::Movable(sf::Vector2f position, sf::Texture const& sprite, float speed)
: Collidable(position, sprite), speed{speed}
{
    /*
    collision_shape.setRadius(shape.getSize().x*0.9f);
    collision_shape.setOrigin({collision_shape.getRadius(),collision_shape.getRadius()});
    collision_shape.setPosition(shape.getPosition());
    collision_shape.setFillColor(sf::Color::Red);
     */
}

void Movable::update_position(sf::Time const& delta_time)
{
    float distance = 250.0f * delta_time.asSeconds() * float(speed);
    position -= direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}

void Movable::set_rotation(sf::Vector2f rotate_direction)
{
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);
    shape.setRotation((rotate_degrees * 180 / 3.1415f) - 90.f);
}
/*
sf::CircleShape Movable::get_collision_shape()
{
    return collision_shape;
}*/

/*sf::Vector2f Movable::get_direction()
{
    return direction;
}*/
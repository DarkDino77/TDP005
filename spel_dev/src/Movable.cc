#include "Movable.h"
#include <cmath>

Movable::Movable(sf::Vector2f const& position, sf::Texture const& sprite, float const speed)
: Collidable(position, sprite), speed{speed}
{}

void Movable::update_position(sf::Time const& delta_time)
{
    float distance = 250.0f * delta_time.asSeconds() * float(speed);
    position -= direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}

void Movable::set_rotation(sf::Vector2f const& rotate_direction)
{
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);
    shape.setRotation((rotate_degrees * 180 / 3.1415f) - 90.f);
}

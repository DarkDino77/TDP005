#include "Character.h"
#include "World.h"

Character::Character(sf::Vector2f position, sf::Texture const& sprite, float speed, int health)
: Movable(position, sprite, speed), Damageable(health)
{}

void Character::knock_back(sf::Vector2f const& direction, float force)
{
    position -= direction * force;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}
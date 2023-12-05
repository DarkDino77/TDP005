#include "Character.h"
#include "World.h"

Character::Character(sf::Vector2f position, sf::Texture const& sprite, float speed, int health)
: Movable(position, sprite, speed), health{health}
{}

void Character::take_damage(int damage)
{
    health -= damage;
    //world.play_sound(hurt_sound);
}

void Character::knock_back(sf::Vector2f const& direction)
{
    position -= direction * 10.0f;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}
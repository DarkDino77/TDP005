#include "Character.h"
Character::Character(sf::Vector2f position, sf::Texture const& sprite, float speed, int health)
: Movable(position, sprite, speed), health{health}
{}

void Character::take_damage(int damage)
{
    health -= damage;
}
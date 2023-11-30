#include "Character.h"
Character::Character(sf::Vector2f position, sf::Texture const& sprite, float speed)
: Movable(position, sprite, speed)
{};
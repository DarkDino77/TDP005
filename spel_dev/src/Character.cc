#include "Character.h"
Character::Character(sf::Vector2f position, sf::Texture const& sprite, bool detect_collision) : Movable(position, sprite, detect_collision){};
#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, sf::Texture const& sprite, float speed, int health, int melee_damage)
        : Character(position, sprite, speed, health), melee_damage{melee_damage}
{}

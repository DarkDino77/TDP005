#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movable.h"
#include "Damageable.h"

class Weapon;

class Character : public Movable, public Damageable
{
public:
    std::vector<std::shared_ptr<Weapon>> available_weapons{};
    std::shared_ptr<Weapon> current_weapon{};

    Character(sf::Vector2f position, sf::Texture const& sprite, float speed, int health);
    void knock_back(sf::Vector2f const& direction, float force);
};

#endif

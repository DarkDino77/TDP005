#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movable.h"

class Weapon;

class Character : public Movable
{
public:
    std::vector<std::shared_ptr<Weapon>> available_weapons{};
    std::shared_ptr<Weapon> current_weapon{};

    Character(sf::Vector2f position, sf::Texture const& sprite, float speed, int health);
    void take_damage(int damage);
    void knock_back(sf::Vector2f const& direction);

protected:
    int health{};
};

#endif

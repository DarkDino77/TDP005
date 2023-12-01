#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movable.h"

class Weapon;

class Character : public Movable
{
public:
    Character(sf::Vector2f position, sf::Texture const& sprite, float speed);
    std::vector<std::shared_ptr<Weapon>> available_weapons{};
    std::shared_ptr<Weapon> current_weapon{};
private:
    int health{};

};

#endif

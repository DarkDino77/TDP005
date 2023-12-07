#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movable.h"
#include "Damageable.h"

class Weapon;

class Character : public Movable, public Damageable
{
public:
    Character(sf::Vector2f position, sf::Texture const& sprite, float speed, int health);
    ~Character() override = default;
    void knock_back(sf::Vector2f const& direction, float force);
    void add_weapon(std::string const& name, int damage,
                    int ammo_capacity, double bullet_speed,double fire_rate);

protected:
    std::vector<std::shared_ptr<Weapon>> available_weapons{};
    std::map<std::string,int> available_ammo{};
    std::shared_ptr<Weapon> current_weapon{};
};

#endif

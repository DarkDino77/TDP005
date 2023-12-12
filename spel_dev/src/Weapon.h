#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Bullet.h"

/**
 * @class Weapon
 * @brief Represents a weapon that a character can wield.
 *
 * The weapon class holds all the parameters that are to be sent into the bullet
 * once a character fires a shot.
 */
class Weapon {
public:
    /**
     * Constructor for the Weapon class
     *
     * @param name The name of the weapon.
     * @param damage The damage that each bullet should deal.
     * @param ammo_capacity The max amount of ammo that the weapon can hold.
     * @param bullet_speed The speed multiplier of which the instantiated bullets should travel.
     * @param fire_rate The amount of bullets per second the weapon can shoot.
     */
    Weapon(std::string const& name, int const damage, int const ammo_capacity,
           double const bullet_speed, double const fire_rate);

    /**
     * Instantiates a bullet in the world
     *
     * @param direction The direction which the bullet should travel in.
     * @param world A reference to the world instance that the bulle should exist in.
     * @param position
     * @param is_friendly
     * @return
     */
    bool shoot(sf::Vector2f const& direction, World & world,
               sf::Vector2f const& position, bool const is_friendly);
    bool can_shoot() const;
    std::string& get_name();
    void add_ammo(int const amount);
    int get_ammo_amount() const;
    int get_ammo_capacity() const;

private:
    std::string name;
    int damage;
    int ammo_capacity;
    int ammo_amount{0};
    double bullet_speed;
    double fire_rate;
    sf::Clock time_since_shot{};
};

#endif

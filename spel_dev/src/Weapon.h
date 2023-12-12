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
     * @brief Constructor for the Weapon class
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
     * @brief Instantiates a bullet in the world
     *
     * @param direction The direction which the bullet should travel in.
     * @param world A reference to the world instance that the bullet exists in.
     * @param position The initial position of the bullet.
     * @param is_friendly If the bullet is fired by the player, true elese false.
     * @return If the weapon can shoot, return true, else false.
     */
    bool shoot(sf::Vector2f const& direction, World & world,
               sf::Vector2f const& position, bool const is_friendly);

    /**
     * @brief Used to determine if the weapon can shoot based on the time since the last shot.
     */
    bool can_shoot() const;

    /**
     * @brief Gets the name of the weapon.
     *
     * @return The name variable of the weapon.
     */
    std::string& get_name();

    /**
     * @brief Add ammo to the weapon, until the max ammo is reached.
     *
     * @param amount The amount of ammo to be added.
     */
    void add_ammo(int const amount);

    /**
     * @brief Gets the current amount of ammo.
     * @return The current ammo amount.
     */
    int get_ammo_amount() const;

    /**
     * @brief Gets the maximum ammo capacity.
     * @return The ammo capacity.
     */
    int get_ammo_capacity() const;

private:
    /**
     * The name of the weapon
     */
    std::string name;

    /**
     * The damage that each bullet fired from the weapon should deal
     */
    int damage;

    /**
     * The maximum amount of ammo the weapon can hold.
     */
    int ammo_capacity;

    /**
     * The current amount of ammo.
     */
    int ammo_amount{0};

    /**
     * The speed multiplier of which the bullet should travel in.
     */
    double bullet_speed;

    /**
     * The amount of bullets per second the weapon can shoot.
     */
    double fire_rate;

    /**
     * The time since the last bullet was shot.
     */
    sf::Clock time_since_shot{};
};

#endif

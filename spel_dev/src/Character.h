#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movable.h"
#include "Damageable.h"

class Weapon;

/**
 * A character in the game.
 *
 * This is used to bundle together all functionality that the characters, such as the player and the enemies,
 * have in common. Does nothing on its own.
 */
class Character : public Movable, public Damageable
{
public:
    /**
     * Constructor for the Character class.
     *
     * @param[in] position The initial position of the Character object.
     * @param[in] sprite The texture that is used to render the Character object.
     * @param[in] speed The speed multiplier used to determine movement speed.
     * @param[in] health The amount of health points that the character starts with.
     */
    Character(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health);

    /**
     * Destructor for Character class.
     */
    ~Character() override = default;

    /**
     * Function to knock back the character.
     *
     * @param[in] direction The direction of which the character is to be pushed in.
     * @param[in] force The force multiplier determining how far the character should be knocked back.
     */
    void knock_back(sf::Vector2f const& direction, float force);

    /**
     * Function to add a weapon to the Character.
     *
     * @param[in] name The name of the weapon.
     * @param[in] damage The damage that is passed into each bullet it instantiates.
     * @param[in] ammo_capacity The maximum amount of ammo that the weapon can hold. -1 means no limit.
     * @param[in] bullet_speed The speed multiplier specifying how fast the bullets should travel.
     */
    void add_weapon(std::string const& name, int damage,
                    int ammo_capacity, double bullet_speed,double fire_rate);

protected:
    /**
     * A list of all available weapons that the character has.
     */
    std::vector<std::shared_ptr<Weapon>> available_weapons{};

    /**
     * A shared pointer to the current weapon that the character wields.
     */
    std::shared_ptr<Weapon> current_weapon{};
};

#endif

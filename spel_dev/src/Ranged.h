#ifndef RANGED_H
#define RANGED_H

#include "Enemy.h"

/**
 * @class Ranged
 * @brief Represents a ranged enemy in the game that inherits from the Enemy class.
 *
 * The Ranged enemy class provides additional functionality needed to be able to shoot
 * at the player.
 */
class Ranged : public Enemy
{
public:
    /**
     * @brief The constructor for the ranged enemy object.
     *
     * @param position The initial position of the ranged enemy.
     * @param sprite The sprite used to render the ranged enemy.
     * @param speed The speed multiplier that determines the enemies movement speed.
     * @param health The amount of health points the ranged enemy begins with.
     * @param melee_damage The amount of damage to be dealt on a melee attack.
     * @param xp The amount of xp to be added to the players xp once the enemy dies.
     */
    Ranged(sf::Vector2f const& position, sf::Texture const& sprite,
           float const speed, int const health, int const melee_damage, int const xp);

    /**
     * @brief The destructor of the Ranged enemy object.
     */
    ~Ranged() override = default;

    /**
     * @brief Updates the position of the enemy, and handles shoot logic.
     *
     * @param delta_time The time since the update function was last called.
     * @param world A reference to the world instance that the ranged enemy exists in.
     * @param current_obj A shared pointer to the current enemy as stored in the world instance.
     */
    void update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj) override;
};


#endif

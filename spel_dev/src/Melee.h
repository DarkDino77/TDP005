#ifndef MELEE_H
#define MELEE_H

#include "Enemy.h"
/**
 * @class Melee
 * @brief This class represents all Melee enemy's that inherits form Enemy.
 */
class Melee : public Enemy
{
public:
    /**
     * @brief This is the constructor for a Melee Enemy.
     * @param position This represents it's initial position.
     * @param sprite This represents the Texture that it displays.
     * @param speed This is the speed that a Melee Enemy can move around in the game world
     * @param health This is the amount of damage a Melee Enemy can take before it dies
     * @param melee_damage This is the amount of damage a Melee Enemy can deal every instance of its damage
     * @param xp This is the amount of xp the player will receive upon killing the enemy.
     */
    Melee(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, int const melee_damage, int const xp);
    /**
     * @brief this is the default destructor for a melee enemy.
     */
    ~Melee() override = default;
};

#endif

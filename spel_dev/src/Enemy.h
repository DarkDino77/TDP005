#ifndef ENEMY_H
#define ENEMY_H

#include "World.h"
#include "Character.h"

/**
 * @class Enemy
 * @brief Represents an enemy character that inherits from the Character class.
 */
class Enemy : public Character
{
public:
    /**
     * @brief Constructor for the Enemy class.
     * @param position The initial position of the enemy.
     * @param sprite The texture for the enemy's sprite.
     * @param speed The speed of that an enemy can move with.
     * @param health The initial health of the enemy.
     * @param melee_damage The damage inflicted by the enemy in melee attacks.
     * @param xp The experience points awarded when the enemy is defeated.
     */
    Enemy(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, int const melee_damage, int const xp);

    /**
     * @brief Pure virtual destructor for the Enemy class.
     */
    virtual ~Enemy() = 0;

    /**
     * @brief Handles collision events involving the enemy.
     * @param world Reference to the game world.
     * @param current_obj Shared pointer to the current game object.
     * @param other_obj Shared pointer to the other game object involved in the collision.
     */
    void handle_collision(World& world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;

    /**
     * @brief Updates the state of the enemy over time.
     * @param delta_time The time elapsed since the last update.
     * @param world Reference to the game world.
     * @param current_obj Shared pointer to the current game object.
     */
    void update(sf::Time const& delta_time, World& world, std::shared_ptr<Game_Object> const& current_obj) override;

protected:
    /**
    *  The total lifetime of the enemy.
    */
    float life_time{0};

    /**
    *  Timer for controlling the melee attack rate.
    */
    float melee_timer{0};

    /**
    *  he damage inflicted by melee attacks.
    */
    int melee_damage{};

    /**
    * The experience points awarded when the enemy is defeated.
    */
    int xp{};
};
#endif


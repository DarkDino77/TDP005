#ifndef EXPLOSION_H
#define EXPLOSION_H


#include "Collidable.h"

/**
 * @class Explosion
 * @brief Represents an explosion that inherits from the Collidable class.
 */
class Explosion : public Collidable {
public:
    /**
     * @brief Constructor for the Explosion class.
     * @param position The initial position of the explosion.
     * @param sprite The texture for the explosion's sprite.
     * @param explosive_radius The radius of the explosive area.
     * @param explosive_damage The damage inflicted by the explosion.
     */
    Explosion(sf::Vector2f const &position, sf::Texture const &sprite, float const explosive_radius,
              int const explosive_damage);

    /**
     * @brief Updates the state of the explosion over time.
     * @param delta_time The time elapsed since the last update.
     * @param world Reference to the game world.
     * @param current_obj Shared pointer to the current game object.
     */
    void update(sf::Time const &delta_time, World &world, std::shared_ptr<Game_Object> const &current_obj) override;

    /**
     * @brief Handles collision events involving the explosion.
     * @param world Reference to the game world.
     * @param current_obj Shared pointer to the current game object.
     * @param other_obj Shared pointer to the other game object involved in the collision.
     */
    void handle_collision(World &world, std::shared_ptr<Game_Object> const &current_obj,
                          std::shared_ptr<Game_Object> const &other_obj) override;

private:
    /**
     * The total lifetime of the explosion.
     */
    float life_time{0};

    /**
     * The maximum duration of the explosion.
     */
    float life_span{2};

    /**
     * The damage inflicted by the explosion.
     */
    int explosive_damage{};

    /**
     * List of game objects affected by the explosion.
     */
    std::vector<std::shared_ptr<Game_Object>> exploded_objects{};
};

#endif

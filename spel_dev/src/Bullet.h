#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Movable.h"

class Movable;

/**
 * A bullet in the game.
 *
 * The Bullet class inherits from the Movable class
 * and overrides the update and handle_collisions functions.
 */
class Bullet :public Movable{
public:
    /**
     * Constructor for the Bullet class.
     *
     * @param damage The damage that the bullet should deal upon impact with a valid target.
     * @param direction The initial direction that the bullet is to be fired in.
     * @param speed The travel speed of the bullet.
     * @param sprite The texture that is used to render the bullet object.
     * @param position The initial position of the bullet object.
     * @param is_friendly A bool specifying if the bullet was fired from the player or an enemy.
     */
    Bullet(int const damage, sf::Vector2f const& direction, double const speed, sf::Texture const& sprite, sf::Vector2f const& position, bool const is_friendly);

    /**
     * Specifies how the bullet object should move each update.
     *
     * @param delta_time The time since the update function was last called.
     * @param world A reference to the World object that the Bullet object exists in.
     * @param current_obj A shared pointer to the instance of the current bullet as stored in World.
     */
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;

    /**
     * Specifies what happens when the bullet collides with another object.
     *
     * @param delta_time The time since the update function was last called.
     * @param world A reference to the World object that the Bullet object exists in.
     * @param current_obj A shared pointer to the instance of the current bullet, as stored in World.
     */
    void handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;
private:
    /**
     * The damage per bullet.
     */
    int const damage;

    /**
     * A shared pointer to the source of the bullet.
     */
    bool const is_friendly;

    /**
     * Is the bullet alive?
     */
    bool is_alive{true};
};

#endif

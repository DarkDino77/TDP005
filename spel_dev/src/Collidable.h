#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Updatable.h"

/**
 * A collidable object in the game.
 *
 * The Collidable class inherits from the Updatable class and bundles all updatable objects
 * that are to handle collisions. These objects have a circular collision shape.
 */
class Collidable: public Updatable
{
public:
    /**
     * Constructor for the Collidable class.
     *
     * @param[in] position The initial position of the Collidable object.
     * @param[in] sprite The texture that is used to render the Collidable object.
     */
    Collidable(sf::Vector2f const& position, sf::Texture const& sprite);

    /**
     * Destructor for Collidable class.
     */
    virtual ~Collidable() = default;

    /**
     * Gets the collision shape of the Collidable object.
     *
     * @return[out] A shared pointer to the collision shape.
     */
    sf::CircleShape& get_collision_shape();

    /**
     * Specifies what happens when the collidable object collides with another object.
     *
     * @param[in] delta_time The time since the update function was last called.
     * @param[in] world A reference to the World object that the Collidable object exists in.
     * @param[in] current_obj A shared pointer to the instance of the current Collidable, as stored in World.
     */
    virtual void handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const&) = 0;
protected:
    /**
     * The circular collision shape of the Collidable object. Is 90% smaller than the sprite of the Game_Object.
     */
    sf::CircleShape collision_shape{};
};


#endif

#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H
#include "Updatable.h"
#include "Damageable.h"

/**
 * A destructible object in the game.
 *
 * The Destructible class gives all destructible Game_Objects that belong to the map
 * the functionality needed.
 */
class Destructible :public Updatable, public Damageable
{
public:
    /**
     * Constructor for the Destructible class.
     *
     * @param position The initial position of the Destructible object.
     * @param sprite The texture that is used to render the Destructible object.
     * @param health The amount of health points that the destructible object has.
     */
    Destructible(sf::Vector2f const& position, sf::Texture const& sprite, int health);

    /**
     * Destructor for Destructible class.
     */
    ~Destructible() override = default;

    /**
     * Checks that the health is above 0.
     *
     * @param delta_time The time since the update function was last called.
     * @param world A reference to the World object that the Destructible object exists in.
     * @param current_obj A shared pointer to the instance of the current Destructible, as stored in World.
     */
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;

    /**
     * Specifies what happens when the destructible is destroyed.
     *
     * @param destructible_target A shared pointer to the instance of the current Destructible, as stored in World.
     * @param world A reference to the World object that the Destructible object exists in.
     */
    virtual void destroy(std::shared_ptr<Game_Object> const& destructible_target, World & world) const = 0;
};

#endif
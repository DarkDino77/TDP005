#ifndef CRATE_H
#define CRATE_H
#include "Destructible.h"

/**
 * A crate object in the game.
 *
 * The Crate class inherits from the Destructible class and specifies what happens
 * when a crate is destroyed.
 */
class Crate : public Destructible
{
public:
    /**
     * Constructor for the Crate class.
     *
     * @param[in] position The initial position of the Crate object.
     * @param[in] sprite The texture that is used to render the Crate object.
     * @param[in] health The amount of health points that the crate has.
     */
    Crate(sf::Vector2f const& position, sf::Texture const& sprite, int const health);

    /**
     * Specifies what happens when the crate is destroyed (health below 0).
     *
     * @param[in] destructible_target A shared pointer to the instance of the current Crate, as stored in World.
     * @param[in] world A reference to the World object that the Crate object exists in.
     */
    void destroy(std::shared_ptr<Game_Object> const& destructible_target, World & world) const override;
};

#endif

#ifndef AMMO_H
#define AMMO_H

#include "Pick_Up.h"

/**
 * An ammo pickup in the game.
 *
 * The Ammo class inherits from the Pick-Up class and specifies
 * what happens when the player picks it up. Also manages ammo-type.
 */
class Ammo: public Pick_Up{
public:
    /**
     * Constructor for the Ammo class.
     *
     * @param[in] position The initial position of the Ammo object.
     * @param[in] sprite The texture that is used to render the Ammo object.
     * @param[in] ammo_type The type of ammo.
     */
    Ammo(sf::Vector2f const& position, sf::Texture const& sprite, std::string const& ammo_type);

protected:
    /**
     * Specifies what happens when the ammo object is picked up by the player.
     *
     * @param[in] other_obj A shared pointer to the Game_Object that collided with the Pick Up.
     */
    void pick_up(std::shared_ptr<Game_Object> const& other_obj) const override;

private:
    /**
     * Which ammo-type.
     */
    std::string const ammo_type{};
};


#endif

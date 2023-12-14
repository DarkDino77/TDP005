#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "Game_Object.h"

/**
 * @class Updatable
 * @brief Represents all game objects that should update each tick. Inherits from the Game_Object class.
 *
 * Updatable objects are those who should do something each tick, like move or check health.
 */
class Updatable : public Game_Object{
public:
    /**
     * @brief The constructor for the Updatable object.
     *
     * @param position The initial position of the Updatable object.
     * @param sprite The sprite used to render the Updatable object.
     */
    Updatable(sf::Vector2f const& position, sf::Texture const& sprite);

    /**
     * @brief The destructor of the Updatable object.
     */
    virtual ~Updatable() = default;

    /**
     * @brief Update function to be implemented in the subclasses of the Updatable class.
     */
    virtual void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) = 0;
};


#endif

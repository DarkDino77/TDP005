#ifndef EXPLOSIVE_BARREL_H
#define EXPLOSIVE_BARREL_H

#include "Destructible.h"

/**
 * @class Explosive_Barrel
 * @brief Represents an explosive barrel that inherits from the Destructible class.
 */
class Explosive_Barrel : public Destructible {
public:
    /**
     * @brief Constructor for the Explosive_Barrel class.
     * @param position The position of the explosive barrel.
     * @param sprite The texture for the explosive barrel's sprite.
     * @param health The initial health of the explosive barrel.
     */
    Explosive_Barrel(sf::Vector2f const& position, sf::Texture const& sprite, int const health);

    /**
     * @brief Destroys the explosive barrel, creating an instace of exploison on it's current position
     * @param destructible_target Shared pointer to the destructible target affected by the explosion.
     * @param world Reference to the game world.
     */
    void destroy(std::shared_ptr<Game_Object> const& destructible_target, World & world) const override;
};



#endif

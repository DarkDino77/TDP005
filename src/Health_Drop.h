#ifndef HEALTH_DROP_H
#define HEALTH_DROP_H

#include "Pick_Up.h"

/**
 * @class Health_Drop
 * @brief Represents a available pick up that should heal the target that picks it up
 */
class Health_Drop: public Pick_Up{
public:
    /**
     * @brief The constructor for Health_Drop
     * @param position Represents the postions that the Health_Drop takes
     * @param sprite Represents the Texture that the Health_Drop displays
     */
    Health_Drop(sf::Vector2f const& position, sf::Texture const& sprite);
protected:
    /**
     * @brief This function adds health to the player when he picks up the Health Drop
     * @param other_obj This represents the Player.
     */
    void pick_up(std::shared_ptr<Game_Object> const& other_obj) const override;

};


#endif

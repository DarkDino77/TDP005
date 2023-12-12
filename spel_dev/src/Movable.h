#ifndef MOVABLE_H
#define MOVABLE_H
#include "Collidable.h"

/**
 * @class Movable
 * @brief This class represents the ability for objects to move around and inherits from the Collidable class.
 */
class Movable : public Collidable
{
public:
    /**
     * @brief This is the constructor for a movable object.
     *
     * @param position This represents it's initial position.
     * @param sprite This represents the Texture that it displays.
     * @param speed This is the speed that a game object is abel to move around in the game world with.
     */
    Movable(sf::Vector2f const& position, sf::Texture const& sprite, float const speed);

protected:
    /**
     * This variable represents the speed that the game object is abel to move around the world with.
     */
    double speed{};

    /**
     * This parameter represents the vector direction that the game object has.
     */
    sf::Vector2f direction{};

    /**
     * @brief moves a movable object based on the amount of time that has passed since the game object last moved.
     *
     * @param delta_time This variable represents the reletive time that has passed in world
     * relative to the game object.
     */
    void update_position(sf::Time const& delta_time);

    /**
     * @brief Rotates a the movable object relative to a rotation vector.
     *
     * @param rotate_direction Specifies which direction the Movable object should be rotated to.
     */
    void set_rotation(sf::Vector2f const& rotate_direction);

};


#endif

#ifndef MOVABLE_H
#define MOVABLE_H
#include "Collidable.h"

/**
 * @class Movable
 * @brief This class represents the ability for objects to move around
 */
class Movable : public Collidable
{
public:
    Movable(sf::Vector2f const& position, sf::Texture const& sprite, float const speed);
//move function ?
protected:
    double speed{};
    sf::Vector2f direction{};

    void update_position(sf::Time const& delta_time);
    void set_rotation(sf::Vector2f const& rotate_direction);

};


#endif

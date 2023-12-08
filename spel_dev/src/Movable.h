#ifndef MOVABLE_H
#define MOVABLE_H
#include "Collidable.h"

class Movable : public Collidable
{
public:
    Movable(sf::Vector2f position, sf::Texture const& sprite, float speed);

protected:
    double speed{};
    sf::Vector2f direction{};

    void update_position(sf::Time const& delata_time);
    void set_rotation(sf::Vector2f rotate_direction);

};


#endif

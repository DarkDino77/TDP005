#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Game_Object.h"

class Collidable: public Game_Object
{
public:
    Collidable(sf::Vector2f position, sf::Texture const& sprite);
    sf::CircleShape get_collision_shape();
protected:
    sf::CircleShape collision_shape{};
};


#endif

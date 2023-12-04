#ifndef MOVABLE_H
#define MOVABLE_H
#include "Game_Object.h"

class Movable : public Game_Object
{
public:
    sf::CircleShape collision_shape{};
    sf::Vector2f direction{};

    Movable(sf::Vector2f position, sf::Texture const& sprite, float speed);

protected:
    double speed{};
};


#endif

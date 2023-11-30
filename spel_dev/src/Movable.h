#ifndef MOVABLE_H
#define MOVABLE_H
#include "Game_Object.h"


class Movable : public Game_Object
{
public:
    Movable(sf::Vector2f position, sf::Texture const& sprite, bool detect_collision);
private:
    sf::Vector2f direction{};
    double speed{};
};


#endif

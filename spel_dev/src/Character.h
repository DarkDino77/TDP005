#ifndef CHARACTER_H
#define CHARACTER_H
#include "Movable.h"

class Character : public Movable
{
public:
    Character(sf::Vector2f position, sf::Texture const& sprite);
private:
    int health{};
};

#endif

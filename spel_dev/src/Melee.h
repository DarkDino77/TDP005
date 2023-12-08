#ifndef MELEE_H
#define MELEE_H

#include "Enemy.h"

class Melee : public Enemy
{
public:
    Melee(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, int const melee_damage, int const xp);
};

#endif

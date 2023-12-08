#ifndef MELEE_H
#define MELEE_H

#include "Enemy.h"

class Melee : public Enemy
{
public:
    Melee(sf::Vector2f position, sf::Texture const& sprite, float speed,int health, int melee_damage, int xp);
};

#endif

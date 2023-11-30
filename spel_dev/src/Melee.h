#ifndef MELEE_H
#define MELEE_H

#include "Enemy.h"

class Melee : public Enemy
{
    Melee(sf::Vector2f position, sf::Texture const& sprite);
};


#endif //SPEL_DEV_MELEE_H

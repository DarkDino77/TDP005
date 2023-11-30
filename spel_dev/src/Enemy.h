#ifndef ENEMY_H
#define ENEMY_H

#include "World.h"
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(sf::Vector2f position, sf::Texture const& sprite);
};


#endif

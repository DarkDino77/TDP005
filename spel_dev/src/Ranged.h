#ifndef RANGED_H
#define RANGED_H

#include "Enemy.h"

class Ranged : public Enemy
{
public:
    Ranged(sf::Vector2f position, sf::Texture const& sprite, float speed, int health, int melee_damage, int xp);
    void update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj) override;
};


#endif

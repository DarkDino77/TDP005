#ifndef RANGED_H
#define RANGED_H


#include "Enemy.h"

class Ranged : public Enemy
{
public:
    Ranged(sf::Vector2f position, sf::Texture const& sprite, float speed,int health, int melee_damage);
    void update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> current_obj) override;
private:
    float life_time{0};
    float melee_timer{0};
};


#endif

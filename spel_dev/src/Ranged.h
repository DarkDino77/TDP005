#ifndef RANGED_H
#define RANGED_H

#include "Enemy.h"

class Ranged : public Enemy
{
public:
    Ranged(sf::Vector2f const& position, sf::Texture const& sprite,
           float const speed, int const health, int const melee_damage, int const xp);
    ~Ranged() override = default;
    void update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj) override;
};


#endif

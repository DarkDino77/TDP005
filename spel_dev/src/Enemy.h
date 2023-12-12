#ifndef ENEMY_H
#define ENEMY_H

#include "World.h"
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, int const melee_damage, int const xp);
    virtual ~Enemy() = 0;
    void handle_collision( World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;
protected:
    float life_time{0};
    float melee_timer{0};
    int melee_damage{};
    int xp{};
};

#endif

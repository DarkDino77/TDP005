#ifndef ENEMY_H
#define ENEMY_H

#include "World.h"
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(sf::Vector2f position, sf::Texture const& sprite, float speed, int health ,int melee_damage);
    void handle_collision( World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;

protected:
    float life_time{0};
    float melee_timer{0};
    int melee_damage{};
};


#endif

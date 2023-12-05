#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H
#include "Map_Object.h"
#include "Damageable.h"

class Destructible :public Map_Object, public Damageable{
public:
    Destructible(sf::Vector2f const& position, sf::Texture const& sprite, int health);
    void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) override;
    virtual void destroy(std::shared_ptr<Game_Object> destructible_target, World & world) = 0;

};


#endif
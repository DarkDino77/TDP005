#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H
#include "Updatable.h"
#include "Damageable.h"

class Destructible :public Updatable, public Damageable
{
public:
    Destructible(sf::Vector2f const& position, sf::Texture const& sprite, int health);
    ~Destructible() override = default;
    void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) override;
    virtual void destroy(std::shared_ptr<Game_Object> const& destructible_target, World & world) const = 0;

};


#endif
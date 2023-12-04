#ifndef CRATE_H
#define CRATE_H
#include "Destructible.h"

class Crate : public Destructible
{
public:
    Crate(sf::Vector2f const& position, sf::Texture const& sprite, int health);
    void destroy(std::shared_ptr<Game_Object> destructible_target, World & world) override;
};


#endif

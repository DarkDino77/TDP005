#ifndef EXPLOSIVE_BARREL_H
#define EXPLOSIVE_BARREL_H
#include "Destructible.h"

class Explosive_Barrel: public Destructible{
public:
    Explosive_Barrel(sf::Vector2f const& position, sf::Texture const& sprite, int const health);
    void destroy(std::shared_ptr<Game_Object> const& destructible_target, World & world) const override;
};


#endif

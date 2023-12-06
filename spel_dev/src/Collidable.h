#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Updatable.h"

class Collidable: public Updatable
{
public:
    Collidable(sf::Vector2f position, sf::Texture const& sprite);
    virtual ~Collidable() = default;
    sf::CircleShape get_collision_shape();
    virtual void handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const&) = 0;
protected:
    sf::CircleShape collision_shape{};
};


#endif

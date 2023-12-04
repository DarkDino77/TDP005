#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H
#include "Map_Object.h"

class Destructible :public Map_Object{
public:
    Destructible(sf::Vector2f const& position, sf::Texture const& sprite, int health);
    void take_damage(int damage, std::shared_ptr<Game_Object> destructible_target, World & world);
    virtual void destroy(std::shared_ptr<Game_Object> destructible_target, World & world) = 0;
protected:
    int health{};
};


#endif
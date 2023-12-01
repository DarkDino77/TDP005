#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Movable.h"

class Movable;

class Bullet :public Movable{
public:
    Bullet(int damage, sf::Vector2f const& direction, double speed, sf::Texture const& sprite, sf::Vector2f & position, World & world);
    void update(sf::Time const& delta_time, World & world, sf::Window & window, std::shared_ptr<Game_Object> obj) override;
    int damage;
};

#endif

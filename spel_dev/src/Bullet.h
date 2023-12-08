#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Movable.h"

class Movable;

class Bullet :public Movable{
public:
    Bullet(int damage, sf::Vector2f const& direction, double const speed, sf::Texture const& sprite, sf::Vector2f const& position, std::shared_ptr<Game_Object> const& source);
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;
    void handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;
private:
    int const damage;
    std::shared_ptr<Game_Object> const source;
    bool is_alive{true};
};

#endif

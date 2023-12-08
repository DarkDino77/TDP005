#ifndef EXPLOSION_H
#define EXPLOSION_H


#include "Collidable.h"

class Explosion : public Collidable
{
public:
    Explosion(sf::Vector2f const& position, sf::Texture const& sprite, float const explosive_radius, int const explosive_damage);
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;
    void handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;

private:
    float explosive_radius{};
    float life_time{0};
    float life_span{2};
    int explosive_damage{};
    std::vector<std::shared_ptr<Game_Object>> exploded_objects{};
};



#endif

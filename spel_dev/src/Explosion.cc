#include "Explosion.h"
#include "World.h"
#include "Destructible.h"
#include "point.h"
#include <iostream>

Explosion::Explosion(sf::Vector2f const& position, sf::Texture const& sprite, float explosive_radius, int explosive_damage)
: Game_Object(position, sprite), explosive_radius{explosive_radius}, explosive_damage(explosive_damage)
{
    collision_shape.setRadius(shape.getSize().x);
    collision_shape.setOrigin({collision_shape.getRadius(),collision_shape.getRadius()});
    collision_shape.setPosition(position);
    collision_shape.setFillColor(sf::Color::Red);
}

void Explosion::update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> current_obj)
{
    life_time += delta_time.asSeconds();
    if(life_time > life_span)
    {
        world.kill_queue.push_back(current_obj);
    }
}

void Explosion::handle_collision( World &, std::shared_ptr<Game_Object>, std::shared_ptr<Game_Object> other_obj)
{
    std::shared_ptr<Damageable> damageable_target =  std::dynamic_pointer_cast<Damageable>(other_obj);
    if(damageable_target == nullptr)
    {
        return;
    }

    auto it = std::find(exploded_objects.begin(), exploded_objects.end(),other_obj);
    if(it == exploded_objects.end())
    {
        damageable_target->take_damage(explosive_damage);
        exploded_objects.push_back(other_obj);
    }

    std::shared_ptr<Character> character_target =  std::dynamic_pointer_cast<Character>(other_obj);
    if(character_target != nullptr)
    {
        character_target->knock_back(normalize(position - character_target->position), 3);
    }
}
#include "Explosion.h"
#include "World.h"
#include "Destructible.h"
#include "point.h"

Explosion::Explosion(sf::Vector2f const& position, sf::Texture const& sprite, float const explosive_radius, int const explosive_damage)
: Collidable(position, sprite), explosive_damage(explosive_damage)
{
    shape.setSize({explosive_radius, explosive_radius});
    collision_shape.setRadius(explosive_radius);
    collision_shape.setOrigin(explosive_radius, explosive_radius);
    shape.setOrigin(collision_shape.getOrigin()/2.0f);
    shape.setPosition(collision_shape.getPosition());
}

void Explosion::update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj)
{
    life_time += delta_time.asSeconds();
    if(life_time > life_span)
    {
        world.kill(current_obj);
    }
}

void Explosion::handle_collision( World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const& other_obj)
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
        character_target->knock_back(normalize(position - character_target->get_position()), 3);
    }
}
#include "Explosion.h"
#include "World.h"
#include "Destructible.h"

Explosion::Explosion(sf::Vector2f const& position, sf::Texture const& sprite, float explosive_radius, int explosive_damage)
: Game_Object(position, sprite), explosive_radius{explosive_radius}, explosive_damage(explosive_damage)
{}

void Explosion::update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> current_obj)
{
    life_time += delta_time.asSeconds();
    if(life_time > life_span)
    {
        world.kill_queue.push_back(current_obj);
    }
}

void Explosion::handle_collision(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> current_obj, std::shared_ptr<Game_Object> other_obj)
{
    std::shared_ptr<Character> character_target =  std::dynamic_pointer_cast<Character>(other_obj);
    std::shared_ptr<Destructible> destructible_target =  std::dynamic_pointer_cast<Destructible>(other_obj);
    if(character_target == nullptr && destructible_target == nullptr)
    {
        return;
    }

    auto it = std::find(exploded_objects.begin(), exploded_objects.end(),other_obj);
    if(it != exploded_objects.end())
    {
        if(character_target != nullptr) {
            character_target->take_damage(explosive_damage);
        }
        else if(destructible_target)
        {
            destructible_target->take_damage(explosive_damage, other_obj, world);
        }
        exploded_objects.push_back(other_obj);
    }
}
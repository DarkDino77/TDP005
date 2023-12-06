#include "Destructible.h"

Destructible::Destructible(sf::Vector2f const& position, sf::Texture const& sprite, int health)
: Updatable(position, sprite), Damageable(health)
{}

void Destructible::update(sf::Time const& , World & world, std::shared_ptr<Game_Object> const& current_obj)
{
    if(health <= 0)
    {
        destroy(current_obj, world);
    }
}

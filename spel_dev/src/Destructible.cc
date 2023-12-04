#include "Destructible.h"

Destructible::Destructible(sf::Vector2f const& position, sf::Texture const& sprite, int health)
: Map_Object(position, sprite), health{health}
{}

void Destructible::take_damage(int damage, std::shared_ptr<Game_Object> destructible_target, World & world)
{
    health -= damage;
    if(health <= 0)
    {
        destroy(destructible_target, world);
    }
}

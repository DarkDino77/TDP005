#include <iostream>
#include "Explosive_Barrel.h"
#include "World.h"

Explosive_Barrel::Explosive_Barrel(sf::Vector2f const& position, sf::Texture const& sprite, int const health)
: Destructible(position, sprite, health)
{}

void Explosive_Barrel::destroy(std::shared_ptr<Game_Object> const& destructible_target, World & world) const
{
    world.get_resource_manager().play_sound("explosion");
    world.add_explosion(position, 80, 30);
    world.kill(destructible_target);
}

#include <iostream>
#include "Explosive_Barrel.h"
#include "World.h"

Explosive_Barrel::Explosive_Barrel(sf::Vector2f const& position, sf::Texture const& sprite, int health)
: Destructible(position, sprite, health)
{}

void Explosive_Barrel::destroy(std::shared_ptr<Game_Object> destructible_target, World & world)
{
    world.play_sound("explosion");
    world.add_explosion(position, 80, 30);
    world.kill(destructible_target);
}

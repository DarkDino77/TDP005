#include <iostream>
#include "Crate.h"
#include "World.h"

Crate::Crate(sf::Vector2f const& position, sf::Texture const& sprite, int health)
: Destructible(position, sprite, health)
{}

void Crate::destroy(std::shared_ptr<Game_Object> destructible_target, World & world)
{
    world.kill_queue.push_back(destructible_target);
}

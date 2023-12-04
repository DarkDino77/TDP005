#include <iostream>
#include "Explosive_Barrel.h"
#include "World.h"

Explosive_Barrel::Explosive_Barrel(sf::Vector2f const& position, sf::Texture const& sprite, int health)
: Destructible(position, sprite, health)
{}

void Explosive_Barrel::destroy(std::shared_ptr<Game_Object> destructible_target, World & world)
{
    world.add_explosion("player", position);
    std::cout << "Added explosion" << std::endl;
    world.kill_queue.push_back(destructible_target);
}

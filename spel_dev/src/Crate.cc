#include <iostream>
#include "Crate.h"
#include "World.h"

Crate::Crate(sf::Vector2f const& position, sf::Texture const& sprite, int const health)
: Destructible(position, sprite, health)
{}

void Crate::destroy(std::shared_ptr<Game_Object> const& destructible_target, World & world) const
{
    world.play_sound("crate_destroy");
    world.kill(destructible_target);
}

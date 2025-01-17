#include <SFML/Graphics.hpp>
#include "Ranged.h"

Ranged::Ranged(sf::Vector2f const& position, sf::Texture const& sprite,
               float const speed, int const health, int const melee_damage, int const xp)
        : Enemy(position, sprite, speed, health, melee_damage, xp)
{
    //TODO: Fix so that ranged enemy takes in weapon parameter as a construction variable
    available_weapons.push_back(std::make_shared<Weapon>("spitter", 5, -1, 1.0f, 0.5));
    current_weapon = available_weapons.at(0);
}

void Ranged::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj)
{
    Enemy::update(delta_time, world, current_obj);

    if(current_weapon->can_shoot())
    {
        if(world.can_see_player(current_obj, direction))
        {
            current_weapon->shoot(direction, world, position, false);
        }
    }
}

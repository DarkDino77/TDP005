#include "Ranged.h"
#include "point.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Ranged::Ranged(sf::Vector2f position, sf::Texture const& sprite, float speed,int health, int melee_damage, int xp)
        : Enemy(position, sprite, speed, health, melee_damage, xp)
{
    //TODO: Fix so that ranged enemy takes in weapon parameter as a construction variable
    available_weapons.push_back(std::make_shared<Weapon>("spitter", 5, -1, 1.0f, 0.5));
    current_weapon = available_weapons.at(0);
}

void Ranged::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj)
{
    Enemy::update(delta_time, world, current_obj);

    if(current_weapon->can_shoot() && world.can_see_player(current_obj, direction))
    {
        current_weapon->shoot(direction, world, position, current_obj);
    }
}

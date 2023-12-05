#include "Ranged.h"
#include "point.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Ranged::Ranged(sf::Vector2f position, sf::Texture const& sprite, float speed,int health, int melee_damage)
        : Enemy(position, sprite, speed, health, melee_damage)
{
    available_weapons.push_back(std::make_shared<Weapon>("spitter", 5, "spitter_ammo", -1, 1.0f, 0.5));
    current_weapon = available_weapons.at(0);
}



void Ranged::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj)
{
    if(health <= 0)
    {
        world.kill(current_obj);
        return;
    }

    life_time += delta_time.asSeconds();
    std::shared_ptr<Player> player{world.get_player()};

    // Rotate the enemy towards the player.
    sf::Vector2f rotate_direction = normalize(position - (player -> position));
    direction = rotate_direction;
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);
    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);

    // Update the enemy position based on delta time.
    float distance = 250.0f * delta_time.asSeconds() * float(speed);
    position -= rotate_direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);

    if(current_weapon->can_shoot() && world.can_see_player(current_obj, direction))
    {
        current_weapon->shoot(direction, world, position, current_obj);
    }
}

#include "Melee.h"
#include "point.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Melee::Melee(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, int const melee_damage, int const xp)
        : Enemy(position, sprite, speed, health, melee_damage, xp)
{}
/*
void Melee::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj)
{
    if(health <= 0)
    {
        world.kill(current_obj);
        return;
    }
    life_time += delta_time.asSeconds();
    std::shared_ptr<Player> player{world.get_player()};

    // Rotate the enemy towards the player.
    sf::Vector2f rotate_direction = normalize(position - (player -> get_position()));
    direction = rotate_direction;
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);
    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);

    // Update the enemy position based on delta time.
    float distance = 250.0f * delta_time.asSeconds() * float(speed);
    position -= rotate_direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}
*/


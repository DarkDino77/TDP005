
#include "Weapon.h"
#include <iostream>
Weapon::Weapon(std::string name, int damage, std::string ammo_type, int ammo_capacity, double bullet_speed, double fire_rate)
: name{name}, damage{damage}, ammo_type{ammo_type}, ammo_capacity{ammo_capacity}, bullet_speed{bullet_speed}, fire_rate{fire_rate}
{}

bool Weapon::can_shoot()
{
    return time_since_shot.getElapsedTime().asSeconds() > 1/fire_rate;
}

void Weapon::shoot(sf::Vector2f direction, World & world, sf::Vector2f position, std::shared_ptr<Game_Object> source)
{
    if(can_shoot())
    {
        world.play_sound(name + "_shoot");
        sf::Vector2f bullet_spawn{position -= direction*32.0f};
        std::shared_ptr<Bullet> bullet{std::make_shared<Bullet>(damage, direction, bullet_speed, *world.sprites[ammo_type], bullet_spawn, source)};
        world.add_queue.push_back(bullet);
        time_since_shot.restart();
    }
}
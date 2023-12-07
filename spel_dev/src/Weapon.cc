
#include "Weapon.h"
#include <iostream>
Weapon::Weapon(std::string const& name, int damage, int ammo_capacity, double bullet_speed, double fire_rate)
: name{name}, damage{damage}, ammo_capacity{ammo_capacity}, bullet_speed{bullet_speed}, fire_rate{fire_rate}
{}

bool Weapon::can_shoot()
{
    return time_since_shot.getElapsedTime().asSeconds() > 1/fire_rate;
}

bool Weapon::shoot(sf::Vector2f const& direction, World & world, sf::Vector2f const& position, std::shared_ptr<Game_Object> const& source)
{
    if(can_shoot() && (ammo_capacity == -1 || ammo_amount > 0 ))
    {
        world.play_sound(name + "_shoot");
        sf::Vector2f bullet_spawn{position - direction*16.0f};
        world.add_bullet(damage, direction, bullet_speed, name + "_bullet", bullet_spawn, source);
        time_since_shot.restart();
        ammo_amount--;
        return true;
    }
    return false;
}

std::string Weapon::get_ammo_type()
{
    return name + "_ammo";
}
void Weapon::add_ammo(int amount)
{
    ammo_amount += amount;
    if (ammo_capacity != -1 && ammo_amount > ammo_capacity)
    {
        ammo_amount -= ammo_amount - ammo_capacity;
    }
}

int Weapon::get_ammo_amount()
{
    return ammo_amount;
}

int Weapon::get_ammo_capacity()
{
    return ammo_capacity;
}
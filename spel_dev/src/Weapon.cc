
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
    if(can_shoot() && (ammo_capacity == -1 || ammo_amount > 0 ))
    {
        std::cout << "Could shoot" << std::endl;
        world.play_sound(name + "_shoot");
        sf::Vector2f bullet_spawn{position -= direction*16.0f};
        world.add_bullet(damage, direction, bullet_speed, ammo_type, bullet_spawn, source);
        time_since_shot.restart();
        ammo_amount--;
    }

}
std::string Weapon::get_ammo_type()
{
    return ammo_type;
}
void Weapon::add_ammo(int amount)
{
    ammo_amount += amount;
    if (ammo_capacity != -1 && ammo_amount > ammo_capacity)
    {
        ammo_amount -= ammo_amount - ammo_capacity;
    }
}
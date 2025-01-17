#include "Weapon.h"
#include "Bullet.h"

Weapon::Weapon(std::string const& name, int const damage, int const ammo_capacity,
               double const bullet_speed, double const fire_rate)
: name{name}, damage{damage}, ammo_capacity{ammo_capacity}, bullet_speed{bullet_speed}, fire_rate{fire_rate}
{}

bool Weapon::can_shoot() const
{
    return time_since_shot.getElapsedTime().asSeconds() > 1/fire_rate;
}

bool Weapon::shoot(sf::Vector2f const& direction, World & world, sf::Vector2f const& position, bool const is_friendly)
{
    if(can_shoot() && (ammo_capacity == -1 || ammo_amount > 0 ))
    {
        world.get_resource_manager().play_sound(name + "_shoot");
        sf::Vector2f bullet_spawn{position - direction*16.0f};
        world.add_bullet(damage, direction, bullet_speed, name + "_bullet", bullet_spawn, is_friendly);
        time_since_shot.restart();
        ammo_amount--;
        return true;
    }
    return false;
}

std::string& Weapon::get_name()
{
    return name;
}
void Weapon::add_ammo(int const amount)
{
    ammo_amount += amount;
    if (ammo_capacity != -1 && ammo_amount > ammo_capacity)
    {
        ammo_amount -= ammo_amount - ammo_capacity;
    }
}

int Weapon::get_ammo_amount() const
{
    return ammo_amount;
}

int Weapon::get_ammo_capacity() const
{
    return ammo_capacity;
}
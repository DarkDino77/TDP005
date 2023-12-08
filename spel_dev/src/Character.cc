#include "Character.h"
#include "World.h"

Character::Character(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health)
: Movable(position, sprite, speed), Damageable(health)
{}

void Character::knock_back(sf::Vector2f const& direction, float force)
{
    position -= direction * force;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}
void Character::add_weapon(std::string const& name, int const damage,
                           int const ammo_capacity, double bullet_speed,double fire_rate)
{
    available_weapons.push_back(std::make_shared<Weapon>(name, damage, ammo_capacity, bullet_speed, fire_rate));
}
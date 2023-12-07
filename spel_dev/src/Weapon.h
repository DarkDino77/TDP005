#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Bullet.h"

class Weapon {
public:
    Weapon(std::string const& name, int damage, int ammo_capacity, double bullet_speed, double fire_rate);
    //sf::Texture const& hud_sprite;
    bool shoot(sf::Vector2f const& direction, World & world, sf::Vector2f const& position, std::shared_ptr<Game_Object> const& source);
    bool can_shoot();
    std::string get_ammo_type();
    void add_ammo(int amount);
    int get_ammo_amount();
    int get_ammo_capacity();

private:
    std::string name;
    int damage;
    int ammo_capacity;
    int ammo_amount{0};
    double bullet_speed;
    double fire_rate;
    sf::Clock time_since_shot{};
};

#endif

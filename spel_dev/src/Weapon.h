#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Bullet.h"

class Weapon {
public:
    Weapon(std::string const& name, int const damage, int const ammo_capacity,
           double const bullet_speed, double const fire_rate);
    //sf::Texture const& hud_sprite;
    bool shoot(sf::Vector2f const& direction, World & world,
               sf::Vector2f const& position, std::shared_ptr<Game_Object> const& source);
    bool can_shoot() const;
    std::string& get_name();
    void add_ammo(int const amount);
    int get_ammo_amount() const;
    int get_ammo_capacity() const;

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

#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Bullet.h"

class Weapon {
public:
    Weapon(std::string name, int damage, std::string ammo_type, int ammo_capacity, double bullet_speed, double fire_rate);
    //sf::Texture const& hud_sprite;
    void shoot(sf::Vector2f direction, World & world, sf::Vector2f position, std::shared_ptr<Game_Object> source);
    bool can_shoot();

private:
    std::string name;
    int damage;
    std::string ammo_type;
    int ammo_capacity;
    double bullet_speed;
    double fire_rate;
    sf::Clock time_since_shot{};
};


#endif

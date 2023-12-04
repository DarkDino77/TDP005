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
    std::string name;
    int damage;
    std::string ammo_type;
    int ammo_capacity;
    double bullet_speed;
    double fire_rate;
    bool can_shoot();
    void shoot(sf::Vector2f direction, World & world, sf::Vector2f position, std::shared_ptr<Game_Object> source);

private:
    sf::Clock time_since_shot{};
};


#endif

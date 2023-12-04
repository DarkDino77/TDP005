#include <cmath>
#include <iostream>
#include "Bullet.h"
#include "World.h"
#include "Destructible.h"

Bullet::Bullet(int damage, sf::Vector2f const& aim_direction, double speed, sf::Texture const& sprite, sf::Vector2f & position, std::shared_ptr<Game_Object> source)
: Movable(position, sprite, speed), damage{damage}, source{source}
{
    direction = aim_direction;
    float rotate_degrees = std::atan2(direction.y, direction.x);
    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);
}

void Bullet::update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> obj)
{
    float distance = 250.0f * delta_time.asSeconds() * speed;
    position -= direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}

void Bullet::handle_collision(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> current_obj, std::shared_ptr<Game_Object> other_obj)
{
    if (other_obj == source || not is_alive || std::dynamic_pointer_cast<Bullet>(other_obj) != nullptr)
    {
        return;
    }

    std::shared_ptr<Character> character_target =  std::dynamic_pointer_cast<Character>(other_obj);
    std::shared_ptr<Destructible> destructible_target =  std::dynamic_pointer_cast<Destructible>(other_obj);
    if(character_target != nullptr) {
        character_target->take_damage(damage);
        character_target->knock_back(direction);
    }
    else if(destructible_target)
    {
        destructible_target->take_damage(damage, other_obj, world);
    }

    world.kill_queue.push_back(current_obj);
    is_alive = false;
}



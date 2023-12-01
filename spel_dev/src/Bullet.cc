#include <cmath>
#include "Bullet.h"
#include "World.h"
#include <iostream>
#include <vector>

Bullet::Bullet(int damage, sf::Vector2f const& aim_direction, double speed, sf::Texture const& sprite, sf::Vector2f & position, World & world)
: Movable(position, sprite, speed), damage{damage}
{
    direction = aim_direction;
    float rotate_degrees = std::atan2(direction.y, direction.x);
    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);
}

void Bullet::update(sf::Time const& delta_time, World & world, sf::Window & window, std::shared_ptr<Game_Object> obj)
{
    float distance = 250.0f * delta_time.asSeconds() * speed;
    position -= direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);

    for(std::shared_ptr<Game_Object> collide_obj : world.game_objects) {
        std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(collide_obj)};
        bool collides{};
        collides = (collide_obj != obj && collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()));
        if(collides)
        {
            if(movable_target == nullptr) // Collides with non-movable object
            {
                std::cout << "Collided with movable object" << std::endl;
            }
            //auto it = std::remove(world.game_objects.begin(), world.game_objects.end(), obj);
            //world.game_objects.erase(it);
            //std::erase(std::remove(world.game_objects.begin(), world.game_objects.end(), obj), world.game_objects.end())
        }
    }
}



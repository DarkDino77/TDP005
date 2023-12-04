#include <cmath>
#include "Bullet.h"
#include "World.h"

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

    for(std::shared_ptr<Game_Object> const& collide_obj : world.game_objects) {
        std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(collide_obj)};
        std::shared_ptr<Bullet> bullet_target{std::dynamic_pointer_cast<Bullet>(collide_obj)};
        bool collides {bullet_target == nullptr && collide_obj != obj && collide_obj != source && collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds())};
        if(collides)
        {
            if(movable_target != nullptr) // Collides with non-movable object
            {
                std::dynamic_pointer_cast<Character>(collide_obj)->take_damage(damage);
                // TODO: Apply damage to target
            }
            world.kill_queue.push_back(obj);
            break;
        }
    }
}



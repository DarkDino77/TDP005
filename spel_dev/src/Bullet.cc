#include <cmath>
#include <iostream>
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

    /*for(std::shared_ptr<Game_Object> const& collide_obj : world.game_objects) {
        std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(collide_obj)};
        std::shared_ptr<Bullet> bullet_target{std::dynamic_pointer_cast<Bullet>(collide_obj)};
        bool collides {bullet_target == nullptr && collide_obj != obj && collide_obj != source && collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds())};
        if(collides)
        {
            if(movable_target != nullptr) // Collides with non-movable object
            {
                std::shared_ptr<Character> character =  std::dynamic_pointer_cast<Character>(collide_obj);
                if(character != nullptr)
                {
                    character->take_damage(damage);
                    character->knock_back(direction);
                }

            }
            world.kill_queue.push_back(obj);
            break;
        }
    }*/
}

void Bullet::handle_collision(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> current_obj, std::shared_ptr<Game_Object> other_obj)
{
    if (other_obj == source || not is_alive || std::dynamic_pointer_cast<Bullet>(other_obj) != nullptr)
    {
        return;
    }

    std::shared_ptr<Character> character_target =  std::dynamic_pointer_cast<Character>(other_obj);
    if(character_target != nullptr) {
        character_target->take_damage(damage);
        character_target->knock_back(direction);
    }

    std::cout << "Added to killqueue, current object: " << current_obj << ", other object: " << other_obj << ", player: " << world.get_player() << ", first obj: " << world.game_objects.at(1) << std::endl;
    world.kill_queue.push_back(current_obj);
    is_alive = false;
}



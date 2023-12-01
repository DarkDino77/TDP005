#include "Melee.h"
#include "point.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

Melee::Melee(sf::Vector2f position, sf::Texture const& sprite, float speed)
        : Enemy(position, sprite, speed)
{}

void Melee::update(sf::Time const& delta_time, World &world, sf::Window &window, std::shared_ptr<Game_Object> obj)
{
    std::shared_ptr<Player> player{world.get_player()};

    sf::Vector2f rotate_direction = normalize(position - (player -> position));
    direction = rotate_direction;
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);
    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);

    rotate_direction.x*= speed;
    rotate_direction.y*= speed;
    position-= rotate_direction;
    shape.setPosition(position);
    collision_shape.setPosition(position);

    for(std::shared_ptr<Game_Object> collide_obj : world.game_objects) {
        std::shared_ptr<Movable> target_obj{std::dynamic_pointer_cast<Movable>(collide_obj)};

        bool collides{};
        if(target_obj == nullptr) // Collides with non-movable object
        {
            collides = (collide_obj != obj
                                 && collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds())
                                 && (length(position - collide_obj->position)
                                     <= std::sqrt(std::pow(collision_shape.getRadius(),2)
                                                  + std::pow(length({collide_obj->shape.getSize().x/2.0f, collide_obj->shape.getSize().x/2.0f}),2) ) * 2.0f) // TODO: Fix this so that * 1.95 is not necessary.
            );
        }
        else // Collides with movable object.
        {
            collides = (collide_obj != obj && collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()));
        }

        if(collides)
        {
            sf::Vector2f push_direction{};
            push_direction = normalize(position - collide_obj->position);
            float temp_increment{0.005f};

            if(target_obj == nullptr)
            {
                if((push_direction.x * push_direction.x) >= (push_direction.y * push_direction.y))
                {
                    push_direction.y = 0.0f;
                    if(push_direction.x > 0)
                    {
                        push_direction.x = 1.0f;
                    }
                    else
                    {
                        push_direction.x = -1.0f;
                    }
                }
                else
                {
                    push_direction.x = 0.0f;
                    if(push_direction.y > 0)
                    {
                        push_direction.y = 1.0f;
                    }
                    else
                    {
                        push_direction.y = -1.0f;
                    }
                }
                while (collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()) )
                {
                    position += (push_direction * temp_increment);
                    shape.setPosition(position);
                    collision_shape.setPosition(position);

                    direction = normalize(position - (player -> position));
                }
            }
            else
            {
                while (collision_shape.getGlobalBounds().intersects((target_obj->collision_shape).getGlobalBounds()) )
                {
                    position += (push_direction * temp_increment);
                    shape.setPosition(position);
                    collision_shape.setPosition(position);

                    direction = normalize(position - (player -> position));
                }
            }

            /*if(collide_obj == player) { === Pushback ===
                position += push_direction * temp_increment;
                shape.setPosition(position);
                collision_shape.setPosition(position);
            }*/
        }
    }
}



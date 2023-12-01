#include "Melee.h"
#include "point.h"
#include <iostream>

Melee::Melee(sf::Vector2f position, sf::Texture const& sprite, float speed)
        : Enemy(position, sprite, speed)
{}

void Melee::update(sf::Time const& delta_time, World &world, sf::Window &window, std::shared_ptr<Game_Object> obj)
{
    std::shared_ptr<Player> player{world.get_player()};

    sf::Vector2f rotate_direction = normalize(position - (player -> position));
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);

    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);

    rotate_direction.x*= speed;
    rotate_direction.y*= speed;
    position-= rotate_direction;
    shape.setPosition(position);
    collision_shape.setPosition(position);

    for(std::shared_ptr<Game_Object> collide_obj : world.game_objects) {
        const bool collides = ( collide_obj != obj && (collision_shape).getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()) );

        if(collides)
        {
            sf::Vector2f push_direction{};
            push_direction = normalize(get_collision_shape().getPosition() - collide_obj->get_collision_shape().getPosition());

            float temp_increment{0.5f};

            /*if(collide_obj == player) {
                position += push_direction * temp_increment; // TODO: The game crashes if the knockback is to small and the player is not moving.
                shape.setPosition(position);
                collision_shape.setPosition(position);
            }*/

            while ((get_collision_shape()).getGlobalBounds().intersects((collide_obj->get_collision_shape()).getGlobalBounds()) ) {
                get_collision_shape().setPosition(get_collision_shape().getPosition() + push_direction * temp_increment);
                //position += normalize(push_direction * temp_increment + direction * 1.5f);
                position += push_direction * temp_increment;
                shape.setPosition(position);
                collision_shape.setPosition(position);
            }
        }
    }
}
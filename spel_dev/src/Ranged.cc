#include "Ranged.h"
#include "point.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Ranged::Ranged(sf::Vector2f position, sf::Texture const& sprite, float speed,int health, int melee_damage)
        : Enemy(position, sprite, speed, health, melee_damage)
{
    available_weapons.push_back(std::make_shared<Weapon>("spitter", 5, "spitter_ammo", -1, 1.0f, 0.5));
    current_weapon = available_weapons.at(0);
}



void Ranged::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> current_obj)
{
    if(current_weapon->can_shoot())
    {
        sf::CircleShape collision_checker;
        collision_checker.setRadius(5);
        collision_checker.setOrigin({collision_checker.getRadius(),collision_checker.getRadius()});
        collision_checker.setPosition(position);
        collision_checker.setFillColor(sf::Color::Red);

        bool checked{false};
        while(not checked)
        {
            for(std::shared_ptr<Game_Object> const& collide_obj : world.game_objects) {
                sf::FloatRect collision_bounds = collision_checker.getGlobalBounds();
                sf::FloatRect other_bounds = (collide_obj->shape).getGlobalBounds();

                if(collide_obj == current_obj || not collision_bounds.intersects(other_bounds)  )
                {
                    continue;
                }

                std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(collide_obj)};
                if( player_target == nullptr)
                {
                    checked = true;
                    break;
                }
                else
                {
                    current_weapon->shoot(direction, world, position, current_obj);
                    checked = true;
                    break;
                }
            }
            collision_checker.setPosition(collision_checker.getPosition() - direction * 16.0f * 2.f * 0.9f);
        }
    }

    if(health <= 0)
    {
        world.kill_queue.push_back(current_obj);
        return;
    }
    life_time += delta_time.asSeconds();
    std::shared_ptr<Player> player{world.get_player()};

    // Rotate the enemy towards the player.
    sf::Vector2f rotate_direction = normalize(position - (player -> position));
    direction = rotate_direction;
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);
    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);

    // Update the enemy position based on delta time.
    float distance = 250.0f * delta_time.asSeconds() * float(speed);
    position -= rotate_direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);

    /*
    // Loop through all game objects in world, handle collision.
    for(std::shared_ptr<Game_Object> const& collide_obj : world.game_objects) {
        sf::FloatRect enemy_bounds = collision_shape.getGlobalBounds();
        sf::FloatRect other_bounds = (collide_obj->shape).getGlobalBounds();

        // If other object is same as this object, no collision is detected, or the other object is a bullet,
        // skip to the next object.
        if(collide_obj == current_obj || not enemy_bounds.intersects(other_bounds) || std::dynamic_pointer_cast<Bullet>(collide_obj) != nullptr)
        {
            continue;
        }

        std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(collide_obj)};

        if(movable_target != nullptr)
        {
            other_bounds = (movable_target->collision_shape).getGlobalBounds();
            if(not enemy_bounds.intersects(other_bounds))
            {
                continue;
            }
            else
            {
                std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(collide_obj)};
                if( player_target != nullptr && life_time > melee_timer + 1)
                {
                    melee_timer = life_time;
                    player_target->take_damage(melee_damage);
                }

            }
        }
        else
        {
            if(length(position - collide_obj->position)
               > std::sqrt(std::pow(collision_shape.getRadius()*2,2)
                           + std::pow(length(collide_obj->shape.getSize()),2)) * 1.1f)
            {
                continue;
            }
        }

        sf::Vector2f push_direction{};
        push_direction = normalize(position - collide_obj->position);
        float temp_increment{0.005f};

        // If other object is not a movable object, make the push-direction perpendicular to the collided surface.
        if (movable_target == nullptr) {
            if (std::abs(push_direction.x) >= std::abs(push_direction.y))
            {
                push_direction.y = 0.0f;
                push_direction.x = (push_direction.x > 0) ? 1.0f : -1.0f;
            }
            else
            {
                push_direction.x = 0.0f;
                push_direction.y = (push_direction.y > 0) ? 1.0f : -1.0f;
            }
        }

        // Push the enemy in the push-direction until it no longer collides with the other object
        while (enemy_bounds.intersects(other_bounds)) {
            position += push_direction * temp_increment;
            shape.setPosition(position);
            collision_shape.setPosition(position);
            enemy_bounds = collision_shape.getGlobalBounds();
        }
    }*/
}

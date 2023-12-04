#include <iostream>
#include "Player.h"
#include "point.h"

sf::Vector2f find_direction() {
    sf::Vector2f direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction.x += 1;

    return normalize(direction);
}

Player::Player(sf::Vector2f position, sf::Texture const& sprite, float speed, int health, sf::Window const& window)
        : Character(position, sprite, speed, health), window{window}
{
    available_weapons.push_back(std::make_shared<Weapon>("glock", 5, "glock_ammo", -1, 2.0f, 2));
    current_weapon = available_weapons.at(0);
}

void Player::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> current_obj)
{
    if(health <= 0)
    {
        world.kill_queue.push_back(current_obj);
        return;
    }

    // Rotate the player towards the mouse cursor.
    sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    sf::Vector2f rotate_direction = normalize(position - mouse_pos);
    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);
    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);

    // Update the players position based on input.
    direction = find_direction();
    float distance = 250.0f * delta_time.asSeconds() * float(speed);
    position += direction * distance;
    shape.setPosition(position);
    collision_shape.setPosition(position);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        current_weapon->shoot(rotate_direction, world, position, current_obj);
    }

    // Loop through all game objects in world, handle collision.
    for(std::shared_ptr<Game_Object> const& collide_obj : world.game_objects)
    {
        sf::FloatRect player_bounds = collision_shape.getGlobalBounds();
        sf::FloatRect other_bounds = (collide_obj->shape).getGlobalBounds();

        // If other object is same as this object, no collision is detected, or the other object is a bullet,
        // skip to the next object.
        if(collide_obj == current_obj || not player_bounds.intersects(other_bounds) || std::dynamic_pointer_cast<Bullet>(collide_obj) != nullptr)
        {
            continue;
        }

        std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(collide_obj)};

        if(movable_target != nullptr)
        {
            other_bounds = (movable_target->collision_shape).getGlobalBounds();
            if(not player_bounds.intersects(other_bounds))
            {
                continue;
            }
        }
        else
        {
            if(length(position - collide_obj->position)
               > std::sqrt(std::pow(collision_shape.getRadius()*2,2)
               + std::pow(length(collide_obj->shape.getSize()),2)))
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

        /*sf::Vector2f push_direction{};
        bool collision_x{
                (direction.y == 0 && direction.x != 0)
                &&
                (std::abs(collide_obj->shape.getPosition().y - collision_shape.getPosition().y) <= (collide_obj->shape.getSize().y/2.0f))
        };

        bool collision_y{
                (direction.x == 0 && direction.y != 0) // Added this check
                &&
                (std::abs(collide_obj->shape.getPosition().x - collision_shape.getPosition().x) <= (collide_obj->shape.getSize().x/2.0f))
        };
        if( (not (collision_x && collision_y)) && (collision_x  || collision_y))
        {
            push_direction = (-direction);
        }
        else
        {
            push_direction = normalize(position - collide_obj->position);
        }*/

        // Push the player in the push-direction until it no longer collides with the other object
        while (player_bounds.intersects(other_bounds)) {
            position += push_direction * temp_increment;
            shape.setPosition(position);
            collision_shape.setPosition(position);
            player_bounds = collision_shape.getGlobalBounds();
        }
    }
}


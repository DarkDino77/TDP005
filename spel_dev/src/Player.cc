#include <iostream>
#include "Player.h"
#include "point.h"
#include "Enemy.h"

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
}

void Player::handle_collision(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> current_obj, std::shared_ptr<Game_Object> other_obj)
{
    if(std::dynamic_pointer_cast<Bullet>(other_obj) != nullptr || std::dynamic_pointer_cast<Enemy>(other_obj) != nullptr)
    {
        return;
    }

    if(length(position - other_obj->position)
       > std::sqrt(std::pow(collision_shape.getRadius()*2,2)
       + std::pow(length(other_obj->shape.getSize()),2)))
    {
        return;
    }

    sf::Vector2f push_direction{};
    push_direction = normalize(position - other_obj->position);
    float temp_increment{0.005f};

    // TODO:Cheack if movable target should be sent in to this function or not.
    std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(other_obj)};
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

    sf::FloatRect other_bounds = (other_obj->shape).getGlobalBounds();
    std::shared_ptr<Movable> other_movable_target{std::dynamic_pointer_cast<Movable>(other_obj)};
    if(other_movable_target != nullptr)
    {
        other_bounds = other_movable_target->collision_shape.getGlobalBounds();
    }

    // Push the player in the push-direction until it no longer collides with the other object
    while (collision_shape.getGlobalBounds().intersects(other_bounds)) {
        position += push_direction * temp_increment;
        shape.setPosition(position);
        collision_shape.setPosition(position);
    }
}


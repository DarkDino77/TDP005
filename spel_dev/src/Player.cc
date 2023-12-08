#include <iostream>
#include "Player.h"
#include "point.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Pick_Up.h"

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

Player::Player(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, World & world)
: Character(position, sprite, speed, health)
{
    available_weapons.push_back(std::make_shared<Weapon>("glock", 5, -1, 2.0f, 2));
    current_weapon = available_weapons.at(0);
    world.set_weapon_stats(current_weapon);
}

void Player::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj) {
    if(hit)
    {
        hit = false;
        world.play_sound("player_hurt");
    }
    if (health <= 0) {
        world.kill(current_obj);
        return;
    }

    // Rotate the player towards the mouse cursor.
    sf::Vector2f rotate_direction = normalize(position - world.get_mouse_pos());
    set_rotation(rotate_direction);
    // ==============================[ INPUT ]==============================
    // Update the players position based on input.
    direction = -find_direction();
    update_position(delta_time);


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(current_weapon->shoot(rotate_direction, world, position, current_obj))
        {
            world.set_weapon_stats(current_weapon);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        current_weapon = available_weapons[0];
        world.set_weapon_stats(current_weapon);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        if(int(available_weapons.size()) >= 2)
        {
            current_weapon = available_weapons[1];
            world.set_weapon_stats(current_weapon);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        if(int(available_weapons.size()) >= 3)
        {
            current_weapon = available_weapons[2];
            world.set_weapon_stats(current_weapon);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        if(int(available_weapons.size()) >= 4)
        {
            current_weapon = available_weapons[3];
            world.set_weapon_stats(current_weapon);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        if(int(available_weapons.size()) >= 5)
        {
            current_weapon = available_weapons[4];
            world.set_weapon_stats(current_weapon);
        }
    }

    world.set_health_percent(health, max_health);
}



void Player::handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const& other_obj)
{
    if(std::dynamic_pointer_cast<Bullet>(other_obj) != nullptr || std::dynamic_pointer_cast<Enemy>(other_obj) != nullptr||
            std::dynamic_pointer_cast<Explosion>(other_obj)!=nullptr || std::dynamic_pointer_cast<Pick_Up>(other_obj) != nullptr)
    {
        return;
    }

    if(length(position - other_obj->get_position())
       > std::sqrt(std::pow(collision_shape.getRadius()*2,2)
       + std::pow(length(other_obj->get_shape().getSize()),2)))
    {
        return;
    }

    sf::Vector2f push_direction{};
    push_direction = normalize(position - other_obj->get_position());
    float temp_increment{0.005f};

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

    sf::FloatRect other_bounds = (other_obj->get_shape()).getGlobalBounds();
    std::shared_ptr<Movable> other_movable_target{std::dynamic_pointer_cast<Movable>(other_obj)};
    if(other_movable_target != nullptr)
    {
        other_bounds = other_movable_target->get_collision_shape().getGlobalBounds();
    }

    // Push the player in the push-direction until it no longer collides with the other object
    while (collision_shape.getGlobalBounds().intersects(other_bounds)) {
        position += push_direction * temp_increment;
        shape.setPosition(position);
        collision_shape.setPosition(position);
    }
}

void Player::add_ammo(std::string const& ammo_type, int const amount)
{
    for (std::shared_ptr<Weapon> weapon: available_weapons)
    {
        if(ammo_type == weapon->get_name() + "_ammo")
        {
            weapon->add_ammo(amount);
        }
    }
}

void Player::add_health(int const amount)
{
    health += amount;
    if (health > max_health)
    {
        health -= health - max_health;
    }
}

void Player::increase_max_health(int const amount)
{
    max_health += amount;
}


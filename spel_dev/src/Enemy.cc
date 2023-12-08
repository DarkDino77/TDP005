#include "Enemy.h"
#include "point.h"
#include "Explosion.h"
#include "Pick_Up.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

Enemy::Enemy(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, int const melee_damage, int const xp)
        : Character(position, sprite, speed, health), melee_damage{melee_damage}, xp{xp}
{}

void Enemy::handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const& other_obj)
{
    if(std::dynamic_pointer_cast<Bullet>(other_obj) != nullptr
            || std::dynamic_pointer_cast<Explosion>(other_obj) != nullptr
            || std::dynamic_pointer_cast<Pick_Up>(other_obj) != nullptr)
    {
        return;
    }

    if(length(position - other_obj->get_position())
       > std::sqrt(std::pow(collision_shape.getRadius()*2,2)
       + std::pow(length(other_obj->get_shape().getSize()),2)) * 1.1f)
    {
        return;
    }

    sf::Vector2f push_direction{};
    push_direction = normalize(position - other_obj->get_position());
    float temp_increment{0.005f};

    // TODO:Check if movable target should be sent in to this function or not.
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

        std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(other_obj)};
        if( player_target != nullptr && life_time > melee_timer + 1)
        {
            melee_timer = life_time;
            player_target->take_damage(melee_damage);
            player_target->knock_back(direction, 10);
        }
    }

    // Push the enemy in the push-direction until it no longer collides with the other object
    while (collision_shape.getGlobalBounds().intersects(other_bounds)) {
        position += push_direction * temp_increment;
        shape.setPosition(position);
        collision_shape.setPosition(position);
    }
}

void Enemy::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj)
{
    if(hit)
    {
        hit = false;
        world.play_sound("enemy_hurt");
    }
    if(health <= 0)
    {
        world.kill(current_obj);
        world.add_player_xp(xp);
        world.add_pick_up(position, 25);
        return;
    }

    life_time += delta_time.asSeconds();
    std::shared_ptr<Player> player{world.get_player()};

    // Rotate the enemy towards the player.
    sf::Vector2f rotate_direction = normalize(position - (player -> get_position()));
    direction = rotate_direction;
    set_rotation(direction);
    // Update the enemy position based on delta time.
    update_position(delta_time);

}

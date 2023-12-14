#include <cmath>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "point.h"
#include "Explosion.h"
#include "Pick_Up.h"
#include "Explosive_Barrel.h"
#include "Bullet.h"


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

    float temp_increment{0.005f};
    sf::Vector2f push_direction{calculate_push_direction(other_obj)};


    std::shared_ptr<Damageable> damageable_target{std::dynamic_pointer_cast<Damageable>(other_obj)};
    if( damageable_target != nullptr && life_time > melee_timer + 1 &&
        std::dynamic_pointer_cast<Enemy>(other_obj) == nullptr &&
                std::dynamic_pointer_cast<Explosive_Barrel>(other_obj) == nullptr)
    {
        melee_timer = life_time;
        damageable_target->take_damage(melee_damage);
        std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(other_obj)};
        if (player_target != nullptr)
        {
            player_target->knock_back(direction, 10);
        }
    }

    push_out(push_direction, temp_increment, other_obj);
}

void Enemy::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj)
{
    if(hit)
    {
        hit = false;
        world.get_resource_manager().play_sound("enemy_hurt");
    }
    if(health <= 0)
    {
        world.kill(current_obj);
        world.get_player()->add_player_xp(xp, world);
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

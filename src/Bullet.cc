#include "Bullet.h"
#include "World.h"
#include "Destructible.h"
#include "Explosion.h"
#include "Pick_Up.h"
#include "Enemy.h"

Bullet::Bullet(int const damage, sf::Vector2f const& aim_direction, double const speed, sf::Texture const& sprite, sf::Vector2f const& position, bool const is_friendly)
: Movable(position, sprite, speed), damage{damage}, is_friendly{is_friendly}
{
    direction = aim_direction;
    set_rotation(direction);
}

void Bullet::update(sf::Time const& delta_time, World & , std::shared_ptr<Game_Object> const&)
{
    update_position(delta_time);
}

void Bullet::handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj)
{
    std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(other_obj)};
    std::shared_ptr<Enemy> enemy_target{std::dynamic_pointer_cast<Enemy>(other_obj)};
    if (((player_target != nullptr && is_friendly) || (enemy_target != nullptr && not is_friendly)) || not is_alive || std::dynamic_pointer_cast<Bullet>(other_obj) != nullptr
            || std::dynamic_pointer_cast<Explosion>(other_obj) != nullptr
            || std::dynamic_pointer_cast<Pick_Up>(other_obj) != nullptr)
    {
        return;
    }

    std::shared_ptr<Damageable> damageable_target =  std::dynamic_pointer_cast<Damageable>(other_obj);
    if(damageable_target != nullptr)
    {
        damageable_target->take_damage(damage);
        std::shared_ptr<Character> character_target =  std::dynamic_pointer_cast<Character>(other_obj);
        if(character_target != nullptr) {
            character_target->knock_back(direction, 10);
        }
    }

    world.get_resource_manager().play_sound("bullet_impact");
    world.kill(current_obj);
    is_alive = false;
}



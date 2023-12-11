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
}
int Player::get_level() const
{
    return player_level;
}

float Player::get_level_percent() const
{
    return level_percent;
}

float Player::get_health_percent() const
{
    return health_percent;
}

std::shared_ptr<Weapon>& Player::get_weapon_stats()
{
    return current_weapon;
}

void Player::update(sf::Time const& delta_time, World &world, std::shared_ptr<Game_Object> const& current_obj) {
    if(hit)
    {
        hit = false;
        world.get_resource_manager().play_sound("player_hurt");
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
        current_weapon->shoot(rotate_direction, world, position, true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        current_weapon = available_weapons[0];

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        if(int(available_weapons.size()) >= 2)
        {
            current_weapon = available_weapons[1];
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        if(int(available_weapons.size()) >= 3)
        {
            current_weapon = available_weapons[2];
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        if(int(available_weapons.size()) >= 4)
        {
            current_weapon = available_weapons[3];

        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        if(int(available_weapons.size()) >= 5)
        {
            current_weapon = available_weapons[4];
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
    {
        if(int(available_weapons.size()) >= 6)
        {
            current_weapon = available_weapons[5];
        }
    }

    health_percent = (float(health) / float(max_health));
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

void Player::add_player_xp(int const xp, World & world)
{
    player_level_progression+=xp;
    while(player_level_progression >= xp_to_level)
    {
        level_up_player(world);
    }
    level_percent = float(player_level_progression)/float(xp_to_level);
}

void Player::level_up_player(World & world)
{
    world.get_hud()->pop_up("LEVEL UP");
    player_level_progression -= xp_to_level;
    xp_to_level+=5;
    player_level+= 1;
    // Give player max health every 10 levels
    if (player_level % 10 == 0)
    {
        max_health+=10;
        world.get_hud()->pop_up("MAX HEALTH +10");
    }
    // Give player a weapon every 5 levels
    if (player_level % 5 == 0)
    {
        add_player_weapon(world);
    }
}

void Player::add_player_weapon(World & world)
{
    switch (player_level)
    {
        case(5):
            add_weapon("baretta", 15, 200, 2.5, 2);
            add_ammo("baretta_ammo", 200);
            world.get_available_pick_ups().push_back("baretta_ammo");
            break;
        case(10):
            add_weapon("uzi", 10, 500, 2.5, 5);
            add_ammo("uzi_ammo", 500);
            world.get_available_pick_ups().push_back("uzi_ammo");
            break;
        case(15):
            add_weapon("shotgun", 30, 50, 2, 0.75);
            add_ammo("shotgun_ammo", 50);
            world.get_available_pick_ups().push_back("shotgun_ammo");
            break;
        case(20):
            add_weapon("assault_rifle", 35, 300, 2.5, 4);
            add_ammo("assault_rifle_ammo", 300);
            world.get_available_pick_ups().push_back("assault_rifle_ammo");
            break;
        case(25):
            add_weapon("sniper_rifle", 70, 40, 3, 2);
            add_ammo("sniper_rifle_ammo", 40);
            world.get_available_pick_ups().push_back("sniper_rifle_ammo");
            break;
    }
}


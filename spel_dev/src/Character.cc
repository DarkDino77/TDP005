#include "Character.h"
#include "World.h"
#include "point.h"

Character::Character(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health)
: Movable(position, sprite, speed), Damageable(health)
{}

void Character::knock_back(sf::Vector2f const& direction, float force)
{
    position -= direction * force;
    shape.setPosition(position);
    collision_shape.setPosition(position);
}
void Character::add_weapon(std::string const& name, int const damage,
                           int const ammo_capacity, double bullet_speed,double fire_rate)
{
    available_weapons.push_back(std::make_shared<Weapon>(name, damage, ammo_capacity, bullet_speed, fire_rate));
}

void Character::push_out(sf::Vector2f const& push_direction, float temp_increment, std::shared_ptr<Game_Object> const& other_obj)
{
    std::shared_ptr<Collidable> other_collidable_target{std::dynamic_pointer_cast<Collidable>(other_obj)};
    sf::FloatRect other_bounds;
    if(other_collidable_target != nullptr)
    {
        other_bounds = other_collidable_target->get_collision_shape().getGlobalBounds();
    } else
    {
        other_bounds = (other_obj->get_shape()).getGlobalBounds();
    }

    // Push the player in the push-direction until it no longer collides with the other object
    while (collision_shape.getGlobalBounds().intersects(other_bounds)) {
        position += push_direction * temp_increment;
        shape.setPosition(position);
        collision_shape.setPosition(position);
    }
}

sf::Vector2f Character::calculate_push_direction(std::shared_ptr<Game_Object> const& other_obj)
{
    sf::Vector2f push_direction{};
    push_direction = normalize(position - other_obj->get_position());

    std::shared_ptr<Collidable> other_collidable_target{std::dynamic_pointer_cast<Collidable>(other_obj)};
    // If other object is not a movable object, make the push-direction perpendicular to the collided surface.
    if (other_collidable_target == nullptr) {
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

    return push_direction;
}
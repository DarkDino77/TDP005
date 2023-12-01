#include "Player.h"
#include "point.h"
#include <iostream>

sf::Vector2f Player::find_direction() {
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

Player::Player(sf::Vector2f position, sf::Texture const& sprite, float speed)
        : Character(position, sprite, speed)
{
    available_weapons.push_back(std::make_shared<Weapon>("glock", 10, "glock", -1, 1, 10));
    current_weapon = available_weapons.at(0);
}
// TODO: determine if window is const&
void Player::update(sf::Time const& delta_time, World &world, sf::Window &window, std::shared_ptr<Game_Object> obj)
{
    sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    sf::Vector2f rotate_direction = normalize(position - mouse_pos);

    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);

    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);
    direction = find_direction();

    float distance = 250.0f * delta_time.asSeconds() * player_speed;
    position += direction * distance;

    shape.setPosition(position);
    collision_shape.setPosition(position);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        current_weapon->shoot(rotate_direction, world, position);
    }


    for(std::shared_ptr<Game_Object> collide_obj : world.game_objects) {
        std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(collide_obj)};
        bool collides{};
        if(movable_target == nullptr) // Collides with non-movable object
        {
            collides = (collide_obj != obj
                        && collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds())
                        && (length(position - collide_obj->position)
                            <= std::sqrt(std::pow(collision_shape.getRadius(),2)
                                         + std::pow(length({collide_obj->shape.getSize().x/2.0f, collide_obj->shape.getSize().x/2.0f}),2) ) * 2.0f) // TODO: Fix this so that * 1.95 is not necessary.
            );
        }
        else // Collides with movable object.
        {
            collides = (collide_obj != obj && collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()));
        }


        if(collides)
        {
            sf::Vector2f push_direction{};
            push_direction = normalize(position - collide_obj->position);
            float temp_increment{0.005f};

            if(movable_target == nullptr)
            {
                if((push_direction.x * push_direction.x) >= (push_direction.y * push_direction.y))
                {
                    push_direction.y = 0.0f;
                    if(push_direction.x > 0)
                    {
                        push_direction.x = 1.0f;
                    }
                    else
                    {
                        push_direction.x = -1.0f;
                    }
                }
                else
                {
                    push_direction.x = 0.0f;
                    if(push_direction.y > 0)
                    {
                        push_direction.y = 1.0f;
                    }
                    else
                    {
                        push_direction.y = -1.0f;
                    }
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

            //float temp_increment{0.005f};
            if(movable_target != nullptr)
            {
                while (collision_shape.getGlobalBounds().intersects((movable_target->collision_shape).getGlobalBounds())) {
                    //get_collision_shape().setPosition(get_collision_shape().getPosition() + push_direction * temp_increment);
                    position += push_direction * temp_increment;
                    shape.setPosition(position);
                    collision_shape.setPosition(position);
                }
            }
            else
            {
                while (collision_shape.getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()) ) {
                    //get_collision_shape().setPosition(get_collision_shape().getPosition() + push_direction * temp_increment);
                    position += push_direction * temp_increment;
                    shape.setPosition(position);
                    collision_shape.setPosition(position);
                }
            }
        }
    }
}


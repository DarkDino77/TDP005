#include "Player.h"
#include "point.h"

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

Player::Player(sf::Vector2f position, sf::Texture const& sprite)
        : Character(position, sprite)
{}
// TODO: determine if window is const&
void Player::update(sf::Time const& delta_time, World &world, sf::Window &window, std::shared_ptr<Game_Object> obj)
{
    sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    sf::Vector2f rotate_direction = normalize(position - mouse_pos);

    float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);

    shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);

    direction = find_direction();
    //world.get_player()->direction = direction;

    float distance = 250.0f * delta_time.asSeconds() * player_speed;
    position += direction * distance;

    shape.setPosition(position);
    collision_shape.setPosition(position);


    // Handle collision

    for(std::shared_ptr<Game_Object> collide_obj : world.game_objects) {

        const bool collides = ( collide_obj != obj && (collision_shape).getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()) );

        if(collides)
        {
            sf::Vector2f push_direction{};
            bool collision_x{
                    (direction.y == 0)
                    &&
                    (std::abs(collide_obj->shape.getPosition().y - collision_shape.getPosition().y) <= (collide_obj->shape.getSize().y/2.0f))
            };

            bool collision_y{
                    (direction.x == 0)
                    &&
                    (std::abs(collide_obj->shape.getPosition().x - collision_shape.getPosition().x) < (collide_obj->shape.getSize().x/2.0f))
            };
            if(collision_x || collision_y)
            {
                push_direction = (-direction);
            }
            else
            {
                push_direction = normalize(get_collision_shape().getPosition() - collide_obj->get_collision_shape().getPosition());
            }

            float temp_increment{0.005f};
            while ((get_collision_shape()).getGlobalBounds().intersects((collide_obj->get_collision_shape()).getGlobalBounds()) ) {
                get_collision_shape().setPosition(get_collision_shape().getPosition() + push_direction * temp_increment);
                position += push_direction * temp_increment;
            }
        }
    }
}


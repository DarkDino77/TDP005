#include "player.h"
#include "world.h"
#include "enemy.h"

Player::Player(sf::Vector2f position)
    : Textured_Object(position, "player.png"), speed{300.0f} {

    shield.setRadius(radius * 2);
    shield.setOrigin(radius * 2, radius * 2);
    shield.setFillColor(sf::Color(255, 0, 0, 128));
}

static sf::Vector2f find_direction() {
    sf::Vector2f direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction.x += 1;

    float len = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    if (len > 0.0f)
        return direction * (1.0f / len);
    else
        return direction;
}

bool Player::tick(sf::Time delta, World &world) {
    auto dir = find_direction();
    center += dir * (speed * delta.asMicroseconds() / 1000000.0f);

    shield_visible -= delta;
    if (shield_visible <= sf::Time{}) {
        shield_visible = sf::Time{};

        // Don't check for collisions if the shield is up.
        for (auto &collision : world.collides_with(*this)) {
            // Was it an enemy?
            if (dynamic_cast<Enemy *>(collision.get())) {
                shield_visible = sf::milliseconds(1000);
            }
        }
    }

    return true;
}

void Player::render(sf::RenderWindow &to) {
    Textured_Object::render(to);

    if (shield_visible > sf::Time{}) {
        shield.setPosition(center);
        to.draw(shield);
    }
}

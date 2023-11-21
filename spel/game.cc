#include <SFML/Graphics.hpp>    
#include "point.h"
#include "standard.h"
#include <cmath>

const size_t width = 1024;
const size_t height = 768;

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

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Demo"};
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    // ==============================[ Cursor ]==============================
    sf::Texture mouse_cursor_texture;
    mouse_cursor_texture.loadFromFile("sprites/crosshair.png");

    sf::Vector2f mouse_texture_size{mouse_cursor_texture.getSize()};
    sf::RectangleShape mouse_cursor{mouse_texture_size};
    mouse_cursor.setTexture(&mouse_cursor_texture);
    mouse_cursor.setOrigin(mouse_texture_size / 2.f);
    mouse_cursor.setScale(4.0f,4.0f);

    // ==============================[ Player ]==============================
    sf::Texture texture;
    texture.loadFromFile("sprites/player.png");

    sf::Vector2f textureSize{texture.getSize()};
    sf::RectangleShape player{textureSize};
    player.setTexture(&texture);
    player.setOrigin(textureSize / 2.0f);
    player.setScale(4.0f,4.0f);
    sf::Vector2f location{300, 300};

    sf::Clock clock;

    bool quit = false;
    while (!quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                quit = true;
                break;
            default:
                break;
            }
        }

        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        sf::Vector2f rotate_direction = normalize(location - mouse_pos);

        float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);

        player.setRotation((rotate_degrees*180/3.1415f) - 90.f);


        if (quit)
            break;

        sf::Vector2f direction = find_direction();

        auto delta = clock.restart();
        {
            float distance = 250.0f * delta.asSeconds();
            location += direction * distance;
        }

        mouse_cursor.setPosition(mouse_pos);

        window.clear();
        player.setPosition(location);
        window.draw(player);
        window.draw(mouse_cursor);
        window.display();
    }

    return 0;
}

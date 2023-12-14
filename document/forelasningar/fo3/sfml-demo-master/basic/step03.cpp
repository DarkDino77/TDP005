#include <SFML/Graphics.hpp>
#include "standard.h"

/**
 * Steg 3: Flytta objektet!
 *
 * Testa:
 * - Vad händer om du lägger till window.setKeyRepeatEnabled(false)?
 * - Vad händer om du kör window.clear() innan du ritar?
 */


const size_t width = 1024;
const size_t height = 768;

void updateLocation(sf::Vector2f &location, sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::W:
    case sf::Keyboard::Up:
        location.y -= 10;
        break;
    case sf::Keyboard::S:
    case sf::Keyboard::Down:
        location.y += 10;
        break;
    case sf::Keyboard::A:
    case sf::Keyboard::Left:
        location.x -= 10;
        break;
    case sf::Keyboard::D:
    case sf::Keyboard::Right:
        location.x += 10;
        break;
    default:
        break;
    }
}

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Demo"};

    sf::CircleShape circle{40};
    sf::Vector2f location{300, 300};

    bool quit = false;
    sf::Event event;
    while (window.waitEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            quit = true;
            break;
        case sf::Event::KeyPressed:
            updateLocation(location, event.key.code);
            break;
        default:
            break;
        }

        if (quit)
            break;

        window.clear(); // Tömmer fönstret varje gpng
        circle.setPosition(location);
        window.draw(circle);
        window.display();
    }

    return 0;
}

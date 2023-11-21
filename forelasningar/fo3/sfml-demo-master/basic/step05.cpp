#include <SFML/Graphics.hpp>
#include "point.h"
#include "standard.h"

/**
 * Steg 5: Bättre förflyttning av objekt!
 *
 * Fundera på:
 * - Vad är skillnaden här jämfört med förra?
 * - Hur påverkas hastigheten av olika hastighet på programmet?
 * - Hur fungerar detta med avseende på om programmet har fokus eller ej?
 */


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
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true); // <--

    sf::CircleShape circle{40};
    sf::Vector2f location{300, 300};

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

        if (quit)
            break;

        sf::Vector2f direction = find_direction();
        location += direction;

        window.clear();
        circle.setPosition(location);
        window.draw(circle);
        window.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include "standard.h"

/**
 * Steg 2: Rita något på skärmen!
 *
 * Testa:
 * - Vad händer om vi inte har med "window.display()"?
 * - Var är punkten (0, 0)?
 * - Vad händer om vi kör circle.setOrigin(sf::Vector2f{40, 40});
 */


const size_t width = 1024;
const size_t height = 768;

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Demo"};

    sf::CircleShape circle{40};
    circle.setPosition(sf::Vector2f{300, 300});

    bool quit = false;
    sf::Event event;
    while (window.waitEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            quit = true;
            break;
        default:
            break;
        }

        if (quit)
            break;

        window.draw(circle);
        window.display();
    }

    return 0;
}

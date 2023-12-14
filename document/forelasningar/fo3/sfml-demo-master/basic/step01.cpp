#include <SFML/Graphics.hpp>
#include "standard.h"

/**
 * Steg 1: Hantera "event"
 *
 * Testa:
 * - Vad händer om vi inte hanterar sf::Event::Closed?
 */


const size_t width = 1024;
const size_t height = 768;

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Demo"};

    bool quit = false;
    sf::Event event;
    while (window.waitEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            quit = true;
            break;
        default:
            cout << "Event: " << event.type << endl;
            break;
        }

        if (quit)
            break;
    }

    return 0;
}

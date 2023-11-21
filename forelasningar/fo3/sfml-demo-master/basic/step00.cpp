#include <SFML/Graphics.hpp>

/**
 * Steg 0: Skapa ett fönster
 *
 * Kompilera med:
 * g++ step00.cpp -lsfml-system -lsfml-graphics -lsfml-window
 */


const size_t width = 1024;
const size_t height = 768;

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Demo"};

    sf::sleep(sf::milliseconds(3000));

    return 0;
}

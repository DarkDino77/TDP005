#include <SFML/Graphics.hpp>
#include "point.h"
#include "standard.h"

/**
 * Steg 7: Alternativ hantering av tangentbordsinmatning.
 *
 * Fundera på:
 * - Vad är fördelar och nackdelar gentemot förra lösningen?
 * - Finns det problem med den här lösningen?
 */


const size_t width = 1024;
const size_t height = 768;


class Key_State {
public:
    Key_State()
        : up{false},
          down{false},
          left{false},
          right{false}
        {}

    void onKey(sf::Keyboard::Key key, bool pressed) {
        switch (key) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            up = pressed;
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            down = pressed;
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            left = pressed;
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            right = pressed;
            break;
        default:
            break;
        }
    }

    sf::Vector2f direction() const {
        sf::Vector2f result;
        if (up)
            result.y -= 1;
        if (down)
            result.y += 1;
        if (left)
            result.x -= 1;
        if (right)
            result.x += 1;
        return normalize(result);
    }

private:
    bool up;
    bool down;
    bool left;
    bool right;
};


int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Demo"};
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    sf::CircleShape circle{40};
    sf::Vector2f location{300, 300};

    sf::Clock clock;

    Key_State keys;

    bool quit = false;
    while (!quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                quit = true;
                break;
            case sf::Event::KeyPressed:
                keys.onKey(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                keys.onKey(event.key.code, false);
                break;
            default:
                break;
            }
        }

        if (quit)
            break;

        sf::Vector2f direction = keys.direction();

        auto delta = clock.restart();
        {
            float distance = 250.0f * delta.asSeconds();
            location += direction * distance;
        }

        window.clear();
        circle.setPosition(location);
        window.draw(circle);
        window.display();
    }

    return 0;
}

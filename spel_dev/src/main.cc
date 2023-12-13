#include <SFML/Graphics.hpp>
#include "State.h"

int main() {
    sf::RenderWindow window{sf::VideoMode{1920, 1024}, "The Grand Arena", sf::Style::Titlebar | sf::Style::Close};
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(false);

    State::run(window, std::make_shared<Menu_State>());

    return 0;
}

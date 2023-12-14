#include "state.h"

State::State() {}

State::~State() {}

void State::on_key_press(sf::Keyboard::Key) {}

void State::on_key_release(sf::Keyboard::Key) {}

void State::run(sf::RenderWindow &window, shared_ptr<State> state) {
    sf::Clock clock;

    while (state) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                return;
            case sf::Event::KeyPressed:
                state->on_key_press(event.key.code);
                break;
            case sf::Event::KeyReleased:
                state->on_key_release(event.key.code);
                break;
            default:
                break;
            }
        }

        window.clear();
        if (auto new_state = state->tick(clock.restart())) {
            if (std::dynamic_pointer_cast<Exit_State>(new_state)) {
                return;
            } else {
                state = new_state;
            }
            continue;
        }

        state->render(window);
        window.display();
    }
}

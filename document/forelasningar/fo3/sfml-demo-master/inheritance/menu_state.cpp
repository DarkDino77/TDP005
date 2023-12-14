#include "menu_state.h"
#include "game_state.h"

Menu_State::Menu_State(shared_ptr<State> resume)
    : selected(0), enter_pressed(false), delay(sf::milliseconds(300)) {

    font.loadFromFile("font.ttf");

    if (resume) {
        add("Resume", [resume]() { return resume; });
        background = resume;
    }

    add("New game", []() { return std::make_shared<Game_State>(); });
    add("Exit", []() { return std::make_shared<Exit_State>(); });
}

void Menu_State::add(const string &text, Action action) {
    entries.push_back({ sf::Text{text, font, 60}, 0.0f, action });
}

void Menu_State::on_key_press(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::Down:
        if (selected + 1 < entries.size())
            selected++;
        break;
    case sf::Keyboard::Up:
        if (selected > 0)
            selected--;
        break;
    case sf::Keyboard::Return:
        enter_pressed = true;
        break;
    default:
        break;
    }
}

shared_ptr<State> Menu_State::tick(sf::Time time) {
    float diff = float(time.asMicroseconds()) / float(delay.asMicroseconds());

    for (size_t i = 0; i < entries.size(); i++) {
        Entry &e = entries[i];

        if (i == selected) {
            e.state += diff;
            if (e.state > 1.0f)
                e.state = 1.0f;
        } else {
            e.state -= diff;
            if (e.state < 0.0f)
                e.state = 0.0f;
        }
    }

    if (enter_pressed)
        return entries[selected].action();
    else
        return nullptr;
}

void Menu_State::render(sf::RenderWindow &to) {
    if (background)
        background->render(to);

    float y{100};
    auto windowSize = to.getSize();

    for (auto &e : entries) {
        auto bounds = e.text.getLocalBounds();
        e.text.setPosition((windowSize.x - bounds.width) / 2, y);
        y += bounds.height * 2.0f;

        int state = static_cast<int>(255 * e.state);
        e.text.setFillColor(sf::Color(state, 255, state));
        to.draw(e.text);
    }
}

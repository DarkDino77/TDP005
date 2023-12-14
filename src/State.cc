#include "State.h"

// ==============================[ State ]==============================

void State::on_key_press(sf::Keyboard::Key) {}

void State::on_key_release(sf::Keyboard::Key) {}

void State::run(sf::RenderWindow & window, std::shared_ptr<State> state) {
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
        if (auto new_state = state->tick(clock.restart(), window))
        {
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

// ==============================[ Game State ]==============================

Game_State::Game_State()
{
    //world.load();
}

std::shared_ptr<State> Game_State::tick(sf::Time delta, sf::RenderWindow & window)
{
    elapsed_time += delta.asSeconds();

    // Create new enemies from time to time.
    if(world.simulate(delta, elapsed_time, window))
    {
        window.clear();
        return std::make_shared<Menu_State>(nullptr);
    }

    // Pause?
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
        return std::make_shared<Menu_State>(shared_from_this());

    return nullptr;
}

void Game_State::render(sf::RenderWindow &to) {
    world.render(to);
}

// ==============================[ Menu State ]==============================

Menu_State::Menu_State(std::shared_ptr<State> resume)
: selected(0), enter_pressed(false), delay(sf::milliseconds(300))
{
    font.loadFromFile("res/font3.ttf");


    if (resume) {
        add("RESUME GAME", [resume]() { return resume; });
        add("START NEW GAME", []() { return std::make_shared<Game_State>(); });
        background = resume;
    }
    else
    {
        add("START GAME", []() { return std::make_shared<Game_State>(); });
    }

    add("EXIT GAME", []() { return std::make_shared<Exit_State>(); });
}

void Menu_State::add(const std::string &text, Action action) {
    sf::Text menu_item{text, font, 60};
    menu_item.setOutlineColor(sf::Color (0x373737ff));
    menu_item.setOutlineThickness(6);
    entries.push_back({ menu_item, 0.0f, action });
}

void Menu_State::on_key_press(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            if (selected + 1 < entries.size())
                selected++;
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
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

std::shared_ptr<State> Menu_State::tick(sf::Time time, sf::RenderWindow &) {
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
    float y;
    if (background)
    {
        background->render(to);
        y = 350;
    }
    else
    {
        std::shared_ptr<sf::Texture> background_texture{std::make_shared<sf::Texture>()};
        if (!background_texture->loadFromFile("textures/main_menu.png"))
        {
            std::cerr << "Error: Background image not found" << std::endl;
        }
        sf::RectangleShape background_sprite{};
        background_sprite.setTexture(&*background_texture);
        background_sprite.setSize({1920,1024});
        to.draw(background_sprite);
        y = 500;
    }


    auto windowSize = to.getSize();

    for (size_t i = 0; i < entries.size(); i++) {
        auto &e = entries[i];
        auto bounds = e.text.getLocalBounds();
        e.text.setPosition((windowSize.x - bounds.width) / 2, y);
        y += bounds.height * 2.0f;

        // Set the color to white for the selected item, and grey for others
        int baseColor = 175; // Grey base color
        int selectedColor = 255; // White selected color
        int state = (i == selected) ? selectedColor : baseColor;

        e.text.setFillColor(sf::Color(state, state, state));
        to.draw(e.text);
    }
}

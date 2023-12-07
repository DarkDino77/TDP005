
#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <functional>
#include "World.h"

// ==============================[ State ]==============================
class State : public std::enable_shared_from_this<State> {
public:
    State();
    virtual ~State();
    virtual void on_key_press(sf::Keyboard::Key key);
    virtual void on_key_release(sf::Keyboard::Key key);
    virtual std::shared_ptr<State> tick(sf::Time time, sf::RenderWindow & window) = 0;
    virtual void render(sf::RenderWindow &to) = 0;
    static void run(sf::RenderWindow &window, std::shared_ptr<State> state);

};

// ==============================[ Game State ]==============================

class Game_State : public State {
public:
    Game_State();
    std::shared_ptr<State> tick(sf::Time delta, sf::RenderWindow & window) override;
    void render(sf::RenderWindow &to) override;

private:
    World world;
    float elapsed_time{};
};
// ==============================[ Menu State ]==============================

class Menu_State : public State {
public:
    Menu_State(std::shared_ptr<State> resume = nullptr);
    void on_key_press(sf::Keyboard::Key key) override;
    std::shared_ptr<State> tick(sf::Time time, sf::RenderWindow & window) override;
    void render(sf::RenderWindow &drawTo) override;

private:
    using Action = std::function<std::shared_ptr<State>()>;

    struct Entry {
        sf::Text text;
        float state;
        Action action;
    };

    sf::Font font;
    std::vector<Entry> entries;
    size_t selected;
    bool enter_pressed;
    sf::Time delay;
    std::shared_ptr<State> background;
    void add(const std::string &text, Action action);
};

// ==============================[ Exit State ]==============================
class Exit_State : public State {
public:
    std::shared_ptr<State> tick(sf::Time,sf::RenderWindow &window) { return nullptr; }
    void render(sf::RenderWindow &) {}
};

#endif

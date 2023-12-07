
#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>

class State : public std::enable_shared_from_this<State> {
public:
    State();
    virtual ~State();
    virtual void on_key_press(sf::Keyboard::Key key);
    virtual void on_key_release(sf::Keyboard::Key key);
    virtual std::shared_ptr<State> tick(sf::Time time) = 0;
    virtual void render(sf::RenderWindow &to) = 0;
    static void run(sf::RenderWindow &window, std::shared_ptr<State> state);
};

class Exit_State : public State {
public:
    std::shared_ptr<State> tick(sf::Time) { return nullptr; }
    void render(sf::RenderWindow &) {}
};


#endif

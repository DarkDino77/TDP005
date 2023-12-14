#pragma once
#include "state.h"
#include <functional>

/**
 * State responsible for showing either the start menu or the pause menu.
 */
class Menu_State : public State {
public:
    /**
     * Create the state. If 'resume' is set, the menu will show a "resume"
     * option to return to that state.
     */
    Menu_State(shared_ptr<State> resume = nullptr);

    /**
     * Handle key presses.
     */
    void on_key_press(sf::Keyboard::Key key) override;

    /**
     * Tick.
     */
    shared_ptr<State> tick(sf::Time time) override;

    /**
     * Render.
     */
    void render(sf::RenderWindow &drawTo) override;

private:
    /**
     * What to do when an item is selected.
     */
    using Action = std::function<shared_ptr<State>()>;

    /**
     * Menu item.
     */
    struct Entry {
        /**
         * Text to draw.
         */
        sf::Text text;

        /**
         * Determine the color (i.e. how selected it is). 0-1.
         */
        float state;

        /**
         * Action to perform when selected.
         */
        Action action;
    };

    /**
     * Font to use.
     */
    sf::Font font;

    /**
     * All menu entries.
     */
    vector<Entry> entries;

    /**
     * Which one is currently selected?
     */
    size_t selected;

    /**
     * Was the enter key pressed?
     */
    bool enter_pressed;

    /**
     * Animation delay.
     */
    sf::Time delay;

    /**
     * State to use as a background (if any).
     */
    shared_ptr<State> background;

    /**
     * Helper to add an element.
     */
    void add(const string &text, Action action);
};

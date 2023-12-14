#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "World.h"

// ==============================[ State ]==============================
/**
 * @class State
 * @brief A state that represents a state of the program. This could for example be
 * a menu state or the main game loop.
 */
class State : public std::enable_shared_from_this<State>
{
public:
    /**
     * @brief The constructor for the State, set to default.
     */
    State() = default;

    /**
     * @brief The destructor of the state object.
     */
    virtual ~State() = default;

    /**
     * @brief Called when the user presses a key.
     *
     * @param key The key which the user presses.
     */
    virtual void on_key_press(sf::Keyboard::Key key);

    /**
     * @brief Called when the user releases a key.
     *
     * @param key The key which the user released.
     */
    virtual void on_key_release(sf::Keyboard::Key key);

    /**
     * @brief used to update the current state each frame update.
     *
     * @param time The time since the tick was last called.
     * @param window A reference to the render window which the state should be rendered on.
     * @return A shared pointer to the state to switch to, if nullptr no switch should be done.
     */
    virtual std::shared_ptr<State> tick(sf::Time time, sf::RenderWindow & window) = 0;

    /**
     * @brief Function to handle the rendering of the relevant elements of the current state.
     *
     * @param to A reference to the render window to render to.
     */
    virtual void render(sf::RenderWindow &to) = 0;

    /**
     * @brief Used to run a state. Used on application start.
     *
     * @param window A reference to the window which the state should be rendered on.
     * @param state A shared pointer to the state to run.
     */
    static void run(sf::RenderWindow &window, std::shared_ptr<State> state);

};

// ==============================[ Game State ]==============================
/**
 * @class Game_State
 * @brief A state representing the game simulation, inherits from the State class.
 *
 * When the user selects the "new game" option in the menu state,
 * it changes the state to an instance of a game_state, which simulates the game loop.
 */
class Game_State : public State
{
public:
    /**
     * @brief Constructor for the Game_State.
     */
    Game_State();

    /**
     * @brief Destructor for the Game_state.
     */
    ~Game_State() override = default;

    /**
     * @brief used to update the Game state each frame update.
     *
     * @param delta The time since the tick was last called.
     * @param window A reference to the render window which the state should be rendered on.
     * @return A shared pointer to the state to switch to, if nullptr no switch should be done.
     */
    std::shared_ptr<State> tick(sf::Time delta, sf::RenderWindow & window) override;

    /**
     * @brief Function to handle the rendering of the relevant elements of the current
     * game state.
     *
     * @param to A reference to the render window to render to.
     */
    void render(sf::RenderWindow &to) override;

private:
    /**
     * An instance of the game world.
     */
    World world{};

    /**
     * The time since the world was instantiated, in seconds.
     */
    float elapsed_time{};
};
// ==============================[ Menu State ]==============================

/**
 * @class Menu_State
 * @brief A state representing the main menu or the pause menu, inherits from the State class.
 *
 * The menu state is what appears when the game application is launched,
 * it can also be accessed by pausing the game when in the game state.
 */
class Menu_State : public State
{
public:
    /**
     * @brief The constructor for the Menu_State.
     *
     * @param resume which state to resume to if paused (if any).
     */
    Menu_State(std::shared_ptr<State> resume = nullptr);

    /**
     * @brief The destructor of the Menu state.
     */
    ~Menu_State() override = default;

    /**
     * @brief Called when the user presses a key, overrides the default behaviour.
     *
     * @param key The key which the user presses.
     */
    void on_key_press(sf::Keyboard::Key key) override;

    /**
     * @brief used to update the Game state each frame update.
     *
     * @param delta The time since the tick was last called.
     * @param window A reference to the render window which the state should be rendered on.
     * @return A shared pointer to the state to switch to, if nullptr no switch should be done.
     */
    std::shared_ptr<State> tick(sf::Time time, sf::RenderWindow &) override;

    /**
     * @brief Function to handle the rendering of the relevant elements of the current
     * menu state.
     *
     * @param to A reference to the render window to render to.
     */
    void render(sf::RenderWindow &drawTo) override;

private:
    using Action = std::function<std::shared_ptr<State>()>;

    /**
     * @struct Entry
     * @brief Represents a menu choice item.
     */
    struct Entry {
        /**
         * The text on the menu item.
         */
        sf::Text text;

        /**
         * The state that should be switched to if selected.
         */
        float state;

        /**
         * What happens when the state is selected.
         */
        Action action;
    };

    /**
     * The font used in the menu state.
     */
    sf::Font font{};

    /**
     * A list of all entries available in the current menu state.
     */
    std::vector<Entry> entries{};

    /**
     * Keeps track of the currently hovered entry.
     */
    size_t selected;

    /**
     * Determines if the enter key was pressed or not.
     */
    bool enter_pressed;

    /**
     * The delay used when switching entries.
     */
    sf::Time delay;

    /**
     * A shared pointer to the background state.
     */
    std::shared_ptr<State> background{};

    /**
     * @brief Function to add a new entry to entries.
     *
     * @param text The text that should be displayed on the entry.
     * @param action The action to be performed on selected.
     */
    void add(const std::string &text, Action action);
};

// ==============================[ Exit State ]==============================
/**
 * @class Exit_State
 * @brief Represents the state which is called when the game is to be exited, inherits from the State class.
 */
class Exit_State : public State
{
public:
    /**
     * @brief When tick is called in the exit state, end the state machine.
     * @return A nullptr.
     */
    std::shared_ptr<State> tick(sf::Time,sf::RenderWindow &) { return nullptr; }

    /**
     * @brief Does nothing.
     */
    void render(sf::RenderWindow &) {}
};

#endif

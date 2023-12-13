#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <memory>

class World;

/**
 * @class Game_Object
 * @brief Represents a generic game object.
 *
 * @details This class is associated with the World class for rendering and positioning.
 */
class Game_Object {
public:
    /**
     * @brief Constructor for the Game_Object class.
     * @param position The initial position of the game object.
     * @param sprite The texture for the game object's sprite.
     */
    Game_Object(sf::Vector2f const& position, sf::Texture const& sprite);

    /**
     * @brief Pure virtual destructor for the Game_Object class.
     */
    virtual ~Game_Object() = default;

    // Copy and move constructors and assignment operators are deleted to prevent unintended usage.
    Game_Object(Game_Object const& other_obj) = delete;
    Game_Object(Game_Object && other_obj) = delete;
    Game_Object& operator=(Game_Object const& other_obj) = delete;
    Game_Object& operator=(Game_Object && other_obj) = delete;

    /**
     * @brief Renders the game object on the provided render window.
     * @param window Reference to the SFML render window.
     */
    virtual void render(sf::RenderWindow & window);

    /**
     * @brief Retrieves the rectangle shape of the game object.
     * @return Reference to the SFML rectangle shape.
     */
    sf::RectangleShape& get_shape();

    /**
     * @brief Retrieves the position vector of the game object.
     * @return Reference to the SFML vector representing the position.
     */
    sf::Vector2f& get_position();

protected:
    /**
     * The rectangle shape representing the game object.
     */
    sf::RectangleShape shape{};

    /**
     * The position vector of the game object.
     */
    sf::Vector2f position{};

private:
    /**
     * The texture for the game object's sprite.
     */
    sf::Texture sprite;
};


#endif
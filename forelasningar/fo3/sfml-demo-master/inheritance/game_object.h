#pragma once
#include "common.h"

class World;

/**
 * A game object (abstract).
 */
class Game_Object {
public:
    /**
     * Create a game object.
     */
    Game_Object(sf::Vector2f center, float radius)
        : center{center}, radius{radius} {}

    /**
     * We need a virtual destructor.
     */
    virtual ~Game_Object() = default;

    /**
     * Position of the center of this object.
     */
    sf::Vector2f center;

    /**
     * Radius of this object.
     */
    float radius;

    /**
     * Update the object for each frame. Returns 'false' if the object wishes to
     * be removed.
     */
    virtual bool tick(sf::Time time, World &world) = 0;

    /**
     * Render the object.
     */
    virtual void render(sf::RenderWindow &window) = 0;
};


/**
 * A game object with a texture.
 */
class Textured_Object : public Game_Object {
public:
    /**
     * Create.
     */
    Textured_Object(sf::Vector2f center, const string &texture);

    /**
     * Render the object.
     */
    void render(sf::RenderWindow &window) override;

private:
    /**
     * Shape to render.
     */
    sf::RectangleShape shape;
};

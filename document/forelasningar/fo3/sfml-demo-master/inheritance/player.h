#pragma once
#include "game_object.h"

/**
 * Object representing the player.
 */
class Player : public Textured_Object {
public:
    /**
     * Create the player.
     */
    Player(sf::Vector2f position);

    /**
     * Update the player position.
     */
    bool tick(sf::Time delta, World &world) override;

    /**
     * Draw the player.
     */
    void render(sf::RenderWindow &to) override;

private:
    /**
     * Speed. Pixels/second.
     */
    float speed;

    /**
     * Shield shape.
     */
    sf::CircleShape shield;

    /**
     * How long should the shield be visible for?
     */
    sf::Time shield_visible;
};

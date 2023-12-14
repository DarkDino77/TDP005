#pragma once
#include "game_object.h"

/**
 * An enemy in the game.
 *
 * We only use this to be able to detect when the player is hit by an enemy
 * object. It does not do anything by itself.
 */
class Enemy : public Textured_Object {
public:
    Enemy(sf::Vector2f position, const string &texture)
        : Textured_Object(position, texture) {}
};


/**
 * This is an enemy that moves from the top somewhere and down through the
 * screen. It also spawns smaller bullets towards the player.
 */
class Spawner : public Enemy {
public:
    Spawner(float x, size_t lifetime);

    /**
     * Update the position of this enemy.
     */
    bool tick(sf::Time delta, World &world) override;

private:
    /**
     * Total time we have been alive.
     */
    sf::Time cumulated_time;

    /**
     * Total lifetime.
     */
    sf::Time lifetime;

    /**
     * Time left until spawn.
     */
    sf::Time until_spawn;

    /**
     * Original x position.
     */
    float x;
};


/**
 * This is an enemy that moves from a Spawner and then downwards to the edge of
 * the screen.
 */
class Bullet : public Enemy {
public:
    Bullet(sf::Vector2f position);

    /**
     * Update the position of this enemy.
     */
    bool tick(sf::Time delta, World &world) override;

private:
    /**
     * Speed.
     */
    float speed;

    /**
     * Direction we're aiming for.
     */
    sf::Vector2f direction;
};

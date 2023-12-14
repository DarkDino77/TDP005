#pragma once
#include "common.h"
#include "game_object.h"

/**
 * The game world. Contains a set of game objects.
 */
class World {
public:
    /**
     * Update all objects in the world.
     */
    void tick(sf::Time delta);

    /**
     * Render the world.
     */
    void render(sf::RenderWindow &to);

    /**
     * Add an object. This is safe to do while the world is updating itself.
     */
    void add(shared_ptr<Game_Object> object);

    /**
     * See if something collides with 'me'.
     */
    vector<shared_ptr<Game_Object>> collides_with(Game_Object &me) const;

private:
    /**
     * All game objects.
     */
    vector<shared_ptr<Game_Object>> objects;
};

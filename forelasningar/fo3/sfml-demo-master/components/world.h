#pragma once
#include "common.h"
#include "entity.h"

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
    void add(shared_ptr<Entity> object);

    /**
     * See if something collides with 'me'.
     */
    vector<shared_ptr<Entity>> collides_with(Entity &me) const;

private:
    /**
     * All game objects.
     */
    vector<shared_ptr<Entity>> objects;
};

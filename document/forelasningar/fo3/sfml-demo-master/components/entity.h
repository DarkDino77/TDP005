#pragma once
#include "common.h"
#include "tag.h"

class World;
class Component;

/**
 * An entity in the game world.
 */
class Entity {
public:
    /**
     * Create a game object.
     */
    Entity(sf::Vector2f center, float radius = 0.0f)
        : center{center}, radius{radius}, type{Tag::unknown} {}

    /**
     * Position of the center of this object.
     */
    sf::Vector2f center;

    /**
     * Radius of this object.
     */
    float radius;

    /**
     * Tag that indicates what kind of entity this is.
     */
    Tag type;

    /**
     * Update the object for each frame. Returns 'false' if the object wishes to
     * be removed.
     */
    bool tick(sf::Time time, World &world);

    /**
     * Render the object.
     */
    void render(sf::RenderWindow &window);

    /**
     * Add a component.
     */
    void add(shared_ptr<Component> c);

private:
    /**
     * All components of this entity.
     */
    vector<shared_ptr<Component>> components;
};

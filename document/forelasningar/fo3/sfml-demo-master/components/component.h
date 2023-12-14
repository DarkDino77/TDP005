#pragma once
#include "common.h"

class World;
class Entity;

/**
 * A part of an entity. It implements all of the behavior of the entity.
 */
class Component {
public:
    /**
     * We need a virtual destructor.
     */
    virtual ~Component() = default;

    /**
     * Called when this component is added to an entity.
     */
    virtual void added(Entity &to);

    /**
     * Update the object for each frame. Returns 'false' if the object wishes to
     * be removed.
     */
    virtual bool tick(sf::Time time, Entity &entity, World &world);

    /**
     * Render the object.
     */
    virtual void render(sf::RenderWindow &window, Entity &entity);
};

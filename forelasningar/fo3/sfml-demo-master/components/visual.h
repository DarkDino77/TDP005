#pragma once
#include "component.h"
#include "tag.h"

/**
 * This file contains a set of components that define how an entity looks.
 */


/**
 * Draw a textured element. Will modify "radius" when added to an Entity.
 */
class Textured : public Component {
public:
    /**
     * Create, give a particular texture.
     */
    Textured(const string &texture);

    /**
     * Update the radius.
     */
    void added(Entity &to) override;

    /**
     * Draw the texture.
     */
    void render(sf::RenderWindow &to, Entity &entity) override;

private:
    /**
     * The shape we want to draw.
     */
    sf::RectangleShape shape;
};


/**
 * An overlay that can be used to indicate collisions.
 */
class Shield : public Component {
public:
    /**
     * Create, indicate what we are interested in collisions with.
     */
    Shield(Tag for_type);

    /**
     * Update.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

    /**
     * Draw.
     */
    void render(sf::RenderWindow &to, Entity &entity) override;

private:
    /**
     * What to look out for.
     */
    Tag for_type;

    /**
     * Shape.
     */
    sf::CircleShape shield;

    /**
     * How long it is visible for.
     */
    sf::Time shield_visible;
};


/**
 * Draws particles around the entity.
 */
class Particles : public Component {
public:
    /**
     * Create, given:
     * - spawn - the number of particle to spawn each tick
     * - distance - the distance from the center of the entity that particles should spawn
     * - live - how long each particle should live for
     * - color - color of the particles
     */
    Particles(size_t spawn, float distance, sf::Time live, sf::Color color);

    /**
     * Update the particles.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

    /**
     * Draw the particles.
     */
    void render(sf::RenderWindow &to, Entity &entity) override;

private:
    /**
     * How many particles to spawn each tick.
     */
    size_t spawn;

    /**
     * Approximate distance from the center particles should spawn.
     */
    float distance;

    /**
     * Time each particle shall live.
     */
    sf::Time live;

    /**
     * Color of the particles.
     */
    sf::Color color;

    /**
     * Information about each particle.
     */
    struct Particle {
        /**
         * How far along its lifespan this particle is.
         */
        float life;

        /**
         * Original position.
         */
        sf::Vector2f pos;

        /**
         * Direction it is travelling in.
         */
        sf::Vector2f delta;
    };

    /**
     * All particles.
     */
    vector<Particle> particles;
};

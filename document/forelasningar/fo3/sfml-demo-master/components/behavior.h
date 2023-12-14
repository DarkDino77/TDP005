#include "component.h"
#include <functional>

/**
 * This file contains a set of components that define how an entity behaves.
 */


/**
 * Component that lets the player steer the component.
 */
class Player_Control : public Component {
public:
    /**
     * Create, and set the speed.
     */
    Player_Control(float speed);

    /**
     * Update the object.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

private:
    /**
     * The speed.
     */
    float speed;
};


/**
 * Component that removes the entity whenever it is outside of the screen.
 */
class Remove_Outside : public Component {
public:
    /**
     * Create, optionally with additional margins.
     */
    Remove_Outside(float margin = 0.0f)
        : margin{margin} {}

    /**
     * Update.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

private:
    /**
     * Additional margin.
     */
    float margin;
};


/**
 * Component that spawns other components regularly.
 */
class Spawn : public Component {
public:
    /**
     * Create, specify what to create and how often.
     */
    Spawn(sf::Time interval, std::function<shared_ptr<Entity>(Entity &)> create);

    /**
     * Update.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

private:
    /**
     * Function to create new entities.
     */
    std::function<shared_ptr<Entity>(Entity &)> create;

    /**
     * How often to spawn things.
     */
    sf::Time spawn_interval;

    /**
     * How much time left to the next spawn.
     */
    sf::Time remaining;
};


/**
 * Component that moves the entity in a sine-wave pattern from the top to the
 * bottom of the screen.
 */
class Sine_Movement : public Component {
public:
    /**
     * Create, specify initial x coordinate and desired duration.
     */
    Sine_Movement(float x, sf::Time duration);

    /**
     * Update.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

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
     * Original x position.
     */
    float x;
};


/**
 * Component that moves the entity in a straight line towards the bottom of the
 * screen.
 */
class Down_Movement : public Component {
public:
    /**
     * Create, specify speed.
     */
    Down_Movement(float speed) : speed{speed} {}

    /**
     * Update.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

private:
    /**
     * Speed.
     */
    float speed;
};


/**
 * Component that moves the entity in a straight line towards the bottom center
 * of the screen.
 */
class Down_Center_Movement : public Component {
public:
    /**
     * Create, specify speed.
     */
    Down_Center_Movement(float speed) : speed{speed} {}

    /**
     * Update.
     */
    bool tick(sf::Time time, Entity &entity, World &world) override;

private:
    /**
     * Speed.
     */
    float speed;
};

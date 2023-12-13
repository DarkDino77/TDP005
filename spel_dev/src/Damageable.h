#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

/**
 * @class Damageable
 * @brief Gives an object the ability to take damage.
 *
 * The Damageable class provides alla objects that should be able to take damage with
 * the necessary function. A damageable target has health.
 */
class Damageable {
public:
    /**
     * Destructor for Damageable class.
     */
    virtual ~Damageable() = default;

    /**
     * Function to take damage to the objects health.
     *
     * @param damage The amount of health points that is to be deducted from health.
     */
    void take_damage(int damage);

protected:
    /**
     * Constructor for the Damageable class.
     *
     * @param health The amount of health points that the damageable object has.
     */
    Damageable(int const health);

    /**
     * Amount of health points.
     */
    int health{};

    /**
     * Was the object hit.
     */
    bool hit{false};
};


#endif

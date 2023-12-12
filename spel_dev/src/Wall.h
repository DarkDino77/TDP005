#ifndef WALL_H
#define WALL_H
#include "Game_Object.h"

/**
 * @class Wall
 * @brief Represents a static wall in the world and inherits from the Game_Object class.
 *
 * The Wall class represents a static wall that movable targets can collide with.
 */
class Wall : public Game_Object
{
public:
    /**
     * @brief The constructor of the Wall object.
     *
     * @param position The initial position of the wall object.
     * @param sprite The sprite that is used to render the wall object.
     */
    Wall(sf::Vector2f const& position, sf::Texture const& sprite);

    /**
     * @brief The destructor for the wall object.
     */
    ~Wall() override = default;

};

#endif

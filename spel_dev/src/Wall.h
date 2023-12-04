#ifndef WALL_H
#define WALL_H
#include "Map_Object.h"

class Wall : public Map_Object
{
public:
    Wall(sf::Vector2f const& position, sf::Texture const& sprite);
};

#endif

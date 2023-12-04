#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "Game_Object.h"

class Map_Object : public Game_Object
{
public:
    Map_Object(sf::Vector2f const& position, sf::Texture const& sprite);
};


#endif

#ifndef WALL_H
#define WALL_H
#include "Game_Object.h"

class Wall : public Game_Object
{
public:
    Wall(sf::Vector2f const& position, sf::Texture const& sprite);
    ~Wall() override = default;

};

#endif

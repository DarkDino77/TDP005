
#ifndef UPDATABLE_H
#define UPDATABLE_H


#include "Game_Object.h"

class Updatable : public Game_Object{
public:
    Updatable(sf::Vector2f position, sf::Texture const& sprite);
    virtual ~Updatable() = default;
    virtual void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) = 0;
};


#endif

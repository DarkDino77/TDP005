#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character
{
public:
    Player(sf::Vector2f position, sf::Texture const& sprite, bool detect_collision);
private:
    int level{0};
    int level_progress{0};
};

#endif

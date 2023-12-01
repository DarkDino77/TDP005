#ifndef MELEE_H
#define MELEE_H

#include "Enemy.h"

class Melee : public Enemy
{
public:
    Melee(sf::Vector2f position, sf::Texture const& sprite, float speed);
    Melee();
    void update(sf::Time const& delta_time, World &world, sf::Window &window, std::shared_ptr<Game_Object> obj) override;
};


#endif //SPEL_DEV_MELEE_H

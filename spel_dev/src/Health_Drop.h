#ifndef HEALTH_DROP_H
#define HEALTH_DROP_H

#include "Pick_Up.h"

class Health_Drop: public Pick_Up{
public:
    Health_Drop(sf::Vector2f const& position, sf::Texture const& sprite);
protected:
    void pick_up(std::shared_ptr<Game_Object> const& other_obj) const override;

};


#endif

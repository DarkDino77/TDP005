#ifndef AMMO_H
#define AMMO_H


#include "Pick_Up.h"

class Ammo: public Pick_Up{
public:
    Ammo(sf::Vector2f const& position, sf::Texture const& sprite, std::string const& ammo_type);
protected:
    void pick_up(std::shared_ptr<Game_Object> const& other_obj) const override;
private:
    std::string const ammo_type{};
};


#endif

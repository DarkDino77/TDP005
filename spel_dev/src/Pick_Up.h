#ifndef PICK_UP_H
#define PICK_UP_H

#include "Collidable.h"
#include "Player.h"

class Pick_Up : public Collidable
{
public:
    Pick_Up(sf::Vector2f position, sf::Texture const& sprite);
    virtual ~Pick_Up() = default;
    void update(const sf::Time &, World &, const std::shared_ptr<Game_Object> &) override;
    void handle_collision(World &, const std::shared_ptr<Game_Object> &, const std::shared_ptr<Game_Object> &) override;

protected:
    virtual void pick_up(std::shared_ptr<Game_Object> const& other_obj) = 0;
    bool picked_up{false};
};


#endif

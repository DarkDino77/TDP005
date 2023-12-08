#ifndef PICK_UP_H
#define PICK_UP_H

#include "Collidable.h"
#include "Player.h"

class Pick_Up : public Collidable
{
public:
    Pick_Up(sf::Vector2f const& position, sf::Texture const& sprite);
    virtual ~Pick_Up() = default;
    void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) override;
    void handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const&) override;

protected:
    virtual void pick_up(std::shared_ptr<Game_Object> const& other_obj) const = 0;
    bool picked_up{false};
};


#endif

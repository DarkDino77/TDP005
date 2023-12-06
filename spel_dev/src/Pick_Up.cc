#include "Pick_Up.h"
#include "Player.h"

Pick_Up::Pick_Up(sf::Vector2f position, sf::Texture const& sprite)
: Collidable(position, sprite)
{}

void Pick_Up::update(const sf::Time & delta_time, World & world, const std::shared_ptr<Game_Object> & current_obj)
{
    if(picked_up)
    {
        world.kill(current_obj);
    }
}

void Pick_Up::handle_collision(World & world, const std::shared_ptr<Game_Object> & current_obj, const std::shared_ptr<Game_Object> & other_obj)
{
    std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(other_obj)};
    if(player_target != nullptr)
    {
        pick_up(other_obj);
        picked_up = true;
    }
}
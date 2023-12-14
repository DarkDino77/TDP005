#include <iostream>
#include "Pick_Up.h"
#include "Player.h"

Pick_Up::Pick_Up(sf::Vector2f const& position, sf::Texture const& sprite)
: Collidable(position, sprite)
{}

void Pick_Up::update(sf::Time const&, World & world, std::shared_ptr<Game_Object> const& current_obj)
{
    if(picked_up)
    {
        world.get_resource_manager().play_sound("ammo_pick_up");
        world.kill(current_obj);
    }
}

void Pick_Up::handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const& other_obj)
{
    std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(other_obj)};
    if(player_target != nullptr)
    {
        pick_up(other_obj);
        picked_up = true;
    }
}
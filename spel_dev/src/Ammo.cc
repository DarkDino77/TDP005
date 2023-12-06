#include "Ammo.h"

Ammo::Ammo(sf::Vector2f const& position, sf::Texture const& sprite, std::string const& ammo_type)
: Pick_Up(position, sprite), ammo_type{ammo_type}
{}

void Ammo::pick_up(std::shared_ptr<Game_Object> const& other_obj)
{
    std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(other_obj)};
    player_target->add_ammo(ammo_type, 20);
}
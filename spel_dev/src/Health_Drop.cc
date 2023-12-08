#include "Health_Drop.h"

Health_Drop::Health_Drop(sf::Vector2f const& position, sf::Texture const& sprite)
        : Pick_Up(position, sprite)
{}

void Health_Drop::pick_up(std::shared_ptr<Game_Object> const& other_obj) const
{
    std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(other_obj)};
    player_target->add_health(20);
}
#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "World.h"
#include "Weapon.h"

class Player : public Character
{
public:
    Player(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, World & world);
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;
    void handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;
    void add_ammo(std::string const& ammo_type, int const amount);
    void add_health(int const amount);
    void increase_max_health(int const amount);

private:
    int max_health{100};
};

#endif

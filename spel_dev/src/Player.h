#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "World.h"
#include "Weapon.h"

class Player : public Character
{
public:
    Player(sf::Vector2f position, sf::Texture const& sprite, float speed, int health, sf::Window const& window);
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;
    void handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;
    void add_ammo(std::string ammo_type, int amount);

private:
    sf::Window const& window;
    int max_health{100};
};

#endif

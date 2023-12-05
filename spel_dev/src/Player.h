#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "World.h"
#include "Weapon.h"

class Player : public Character
{
public:
    Player(sf::Vector2f position, sf::Texture const& sprite, float speed, int health, sf::Window const& window);
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> current_obj) override;
    void handle_collision(World & world, std::shared_ptr<Game_Object> current_obj, std::shared_ptr<Game_Object> other_obj) override;
    sf::Window const& window;
private:
    int level{0};
    int level_progress{0};
};

#endif

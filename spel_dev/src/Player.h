#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "World.h"
#include "Weapon.h"

class Player : public Character
{
private:
    sf::Vector2f find_direction();
public:
    Player(sf::Vector2f position, sf::Texture const& sprite, float speed);
    void update(sf::Time const& delta_time, World & world, sf::Window & window, std::shared_ptr<Game_Object> obj) override;
    //void handle_collision(World const& world) override;
private:
    float player_speed{1.0f};
    int level{0};
    int level_progress{0};

};

#endif

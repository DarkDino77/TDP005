#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "World.h"
#include "Weapon.h"
#include "Hud.h"

class Player : public Character
{
public:
    Player(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health, World & world);
    int get_level() const;
    float get_level_percent() const;
    float get_health_percent() const;
    std::shared_ptr<Weapon>& get_weapon_stats();
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;
    void handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;
    void add_ammo(std::string const& ammo_type, int const amount);
    void add_health(int const amount);
    void add_player_xp(int const xp, World & world);

private:
    int max_health{100};
    int player_level{0};
    int player_level_progression{0};
    int xp_to_level{20};
    float health_percent{100};
    float level_percent{0};

    void level_up_player(World & world);
    void add_player_weapon(World & world);
};

#endif

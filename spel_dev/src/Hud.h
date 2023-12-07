#ifndef HUD_H
#define HUD_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Weapon;

class World;

class Hud {
public:
    Hud() = default;
    void load_hud(World & world);
    void draw_hud(sf::RenderWindow & window);
    void set_level_percent(float percent);
    void set_health_percent(float health_percent);
    void set_player_level(int player_level);
    void set_weapon_stats(std::shared_ptr<Weapon> const& weapon);

private:
    int player_level{0};
    float level_percent{0};
    float health_percent{100};
    std::vector<std::shared_ptr<sf::RectangleShape>> hud_elements{};
    std::vector<std::shared_ptr<sf::Text>> hud_texts{};
};

#endif

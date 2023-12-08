#ifndef HUD_H
#define HUD_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Updatable.h"

class Weapon;
class World;

class Hud : public Updatable
{
public:
    Hud(sf::Vector2f const& position, sf::Texture const& sprite, World & world);
    void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) override;
    void load_hud(World & world);
    void render(sf::RenderWindow & window) override;

private:
    int player_level{0};
    float level_percent{0};
    float health_percent{100};
    std::vector<std::shared_ptr<sf::RectangleShape>> hud_elements{};
    std::vector<std::shared_ptr<sf::Text>> hud_texts{};
};

#endif

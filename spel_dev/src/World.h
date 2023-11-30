#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class Game_Object;

class World
{
public:
    std::map<std::string, std::shared_ptr<sf::Texture>> sprites;
    void add_texture(std::string name, std::string filename);

    void add_wall(sf::Vector2f position);
    void add_crate(sf::Vector2f position);
    void add_barrel(sf::Vector2f position);
    void add_player(sf::Vector2f position);
    std::vector<std::shared_ptr<Game_Object>> game_objects{};
private:
    float sprite_scale{2.0f};
};
#endif
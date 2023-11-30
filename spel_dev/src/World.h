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
    std::map<std::string, std::shared_ptr<sf::Texture>> sprites; //TODO: Determine if public
    std::vector<std::shared_ptr<Game_Object>> game_objects{}; //TODO: Determine if public
    void add_texture(std::string name, std::string filename);

    void add_game_object(std::string const& name, sf::Vector2f position);
    void add_player(sf::Vector2f position);

    //std::shared_ptr<Player> get_player();


private:
    float sprite_scale{2.0f};
    //std::shared_ptr<Player> player{nullptr};
};
#endif
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game_Object;
class Player;

class World
{
public:
    std::map<std::string, std::shared_ptr<sf::Texture>> sprites{}; //TODO: Determine if public
    std::vector<std::shared_ptr<Game_Object>> game_objects{}; //TODO: Determine if public
    std::vector<std::shared_ptr<Game_Object>> kill_queue{};
    std::shared_ptr<Player> get_player();
    bool debug_mode{false};


    void add_texture(const std::string& name, const std::string& filename);
    void add_game_object(std::string const& name, sf::Vector2f const& position);
    void add_player(sf::Vector2f const& position, sf::Window const& window);
    void add_melee_enemy(std::string const& name, sf::Vector2f const& position);
    void add_ranged_enemy(std::string const& name, sf::Vector2f const& position);
    void spawn_monsters();
    void load_level_file(std::string const& filename, sf::Window const& window);

private:
    std::shared_ptr<Player> player{nullptr};
};
#endif
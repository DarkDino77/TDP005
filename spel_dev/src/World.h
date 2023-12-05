#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"

class Game_Object;
class Player;

class World
{
public:
    std::map<std::string, std::shared_ptr<sf::Texture>> sprites{}; //TODO: Determine if public
    std::map<std::string, std::vector<std::shared_ptr<sf::SoundBuffer>>> sound_buffers{};
    std::vector<std::shared_ptr<Game_Object>> game_objects{}; //TODO: Determine if public and if unique_ptr
    std::vector<std::shared_ptr<Game_Object>> kill_queue{};
    std::vector<std::shared_ptr<Game_Object>> add_queue{};
    std::shared_ptr<Player> get_player();
    bool debug_mode{false};

    void add_texture(std::string const& name,  std::string const& filename);
    void add_sound(std::string const& name,  std::string const& filename);
    void play_sound(std::string const& name);
    void add_game_object(std::string const& name, sf::Vector2f const& position);
    void add_player(sf::Vector2f const& position, sf::Window const& window);
    void add_melee_enemy(std::string const& name, sf::Vector2f const& position);
    void add_ranged_enemy(std::string const& name, sf::Vector2f const& position);
    void add_explosion(std::string const& name, sf::Vector2f const& position);
    void spawn_monsters();
    void load_level_file(std::string const& filename, sf::Window const& window);
    bool can_see_player(std::shared_ptr<Game_Object> source, sf::Vector2f direction);


private:
    std::shared_ptr<Player> player{nullptr};
    std::vector<std::shared_ptr<sf::Sound>> sound_queue{};
};
#endif
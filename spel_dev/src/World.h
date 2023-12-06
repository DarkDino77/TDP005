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
    // Getters
    std::shared_ptr<Player> get_player();

    //Setter
    void kill(std::shared_ptr<Game_Object> const& obj_to_kill);
    void set_health_percent(int health);
    void set_level_percent(int level_progress);
    void add_player_xp(int xp);

    void add_texture(std::string const& name,  std::string const& filename);
    void add_sound(std::string const& name,  std::string const& filename);
    void play_sound(std::string const& name);
    void add_player(sf::Vector2f const& position, sf::Window const& window);
    void add_melee_enemy(std::string const& name, sf::Vector2f const& position);
    void add_ranged_enemy(std::string const& name, sf::Vector2f const& position);
    void add_wall(sf::Vector2f const& position);
    void add_explosive_barrel(sf::Vector2f const& position);
    void add_crate(sf::Vector2f const& position);
    void add_explosion(std::string const& name, sf::Vector2f const& position);
    void add_bullet(int damage, sf::Vector2f const& direction, double bullet_speed, std::string const& ammo_type,
                    sf::Vector2f & bullet_spawn, std::shared_ptr<Game_Object> const& source);
    void spawn_monsters();
    void load_level_file(std::string const& filename, sf::Window const& window);
    bool can_see_player(std::shared_ptr<Game_Object> source, sf::Vector2f direction);
    void simulate();

private:
    std::vector<std::shared_ptr<Game_Object>> game_objects{}; //TODO: Determine if public and if unique_ptr
    std::shared_ptr<Player> player{nullptr};
    std::vector<std::shared_ptr<sf::Sound>> sound_queue{};
    int current_wave{1};
    bool sound_on{false};
    sf::RenderWindow window{sf::VideoMode{1920, 1024}, "The Grand Arena"};
    sf::Font font{};
    sf::Texture background_texture{};
    sf::Sprite background_sprite{};
    sf::Texture mouse_cursor_texture{};
    sf::RectangleShape mouse_cursor{};

    std::map<std::string, std::shared_ptr<sf::Texture>> sprites{};
    std::map<std::string, std::vector<std::shared_ptr<sf::SoundBuffer>>> sound_buffers{};
    std::vector<std::shared_ptr<Game_Object>> add_queue{};
    std::vector<std::shared_ptr<Game_Object>> kill_queue{};
    std::vector<std::shared_ptr<sf::RectangleShape>> hud_elements{};
    float health_percent{100};
    float level_percent{0};
    bool debug_mode{false};
    int player_level{0};
    int player_level_progression{0};
    int xp_to_level{20};

    void level_up_player();
    void make_window();
    void load_font();
    void load_background();
    void load_cursor();
    void load_textures();
    void load_audio();
    void load_hud();
    void check_collision(std::shared_ptr<Game_Object> const& current_obj);
    void update_game_objects(sf::Time const& delta_time);
    void draw_game_objects();
    void add_game_objects();
    bool delete_game_objects();
    void draw_hud();
};
#endif
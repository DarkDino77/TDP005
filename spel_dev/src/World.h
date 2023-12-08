#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Hud.h"

class Game_Object;
class Player;

class World
{
public:
    // Getters
    std::shared_ptr<Player> get_player();
    sf::Texture& get_sprite(std::string const& category);
    sf::Font& get_font();
    int get_level();
    float get_level_percent();
    float get_health_percent();
    std::shared_ptr<Weapon> get_weapon_stats();
    sf::Vector2f get_mouse_pos();


    //Setter
    void kill(std::shared_ptr<Game_Object> const& obj_to_kill);
    void set_health_percent(int health, int max_health);
    void set_weapon_stats(std::shared_ptr<Weapon> weapon);
    void add_player_xp(int xp);

    void add_texture(std::string const& category,  std::string const& filename);
    void add_sound(std::string const& name,  std::string const& filename);
    void play_sound(std::string const& name);
    void add_player(sf::Vector2f const& position);
    void add_melee_enemy(std::string const& name, sf::Vector2f const& position);
    void add_ranged_enemy(std::string const& name, sf::Vector2f const& position);
    void add_wall(sf::Vector2f const& position);
    void add_explosive_barrel(sf::Vector2f const& position);
    void add_crate(sf::Vector2f const& position);
    void add_explosion(sf::Vector2f const& position, float const explosive_radius, int explosive_damage);
    void add_pick_up(sf::Vector2f const& position);
    void add_bullet(int damage, sf::Vector2f const& direction, double bullet_speed, std::string const& bullet_type,
                    sf::Vector2f & bullet_spawn, std::shared_ptr<Game_Object> const& source);
    void spawn_monsters();
    void load_level_file(std::string const& filename);
    bool can_see_player(std::shared_ptr<Game_Object> source, sf::Vector2f direction);
    void load();
    bool simulate(sf::Time const& delta_time, float const elapsed_time, sf::RenderWindow &window);
    void render(sf::RenderWindow &window);

private:
    std::vector<std::shared_ptr<Game_Object>> game_objects{}; //TODO: Determine if public and if unique_ptr
    std::vector<std::string> available_pick_ups{};
    std::shared_ptr<Player> player{nullptr};
    std::vector<std::shared_ptr<sf::Sound>> sound_queue{};
    int current_wave{1};
    sf::Font font{};
    sf::Texture background_texture{};
    sf::Sprite background_sprite{};
    sf::Texture mouse_cursor_texture{};
    sf::RectangleShape mouse_cursor{};
    sf::Vector2f mouse_pos{};


    std::map<std::string, std::vector<std::shared_ptr<sf::Texture>>> sprites{};
    std::map<std::string, std::vector<std::shared_ptr<sf::SoundBuffer>>> sound_buffers{};
    std::map<std::string, std::vector<std::shared_ptr<sf::Sound>>> sounds{};
    std::vector<std::shared_ptr<Game_Object>> add_queue{};
    std::vector<std::shared_ptr<Game_Object>> kill_queue{};
    std::vector<std::shared_ptr<sf::RectangleShape>> hud_elements{};
    std::vector<std::shared_ptr<sf::Text>> hud_texts{};

    float time_since_spawn{0};
    float last_time{0};
    sf::Text fps_text;
    float health_percent{100};
    float level_percent{0};
    std::shared_ptr<Weapon> weapon_stats{};
    bool debug_mode{false};
    int player_level{0};
    int player_level_progression{0};
    int xp_to_level{20};
    std::shared_ptr<Hud> hud{};

    void add_player_weapon();
    void level_up_player();
    void load_font();
    void load_background();
    void load_cursor();
    void load_textures();
    void load_audio();
    void check_collision(std::shared_ptr<Game_Object> const& current_obj);
    void update_game_objects(sf::Time const& delta_time);
    void draw_game_objects(sf::RenderWindow & window);
    void add_game_objects();
    bool delete_game_objects();
};
#endif
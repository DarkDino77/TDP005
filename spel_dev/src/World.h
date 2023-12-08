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
    // ==============================[ Getters ]==============================
    std::shared_ptr<Player>& get_player();
    sf::Texture& get_sprite(std::string const& category);
    sf::Font& get_font();
    int get_level() const;
    float get_level_percent() const;
    float get_health_percent() const;
    std::shared_ptr<Weapon>& get_weapon_stats();
    sf::Vector2f& get_mouse_pos();

    // ==============================[ Setters ]==============================
    void kill(std::shared_ptr<Game_Object> const& obj_to_kill);
    void set_health_percent(int health, int max_health);
    void set_weapon_stats(std::shared_ptr<Weapon> weapon);
    void add_player_xp(int xp);

    // ==============================[ Creation ]==============================
    void add_explosion(sf::Vector2f const& position, float explosive_radius, int explosive_damage);
    void add_pick_up(sf::Vector2f const& position);
    void add_bullet(int damage, sf::Vector2f const& direction, double bullet_speed, std::string const& bullet_type,
                    sf::Vector2f & bullet_spawn, std::shared_ptr<Game_Object> const& source);

    // ==============================[ Misc ]==============================
    bool can_see_player(std::shared_ptr<Game_Object> source, sf::Vector2f direction);
    void play_sound(std::string const& name);

    // ==============================[ Game Loop ]==============================
    bool simulate(sf::Time const& delta_time, float elapsed_time, sf::RenderWindow &window);
    void render(sf::RenderWindow &window);

private:
    // ===[ Containers ]===
    std::vector<std::shared_ptr<Game_Object>> game_objects{}; //TODO: Determine if public and if unique_ptr
    std::vector<std::string> available_pick_ups{};
    std::vector<std::shared_ptr<sf::Sound>> sound_queue{};
    std::map<std::string, std::vector<std::shared_ptr<sf::Texture>>> sprites{};
    std::map<std::string, std::vector<std::shared_ptr<sf::SoundBuffer>>> sound_buffers{};
    std::map<std::string, std::vector<std::shared_ptr<sf::Sound>>> sounds{};
    std::vector<std::shared_ptr<Game_Object>> add_queue{};
    std::vector<std::shared_ptr<Game_Object>> kill_queue{};
    std::vector<std::shared_ptr<sf::RectangleShape>> hud_elements{};
    std::vector<std::shared_ptr<sf::Text>> hud_texts{};

    // ===[ Player ]===
    std::shared_ptr<Player> player{nullptr};
    int player_level{0};
    int player_level_progression{0};
    int xp_to_level{20};
    float health_percent{100};
    float level_percent{0};
    std::shared_ptr<Weapon> weapon_stats{};

    // ===[ Waves ]===
    int current_wave{1};
    float time_since_spawn{0};
    float last_time{0};

    // ===[ Graphics ]===
    sf::Font font{};
    sf::Texture background_texture{};
    sf::Sprite background_sprite{};
    sf::Texture mouse_cursor_texture{};
    sf::RectangleShape mouse_cursor{};
    sf::Vector2f mouse_pos{};

    // ===[ Hud ]===
    std::shared_ptr<Hud> hud{};
    sf::Text fps_text;

    // ===[ Debug ]===
    bool debug_mode{false};


    // ==============================[ Load ]==============================
    void load_level_file(std::string const& filename);
    void load();
    void load_font();
    void load_background();
    void load_cursor();
    void load_textures();
    void load_audio();

    // ==============================[ Creation ]==============================
    void add_texture(std::string const& category,  std::string const& filename);
    void add_sound(std::string const& name,  std::string const& filename);
    void add_player(sf::Vector2f const& position);
    void add_melee_enemy(std::string const& name, sf::Vector2f const& position);
    void add_ranged_enemy(std::string const& name, sf::Vector2f const& position);
    void add_wall(sf::Vector2f const& position);
    void add_explosive_barrel(sf::Vector2f const& position);
    void add_crate(sf::Vector2f const& position);
    void spawn_monsters();
    void add_game_objects();
    bool delete_game_objects();

    // ==============================[ Game Loop ]==============================
    void add_player_weapon();
    void level_up_player();
    void check_collision(std::shared_ptr<Game_Object> const& current_obj);
    void update_game_objects(sf::Time const& delta_time);
    void draw_game_objects(sf::RenderWindow & window);
};
#endif